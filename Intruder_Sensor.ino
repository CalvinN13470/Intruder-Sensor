// ---------------------------------------------------------------- //
// Intruder Sensor using Arduino Ultrasonic Sensor HC-SR04
// Writed by Calvin Nguyen
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04
#define LEDpin 4
#define BUZZpin 5
#define button 6
#define ONbutton 7
#define ONLED 8

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int buttonState = 0;
long millisCount = 0;
long millisCatch = 0;
boolean alert = false;
int ONbuttonState = 0;
boolean ON = false;

void setup() {
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(LEDpin, OUTPUT);
  pinMode(BUZZpin, OUTPUT);
  pinMode(button, INPUT);
  pinMode(ONbutton, INPUT);
  pinMode(ONLED, OUTPUT);
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
  digitalWrite(LEDpin, LOW);
  digitalWrite(ONLED, LOW);
  
}
void loop() {
  
  Serial.println(digitalRead(ONbutton));
  ONbuttonState = digitalRead(ONbutton);
  
  if ((ONbuttonState == HIGH) && (ON == false)){
    delay(200);
    digitalWrite(ONLED, HIGH);
    ON = true;
  }
  
  else if ((ONbuttonState == HIGH) && (ON == true)){
    delay(200);
    digitalWrite(ONLED, LOW);
    digitalWrite(BUZZpin, LOW);
    digitalWrite(LEDpin, LOW);
    alert = false;
    ON = false;
  }
  if (ON == true){
    Serial.println(digitalRead(button));
    millisCount = millis();
    
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    buttonState = digitalRead(button);

    //intruder trigger
    if (distance < 80){
      digitalWrite(LEDpin, HIGH);
      alert = true;
    }

    //Alarm after sensing intruder
    if (alert == true){
      if ((millisCount - millisCatch) < 500){
        digitalWrite(BUZZpin, HIGH);
      }
      if (((millisCount - millisCatch) < 1000) && ((millisCount - millisCatch) > 500)){
        digitalWrite(BUZZpin, LOW);
      }
      if ((millisCount - millisCatch) > 1000){
        millisCatch = millisCount;
      }
    }
    else{
      millisCatch = millisCount;
    }
    if (buttonState == HIGH){
      digitalWrite(BUZZpin, LOW);
      digitalWrite(LEDpin, LOW);
      alert = false;
    }
  }
      
}
