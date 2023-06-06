#include <IcsBaseClass.h>
#include <IcsHardSerialClass.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);
  while(!Serial){}
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  uint8_t TXdata[2] = { 0b10100000, 0x00};

  Serial1.write(TXdata, 2);
  Serial1.flush();

  digitalWrite(3, LOW);

  while (true) {
    while (Serial1.available() > 0) {
      Serial.println(Serial1.read());
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
