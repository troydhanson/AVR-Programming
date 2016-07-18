#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

//Adafruit_LEDBackpack matrix = Adafruit_LEDBackpack();
Adafruit_7segment matrix = Adafruit_7segment();

int PUSHBUTTON_PIN = 4;  
int SONAR_CONTROL_PIN = 7;
int SONAR_DISTANCE_PIN = A1;

void setup() {
  Serial.begin(9600);
  matrix.begin(0x70);  // pass in the address
  pinMode(PUSHBUTTON_PIN, INPUT);
  pinMode(SONAR_CONTROL_PIN, OUTPUT);
  digitalWrite(SONAR_CONTROL_PIN, LOW); // sonar off initially
}

//void loop() {
//  int button = digitalRead(PUSHBUTTON_PIN);
//  if (button == LOW) {  // start a new measurement
//    matrix.clear(); 
//    matrix.writeDisplay();
//    digitalWrite(SONAR_CONTROL_PIN, HIGH);
//    delay(1); // > 20us to start sonar
//    int dist = analogRead(SONAR_DISTANCE_PIN);
//    digitalWrite(SONAR_CONTROL_PIN, LOW);
//    matrix.println(dist); 
//    matrix.writeDisplay();
//  }
//  delay(500);
//}

  int dist, i, sonar_on=0;

void loop() {
  if (digitalRead(PUSHBUTTON_PIN) == LOW) {
    sonar_on = sonar_on ? 0 : 1;  // toggle sonar on/off
    while(digitalRead(PUSHBUTTON_PIN) == LOW) {}; // wait for unpress
  }
  if (sonar_on == 0) {
    matrix.clear();
    matrix.writeDisplay();
    digitalWrite(SONAR_CONTROL_PIN, LOW); // sonar off
    return;
  }
  
  // sonar on
  digitalWrite(SONAR_CONTROL_PIN, HIGH); // sonar on

  for (i=0; i<8; i++) {
     dist += analogRead(SONAR_DISTANCE_PIN);
     delay(50);
   }
  dist /= 8;
  matrix.println(dist); 
  matrix.writeDisplay();
}



