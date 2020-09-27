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

int ct, total;
double t0, t;
void loop() {
  t0 = micros();
  total = 0;
  for (ct = 1; ct <= 50; ct++) { // CCW rotation
    coilA(NORTH);
    coilB(OFF);
    delayMicroseconds(10000);    // Control speed of motor
  
    coilA(OFF);
    coilB(NORTH);
    delayMicroseconds(10000);
  
    coilA(SOUTH);
    coilB(OFF);
    delayMicroseconds(10000);
  
    coilA(OFF);
    coilB(SOUTH);
    delayMicroseconds(10000);
    t = micros();
    total = total + 4;
    Serial.print(t-t0);
    Serial.print("\t");
    Serial.println(total);
  }

  for (ct = 1; ct <= 50; ct++) {
    coilA(NORTH);
    coilB(OFF);
    delayMicroseconds(10000);
  
    coilA(OFF);
    coilB(SOUTH);
    delayMicroseconds(10000);
  
    coilA(SOUTH);
    coilB(OFF);
    delayMicroseconds(10000);
  
    coilA(OFF);
    coilB(NORTH);
    delayMicroseconds(10000);
    t = micros();
    total = total - 4;
    Serial.print(t-t0);
    Serial.print("\t");
    Serial.println(total);
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
