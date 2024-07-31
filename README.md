# Projeto: “Casa Inteligente”
<p style="text-align: center;">Trabalho feito para a Disciplina de Sistemas Embarcados I </p>

**Objetivo:** Criar um sistema automatizado para monitorar e controlar a iluminação e a temperatura de um ambiente utilizando o ESP32.

## Visão Geral do Projeto:

**Sensores:**
Foi usado os sensores Ultrassonico, LDR e o de Umidade e Temperatura

**Atuadores/Controle:**
A partir dos dados dos sensores foi controlado os atuadores: Motor CC com PWM e Led

**Interface Gráfica:**
Foi feita uma interface gráfica Local usando display LCD e Remota por meio de aplicações web

## Sensores:
### Ldr
Detecta a intensidade da luz ambiente. Foi feita a leitura do sinal analogico recebido do sensor.

### Ultrassonico
Foi gerado um Pulso e apartir da duração desse pulso foi calculado a distancia.

### DHT 11
Para a leitura de dados desse sensor foi usada a Biblioteca <a href= "https://github.com/beegee-tokyo/DHTesp" target = "blank"> DHTesp </a>

## Atuadores / Controle
### LED
O controle do LED foi feito a partir da intensidade da luz medida pelo LDR

### Motor CC
A velocidade do motor foi atenuada a partir de um **PWM** que foi controlado a partir do sensor ultrassonico (quanto mais longe mais rapido mais perto mais devagar)

### PWM
**O que é PWM?**
PWM (Pulse Width Modulation), ou Modulação por Largura de Pulso, é uma técnica que envolve a variação da largura dos pulsos em um sinal elétrico.

Em outras palavras, o PWM pulsa rapidamente um sinal digital em um condutor, transmitindo uma informação pela variação da largura de uma onda. Isso significa que, em vez de manter um sinal em níveis constantes, a largura dos pulsos é alterada.
<a href= "https://blog.smartkits.com.br/pwm-como-usar/#:~:text=PWM%20(Pulse%20Width%20Modulation)%2C,da%20largura%20de%20uma%20onda." target = "blank"> Explicação completa </a>

## Interface Gráfica:

### Local - Display LCD
No display LCD usamos o modulo i²C para diminuir a quantidade de cabos e facilitar a montagem. O display esta configurado para mostrar os dados do sensor DHT11

### Remota - Aplicação Web
Foi feita uma aplicação remota a partir da biblioteca <a href= "https://github.com/me-no-dev/ESPAsyncWebServer" target = "blank"> ESPAsyncWebServer </a> onde foi possivel configurar uma pagina HTML onde podemos ver os dados e ainda controlar os atuadores manualmente

## Testagem e Prototipagem
Para criar um abiente de testes seguro e estavel foi desenvolvido um prototipo do circuito no TinkerCad voce pode ver o esquematico acessando esse <a href= "https://www.tinkercad.com/things/almQPwROdbh-trab-embarcados?sharecode=HNUUGkxfbwIo7BN9pCX_iZ20gPJYtISwEIajwCkqmyk" target = "blank">link</a>
