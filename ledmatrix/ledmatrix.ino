#include "LedControl.h"  // thêm thư viện
LedControl lc = LedControl(2, 4, 3, 1);
unsigned int delaytime = 50;
// Chân 12 nối với chân DataIn
// Chân 11 nối với chân CLK
// Chân 10 nối với chân LOAD
// Sử dụng 1 IC MAX7219
void setup() {
  lc.shutdown(0, false);  // Bật hiển thị
  lc.setIntensity(0, 8);  // Đặt độ sáng
  lc.clearDisplay(0);     // Tắt tất cả led
}

//thuật toán bresenham
void bresenham(int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int sx = x0 < x1 ? 1 : -1;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx - dy;

  while (x0 != x1 || y0 != y1) {
    lc.setLed(0, x0, y0, true);  // Đặt pixel

    int err2 = 2 * err;
    if (err2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (err2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void loop() {
  for (int i{ 0 }; i <= 8; i++) {
    bresenham(0, 0, 8, i);  // Vẽ đường thẳng
    delay(delaytime);
    lc.clearDisplay(0);  // Xóa màn hình
  }
  for (int i{ 8 }; i >= 0; i--) {
    bresenham(0, 0, i, 8);  // Vẽ đường thẳng
    delay(delaytime);
    lc.clearDisplay(0);  // Xóa màn hình
  }
  ////////////////////////////////////////////////////
  for (int i{ 8 }; i >= -1; i--) {
    bresenham(8, 8, -1, i);  // Vẽ đường thẳng
    delay(delaytime);
    lc.clearDisplay(0);  // Xóa màn hình
  }
  for (int i{ -1 }; i <= 8; i++) {
    bresenham(8, 8, i, -1);  // Vẽ đường thẳng
    delay(delaytime);
    lc.clearDisplay(0);  // Xóa màn hình
  }
}
