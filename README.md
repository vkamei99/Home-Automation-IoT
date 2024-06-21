# Home-Automation-IoT
Projeto de automação residencial utilizando IoT (Internet of Things), com controle de iluminação e ventilação baseado em sensores de luz, movimento e temperatura, integrado a interfaces gráficas locais e remotas.

```mermaid
    graph TD
    ESP32["Microcontrolador ESP32"]
    RemoteInterface["Interface Remota (Aplicação Web - Grafana)"]
    LCDInterface["Tela LCD (Interface Local)"]
    Sensors["Sensores"]
    Actuators["Atuadores"]
    LightSensor["Sensor de Luz (LDR)"]
    UltrasonicSensor["Sensor Ultrassônico"]
    Lamp["Lâmpada (Relé)"]
    Fan["Ventilador DC"]

    ESP32 -- "WiFi" --> RemoteInterface
    ESP32 -- "WiFi" --> LCDInterface
    ESP32 -- "GPIO" --> Sensors
    ESP32 -- "PWM" --> Actuators
    Sensors --> LightSensor
    Sensors --> UltrasonicSensor
    Actuators --> Lamp
    Actuators --> Fan

    ESP32 -- "Processamento dos sinais" --> Sensors
    Sensors -- "Ajuste automático" --> Actuators
    Actuators -- "Operação" --> ESP32
    LCDInterface -- "Exibe dados" --> Sensors
    LCDInterface -- "Exibe status" --> Actuators
```