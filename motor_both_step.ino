#define OFF 0
#define NORTH 1
#define SOUTH 2

void setup() {
  // Coil A:
  pinMode(12,OUTPUT); // Direction
  pinMode(3,OUTPUT);  // On/Off
  pinMode(9,OUTPUT);  // Brake

  // Coil B:
  pinMode(13,OUTPUT); // Direction
  pinMode(11,OUTPUT); // On/Off
  pinMode(8,OUTPUT);  // Brake

  Serial.begin(115200);
}

int ct;
void loop() {
  for (ct = 1; ct <= 50; ct++) { // Full Step
    coilA(NORTH);
    coilB(OFF);
    delayMicroseconds(6000);    // Control speed of motor
  
    coilA(OFF);
    coilB(NORTH);
    delayMicroseconds(6000);
  
    coilA(SOUTH);
    coilB(OFF);
    delayMicroseconds(6000);
  
    coilA(OFF);
    coilB(SOUTH);
    delayMicroseconds(6000);
  }  
  delay(1000);
  for (ct = 1; ct <= 50; ct++) { // Half Step
    coilA(NORTH);
    coilB(OFF);
    delayMicroseconds(6000);    // Control speed of motor
  
    coilA(NORTH);
    coilB(NORTH);
    delayMicroseconds(6000);
  
    coilA(OFF);
    coilB(NORTH);
    delayMicroseconds(6000);
  
    coilA(SOUTH);
    coilB(NORTH);
    delayMicroseconds(6000);

    coilA(SOUTH);
    coilB(OFF);
    delayMicroseconds(6000);
    
    coilA(SOUTH);
    coilB(SOUTH);
    delayMicroseconds(6000);

    coilA(OFF);
    coilB(SOUTH);
    delayMicroseconds(6000);

    coilA(NORTH);
    coilB(SOUTH);
    delayMicroseconds(6000);    
  }  
  shutdown_all();
  while(true) {};     // Sinkhole

}

void shutdown_all() {
  digitalWrite(12, LOW);
  digitalWrite(3, LOW);
  digitalWrite(9, LOW);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  digitalWrite(8, LOW);
}

void coilA(int polarity) {
  digitalWrite(9, LOW);     // Brake Off
  if (polarity == NORTH) {
    digitalWrite(12, HIGH);
    digitalWrite(3, HIGH);  // Enables Coil A
  }
  if (polarity == SOUTH) {
    digitalWrite(12, LOW);
    digitalWrite(3, HIGH);  // Enables Coil A
  }
  if (polarity == OFF) {
    digitalWrite(12, LOW);
    digitalWrite(3, LOW);  // Enables Coil A
  }
}

void coilB(int polarity) {
  digitalWrite(8, LOW);       // Brake Off
  if (polarity == NORTH) {
    digitalWrite(13, HIGH);
    digitalWrite(11, HIGH);  // Enables Coil A
  }
  if (polarity == SOUTH) {
    digitalWrite(13, LOW);
    digitalWrite(11, HIGH);  // Enables Coil A
  }
  if (polarity == OFF) {
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);  // Enables Coil A
  }
}
