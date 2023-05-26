#include <IcsBaseClass.h>
#include <IcsHardSerialClass.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  uint8_t TXdata[2] = { 0b10100000, 0x00};
  
  Serial.write(TXdata, 2);

  digitalWrite(3, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

}
