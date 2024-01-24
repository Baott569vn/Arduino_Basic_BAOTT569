const byte pinBCD[3] = { 2, 3, 4 };
const int wait = 50;
const byte sensorMic = A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // randomSeed(analogRead(0));
  pinMode(sensorMic, INPUT_PULLUP);
  for (int i{ 0 }; i <= 3; i++) {
    pinMode(pinBCD[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  // displayBCD();
  fillDisplay();
}

void functionSetBCD(int numBCD) {
  for (byte a{ 0 }; a <= 3; a++) {
    byte displayValue = (numBCD >> a) & 0x01;
    digitalWrite(pinBCD[a], displayValue);
  }
}

// void fillDisplay() {
//   byte randumNum = random(7);
//   for (byte b{ 0 }; b <= 50; b++) {
//     for (byte c{ 0 }; c <= randumNum; c++) {
//       for (byte x{ 0 }; x <= c; x++) {
//         functionSetBCD(x);
//       }
//     }
//   }
//   delay(wait);
// }

void fillDisplay() {
  // byte randumNum = random(0, 8 + 1);
  // Serial.println(randumNum);
  float valueMic = analogRead(sensorMic);
  valueMic = map(valueMic, 0, 1023, 0.0, 10.0);
  // Serial.println(valueMic);
  // for (int c = randumNum, x = 0; x++, x %= (c + 1), c -= (x == c), x = (x == c ? 0 : x);) {
  for (byte b{ 0 }, c = valueMic, x{ 0 }; b <= 20; x++, x %= (c + 1), c -= (x == c), x = (x == c ? 0 : x), b++) {
    functionSetBCD(x - 1);
    animation(x);
    if (valueMic <= 0.0) {
      break;
    }
  }
  delay(2);
}



///////////////////////////////////////////////////////////
void animation(int numBCD) {
  for (int super{ 0 }; super <= numBCD; super = constrain(super, 0, 20), super++) {
    Serial.print(super + String("#"));
  }
  Serial.println();
}

void displayBCD() {
  //left
  for (byte numBCD{ 0 }; numBCD <= 7; numBCD++) {
    functionSetBCD(numBCD);
    delay(wait);
    animation(numBCD);
  }
  //right
  for (byte numBCD{ 6 }; numBCD >= 1; numBCD--) {
    functionSetBCD(numBCD);
    delay(wait);
    animation(numBCD);
  }
}
