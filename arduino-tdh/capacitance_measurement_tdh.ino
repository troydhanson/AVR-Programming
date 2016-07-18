
int CHARGE_PIN = 3;
int DISCHARGE_PIN = 8;
int CAP_CHARGE_INPUT = A5;
double CHARGE_RESISTANCE = 330000.0F; //100kohm
int THRESHOLD = 647; // 63.2% of 1023, the capacitor's voltage at 1 time constant

void setup() {
 Serial.begin(9600);
 pinMode(CHARGE_PIN, OUTPUT);

}

void loop() {
  /* begin by discharging capacitor */
  Serial.println("discharging...");
  digitalWrite(CHARGE_PIN, LOW); // drain capacitor through 220ohm to ground
  pinMode(DISCHARGE_PIN, OUTPUT);
  digitalWrite(DISCHARGE_PIN, LOW); // drain capacitor through 220ohm to ground
  while( analogRead(CAP_CHARGE_INPUT) > 0) {}
  Serial.println("at zero charge. starting measurement.");
  
  /* start charging measurement by setting CHARGE_PIN to hi */
  pinMode(DISCHARGE_PIN, INPUT); // high impedance state to prevent discharge
  digitalWrite(CHARGE_PIN, HIGH); // start charging
  unsigned long time1 = micros();

  while(analogRead(CAP_CHARGE_INPUT) < THRESHOLD) {}
  unsigned long time2 = micros();
  unsigned long elapsed = time2-time1; 
  // the time required to acquire 63% of full voltage across cap is the RC time constant
  // so, since Tc = R*C we can now compute C = Tc/R 
  Serial.print("cap charge to 1 RC required "); Serial.print(elapsed); Serial.println(" us");
  
  double nanofarads = (elapsed * 1000.0) / CHARGE_RESISTANCE;
  if (nanofarads >= 1000) {
     double microfarads = nanofarads / 1000.0;
     Serial.print((long)microfarads); Serial.println(" microfarads");
  } else {
     Serial.print((long)nanofarads); Serial.println(" nanofarads");
  }
  delay(10000);
}
