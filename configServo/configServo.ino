#include <IcsBaseClass.h>
#include <IcsHardSerialClass.h>

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(29, OUTPUT);
  digitalWrite(29, LOW);
  while(!Serial){}
  Serial.print("HELLO");
  digitalWrite(29, HIGH);
  delay(1);
  uint8_t TXdata[2] = { 0b10100000, 0x00};

  Serial1.write(TXdata, 2);
  Serial1.flush();

  digitalWrite(29, LOW);

  while (true) {
    while (Serial1.available() > 0) {
      Serial.write(Serial1.read());
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
