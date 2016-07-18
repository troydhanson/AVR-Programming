

#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302)

#define STATUS_LED1 3
#define STATUS_LED2 2
#define RADIATION_LED1 5 // pwm
#define RADIATION_LED2 6 // pwm
#define PIEZO_PIN 12        
#define DHT_PIN 13          // temp humidity
#define GEIGER_PIN 4  

unsigned int pendulum; // this is a 2-byte int; it takes about 7 seconds to roll back to 0
unsigned long interval = 1000UL * 60; // how often to take the temperature, in millisec
unsigned long end_ms, now;
int cpm=0;
float h,t; // humidity, temp
DHT dht(DHT_PIN, DHTTYPE);

void setup() 
{
  Serial.begin(9600);

  pinMode(STATUS_LED1, OUTPUT);
  pinMode(STATUS_LED2, OUTPUT);
  pinMode(RADIATION_LED1, OUTPUT);
  pinMode(RADIATION_LED2, OUTPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(DHT_PIN, INPUT);
  pinMode(GEIGER_PIN, INPUT);

  dht.begin(); // humidity temp
  
  now = millis();
  end_ms = now ;//+ interval;
  //Serial.println("setup complete");
}

byte msg[4] = {2,0,0,0}; // format is tileId, cpm, temp, humidity

// the indicator slowly gets brighter, then dimmer, endlessly
void breathe() {
  unsigned byte = (pendulum++ < 32768) ? (pendulum >> 8) : (255-(pendulum >> 8)); 
  analogWrite(STATUS_LED1, byte/2); 
}

void click() {
  digitalWrite(PIEZO_PIN, HIGH); 
  analogWrite(RADIATION_LED1, 255);
  if (cpm > 30) analogWrite(RADIATION_LED2, 255); 

  //digitalWrite(STATUS_LED2, HIGH); 
  delay(100);
  digitalWrite(PIEZO_PIN, LOW);
  analogWrite(RADIATION_LED1, 0);
  analogWrite(RADIATION_LED2, 0); 
  //digitalWrite(STATUS_LED2, LOW); 

}

void take_temp() {
 now = millis();
 if (now < end_ms) return; // too soon? let more time elapse

 h = dht.readHumidity();
 t = dht.readTemperature(); t = t * 1.8 + 32; // fahrenheit
 /*Serial.print(" Humidity: ");     Serial.print(h);  Serial.println(" %");
 Serial.print(" Temperature: ");  Serial.print(t);  Serial.println(" *F");
 Serial.print(" CPM: "); Serial.println(cpm);
 */
 Serial.print(cpm);  Serial.print(",");
 Serial.print(h);    Serial.print(",");
 Serial.println(t); 
 
 msg[1] = (unsigned char)cpm;
 msg[2] = (unsigned char)t;
 msg[3] = (unsigned char)h;

 end_ms = now + interval;
 cpm = 0;  // reset counter (counts per minute)
}


void loop() {
  int high=0;
  while ((digitalRead(GEIGER_PIN)) == HIGH) high++; // let high state finish - about 54 loops 
  if (high) { cpm++; if (cpm > 20) click(); }
  digitalWrite(STATUS_LED2, cpm>30?HIGH:LOW);
  breathe();
  take_temp();
}
