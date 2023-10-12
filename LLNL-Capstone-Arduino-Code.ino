const int photoGatePin = A0;  // Photogate input
const int solenoidPin = D0;   // Relay output to solenoid

bool initialSignalIgnored = false;
unsigned long startTime = 0;

void setup() {
  pinMode(photoGatePin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  Serial.begin(9600);
}

vvoid loop() {
  // Check for the photogate signal
  int photogateState = digitalRead(photoGatePin);

  if (photogateState == HIGH && !initialSignalIgnored) {
    // Ignore the initial signal
    initialSignalIgnored = true;
    Serial.println("Initial signal ignored");
  } else if (photogateState == HIGH && initialSignalIgnored) {
    // Record the time when the photogate is blocked
    unsigned long startTime = millis();

    // Wait until the photogate is no longer blocked
    while (digitalRead(photoGatePin) == HIGH) {
      // You can add any additional logic here if needed
    }

    // Calculate the time the flag breaks the laser
    unsigned long endTime = millis();
    float timeFlagBreaksLaser = (endTime - startTime) / 1000.0;  // Convert milliseconds to seconds

    // Calculate reaction time using the specified formula
    float reactionTime = lengthOfPhotogateFlag / (timeFlagBreaksLaser * gravitationalConstant);

    // Wait for the calculated reaction time
    delay(reactionTime * 1000);  // Convert seconds to milliseconds

    // Actuate the solenoid
    digitalWrite(solenoidPin, HIGH);
    Serial.println("Solenoid activated");

    // End the program
    while (true) {
      // You can add any additional logic here if needed
    }
  }
}