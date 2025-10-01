#include <Adafruit_NeoPixel.h>

#define PIN         6
#define WIDTH       55          
#define HEIGHT      9         
#define NUM_LEDS    (WIDTH * HEIGHT)

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

int barHeights[WIDTH];         
unsigned long lastUpdate = 0;
unsigned long lastPulse = 0;
bool animar = false;
int modoAtual = 0;  // 0 = parado, 1 = barras, 2 = onda, 3 = arco-íris
int ondaX = 0;
int rainbowOffset = 0;

// ================= Funções auxiliares =================

int getPixelIndex(int x, int y) {
  if (x % 2 == 0) {
    return x * HEIGHT + y;
  } else {
    return x * HEIGHT + (HEIGHT - 1 - y);
  }
}

uint32_t getColorForHeight(int y) {
  if (y < HEIGHT * 0.33) return strip.Color(0, 0, 255);        
  if (y < HEIGHT * 0.66) return strip.Color(0, 255, 255);      
  return strip.Color(255, 0, 0);                               
}

// Função para gerar cores do arco-íris
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// ================= Setup =================
void setup() {
  strip.begin();
  strip.show();
  Serial.begin(9600);
  randomSeed(analogRead(0));

  for (int i = 0; i < WIDTH; i++) {
    barHeights[i] = 0;
  }
}

// ================= Loop =================
void loop() {
  unsigned long now = millis();

  // Verifica comando serial
  if (Serial.available() > 0) {
    char recebido = Serial.read();
    if (recebido == 'G' || recebido == 'g') {
      animar = true;
      modoAtual = 1; // barras
    } 
    else if (recebido == 'O' || recebido == 'o') {
      animar = true;
      modoAtual = 3; // onda horizontal
    }
    else if (recebido == 'T' || recebido == 't') {
      animar = true;
      modoAtual = 2; // arco-íris
    }
    else if (recebido == 'P' || recebido == 'p') {
      animar = false;
      modoAtual = 0; // parar tudo
      strip.clear();
      strip.show();
    }
  }

  if (animar) {
    if (modoAtual == 1) {
      // ======= Modo 1: Barras verticais =======
      if (now - lastPulse > 200) {
        lastPulse = now;
        for (int i = 0; i < WIDTH; i++) {
          int novaAltura = random(10, HEIGHT);
          if (novaAltura > barHeights[i]) {
            barHeights[i] = novaAltura;
          }
        }
      }

      if (now - lastUpdate > 30) {
        lastUpdate = now;
        for (int x = 0; x < WIDTH; x++) {
          for (int y = 0; y < HEIGHT; y++) {
            int index = getPixelIndex(x, HEIGHT - 1 - y);
            if (y < barHeights[x]) {
              strip.setPixelColor(index, getColorForHeight(y));
            } else {
              strip.setPixelColor(index, 0);
            }
          }
          if (barHeights[x] > 0) {
            barHeights[x]--;
          }
        }
        strip.show();
      }
    } 
    else if (modoAtual == 2) {
      // ======= Modo 2: Onda azul =======
      if (now - lastUpdate > 20) {
        lastUpdate = now;
        int verde_random = random(0, 70);
        int vermelho_random = random(0, 70);
        int azul_random = random(0, 70);

        // Fundo azul escuro
        for (int x = 0; x < WIDTH; x++) {
          for (int y = 0; y < HEIGHT; y++) {
            int index = getPixelIndex(x, y);
            strip.setPixelColor(index, strip.Color(verde_random, vermelho_random, azul_random));
          }
        }

  int verde_onda = random(0, 20);
  int vermelho_onda = random(0, 255);
  int azul_onda = random(0, 20);

  for (int x = 0; x < WIDTH; x++) {
    float wave = sin((x + ondaX) * 0.2);
    int y = map(wave * 100, -100, 100, 0, HEIGHT - 1);
    int index = getPixelIndex(x, y);
    strip.setPixelColor(index, strip.Color(verde_onda, vermelho_onda, azul_onda));
  }

        ondaX = (ondaX + 1) % WIDTH;
        strip.show();
      }
    }
    else if (modoAtual == 3) {
      // ======= Modo 3: Arco-íris rodando =======
      if (now - lastUpdate > 40) {
        lastUpdate = now;

        for (int x = 0; x < WIDTH; x++) {
          for (int y = 0; y < HEIGHT; y++) {
            int index = getPixelIndex(x, y);
            byte colorIndex = (x * 5 + y * 10 + rainbowOffset) & 255;
            strip.setPixelColor(index, Wheel(colorIndex));
          }
        }

        rainbowOffset = (rainbowOffset + 2) & 255;
        strip.show();
      }
    }
  }
}