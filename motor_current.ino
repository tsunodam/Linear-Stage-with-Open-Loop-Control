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
float iA, iB;
void loop() {
  coilA(NORTH);
  coilB(NORTH);
  
  for (ct = 0; ct <= 20; ct++) {
    iA= float(analogRead(0)) /1023.0*5.0 / 1.65*1000;
    iB= float(analogRead(1)) /1023.0*5.0 / 1.65*1000;
    Serial.print(iA);
    Serial.print("\t");
    Serial.println(iB);
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
