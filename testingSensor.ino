const int fsrPin = A0;  
int fsrReading = 0;   
float voltage = 0.0;  

void setup() {
  Serial.begin(9600);   
  pinMode(fsrPin, INPUT);
}

void loop() {
  fsrReading = analogRead(fsrPin);        
  voltage = fsrReading * (5.0 / 1023.0);  
  Serial.print("Raw Reading: ");
  Serial.print(fsrReading);
  Serial.print("\tVoltage: ");
  Serial.print(voltage, 3);
  
  if (fsrReading < 10) {
    Serial.println("\tNo force detected");
  } else if (fsrReading < 200) {
    Serial.println("\tLight touch");
  } else if (fsrReading < 700) {
    Serial.println("\tMedium force");
  } else {
    Serial.println("\tHeavy force");
  }

  delay(500);  
}
