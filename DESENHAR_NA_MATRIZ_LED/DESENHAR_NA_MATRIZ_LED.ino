#include <Adafruit_NeoPixel.h>

#define ALTURA 15
#define LARGURA 22
#define NUM_LEDS (ALTURA * LARGURA)
#define DATA_PIN 23   // pino do Arduino/ESP32 onde a fita está conectada

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_RGB + NEO_KHZ800);

int getIndex(int x, int y) {
  if (x % 2 == 0) {
    return x * ALTURA + y;           // coluna par (sobe)
  } else {
    return x * ALTURA + (ALTURA - 1 - y); // coluna ímpar (desce)
  }
}

// ========================================
// Função set_pixel (x,y,r,g,b)
// ========================================
void set_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  if (x < 0 || x >= LARGURA || y < 0 || y >= ALTURA) return;
  int i = getIndex(x, y);
  strip.setPixelColor(i, strip.Color(r, g, b));
}



void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show();  // inicializa todos apagados
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String linha = Serial.readStringUntil('\n');
    int x, y, r, g, b;

    // Lê no formato "x,y,R,G,B"
    if (sscanf(linha.c_str(), "%d,%d,%d,%d,%d", &x, &y, &r, &g, &b) == 5) {
      int idx = getIndex(x, y);
      if (idx >= 0 && idx < NUM_LEDS) {
        strip.setPixelColor(idx, strip.Color(r, g, b));
        strip.show();
      }
    }
  }
}
