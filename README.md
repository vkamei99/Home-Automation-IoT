<h1 style="text-align: center;">Projeto: Casa Inteligente</h1>
<p style="text-align: center;">Trabalho realizado para a disciplina de Sistemas Embarcados I</p>

**Objetivo:** Criar um sistema automatizado para monitorar e controlar a iluminação e a temperatura de um ambiente utilizando o ESP32.

## Visão Geral do Projeto

Este projeto envolve a implementação de um sistema de automação residencial utilizando o ESP32, sensores de luz, distância, umidade e temperatura, além de atuadores como motor CC e LED. A interface gráfica foi desenvolvida tanto localmente, utilizando um display LCD, quanto remotamente, através de uma aplicação web.

## Sensores

### LDR
O sensor LDR detecta a intensidade da luz ambiente. A leitura do sinal analógico recebido do sensor foi utilizada para controlar a iluminação.

### Ultrassônico
Utilizando um sensor ultrassônico, foi gerado um pulso cuja duração permite calcular a distância até um objeto.

### DHT11
Para a leitura de dados de umidade e temperatura, foi utilizada a biblioteca [DHTesp](https://github.com/beegee-tokyo/DHTesp).

## Atuadores / Controle

### LED
O LED foi controlado com base na intensidade da luz medida pelo sensor LDR.

### Motor CC
A velocidade do motor CC foi ajustada utilizando PWM, controlado pela distância medida pelo sensor ultrassônico. Quanto maior a distância, maior a velocidade do motor, e vice-versa.

### PWM
**O que é PWM?**
PWM (Pulse Width Modulation), ou Modulação por Largura de Pulso, é uma técnica que envolve a variação da largura dos pulsos em um sinal elétrico. Em outras palavras, o PWM pulsa rapidamente um sinal digital, transmitindo informações pela variação da largura dos pulsos. Mais detalhes podem ser encontrados [aqui](https://blog.smartkits.com.br/pwm-como-usar/#:~:text=PWM%20(Pulse%20Width%20Modulation)%2C,da%20largura%20de%20uma%20onda).

## Interface Gráfica

### Local - Display LCD
Utilizando um módulo i²C para o display LCD, reduzimos a quantidade de cabos e facilitamos a montagem. O display está configurado para mostrar os dados do sensor DHT11.

### Remota - Aplicação Web
Foi desenvolvida uma aplicação web utilizando a biblioteca [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer), permitindo a visualização dos dados e o controle manual dos atuadores através de uma página HTML.

## Instalação

### Pré-requisitos
- ESP32
- Sensores (LDR, Ultrassônico, DHT11)
- Atuadores (LED, Motor CC)
- Display LCD com módulo i²C
- Arduino IDE instalada no seu computador
- Bibliotecas necessárias: `DHTesp`, `ESPAsyncWebServer`

### Passos para Instalação

1. **Clone o repositório:**

   ```bash
   git clone https://github.com/vkamei99/Home-Automation-IoT.git
   cd Home-Automation-IoT
   ```

2. **Instale as bibliotecas necessárias na Arduino IDE:**
   - Baixe as bibliotecas [`DHTesp`](https://github.com/beegee-tokyo/DHTesp) e [`ESPAsyncWebServer`](https://github.com/me-no-dev/ESPAsyncWebServer).
   - Abra a Arduino IDE.
   - Vá em **Sketch** > **Incluir Biblioteca** > **Add .ZIP Library...**.
   - Adicione as bibliotecas baixadas

3. **Configure o ESP32:**
   - Conecte o ESP32 ao seu computador.
   - Carregue o código do repositório para o ESP32.
   - Certifique-se de que os pinos estão conectados corretamente conforme indicado no código.

4. **Configure a interface web:**
   - Certifique-se de que o ESP32 está conectado à mesma rede que o seu computador.
   - Abra o navegador e acesse o endereço IP fornecido pelo ESP32 para acessar a interface web.

5. **Montagem do hardware:**
   [esquema](img/esquema.jpg)

## Testagem e Prototipagem
Para garantir um ambiente de testes seguro e estável, foi desenvolvido um protótipo do circuito no TinkerCad. O esquemático pode ser visualizado através deste [link](https://www.tinkercad.com/things/almQPwROdbh-trab-embarcados?sharecode=HNUUGkxfbwIo7BN9pCX_iZ20gPJYtISwEIajwCkqmyk).
