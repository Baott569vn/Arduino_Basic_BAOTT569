#define inPut1 2
#define inPut2 3
#define inPut3 4
#define inPut4 5

const byte minSeed = 0;
const byte maxSeed = 255;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inPut1, OUTPUT);
  pinMode(inPut2, OUTPUT);
  pinMode(inPut3, OUTPUT);
  pinMode(inPut4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i{ minSeed }; i <= maxSeed; i += 20) {
    controlMotor2(i, 1);
    controlMotor1(i, 1);
  }
  delay(10);
  for (int a{ maxSeed }; a >= minSeed; a -= 20) {
    controlMotor2(a, 0);
    controlMotor1(a, 0);
  }
}

void controlMotor1(byte presentSeed, byte backword) {
  presentSeed = constrain(presentSeed, minSeed, maxSeed);
  digitalWrite(inPut1, backword);
  analogWrite(inPut2, presentSeed);
  Serial.println(String("input1: ") + inPut1 + String("input2: ") + presentSeed);
}

void controlMotor2(byte presentSeed, byte backword) {
  presentSeed = constrain(presentSeed, minSeed, maxSeed);
  digitalWrite(inPut3, backword);
  analogWrite(inPut4, presentSeed);
  Serial.println(String("input3: ") + inPut3 + String("input4: ") + presentSeed);
}
