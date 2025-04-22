// Pin definitions
const int sensorPin = A0;      // Analog pin for force sensor
const int inflatePumpPin = 9;  // Digital pin to inflate
const int deflatePumpPin = 10; // Digital pin to deflate

// System constants
const float Vref = 5.0;
const int ADC_resolution = 1023;

// Control parameters
float goalPressure = 120.0;  // Target pressure in mmHg
float tolerance = 2.0;       // Acceptable pressure deviation

void setup() {
  pinMode(inflatePumpPin, OUTPUT);
  pinMode(deflatePumpPin, OUTPUT);
  digitalWrite(inflatePumpPin, LOW);
  digitalWrite(deflatePumpPin, LOW);
  Serial.begin(9600);
}

void loop() {
  // Read sensor voltage
  int sensorValue = analogRead(sensorPin);
  float voltage = (sensorValue / (float)ADC_resolution) * Vref;

  // Convert voltage to pressure
  float pressure = 0.4225 * exp(1.0453 * voltage);

  // Debug output
  Serial.print("Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | Pressure: ");
  Serial.print(pressure, 2);
  Serial.println(" mmHg");

  // Control logic
  if (pressure < goalPressure - tolerance) {
    digitalWrite(inflatePumpPin, HIGH);
    digitalWrite(deflatePumpPin, LOW);
  } else if (pressure > goalPressure + tolerance) {
    digitalWrite(inflatePumpPin, LOW);
    digitalWrite(deflatePumpPin, HIGH);
  } else {
    digitalWrite(inflatePumpPin, LOW);
    digitalWrite(deflatePumpPin, LOW);
  }

  delay(100); // small delay to prevent over-driving
}
