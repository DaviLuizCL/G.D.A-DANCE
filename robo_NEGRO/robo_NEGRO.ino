#include <MihuCore.h>

#include "BluetoothSerial.h"
#include <Adafruit_NeoPixel.h>
#define ALTURA 15
#define LARGURA 22
#define NUM_LEDS (ALTURA * LARGURA)
#define DATA_PIN 23

Adafruit_NeoPixel strip(NUM_LEDS, DATA_PIN, NEO_RGB + NEO_KHZ800);

String device_name = "ESP32-NEGRO";

int braco_esq = S3;
int ombro_esq = S1;
int girar_esq = S2;

int braco_dir = S6;
int ombro_dir = S4;
int girar_dir = S5;

int pino_prox = 27;
int prox;

//ENTRADA DE MNOTOR M1 N PEGA

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial blu;

String recebido = "";

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

void gravata() {
  set_pixel(0, 0, 0, 128, 255);
  set_pixel(1, 0, 0, 128, 255);
  set_pixel(2, 0, 0, 128, 255);
  set_pixel(3, 0, 0, 128, 255);
  set_pixel(4, 0, 0, 128, 255);
  set_pixel(5, 0, 0, 128, 255);
  set_pixel(6, 0, 0, 128, 255);
  set_pixel(7, 0, 0, 128, 255);
  set_pixel(8, 0, 0, 128, 255);
  set_pixel(9, 0, 0, 128, 255);
  set_pixel(10, 0, 0, 128, 255);
  set_pixel(11, 0, 0, 128, 255);
  set_pixel(12, 0, 0, 128, 255);
  set_pixel(13, 0, 0, 128, 255);
  set_pixel(14, 0, 0, 128, 255);
  set_pixel(15, 0, 0, 128, 255);
  set_pixel(16, 0, 0, 128, 255);
  set_pixel(17, 0, 0, 128, 255);
  set_pixel(18, 0, 0, 128, 255);
  set_pixel(19, 0, 0, 128, 255);
  set_pixel(20, 0, 0, 128, 255);
  set_pixel(21, 0, 0, 128, 255);
  set_pixel(0, 1, 0, 128, 255);
  set_pixel(1, 1, 0, 128, 255);
  set_pixel(2, 1, 0, 128, 255);
  set_pixel(3, 1, 0, 128, 255);
  set_pixel(4, 1, 0, 128, 255);
  set_pixel(5, 1, 0, 128, 255);
  set_pixel(6, 1, 0, 128, 255);
  set_pixel(7, 1, 0, 128, 255);
  set_pixel(8, 1, 0, 128, 255);
  set_pixel(9, 1, 0, 128, 255);
  set_pixel(10, 1, 0, 128, 255);
  set_pixel(11, 1, 0, 128, 255);
  set_pixel(12, 1, 0, 128, 255);
  set_pixel(13, 1, 0, 128, 255);
  set_pixel(14, 1, 0, 128, 255);
  set_pixel(15, 1, 0, 128, 255);
  set_pixel(16, 1, 0, 128, 255);
  set_pixel(17, 1, 0, 128, 255);
  set_pixel(18, 1, 0, 128, 255);
  set_pixel(19, 1, 0, 128, 255);
  set_pixel(20, 1, 0, 128, 255);
  set_pixel(21, 1, 0, 128, 255);
  set_pixel(0, 2, 0, 128, 255);
  set_pixel(1, 2, 0, 128, 255);
  set_pixel(2, 2, 0, 128, 255);
  set_pixel(3, 2, 0, 128, 255);
  set_pixel(4, 2, 0, 128, 255);
  set_pixel(5, 2, 0, 128, 255);
  set_pixel(6, 2, 0, 128, 255);
  set_pixel(7, 2, 0, 128, 255);
  set_pixel(8, 2, 0, 128, 255);
  set_pixel(9, 2, 0, 128, 255);
  set_pixel(10, 2, 0, 128, 255);
  set_pixel(11, 2, 0, 255, 0);
  set_pixel(12, 2, 0, 128, 255);
  set_pixel(13, 2, 0, 128, 255);
  set_pixel(14, 2, 0, 128, 255);
  set_pixel(15, 2, 0, 128, 255);
  set_pixel(16, 2, 0, 128, 255);
  set_pixel(17, 2, 0, 128, 255);
  set_pixel(18, 2, 0, 128, 255);
  set_pixel(19, 2, 0, 128, 255);
  set_pixel(20, 2, 0, 128, 255);
  set_pixel(21, 2, 0, 128, 255);
  set_pixel(0, 3, 0, 128, 255);
  set_pixel(1, 3, 0, 128, 255);
  set_pixel(2, 3, 0, 128, 255);
  set_pixel(3, 3, 0, 128, 255);
  set_pixel(4, 3, 0, 128, 255);
  set_pixel(5, 3, 0, 128, 255);
  set_pixel(6, 3, 0, 128, 255);
  set_pixel(7, 3, 0, 128, 255);
  set_pixel(8, 3, 0, 128, 255);
  set_pixel(9, 3, 0, 128, 255);
  set_pixel(10, 3, 0, 255, 0);
  set_pixel(11, 3, 0, 255, 0);
  set_pixel(12, 3, 0, 255, 0);
  set_pixel(13, 3, 0, 128, 255);
  set_pixel(14, 3, 0, 128, 255);
  set_pixel(15, 3, 0, 128, 255);
  set_pixel(16, 3, 0, 128, 255);
  set_pixel(17, 3, 0, 128, 255);
  set_pixel(18, 3, 0, 128, 255);
  set_pixel(19, 3, 0, 128, 255);
  set_pixel(20, 3, 0, 128, 255);
  set_pixel(21, 3, 0, 128, 255);
  set_pixel(0, 4, 0, 128, 255);
  set_pixel(1, 4, 0, 128, 255);
  set_pixel(2, 4, 0, 128, 255);
  set_pixel(3, 4, 0, 128, 255);
  set_pixel(4, 4, 0, 128, 255);
  set_pixel(5, 4, 0, 128, 255);
  set_pixel(6, 4, 0, 128, 255);
  set_pixel(7, 4, 0, 128, 255);
  set_pixel(8, 4, 0, 128, 255);
  set_pixel(9, 4, 0, 128, 255);
  set_pixel(10, 4, 0, 255, 0);
  set_pixel(11, 4, 0, 255, 0);
  set_pixel(12, 4, 0, 255, 0);
  set_pixel(13, 4, 0, 128, 255);
  set_pixel(14, 4, 0, 128, 255);
  set_pixel(15, 4, 0, 128, 255);
  set_pixel(16, 4, 0, 128, 255);
  set_pixel(17, 4, 0, 128, 255);
  set_pixel(18, 4, 0, 128, 255);
  set_pixel(19, 4, 0, 128, 255);
  set_pixel(20, 4, 0, 128, 255);
  set_pixel(21, 4, 0, 128, 255);
  set_pixel(0, 5, 0, 128, 255);
  set_pixel(1, 5, 0, 128, 255);
  set_pixel(2, 5, 0, 128, 255);
  set_pixel(3, 5, 0, 128, 255);
  set_pixel(4, 5, 0, 128, 255);
  set_pixel(5, 5, 0, 128, 255);
  set_pixel(6, 5, 0, 128, 255);
  set_pixel(7, 5, 0, 128, 255);
  set_pixel(8, 5, 0, 128, 255);
  set_pixel(9, 5, 0, 128, 255);
  set_pixel(10, 5, 0, 255, 0);
  set_pixel(11, 5, 0, 255, 0);
  set_pixel(12, 5, 0, 255, 0);
  set_pixel(13, 5, 0, 128, 255);
  set_pixel(14, 5, 0, 128, 255);
  set_pixel(15, 5, 0, 128, 255);
  set_pixel(16, 5, 0, 128, 255);
  set_pixel(17, 5, 0, 128, 255);
  set_pixel(18, 5, 0, 128, 255);
  set_pixel(19, 5, 0, 128, 255);
  set_pixel(20, 5, 0, 128, 255);
  set_pixel(21, 5, 0, 128, 255);
  set_pixel(0, 6, 0, 128, 255);
  set_pixel(1, 6, 0, 128, 255);
  set_pixel(2, 6, 0, 128, 255);
  set_pixel(3, 6, 0, 128, 255);
  set_pixel(4, 6, 0, 128, 255);
  set_pixel(5, 6, 0, 128, 255);
  set_pixel(6, 6, 0, 128, 255);
  set_pixel(7, 6, 0, 128, 255);
  set_pixel(8, 6, 0, 128, 255);
  set_pixel(9, 6, 0, 128, 255);
  set_pixel(10, 6, 0, 255, 0);
  set_pixel(11, 6, 0, 255, 0);
  set_pixel(12, 6, 0, 255, 0);
  set_pixel(13, 6, 0, 128, 255);
  set_pixel(14, 6, 0, 128, 255);
  set_pixel(15, 6, 0, 128, 255);
  set_pixel(16, 6, 0, 128, 255);
  set_pixel(17, 6, 0, 128, 255);
  set_pixel(18, 6, 0, 128, 255);
  set_pixel(19, 6, 0, 128, 255);
  set_pixel(20, 6, 0, 128, 255);
  set_pixel(21, 6, 0, 128, 255);
  set_pixel(0, 7, 0, 128, 255);
  set_pixel(1, 7, 0, 128, 255);
  set_pixel(2, 7, 0, 128, 255);
  set_pixel(3, 7, 0, 128, 255);
  set_pixel(4, 7, 0, 128, 255);
  set_pixel(5, 7, 0, 128, 255);
  set_pixel(6, 7, 0, 128, 255);
  set_pixel(7, 7, 0, 128, 255);
  set_pixel(8, 7, 0, 128, 255);
  set_pixel(9, 7, 0, 128, 255);
  set_pixel(10, 7, 0, 255, 0);
  set_pixel(11, 7, 0, 255, 0);
  set_pixel(12, 7, 0, 255, 0);
  set_pixel(13, 7, 0, 128, 255);
  set_pixel(14, 7, 0, 128, 255);
  set_pixel(15, 7, 0, 128, 255);
  set_pixel(16, 7, 0, 128, 255);
  set_pixel(17, 7, 0, 128, 255);
  set_pixel(18, 7, 0, 128, 255);
  set_pixel(19, 7, 0, 128, 255);
  set_pixel(20, 7, 0, 128, 255);
  set_pixel(21, 7, 0, 128, 255);
  set_pixel(0, 8, 0, 128, 255);
  set_pixel(1, 8, 0, 128, 255);
  set_pixel(2, 8, 0, 128, 255);
  set_pixel(3, 8, 0, 128, 255);
  set_pixel(4, 8, 0, 128, 255);
  set_pixel(5, 8, 0, 128, 255);
  set_pixel(6, 8, 0, 128, 255);
  set_pixel(7, 8, 0, 128, 255);
  set_pixel(8, 8, 0, 128, 255);
  set_pixel(9, 8, 0, 128, 255);
  set_pixel(10, 8, 0, 255, 0);
  set_pixel(11, 8, 0, 255, 0);
  set_pixel(12, 8, 0, 255, 0);
  set_pixel(13, 8, 0, 128, 255);
  set_pixel(14, 8, 0, 128, 255);
  set_pixel(15, 8, 0, 128, 255);
  set_pixel(16, 8, 0, 128, 255);
  set_pixel(17, 8, 0, 128, 255);
  set_pixel(18, 8, 0, 128, 255);
  set_pixel(19, 8, 0, 128, 255);
  set_pixel(20, 8, 0, 128, 255);
  set_pixel(21, 8, 0, 128, 255);
  set_pixel(0, 9, 0, 128, 255);
  set_pixel(1, 9, 0, 128, 255);
  set_pixel(2, 9, 0, 128, 255);
  set_pixel(3, 9, 0, 128, 255);
  set_pixel(4, 9, 0, 128, 255);
  set_pixel(5, 9, 0, 128, 255);
  set_pixel(6, 9, 0, 128, 255);
  set_pixel(7, 9, 0, 128, 255);
  set_pixel(8, 9, 0, 128, 255);
  set_pixel(9, 9, 0, 128, 255);
  set_pixel(10, 9, 0, 255, 0);
  set_pixel(11, 9, 0, 255, 0);
  set_pixel(12, 9, 0, 255, 0);
  set_pixel(13, 9, 0, 128, 255);
  set_pixel(14, 9, 0, 128, 255);
  set_pixel(15, 9, 0, 128, 255);
  set_pixel(16, 9, 0, 128, 255);
  set_pixel(17, 9, 0, 128, 255);
  set_pixel(18, 9, 0, 128, 255);
  set_pixel(19, 9, 0, 128, 255);
  set_pixel(20, 9, 0, 128, 255);
  set_pixel(21, 9, 0, 128, 255);
  set_pixel(0, 10, 0, 128, 255);
  set_pixel(1, 10, 0, 128, 255);
  set_pixel(2, 10, 0, 128, 255);
  set_pixel(3, 10, 0, 128, 255);
  set_pixel(4, 10, 0, 128, 255);
  set_pixel(5, 10, 0, 128, 255);
  set_pixel(6, 10, 0, 128, 255);
  set_pixel(7, 10, 0, 128, 255);
  set_pixel(8, 10, 0, 128, 255);
  set_pixel(9, 10, 0, 128, 255);
  set_pixel(10, 10, 0, 255, 0);
  set_pixel(11, 10, 0, 255, 0);
  set_pixel(12, 10, 0, 255, 0);
  set_pixel(13, 10, 0, 128, 255);
  set_pixel(14, 10, 0, 128, 255);
  set_pixel(15, 10, 0, 128, 255);
  set_pixel(16, 10, 0, 128, 255);
  set_pixel(17, 10, 0, 128, 255);
  set_pixel(18, 10, 0, 128, 255);
  set_pixel(19, 10, 0, 128, 255);
  set_pixel(20, 10, 0, 128, 255);
  set_pixel(21, 10, 0, 128, 255);
  set_pixel(0, 11, 0, 128, 255);
  set_pixel(1, 11, 0, 128, 255);
  set_pixel(2, 11, 0, 128, 255);
  set_pixel(3, 11, 0, 128, 255);
  set_pixel(4, 11, 0, 128, 255);
  set_pixel(5, 11, 0, 128, 255);
  set_pixel(6, 11, 0, 128, 255);
  set_pixel(7, 11, 0, 128, 255);
  set_pixel(8, 11, 0, 128, 255);
  set_pixel(9, 11, 0, 128, 255);
  set_pixel(10, 11, 0, 255, 0);
  set_pixel(11, 11, 0, 255, 0);
  set_pixel(12, 11, 0, 255, 0);
  set_pixel(13, 11, 0, 128, 255);
  set_pixel(14, 11, 0, 128, 255);
  set_pixel(15, 11, 0, 128, 255);
  set_pixel(16, 11, 0, 128, 255);
  set_pixel(17, 11, 0, 128, 255);
  set_pixel(18, 11, 0, 128, 255);
  set_pixel(19, 11, 0, 128, 255);
  set_pixel(20, 11, 0, 128, 255);
  set_pixel(21, 11, 0, 128, 255);
  set_pixel(0, 12, 0, 128, 255);
  set_pixel(1, 12, 0, 128, 255);
  set_pixel(2, 12, 0, 128, 255);
  set_pixel(3, 12, 0, 128, 255);
  set_pixel(4, 12, 0, 128, 255);
  set_pixel(5, 12, 0, 128, 255);
  set_pixel(6, 12, 0, 128, 255);
  set_pixel(7, 12, 0, 128, 255);
  set_pixel(8, 12, 0, 128, 255);
  set_pixel(9, 12, 0, 128, 255);
  set_pixel(10, 12, 0, 255, 0);
  set_pixel(11, 12, 0, 255, 0);
  set_pixel(12, 12, 0, 255, 0);
  set_pixel(13, 12, 0, 128, 255);
  set_pixel(14, 12, 0, 128, 255);
  set_pixel(15, 12, 0, 128, 255);
  set_pixel(16, 12, 0, 128, 255);
  set_pixel(17, 12, 0, 128, 255);
  set_pixel(18, 12, 0, 128, 255);
  set_pixel(19, 12, 0, 128, 255);
  set_pixel(20, 12, 0, 128, 255);
  set_pixel(21, 12, 0, 128, 255);
  set_pixel(0, 13, 0, 128, 255);
  set_pixel(1, 13, 0, 128, 255);
  set_pixel(2, 13, 0, 128, 255);
  set_pixel(3, 13, 0, 128, 255);
  set_pixel(4, 13, 0, 128, 255);
  set_pixel(5, 13, 0, 128, 255);
  set_pixel(6, 13, 0, 128, 255);
  set_pixel(7, 13, 0, 128, 255);
  set_pixel(8, 13, 0, 128, 255);
  set_pixel(9, 13, 0, 128, 255);
  set_pixel(10, 13, 0, 128, 255);
  set_pixel(11, 13, 0, 255, 0);
  set_pixel(12, 13, 0, 128, 255);
  set_pixel(13, 13, 0, 128, 255);
  set_pixel(14, 13, 0, 128, 255);
  set_pixel(15, 13, 0, 128, 255);
  set_pixel(16, 13, 0, 128, 255);
  set_pixel(17, 13, 0, 128, 255);
  set_pixel(18, 13, 0, 128, 255);
  set_pixel(19, 13, 0, 128, 255);
  set_pixel(20, 13, 0, 128, 255);
  set_pixel(21, 13, 0, 128, 255);
  set_pixel(0, 14, 0, 128, 255);
  set_pixel(1, 14, 0, 128, 255);
  set_pixel(2, 14, 0, 128, 255);
  set_pixel(3, 14, 0, 128, 255);
  set_pixel(4, 14, 0, 128, 255);
  set_pixel(5, 14, 0, 128, 255);
  set_pixel(6, 14, 0, 128, 255);
  set_pixel(7, 14, 0, 128, 255);
  set_pixel(8, 14, 0, 255, 64);
  set_pixel(9, 14, 0, 255, 64);
  set_pixel(10, 14, 0, 255, 0);
  set_pixel(11, 14, 0, 255, 0);
  set_pixel(12, 14, 0, 255, 0);
  set_pixel(13, 14, 0, 255, 64);
  set_pixel(14, 14, 0, 255, 64);
  set_pixel(15, 14, 0, 128, 255);
  set_pixel(16, 14, 0, 128, 255);
  set_pixel(17, 14, 0, 128, 255);
  set_pixel(18, 14, 0, 128, 255);
  set_pixel(19, 14, 0, 128, 255);
  set_pixel(20, 14, 0, 128, 255);
  set_pixel(21, 14, 0, 128, 255);

  strip.show();
}

