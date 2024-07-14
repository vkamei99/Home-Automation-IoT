#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definições de pinos do sensor ultrassônico e do LED
#define TRIG_PIN 5  // Pino TRIG do sensor conectado ao GPIO 5 do ESP32
#define ECHO_PIN 18 // Pino ECHO do sensor conectado ao GPIO 18 do ESP32
#define LED_PIN 27

// Definição do endereço I2C do LCD (0x27)
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

// Inicializa o display LCD
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial
  pinMode(TRIG_PIN, OUTPUT); // Configura o pino TRIG como saída
  pinMode(ECHO_PIN, INPUT);  // Configura o pino ECHO como entrada
  pinMode(LED_PIN, OUTPUT);

  // Inicializa o display LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distancia:");
}

void loop() {
  long duration, distance;

  // Gera um pulso no pino TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Lê o tempo de duração do pulso no pino ECHO
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calcula a distância (em centímetros)
  distance = (duration / 2) / 29.1;

  if (distance <= 20) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Led aceso");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Led apagado");
  }

  // Exibe a distância no monitor serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Exibe a distância no display LCD
  lcd.setCursor(0, 1);
  lcd.print("                "); // Limpa a linha
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm");

  delay(1000); // Aguarda um segundo antes de fazer a próxima leitura
}
