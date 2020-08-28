const int sensorPin = A0;
const int greenLEDPin = 9;
const int redLEDPin = 11;
const int blueLEDPin = 10;

const float baselineTemp = 20.0;

void setup() {
  Serial.begin(9600); // open a serial port

  // Set pin-out
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);

  for(int pinNumber = 2; pinNumber<5; pinNumber++){
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop() {
  int sensorVal = analogRead(sensorPin);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  // Convert the ADC reading to voltage
  float voltage = (sensorVal/1024.0) * 5.0;

  Serial.print(", Volts: ");
  Serial.print(voltage);

  Serial.print(", degrees C: ");
  // Convert the voltage to temperature in degrees
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);

  if(temperature < baselineTemp) { // If temperature < 20C
    // No red LEDs
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);

    // RGB is blue (for cold)
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 255);
  } else if (temperature >= baselineTemp+2 && temperature < baselineTemp+4) { // If temperature is between 22-23.99
    // Light 1 red LED
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);

    // Red for low match
    analogWrite(redLEDPin, 255);
    analogWrite(greenLEDPin, 0);
    analogWrite(blueLEDPin, 0);
  } else if (temperature >= baselineTemp+4 && temperature < baselineTemp+6) { // If temperature is between 24-25.99
    // Light 2 red LEDs
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);

    // Yellow for medium a match
    analogWrite(redLEDPin, 255);
    analogWrite(greenLEDPin, 255);
    analogWrite(blueLEDPin, 0);
  } else if (temperature >= baselineTemp+6) { // If temperature is >= 26
    // Light 3 red LEDs
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);

    // Green for good match
    analogWrite(redLEDPin, 0);
    analogWrite(greenLEDPin, 255);
    analogWrite(blueLEDPin, 0);
  }

  // Small delay, so we don't go the clock-speed
  delay(1);
}
