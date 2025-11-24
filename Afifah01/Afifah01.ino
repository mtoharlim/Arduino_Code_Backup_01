const int rainSensorPin = A0; // Connect raindrop sensor to analog pin A0
const int motorInput1 = 6; // Pin connected to the first motor control signal
const int motorInput2 = 7; // Pin connected to the second motor control signal
const int motorEnable = 10; // Pin used to enable/disable the motor driver
const int ledPinDry = 8; // Pin connected to the "dry" indicator LED
const int ledPinWet = 9; // Pin connected to the "wet" indicator LED

int previousRainSensorValue = 0; // Store previous raindrop sensor reading
bool isWet = false; // Flag to track wet state

void setup() {
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  pinMode(rainSensorPin, INPUT);
  pinMode(ledPinDry, OUTPUT);
  pinMode(ledPinWet, OUTPUT);
  digitalWrite(ledPinDry, HIGH); // Initially indicate dry state

  Serial.begin(9600);
}

void loop() {
  int rainSensorValue = analogRead(rainSensorPin);
  int threshold = 500; // Adjust threshold based on your sensor (higher for less sensitive)

  // Check for rain sensor value change and dry-to-wet or wet-to-dry transition
  if (abs(rainSensorValue - previousRainSensorValue) > 50 && // Minimum change
     ((rainSensorValue > threshold && !isWet) || // Dry to wet
      (rainSensorValue <= threshold && isWet))) { // Wet to dry
    previousRainSensorValue = rainSensorValue;

    if (rainSensorValue > threshold) {
      // Rain detected (wet)
      isWet = true;
      Serial.println("No Rain detected! Moving clothesline outwards.");
      moveMotorInwards(); // Replace with your inward movement function
      digitalWrite(ledPinDry, LOW);
      digitalWrite(ledPinWet, HIGH);
    } else {
      // No rain detected (dry)
      isWet = false;
      Serial.println("Rain detected! Moving clothesline inwards.");
      moveMotorOutwards(); // Replace with your outward movement function
      digitalWrite(ledPinWet, LOW);
      digitalWrite(ledPinDry, HIGH);
    }
  }

  delay(1000); // Adjust delay between checks as needed
}

void moveMotorInwards() {
  // Implement your inward movement logic here (e.g., motor control signals)
  // Example (replace with the appropriate sequence for your motor driver):
  digitalWrite(motorEnable, HIGH);
  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);
  delay(1000); // Adjust movement duration
  digitalWrite(motorEnable, LOW);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
}

void moveMotorOutwards() {
  // Implement your outward movement logic here (e.g., motor control signals)
  // Example (replace with the appropriate sequence for your motor driver):
  digitalWrite(motorEnable, HIGH);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, HIGH);
  delay(1000); // Adjust movement duration
  digitalWrite(motorEnable, LOW);
  digitalWrite(motorInput1, LOW);
  digitalWrite(motorInput2, LOW);
}
