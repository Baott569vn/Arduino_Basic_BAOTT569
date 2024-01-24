#include "DigiKeyboard.h"

void setup() {
  // don't need to set anything up to use DigiKeyboard
}


void loop() {
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);
  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
  DigiKeyboard.delay(5000);

  for (int value = 1000; value <= 1101; value++) {
    // Chuyển đổi giá trị số thành chuỗi có độ dài 6 ký tự, đầu bằng các số 0 nếu cần
    char formattedValue[7];
    sprintf(formattedValue, "%04d", value);
    DigiKeyboard.println(value);
    DigiKeyboard.delay(150);  // Đợi một chút trước khi xuất giá trị tiếp theo
  }
  DigiKeyboard.delay(5000);
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
}
