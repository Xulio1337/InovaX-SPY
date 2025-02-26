#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  
#define OLED_RESET    -1  
#define SENSOR_PIN A0  // Pino onde o sensor de umidade de solo está conectado

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);  // Definir pino do sensor como entrada

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Inicializa o display com o endereço 0x3C
    Serial.println(F("Falha na inicialização do display OLED!"));
    for (;;);  // Trava o código aqui em caso de falha
  }

  display.clearDisplay();  // Limpa o display
}

void loop() {
  int sensorValue = analogRead(SENSOR_PIN);  // Lê o valor do sensor de umidade
  int umidade = map(sensorValue, 0, 1023, 0, 100);  // Mapeia o valor para uma porcentagem

  display.clearDisplay();  // Limpa o display para atualizar com as novas informações
  
  // Exibe a porcentagem de umidade na parte superior
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Umidade: ");
  display.print(umidade);
  display.print("%");

  // Exibe o rostinho com base no nível de umidade
  display.setTextSize(2);
  display.setCursor(40, 30);  // Posição do rostinho na tela

  if (umidade > 80) {
    display.print(":O");  // Rostinho desesperado
  } else if (umidade >= 40) {
    display.print(":)");  // Rostinho feliz
  } else if (umidade >= 10) {
    display.print(":(");  // Rostinho triste
  } else {
    display.print("X_X");  // Rostinho com "X" nos olhos
  }

  display.display();  // Atualiza o display com as informações
  delay(2000);  // Aguarda 2 segundos antes de ler novamente
}
