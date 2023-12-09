#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <TFT.h>




SoftwareSerial bluetoothSerial(0, 1);  //pinos bluetooth
#define botao 2                        // Pino do botão
#define red 4                          // Pino do LED RGB (cor vermelha)
#define green 5                        // Pino do LED RGB (cor verde)
#define blue 12                        // Pino do LED RGB (cor azul)
#define speakerPin 7                   //pino piezo
#define dc 8
#define rst 9
#define cs 10
#define ring 6
#define numpixels 24
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numpixels, ring, NEO_GRB + NEO_KHZ800);

TFT tft = TFT(cs, dc, rst);
int estadoBotaoAnterior = LOW;     // Estado anterior do botão
unsigned long tempoDebounce = 50;  // Tempo de debounce em milissegundos


int xpos = 0;

void setup() {

  Serial.begin(9600);
  tft.begin();
  tft.background(255, 255, 255);
  tft.setTextSize(5);
  tft.stroke(0,0,0);
  tft.text("RMD", 35, 45);
  pinMode(botao, INPUT);
  pixels.begin();
  pixels.setBrightness(5);
  bluetoothSerial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  pixels.setPixelColor(1, pixels.Color(255, 0, 0));
  pixels.setPixelColor(2, pixels.Color(0, 0, 255));
  pixels.setPixelColor(3, pixels.Color(255, 0, 0));
  pixels.setPixelColor(4, pixels.Color(0, 0, 255));
  pixels.setPixelColor(5, pixels.Color(255, 0, 0));
  pixels.setPixelColor(6, pixels.Color(0, 0, 255));
  pixels.setPixelColor(7, pixels.Color(255, 0, 0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 255));
  pixels.setPixelColor(9, pixels.Color(255, 0, 0));
  pixels.setPixelColor(10, pixels.Color(0, 0, 255));
  pixels.setPixelColor(11, pixels.Color(0, 0, 255));
  pixels.setPixelColor(12, pixels.Color(0, 255, 0));
  pixels.setPixelColor(13, pixels.Color(0, 0, 255));
  pixels.setPixelColor(14, pixels.Color(255, 0, 0));
  pixels.setPixelColor(15, pixels.Color(0, 0, 255));
  pixels.setPixelColor(16, pixels.Color(255, 0, 0));
  pixels.setPixelColor(17, pixels.Color(0, 0, 255));
  pixels.setPixelColor(18, pixels.Color(255, 0, 0));
  pixels.setPixelColor(19, pixels.Color(255, 0, 0));
  pixels.setPixelColor(20, pixels.Color(0, 0, 255));
  pixels.setPixelColor(21, pixels.Color(255, 0, 0));
  pixels.setPixelColor(22, pixels.Color(0, 0, 255));
  pixels.setPixelColor(23, pixels.Color(255, 0, 0));  // Vai de 0 a 255;
  pixels.show();
  randomSeed(analogRead(0));  // Inicia os pixeis no off
}

void loop() {

  int estadoBotao = digitalRead(botao);
  // Verificar se o estado do botão mudou
  if (estadoBotao != estadoBotaoAnterior) {
    delay(tempoDebounce);              // Debounce para evitar leituras falsas
    estadoBotao = digitalRead(botao);  // Ler novamente após o debounce

    if (estadoBotao == HIGH) {
      // Se o botão for pressionado
      pixels.clear();
      int valorI = wave(100);
      char a = char(valorI);
      tft.background(255, 255, 255);
      tft.setTextSize(2);
      tft.stroke(255, 255, 255);  
      Serial.println(String(valorI));
      
      String corDescricao = obterDescricaoCor(valorI);

     
      String nparidade = paridade(valorI);
     
       bluetoothSerial.write(a);

      if (corDescricao == "Azul") {
        tft.background(255, 0, 0);
        setColor(0, 0, 255);
        tft.text(corDescricao.c_str(), 60, 55);
      }
      if (corDescricao == "Vermelho") {
        tft.background(0, 0, 255);
        setColor(255, 0, 0);
        tft.text(corDescricao.c_str(), 35, 55);
      } else if (corDescricao == "Verde") {
        tft.background(0, 255, 0);
        setColor(0, 255, 0);
        soundverde();

        tft.text(corDescricao.c_str(), 50, 55);
      }

      if (nparidade == "Par") {
        tft.text(nparidade.c_str(), 65, 75);
      } else {
        tft.text(nparidade.c_str(), 50, 75);
      }

      if(valorI<10){
      tft.text(String(valorI).c_str(), 75, 35);
      }
      else{
      tft.text(String(valorI).c_str(), 70, 35);
      }

    }

    estadoBotaoAnterior = estadoBotao; 
  }
}

