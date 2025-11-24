// Define pin numbers for D1, D2, and D3

#define D3 0
#define D1 5
#define D2 4

const int D1_PIN = D1;
const int D2_PIN = D2;
const int D3_PIN = D3;

void setup() {
  // Initialize the pins as inputs and outputs
  pinMode(D1_PIN, INPUT);
  pinMode(D2_PIN, INPUT);
  pinMode(D3_PIN, OUTPUT);
  
  // Set initial status to Standby
  digitalWrite(D3_PIN, LOW);
  
  // Start serial communication at 9600 baud
  Serial.begin(115200);
}

void loop() {
  int d1 = digitalRead(D1_PIN);
  int d2 = digitalRead(D2_PIN);
  int d3 = digitalRead(D3_PIN);

  if (d3 == LOW && d1 == LOW && d2 == LOW) {
    // Standby
    digitalWrite(D3_PIN, LOW);
    Serial.println("Status 1: Standby");
  } else if (d3 == HIGH && d1 == LOW && d2 == LOW) {
    // Boiler On
    digitalWrite(D3_PIN, HIGH);
    Serial.println("Status 2: Boiler On");
  } else if (d3 == HIGH && d1 == HIGH && d2 == LOW) {
    // High Temp
    // Code to regulate the temperature
    Serial.println("Status 3: High Temp");
  } else if (d3 == HIGH && d1 == HIGH && d2 == LOW && millis() % 60000 == 0) {
    // Less Than (High)
    // Code to regulate the temperature
    Serial.println("Status 4: Less Than (High)");
  } else if (d3 == HIGH && d1 == LOW && d2 == HIGH) {
    // Low Temp
    // Code to regulate the temperature
    Serial.println("Status 5: Low Temp");
  } else if (d3 == HIGH && d1 == LOW && d2 == HIGH && millis() % 60000 == 0) {
    // More than (Low)
    // Code to regulate the temperature
    Serial.println("Status 6: More than (Low)");
  } else if (d3 == HIGH && d1 == HIGH && d2 == HIGH && millis() % 60000 == 0) {
    // Inspection
    // Code to perform inspection
    Serial.println("Status 7: Inspection");
  } else if (d3 == LOW && d1 == HIGH && d2 == LOW) {
    // Boiler Off
    digitalWrite(D3_PIN, LOW);
    Serial.println("Status 8: Boiler Off");
  }

  // Check D1 and D2 for 60 seconds
  /**if (millis() % 60000 == 0) {
    for (int i = 0; i < 60; i++) {
      // Check the status of D1 and D2 every second
      int d1_check = digitalRead(D1_PIN);
      int d2_check = digitalRead(D2_PIN);

      // If either D1 or D2 is high, give it priority
      if (d1_check == HIGH) {
        digitalWrite(D3_PIN, LOW);
        Serial.println("Priority: D1 is high");
        break;
      } else if (d2_check == HIGH) {
        digitalWrite(D3_PIN, LOW);
        Serial.println("Priority: D2 is high");
        break;
      }**/

      delay(1000);
    }
  
