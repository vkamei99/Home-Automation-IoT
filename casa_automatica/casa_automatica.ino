#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHTesp.h>

// Definições de pinos
#define TRIG_PIN 5  
#define ECHO_PIN 18 
#define LED_PIN 27
#define LDR_PIN 2
#define DHT_PIN 15
#define motorPin 23
#define minDistance 0     // Distancia minima para controlar o motor
#define maxDistance 100   // Distancia maxima para controlar o motor
#define LCD_ADDRESS 0x27  // Definições do endereço I2C do LCD (0x27)
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Configuração do Wi-Fi
const char* ssid = "####";
const char* password = "####";

// Página HTML
const char index_html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
    <head>
      <title>Trabalho 2 de Embarcados</title>
      <style>
      html, body {
        font-family: Arial, Helvetica, sans-serif;
        text-align: center;
      }
      h1 {
        font-size: 1.8rem;
        color: black;
      }
      button {
        border: none;
        color: black;
        padding: 15px 32px;
        text-align: center;
        font-size: 16px;
        width: 150px;
        border-radius: 4px;
      }
      </style>
    </head>
    <body>
      <div>
        <h1>Dashboard</h1>
        <h2>Dados dos Sensores:</h2>
      </div>
    </body>
  </html>
 )rawliteral";

// Inicializa as bibliotecas
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
DHTesp dht;
AsyncWebServer server(80);

// Variáveis globais para armazenar os dados dos sensores e para controle manual
float temperature = 0.0;
float humidity = 0.0;
long distance = 0;
int ldrValue = 0;
bool manualControl = false;
bool ledState = false;
int motorSpeed = 0;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Conectando WiFi");
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    lcd.setCursor(0, 1);
    lcd.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void initSensors() {
  pinMode(TRIG_PIN, OUTPUT);// Configurações do ultrassônico
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);// Configurações do LED
  pinMode(LDR_PIN, INPUT);
  pinMode(motorPin, OUTPUT);// Configurações do motor
  dht.setup(DHT_PIN, DHTesp::DHT11);// Inicializa o sensor DHT
}

void initServer() {
  // Configura o servidor web para servir os dados e controlar LED e motor
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = index_html;
    html += "<p><strong>Distancia: </strong>" + String(distance) + " cm</p>";
    html += "<p><strong>Temperatura: </strong>" + String(temperature) + " *C</p>";
    html += "<p><strong>Umidade: </strong>" + String(humidity) + " %</p>";
    html += "<p><strong>Valor do LDR: </strong>" + String(ldrValue) + "</p>";
    html += "<h2>Controles</h2>";
    html += "<p><a href=\"/toggle_control\"><button>PID = " + String(manualControl ? "OFF" : "ON") + "</button></a></p>";
    html += "<p><a href=\"/toggle_led\"><button> LED </button></a></p>";
    html += "<p><strong>Velocidade do Motor: </strong>" + String(motorSpeed) + "</p>";
    html += "<p><a href=\"/increase_motor\"><button>Aumentar</button></a> <a href=\"/decrease_motor\"><button>Diminuir</button></a></p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/toggle_control", HTTP_GET, [](AsyncWebServerRequest *request){
    manualControl = !manualControl;
    request->redirect("/");
  });

  server.on("/toggle_led", HTTP_GET, [](AsyncWebServerRequest *request){
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    request->redirect("/");
  });

  server.on("/increase_motor", HTTP_GET, [](AsyncWebServerRequest *request){
    if (manualControl) {
      motorSpeed = min(255, motorSpeed + 10);
      analogWrite(motorPin, motorSpeed);
    }
    request->redirect("/");
  });

  server.on("/decrease_motor", HTTP_GET, [](AsyncWebServerRequest *request){
    if (manualControl) {
      motorSpeed = max(0, motorSpeed - 10);
      analogWrite(motorPin, motorSpeed);
    }
    request->redirect("/");
  });

  server.begin();
}

void setup() {
  Serial.begin(115200);
  lcd.init();  // Inicializa o display LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
  initWiFi();
  initSensors();
  initServer();
}

void loop() {
  if (!manualControl) {
    long duration;
    // Gera um pulso no pino TRIG
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    duration = pulseIn(ECHO_PIN, HIGH); // Lê o tempo de duração do pulso no pino ECHO
    distance = (duration / 2) / 29.1;   // Calcula a distância (em centímetros)

    int dutyCycle;
    if (distance <= maxDistance) {
      dutyCycle = map(distance, minDistance, maxDistance, 0, 255);// Mapeia a distância para o valor do duty cycle de 8 bits
    } else {
      dutyCycle = 255;
    }

    // Controla a velocidade do motor
    analogWrite(motorPin, dutyCycle);
    Serial.print("Distância: ");
    Serial.print(distance);
    Serial.print(" cm, Velocidade: ");
    Serial.println(dutyCycle);
    //motorSpeed = dutyCycle;

    // Leitura do valor do LDR
    ldrValue = analogRead(LDR_PIN);
    Serial.print("LDR: ");
    Serial.println(ldrValue);  
    if (ldrValue < 1000) { 
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }

    // Leitura de temperatura e umidade
    TempAndHumidity data = dht.getTempAndHumidity();
    // Verifica se a leitura foi bem-sucedida
    if (dht.getStatus() != 0) {     
      Serial.println("Falha ao ler do sensor DHT");
      lcd.setCursor(0, 0);
      lcd.print("Erro no DHT   ");
      return;
    }
    // Atualiza as variáveis globais com os dados lidos
    temperature = data.temperature;
    humidity = data.humidity;

    // Exibe a temperatura e umidade no display LCD
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" *C  ");

    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(humidity);
    lcd.print(" %   ");
  }

  delay(2000);
}