void olodum() {
  set_pixel(0, 0, 255, 255, 255);
  set_pixel(1, 0, 255, 255, 255);
  set_pixel(2, 0, 255, 255, 255);
  set_pixel(3, 0, 255, 255, 255);
  set_pixel(4, 0, 255, 255, 255);
  set_pixel(5, 0, 255, 255, 255);
  set_pixel(6, 0, 255, 255, 255);
  set_pixel(7, 0, 255, 255, 255);
  set_pixel(8, 0, 255, 255, 255);
  set_pixel(9, 0, 255, 255, 255);
  set_pixel(10, 0, 255, 255, 255);
  set_pixel(11, 0, 255, 255, 255);
  set_pixel(12, 0, 255, 255, 255);
  set_pixel(13, 0, 255, 255, 255);
  set_pixel(14, 0, 255, 255, 255);
  set_pixel(15, 0, 255, 255, 255);
  set_pixel(16, 0, 255, 255, 255);
  set_pixel(17, 0, 255, 255, 255);
  set_pixel(18, 0, 255, 255, 255);
  set_pixel(19, 0, 255, 255, 255);
  set_pixel(20, 0, 255, 255, 255);
  set_pixel(21, 0, 255, 255, 255);
  set_pixel(0, 1, 255, 255, 255);
  set_pixel(1, 1, 255, 255, 255);
  set_pixel(2, 1, 255, 255, 255);
  set_pixel(3, 1, 255, 255, 255);
  set_pixel(4, 1, 255, 255, 255);
  set_pixel(5, 1, 255, 255, 255);
  set_pixel(6, 1, 255, 255, 255);
  set_pixel(7, 1, 255, 255, 255);
  set_pixel(8, 1, 255, 255, 255);
  set_pixel(9, 1, 255, 255, 255);
  set_pixel(10, 1, 255, 255, 255);
  set_pixel(11, 1, 255, 255, 255);
  set_pixel(12, 1, 255, 255, 255);
  set_pixel(13, 1, 255, 255, 255);
  set_pixel(14, 1, 255, 255, 255);
  set_pixel(15, 1, 255, 255, 255);
  set_pixel(16, 1, 255, 255, 255);
  set_pixel(17, 1, 255, 255, 255);
  set_pixel(18, 1, 255, 255, 255);
  set_pixel(19, 1, 255, 255, 255);
  set_pixel(20, 1, 255, 255, 255);
  set_pixel(21, 1, 255, 255, 255);
  set_pixel(0, 2, 255, 255, 255);
  set_pixel(1, 2, 255, 255, 255);
  set_pixel(2, 2, 255, 255, 255);
  set_pixel(3, 2, 255, 255, 255);
  set_pixel(4, 2, 255, 255, 255);
  set_pixel(5, 2, 255, 255, 255);
  set_pixel(17, 2, 255, 255, 255);
  set_pixel(18, 2, 255, 255, 255);
  set_pixel(19, 2, 255, 255, 255);
  set_pixel(20, 2, 255, 255, 255);
  set_pixel(21, 2, 255, 255, 255);
  set_pixel(0, 3, 255, 255, 255);
  set_pixel(1, 3, 255, 255, 255);
  set_pixel(2, 3, 255, 255, 255);
  set_pixel(3, 3, 255, 255, 255);
  set_pixel(4, 3, 255, 255, 255);
  set_pixel(6, 3, 0, 128, 0);
  set_pixel(7, 3, 0, 128, 0);
  set_pixel(8, 3, 0, 128, 0);
  set_pixel(9, 3, 0, 128, 0);
  set_pixel(10, 3, 0, 128, 0);
  set_pixel(12, 3, 217, 0, 0);
  set_pixel(13, 3, 217, 0, 0);
  set_pixel(14, 3, 217, 0, 0);
  set_pixel(15, 3, 217, 0, 0);
  set_pixel(16, 3, 217, 0, 0);
  set_pixel(18, 3, 255, 255, 255);
  set_pixel(19, 3, 255, 255, 255);
  set_pixel(20, 3, 255, 255, 255);
  set_pixel(21, 3, 255, 255, 255);
  set_pixel(0, 4, 255, 255, 255);
  set_pixel(1, 4, 255, 255, 255);
  set_pixel(2, 4, 255, 255, 255);
  set_pixel(3, 4, 255, 255, 255);
  set_pixel(5, 4, 209, 255, 26);
  set_pixel(7, 4, 0, 128, 0);
  set_pixel(8, 4, 0, 128, 0);
  set_pixel(9, 4, 0, 128, 0);
  set_pixel(10, 4, 0, 128, 0);
  set_pixel(12, 4, 217, 0, 0);
  set_pixel(13, 4, 217, 0, 0);
  set_pixel(14, 4, 217, 0, 0);
  set_pixel(15, 4, 217, 0, 0);
  set_pixel(17, 4, 209, 255, 26);
  set_pixel(19, 4, 255, 255, 255);
  set_pixel(20, 4, 255, 255, 255);
  set_pixel(21, 4, 255, 255, 255);
  set_pixel(0, 5, 255, 255, 255);
  set_pixel(1, 5, 255, 255, 255);
  set_pixel(2, 5, 255, 255, 255);
  set_pixel(3, 5, 255, 255, 255);
  set_pixel(5, 5, 209, 255, 26);
  set_pixel(6, 5, 209, 255, 26);
  set_pixel(8, 5, 0, 128, 0);
  set_pixel(9, 5, 0, 128, 0);
  set_pixel(10, 5, 0, 128, 0);
  set_pixel(12, 5, 217, 0, 0);
  set_pixel(13, 5, 217, 0, 0);
  set_pixel(14, 5, 217, 0, 0);
  set_pixel(16, 5, 209, 255, 26);
  set_pixel(17, 5, 209, 255, 26);
  set_pixel(19, 5, 255, 255, 255);
  set_pixel(20, 5, 255, 255, 255);
  set_pixel(21, 5, 255, 255, 255);
  set_pixel(0, 6, 255, 255, 255);
  set_pixel(1, 6, 255, 255, 255);
  set_pixel(2, 6, 255, 255, 255);
  set_pixel(3, 6, 255, 255, 255);
  set_pixel(5, 6, 209, 255, 26);
  set_pixel(6, 6, 209, 255, 26);
  set_pixel(7, 6, 209, 255, 26);
  set_pixel(9, 6, 0, 128, 0);
  set_pixel(10, 6, 0, 128, 0);
  set_pixel(12, 6, 217, 0, 0);
  set_pixel(13, 6, 217, 0, 0);
  set_pixel(15, 6, 209, 255, 26);
  set_pixel(16, 6, 209, 255, 26);
  set_pixel(17, 6, 209, 255, 26);
  set_pixel(19, 6, 255, 255, 255);
  set_pixel(20, 6, 255, 255, 255);
  set_pixel(21, 6, 255, 255, 255);
  set_pixel(0, 7, 255, 255, 255);
  set_pixel(1, 7, 255, 255, 255);
  set_pixel(2, 7, 255, 255, 255);
  set_pixel(3, 7, 255, 255, 255);
  set_pixel(5, 7, 209, 255, 26);
  set_pixel(6, 7, 209, 255, 26);
  set_pixel(7, 7, 209, 255, 26);
  set_pixel(8, 7, 209, 255, 26);
  set_pixel(10, 7, 0, 128, 0);
  set_pixel(12, 7, 217, 0, 0);
  set_pixel(14, 7, 209, 255, 26);
  set_pixel(15, 7, 209, 255, 26);
  set_pixel(16, 7, 209, 255, 26);
  set_pixel(17, 7, 209, 255, 26);
  set_pixel(19, 7, 255, 255, 255);
  set_pixel(20, 7, 255, 255, 255);
  set_pixel(21, 7, 255, 255, 255);
  set_pixel(0, 8, 255, 255, 255);
  set_pixel(1, 8, 255, 255, 255);
  set_pixel(2, 8, 255, 255, 255);
  set_pixel(3, 8, 255, 255, 255);
  set_pixel(5, 8, 209, 255, 26);
  set_pixel(6, 8, 209, 255, 26);
  set_pixel(7, 8, 209, 255, 26);
  set_pixel(8, 8, 209, 255, 26);
  set_pixel(9, 8, 209, 255, 26);
  set_pixel(13, 8, 209, 255, 26);
  set_pixel(14, 8, 209, 255, 26);
  set_pixel(15, 8, 209, 255, 26);
  set_pixel(16, 8, 209, 255, 26);
  set_pixel(17, 8, 209, 255, 26);
  set_pixel(19, 8, 255, 255, 255);
  set_pixel(20, 8, 255, 255, 255);
  set_pixel(21, 8, 255, 255, 255);
  set_pixel(0, 9, 255, 255, 255);
  set_pixel(1, 9, 255, 255, 255);
  set_pixel(2, 9, 255, 255, 255);
  set_pixel(3, 9, 255, 255, 255);
  set_pixel(5, 9, 209, 255, 26);
  set_pixel(6, 9, 209, 255, 26);
  set_pixel(7, 9, 209, 255, 26);
  set_pixel(8, 9, 209, 255, 26);
  set_pixel(9, 9, 209, 255, 26);
  set_pixel(10, 9, 209, 255, 26);
  set_pixel(12, 9, 209, 255, 26);
  set_pixel(13, 9, 209, 255, 26);
  set_pixel(14, 9, 209, 255, 26);
  set_pixel(15, 9, 209, 255, 26);
  set_pixel(16, 9, 209, 255, 26);
  set_pixel(17, 9, 209, 255, 26);
  set_pixel(19, 9, 255, 255, 255);
  set_pixel(20, 9, 255, 255, 255);
  set_pixel(21, 9, 255, 255, 255);
  set_pixel(0, 10, 255, 255, 255);
  set_pixel(1, 10, 255, 255, 255);
  set_pixel(2, 10, 255, 255, 255);
  set_pixel(3, 10, 255, 255, 255);
  set_pixel(5, 10, 209, 255, 26);
  set_pixel(6, 10, 209, 255, 26);
  set_pixel(7, 10, 209, 255, 26);
  set_pixel(8, 10, 209, 255, 26);
  set_pixel(9, 10, 209, 255, 26);
  set_pixel(10, 10, 209, 255, 26);
  set_pixel(12, 10, 209, 255, 26);
  set_pixel(13, 10, 209, 255, 26);
  set_pixel(14, 10, 209, 255, 26);
  set_pixel(15, 10, 209, 255, 26);
  set_pixel(16, 10, 209, 255, 26);
  set_pixel(17, 10, 209, 255, 26);
  set_pixel(19, 10, 255, 255, 255);
  set_pixel(20, 10, 255, 255, 255);
  set_pixel(21, 10, 255, 255, 255);
  set_pixel(0, 11, 255, 255, 255);
  set_pixel(1, 11, 255, 255, 255);
  set_pixel(2, 11, 255, 255, 255);
  set_pixel(3, 11, 255, 255, 255);
  set_pixel(4, 11, 255, 255, 255);
  set_pixel(6, 11, 209, 255, 26);
  set_pixel(7, 11, 209, 255, 26);
  set_pixel(8, 11, 209, 255, 26);
  set_pixel(9, 11, 209, 255, 26);
  set_pixel(10, 11, 209, 255, 26);
  set_pixel(12, 11, 209, 255, 26);
  set_pixel(13, 11, 209, 255, 26);
  set_pixel(14, 11, 209, 255, 26);
  set_pixel(15, 11, 209, 255, 26);
  set_pixel(16, 11, 209, 255, 26);
  set_pixel(18, 11, 255, 255, 255);
  set_pixel(19, 11, 255, 255, 255);
  set_pixel(20, 11, 255, 255, 255);
  set_pixel(21, 11, 255, 255, 255);
  set_pixel(0, 12, 255, 255, 255);
  set_pixel(1, 12, 255, 255, 255);
  set_pixel(2, 12, 255, 255, 255);
  set_pixel(3, 12, 255, 255, 255);
  set_pixel(4, 12, 255, 255, 255);
  set_pixel(5, 12, 255, 255, 255);
  set_pixel(17, 12, 255, 255, 255);
  set_pixel(18, 12, 255, 255, 255);
  set_pixel(19, 12, 255, 255, 255);
  set_pixel(20, 12, 255, 255, 255);
  set_pixel(21, 12, 255, 255, 255);
  set_pixel(0, 13, 255, 255, 255);
  set_pixel(1, 13, 255, 255, 255);
  set_pixel(2, 13, 255, 255, 255);
  set_pixel(3, 13, 255, 255, 255);
  set_pixel(4, 13, 255, 255, 255);
  set_pixel(5, 13, 255, 255, 255);
  set_pixel(6, 13, 255, 255, 255);
  set_pixel(7, 13, 255, 255, 255);
  set_pixel(8, 13, 255, 255, 255);
  set_pixel(9, 13, 255, 255, 255);
  set_pixel(10, 13, 255, 255, 255);
  set_pixel(11, 13, 255, 255, 255);
  set_pixel(12, 13, 255, 255, 255);
  set_pixel(13, 13, 255, 255, 255);
  set_pixel(14, 13, 255, 255, 255);
  set_pixel(15, 13, 255, 255, 255);
  set_pixel(16, 13, 255, 255, 255);
  set_pixel(17, 13, 255, 255, 255);
  set_pixel(18, 13, 255, 255, 255);
  set_pixel(19, 13, 255, 255, 255);
  set_pixel(20, 13, 255, 255, 255);
  set_pixel(21, 13, 255, 255, 255);
  set_pixel(0, 14, 255, 255, 255);
  set_pixel(1, 14, 255, 255, 255);
  set_pixel(2, 14, 255, 255, 255);
  set_pixel(3, 14, 255, 255, 255);
  set_pixel(4, 14, 255, 255, 255);
  set_pixel(5, 14, 255, 255, 255);
  set_pixel(6, 14, 255, 255, 255);
  set_pixel(7, 14, 255, 255, 255);
  set_pixel(8, 14, 255, 255, 255);
  set_pixel(9, 14, 255, 255, 255);
  set_pixel(10, 14, 255, 255, 255);
  set_pixel(11, 14, 255, 255, 255);
  set_pixel(12, 14, 255, 255, 255);
  set_pixel(13, 14, 255, 255, 255);
  set_pixel(14, 14, 255, 255, 255);
  set_pixel(15, 14, 255, 255, 255);
  set_pixel(16, 14, 255, 255, 255);

  strip.show();
}

