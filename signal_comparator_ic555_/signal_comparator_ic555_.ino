const int inputPin = 7;  // Digital pin connected to the input from IC555
const int outputPin =9;  // Digital pin connected to the output
unsigned long pulseStartTime = 0;
unsigned long pulseEndTime = 0;
bool pulseDetected = false;


void setup() {
 pinMode(inputPin, INPUT);
 pinMode(outputPin, OUTPUT); // Set the input pin as INPUT
 Serial.begin(9600);        // Initialize serial communication
}

void loop() {
  // Measure the frequency and duty cycle of the Arduino square wave
 //unsigned long period = pulseIn(inputPin, HIGH);       // Measure the HIGH period
// unsigned long totalPeriod =pulseIn(inputPin, HIGH) + pulseIn(inputPin,LOW);   // Measure the total period
  digitalWrite(outputPin, HIGH);
  delay(5000);   

  digitalWrite(outputPin, LOW);
  delay(5000); 
  unsigned long startTime = micros();
  while (digitalRead(outputPin) == HIGH) {}  // Wait for falling edge
  unsigned long endTime = micros();

  unsigned long timePeriod = endTime - startTime;

  // Print the time period to the Serial Monitor
  Serial.print("Time Period (T): ");
  Serial.print(timePeriod);
  Serial.println(" microseconds");
  //unsigned long startTime = micros();
 if (digitalRead(inputPin) == LOW && pulseDetected) {
    pulseEndTime = micros();
    pulseDetected = false;

  float pulseDuration = pulseEndTime - pulseStartTime;
  float frequency = 1000000.0 / pulseDuration;             // Calculate frequency in Hz
  float dutyCycle = (pulseDuration / (pulseDuration + (pulseEndTime - pulseStartTime))) * 100.0;
 

  Serial.print("ic - Frequency: ");
  Serial.print(frequency);
  Serial.print(" Hz, Duty Cycle: ");
  Serial.print(dutyCycle);
  Serial.println("%");// Calculate duty cycle in percentage
 }
 
else {
    pulseStartTime = micros();
    pulseDetected = true;
  }
  
}
