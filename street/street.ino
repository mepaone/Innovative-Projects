const int RELAY = 2;
const int LDR = A0;
void setup() {
Serial.begin(9600);
 
pinMode(RELAY, OUTPUT);
 
pinMode(LDR, INPUT);
}
void loop() {
int Status = analogRead(LDR);
if (Status < 650) {
  digitalWrite(RELAY, HIGH);
  }
else {
  digitalWrite(RELAY, LOW);
  }
//checking value
Serial.println(Status);
delay(500);
}