void caveira() {
  set_pixel(7, 0, 255, 255, 255);
  set_pixel(8, 0, 255, 255, 255);
  set_pixel(9, 0, 255, 255, 255);
  set_pixel(10, 0, 255, 255, 255);
  set_pixel(11, 0, 255, 255, 255);
  set_pixel(12, 0, 255, 255, 255);
  set_pixel(13, 0, 255, 255, 255);
  set_pixel(14, 0, 255, 255, 255);
  set_pixel(7, 1, 255, 255, 255);
  set_pixel(14, 1, 255, 255, 255);
  set_pixel(7, 2, 255, 255, 255);
  set_pixel(14, 2, 255, 255, 255);
  set_pixel(6, 3, 255, 255, 255);
  set_pixel(7, 3, 255, 255, 255);
  set_pixel(9, 3, 0, 255, 0);
  set_pixel(10, 3, 0, 255, 0);
  set_pixel(11, 3, 0, 255, 0);
  set_pixel(12, 3, 0, 255, 0);
  set_pixel(14, 3, 255, 255, 255);
  set_pixel(15, 3, 255, 255, 255);
  set_pixel(5, 4, 255, 255, 255);
  set_pixel(9, 4, 0, 255, 0);
  set_pixel(10, 4, 0, 255, 0);
  set_pixel(11, 4, 0, 255, 0);
  set_pixel(12, 4, 0, 255, 0);
  set_pixel(16, 4, 255, 255, 255);
  set_pixel(3, 5, 255, 255, 255);
  set_pixel(4, 5, 255, 255, 255);
  set_pixel(10, 5, 0, 255, 0);
  set_pixel(11, 5, 0, 255, 0);
  set_pixel(17, 5, 255, 255, 255);
  set_pixel(18, 5, 255, 255, 255);
  set_pixel(2, 6, 255, 255, 255);
  set_pixel(19, 6, 255, 255, 255);
  set_pixel(2, 7, 255, 255, 255);
  set_pixel(5, 7, 0, 255, 0);
  set_pixel(6, 7, 0, 255, 0);
  set_pixel(7, 7, 0, 255, 0);
  set_pixel(8, 7, 0, 255, 0);
  set_pixel(13, 7, 0, 255, 0);
  set_pixel(14, 7, 0, 255, 0);
  set_pixel(15, 7, 0, 255, 0);
  set_pixel(16, 7, 0, 255, 0);
  set_pixel(19, 7, 255, 255, 255);
  set_pixel(2, 8, 255, 255, 255);
  set_pixel(4, 8, 0, 255, 0);
  set_pixel(5, 8, 0, 255, 0);
  set_pixel(6, 8, 0, 255, 0);
  set_pixel(7, 8, 0, 255, 0);
  set_pixel(8, 8, 0, 255, 0);
  set_pixel(9, 8, 0, 255, 0);
  set_pixel(12, 8, 0, 255, 0);
  set_pixel(13, 8, 0, 255, 0);
  set_pixel(14, 8, 0, 255, 0);
  set_pixel(15, 8, 0, 255, 0);
  set_pixel(16, 8, 0, 255, 0);
  set_pixel(17, 8, 0, 255, 0);
  set_pixel(19, 8, 255, 255, 255);
  set_pixel(2, 9, 255, 255, 255);
  set_pixel(4, 9, 0, 255, 0);
  set_pixel(5, 9, 0, 255, 0);
  set_pixel(6, 9, 0, 255, 0);
  set_pixel(7, 9, 0, 255, 0);
  set_pixel(8, 9, 0, 255, 0);
  set_pixel(9, 9, 0, 255, 0);
  set_pixel(12, 9, 0, 255, 0);
  set_pixel(13, 9, 0, 255, 0);
  set_pixel(14, 9, 0, 255, 0);
  set_pixel(15, 9, 0, 255, 0);
  set_pixel(16, 9, 0, 255, 0);
  set_pixel(17, 9, 0, 255, 0);
  set_pixel(19, 9, 255, 255, 255);
  set_pixel(2, 10, 255, 255, 255);
  set_pixel(4, 10, 0, 255, 0);
  set_pixel(5, 10, 0, 255, 0);
  set_pixel(6, 10, 0, 255, 0);
  set_pixel(7, 10, 0, 255, 0);
  set_pixel(8, 10, 0, 255, 0);
  set_pixel(9, 10, 0, 255, 0);
  set_pixel(12, 10, 0, 255, 0);
  set_pixel(13, 10, 0, 255, 0);
  set_pixel(14, 10, 0, 255, 0);
  set_pixel(15, 10, 0, 255, 0);
  set_pixel(16, 10, 0, 255, 0);
  set_pixel(17, 10, 0, 255, 0);
  set_pixel(19, 10, 255, 255, 255);
  set_pixel(2, 11, 255, 255, 255);
  set_pixel(5, 11, 0, 255, 0);
  set_pixel(6, 11, 0, 255, 0);
  set_pixel(7, 11, 0, 255, 0);
  set_pixel(8, 11, 0, 255, 0);
  set_pixel(13, 11, 0, 255, 0);
  set_pixel(14, 11, 0, 255, 0);
  set_pixel(15, 11, 0, 255, 0);
  set_pixel(16, 11, 0, 255, 0);
  set_pixel(19, 11, 255, 255, 255);
  set_pixel(3, 12, 255, 255, 255);
  set_pixel(18, 12, 255, 255, 255);
  set_pixel(4, 13, 255, 255, 255);
  set_pixel(17, 13, 255, 255, 255);
  set_pixel(5, 14, 255, 255, 255);
  set_pixel(6, 14, 255, 255, 255);
  set_pixel(7, 14, 255, 255, 255);
  set_pixel(8, 14, 255, 255, 255);
  set_pixel(9, 14, 255, 255, 255);
  set_pixel(10, 14, 255, 255, 255);
  set_pixel(11, 14, 255, 255, 255);
  set_pixel(12, 14, 255, 255, 255);
  set_pixel(13, 14, 255, 255, 255);
  set_pixel(14, 14, 255, 255, 255);
  set_pixel(15, 14, 255, 255, 255);
  set_pixel(16, 14, 255, 255, 255);

  strip.show();
}


