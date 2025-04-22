// Pin definitions
const int sensorPin = A0;       // Analog input from FRS
const int pump1Pin = 9;         // PWM output to Pump 1 (inflate)
const int pump2Pin = 10;        // PWM output to Pump 2 (deflate)

// Calibration constants for pressure equation
const float A = 0.4225;
const float B = 1.0453;

// Control parameters
float targetPressure = 120.0;   // Desired pressure in mmHg
float Kp = 50.0;                // Proportional gain (adjust based on system response)
float tolerance = 2.0;          // Acceptable error in mmHg

void setup() {
  Serial.begin(9600);
  pinMode(pump1Pin, OUTPUT);
  pinMode(pump2Pin, OUTPUT);
}

void loop() {
  // Read sensor voltage
  int analogValue = analogRead(sensorPin);
  float voltage = analogValue * (5.0 / 1023.0);

  // Calculate pressure using the exponential model
  float pressure = A * exp(B * voltage);

  // Calculate error
  float error = targetPressure - pressure;

  // Control logic
  if (abs(error) < tolerance) {
    // Within acceptable range, turn off both pumps
    analogWrite(pump1Pin, 0);
    analogWrite(pump2Pin, 0);
  } else if (error > 0) {
    // Pressure too low, inflate
    int pumpSpeed = constrain(int(Kp * error), 0, 255);
    analogWrite(pump1Pin, pumpSpeed);
    analogWrite(pump2Pin, 0);
  } else {
    // Pressure too high, deflate
    int pumpSpeed = constrain(int(-Kp * error), 0, 255);
    analogWrite(pump1Pin, 0);
    analogWrite(pump2Pin, pumpSpeed);
  }

  // Debugging info
  Serial.print("Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V, Pressure: ");
  Serial.print(pressure, 2);
  Serial.print(" mmHg, Error: ");
  Serial.println(error, 2);

  delay(100); // Loop delay to stabilize readings
}