int wave(int wait) {

  bool continuar = true;
  int numeroAleatorio = random(23);
  for (int i = 0; i < pixels.numPixels() * (3) + 1; i++) {
    pixels.clear();  
    // Calcula a posição do pixel aceso
    int pixelAceso = i % pixels.numPixels();

    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
    pixels.setPixelColor(1, pixels.Color(255, 0, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 255));
    pixels.setPixelColor(3, pixels.Color(255, 0, 0));
    pixels.setPixelColor(4, pixels.Color(0, 0, 255));
    pixels.setPixelColor(5, pixels.Color(255, 0, 0));
    pixels.setPixelColor(6, pixels.Color(0, 0, 255));
    pixels.setPixelColor(7, pixels.Color(255, 0, 0));
    pixels.setPixelColor(8, pixels.Color(0, 0, 255));
    pixels.setPixelColor(9, pixels.Color(255, 0, 0));
    pixels.setPixelColor(10, pixels.Color(0, 0, 255));
    pixels.setPixelColor(11, pixels.Color(0, 0, 255));
    pixels.setPixelColor(12, pixels.Color(0, 255, 0));
    pixels.setPixelColor(13, pixels.Color(0, 0, 255));
    pixels.setPixelColor(14, pixels.Color(255, 0, 0));
    pixels.setPixelColor(15, pixels.Color(0, 0, 255));
    pixels.setPixelColor(16, pixels.Color(255, 0, 0));
    pixels.setPixelColor(17, pixels.Color(0, 0, 255));
    pixels.setPixelColor(18, pixels.Color(255, 0, 0));
    pixels.setPixelColor(19, pixels.Color(255, 0, 0));
    pixels.setPixelColor(20, pixels.Color(0, 0, 255));
    pixels.setPixelColor(21, pixels.Color(255, 0, 0));
    pixels.setPixelColor(22, pixels.Color(0, 0, 255));
    pixels.setPixelColor(23, pixels.Color(255, 0, 0));

    pixels.setPixelColor(pixelAceso, pixels.Color(255, 255, 255));
    pixels.show();
    delay(wait);
    if (i >= 2 * pixels.numPixels() && pixelAceso == numeroAleatorio) {

      delay(1000);
      pixels.clear();

      if (pixelAceso == 0 || pixelAceso == 12) {
        // Pixels 0 e 12 são verde

        pixels.setPixelColor(pixelAceso, pixels.Color(0, 255, 0));  // verde
        pixels.show();
      } else if (pixelAceso == 1 || pixelAceso == 3 || pixelAceso == 5 || pixelAceso == 7 || pixelAceso == 9 || pixelAceso == 14 || pixelAceso == 16 || pixelAceso == 18 || pixelAceso == 19 || pixelAceso == 21 || pixelAceso == 23) {

        pixels.setPixelColor(pixelAceso, pixels.Color(255, 0, 0));  // vermelho
      } else {
      
        pixels.setPixelColor(pixelAceso, pixels.Color(0, 0, 255));  // Azul
      }
      pixels.show();

      return i - 48;
      break;
    }
    continuar = false;
  }
}
String obterDescricaoCor(int numero) {
  String descricao;

  if (numero == 0 || numero == 12) {
    descricao = "Verde";
  } else if (numero == 1 || numero == 3 || numero == 5 || numero == 7 || numero == 9 || numero == 14 || numero == 16 || numero == 18 || numero == 19 || numero == 21 || numero == 23) {
    descricao = "Vermelho";
  } else {
    descricao = "Azul";
  }

  return descricao;
}

String paridade(int num) {
  String paridade;
  if (num % 2 == 0) {
    paridade = "Par";
  } else {
    paridade = "Impar";
  }
  return paridade;
}

// Função para definir a cor do LED RGB
void setColor(int cred, int cgreen, int cblue) {
  analogWrite(red, cred);
  analogWrite(green, cgreen);
  analogWrite(blue, cblue);
}

void playTone(int tone, int duration) {  //tone piezo
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playBellSound() {  // sino vitoria do piezo
  int tones[] = { 1500, 1800, 2100, 2400, 2100, 1800, 1500 };
  int durations[] = { 150, 120, 100, 80, 100, 120, 150 };

  for (int i = 0; i < 7; i++) {
    playTone(tones[i], durations[i]);
    delay(20);  
  }
}

void soundverde() {
  unsigned long startTime = millis();  
  unsigned long interval = 500;        
  while (millis() - startTime < 5000) {  
    playBellSound(); 
  }
}
