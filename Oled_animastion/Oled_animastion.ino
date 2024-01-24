#include <splash.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1 // Không sử dụng chân reset OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const String dataString =
    " abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
    "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

String myString = "";
bool newData = false;

void setup()
{
  Serial.begin(9600);
  // Khởi tạo kết nối I2C với màn hình OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Địa chỉ I2C mặc định cho màn hình OLED 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Cài đặt màn hình OLED
  display.display(); // Hiển thị màn hình khởi đầu (đen)
  delay(2000);       // Dừng 2 giây

  // Cài đặt kích thước và màu sắc của văn bản
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void loop()
{
  while (Serial.available() > 0)
  {
    char c = Serial.read();
    if (c == '\n')
    {
      newData = true;
      break;
    }
    myString += c;
  }

  if (newData)
  {
    int x = myString.length();
    String displayStr(x);

    int a = 0;

    while (a != x)
    {
      for (int i = 0; i < dataString.length(); i++)
      {
        displayStr = displayStr.substring(0, a) + dataString.charAt(i) + displayStr.substring(a + 1);
        Serial.println(displayStr);

        // Hiển thị trên màn hình OLED
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(displayStr);
        display.display();

        if (dataString.charAt(i) == myString.charAt(a))
        {
          displayStr = displayStr.substring(0, a) + myString.charAt(a) + displayStr.substring(a + 1);
          a++;
        }
      }
    }
    Serial.println(myString);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(myString);
    display.display();

    newData = false;
    myString = "";
    while (Serial.available() > 0)
    {
      Serial.read(); // Xóa bộ nhớ đệm Serial Monitor
    }
  }

  // Đợi một lúc trước khi lặp lại
  delay(5000);
}
