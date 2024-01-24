#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int minWValue = 5, maxWValue = 124;  // Giá trị nhỏ/lớn nhất trong phạm vi
const int minHValue = 5, maxHValue = 60;   // Giá trị nhỏ/lớn nhất trong phạm vi
int randomW, randomH, lastW, lastH;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  randomSeed(analogRead(0));  // Khởi tạo randomSeed với giá trị đọc từ chân analog A0

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  readreadBurron();
}

void readreadBurron() {
  randomW = random(minWValue, maxWValue);
  randomH = random(minHValue, maxHValue);
  if ((randomW == 5 || randomW == 124)) {
    sulyrandW(randomW, randomH);
  } else if ((randomH == 5 || randomH == 59)) {
    sulyrandH(randomW, randomH);
  }
}

void sulyrandW(int ctX1, int ctY1) {
  if (lastW <= 5) {
    ctX1 = 123;
  } else if (lastW >= 123) {
    ctX1 = 5;
  }
  Bresenham(lastW, lastH, ctX1, ctY1);
  lastW = ctX1;
  lastH = ctY1;
  delay(100);
}

void sulyrandH(int ctX2, int ctY2) {
  if (lastH <= 5) {
    ctY2 = 59;
  } else if (lastH >= 59) {
    ctY2 = 5;
  }
  Bresenham(lastW, lastH, ctX2, ctY2);
  lastH = ctY2;
  lastW = ctX2;
}

// test đưuongf đi củavaatj thể
void showup(int x0, int y0) {
  display.clearDisplay();
  display.drawLine(lastW, lastH, x0, y0, WHITE);
  display.display();
}

//thuật toán bresenham
void Bresenham(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int err = dx - dy;

  while (x0 != x1 || y0 != y1) {
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
    display.clearDisplay();
    Serial.println(x0, y0);
    display.fillCircle(x0, y0, 5, WHITE);
    // display.drawLine(lastW, lastH, x0, y0, WHITE);
    display.display();
  }
}