#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct sheetRand {
  byte randX;
  byte randY;
  byte Dis_randX;
  byte Dis_randY;
  byte defaultX;
  byte defaultY;
};

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A0));

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  delay(2000);
  display.clearDisplay();
}

void display_Circle(byte pussyX, byte pussyY) {
  sheetRand bestDis;
  int totalX = bestDis.Dis_randX;
  int totalY = bestDis.Dis_randY;
  while (pussyX != totalX || pussyY != totalY) {
    display.clearDisplay();
    display.fillCircle(totalX, totalY, 5, WHITE);
    display.display();
    if (totalX > pussyX) {
      totalX--;
    } else if (totalX < pussyX) {
      totalX++;
    }
    if (totalY > pussyY) {
      totalY--;
    } else if (totalY < pussyY) {
      totalY++;
    }
    // Serial.println(".............................");
    // Serial.println(totalX);
    // Serial.println(totalY);
    delay(100);
  }
  bestDis.Dis_randX = pussyX;
  bestDis.defaultX = pussyX;
  bestDis.Dis_randY = pussyY;
  bestDis.defaultY = pussyY;
  Serial.println("===========END=========");
}


void calculate_Funcition_True(int costX, int costY) {
  if (costX > 64) {
    costX -= 5;
  } else if (costX < 64) {
    costX += 5;
  }
  if (costY > 32) {
    costY -= 5;
  } else if (costY < 32) {
    costY += 5;
  }
  display_Circle(costX, costY);
}

void plysisc_Funcition() {
  sheetRand mRand;
  bool compareY = false;
  mRand.randX = random(0, 128 + 1);
  mRand.randY = random(0, 64 + 1);
  do {
    if (mRand.defaultY < mRand.randY && mRand.randY < 32) {
      mRand.randY = mRand.randY - mRand.randY + 64;
      pintleX();
      compareY = true;
    }
  } while (compareY = false);
  Serial.println(mRand.randX);
  Serial.println(mRand.randY);
  calculate_Funcition_True(mRand.randX, mRand.randY);
}

void pintleX() {
  sheetRand xRand;
  if (xRand.randX < 64) {
    xRand.randX = (xRand.randX - xRand.defaultX) + 64;
  } else {
    xRand.randX = (xRand.defaultX - xRand.randX) - 64;
  }
  xRand.randX < 64 ? xRand.randX += 64 : xRand.randX -= 64;
}

// void pintleY() {
//   sheetRand mRand;
//   if (mRand.randY <= 32) {
//     mRand.randY = (mRand.randY - mRand.defaultY) + 32;
//   } else {
//     mRand.randY = (mRand.defaultY - mRand.randY) - 32;
//   }
// }

// void lay_so_ngauNhien() {
//   sheetRand mRand;
//   mRand.randX = random(0, 128 + 1);
//   mRand.randY = random(0, 64 + 1);
// }

void loop() {
  plysisc_Funcition();
}