void setup() {
  MihuCore::begin();
Serial.begin(9600);
blu.begin(device_name); // true ativa o modo slave com emparelhamento
strip.begin();
  strip.setBrightness(30);
  strip.show();  // inicializa todos apagados

//blu.setPin("1234", 4);

  MihuCore::setServo(ombro_esq, 170);//RETO PRA BAIXO
  MihuCore::setServo(ombro_dir, 10);//RETO PRA BAIXO
  MihuCore::setServo(braco_esq, 105);//RETO PRA BAIXO
  MihuCore::setServo(braco_dir, 80);//RETO PRA BAIXO
    MihuCore::setServo(girar_esq, 80);
    MihuCore::setServo(girar_dir, 80);
  delay(1500);

pinMode(pino_prox, INPUT);



}

void loop() {

prox = digitalRead(pino_prox);

blue();

}

void blue() {
  static int faseAtual = 0; // 0 = esperando S, 1 = esperando B, 2 = esperando T

  if (blu.available() > 0) {
    recebido = blu.readStringUntil('\n');
    recebido.trim();
  }

  if (faseAtual == 0) { // Esperando S
    if (recebido == "S" || recebido == "s") {
      faseAtual = 1;
      
    }
  }

  else if (faseAtual == 1) { // Rodando danca_criminal até receber B
    danca_criminal();
    gravata();
    if (recebido == "N" || recebido == "n") {
       strip.clear();
      do{
        prox = digitalRead(pino_prox);
          frente_sempre(110);

      }while(prox != 0);
       parar();
       delay(1000);

      faseAtual = 2;
    }
  }

  else if (faseAtual == 2) { // Rodando bater_tambor até receber T
    bater_tambor();
    olodum();
    if (recebido == "T" || recebido == "t") {
      faseAtual = 3;
       strip.clear();
    }
  }

  else if (faseAtual == 3) { // Rodando thriller para sempre
    danca_thriller();
    caveira();
  }
}