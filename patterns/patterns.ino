/*
 * Interface 7 LEDs to the 2560 controlled by 1 button
 * Short press - increases the frequency of the pattern
 * Long press - changes pattern
 */

int red1 = 7, red2 = 3, green1 = 5, yellow = 6, green2 = 8, blue1 = 9, blue2 = 11;
int buttonPin = 2;
int buttonVal;
int dt1;
int dt2;
int dt3;
int lastState = HIGH;
String presskind;
int count = 0;

void setup() {
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green2, OUTPUT);
  pinMode(blue1, OUTPUT);
  pinMode(blue2, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  Serial.begin(9600);
}

/*
 * Each pattern should be looping ---> how???
 * When shortpress is detected, the frequency of blinking decreases
 * When longpress is detected, pattern changes
 */

void loop() {
  buttonVal = digitalRead(buttonPin);
  presskind = buttonPress();
  
  if (presskind == "longpress") {
    dt1 = 500;
    dt2 = 300;
    dt3 = 100;
    
    if (count == 0) {
      count += 1;
      pattern1(dt1);
    } else if (count == 1) {
      count += 1;
      pattern2(dt2);
    } else if (count == 2) {
      pattern3(dt3); 
      count = 0;
    }
  }
  else if (presskind == "shortpress") {
    if (count == 1) {
      dt1 += 200;
      pattern1(dt1);
    }  
    else if (count == 2) {
      dt2 += 200;
      pattern2(dt2);  
    }
    else if (count == 0) {
      dt3 += 200;
      pattern3(dt3);
    }
  }  
}

/*
 * Function to detect type of buttonpress
 */

String buttonPress(){
  long holdingTime;
  long previousHoldingTime;
  unsigned long firstButtonPressTime;
  String presstype;
  
  if (buttonVal == LOW && lastState == HIGH && (millis()-firstButtonPressTime) > 200) {
    firstButtonPressTime = millis();
  }
  holdingTime = (millis() - firstButtonPressTime);

  if (holdingTime > 50) {
    if (buttonVal == LOW && holdingTime > previousHoldingTime) {
      //Serial.println("Button is pressed");
    }

    if (buttonVal == HIGH && lastState == LOW) {
      if (holdingTime <= 550) {
        Serial.println("This is a short press");
        presstype = "shortpress";
      }
      else if (holdingTime > 550) {
        Serial.println("This is a long press");
        presstype = "longpress";
      }
    }
  }

  lastState = buttonVal;
  previousHoldingTime = holdingTime;

  return presstype;
}

/*
 * Patterns
 */

void off() {
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  digitalWrite(yellow, LOW);
  delay(400);
}

void pattern1(int delaytime){
  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  delay(delaytime);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(delaytime);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(delaytime);
  digitalWrite(yellow, HIGH);
  delay(delaytime);
  off(); 
}

void pattern2(int delaytime) {
  digitalWrite(red1, HIGH);
  digitalWrite(blue1, HIGH);
  delay(delaytime);
  digitalWrite(red1, LOW);
  digitalWrite(blue1, LOW);
  delay(delaytime);
  digitalWrite(green1, HIGH);
  digitalWrite(yellow, HIGH);
  delay(delaytime);
  digitalWrite(green1, LOW);
  digitalWrite(yellow, LOW);
  delay(delaytime);
  digitalWrite(green2, HIGH);
  digitalWrite(red2, HIGH);
  delay(delaytime);
  digitalWrite(green2, LOW);
  digitalWrite(red2, LOW);
  delay(delaytime); 
  digitalWrite(blue2, HIGH);
  delay(delaytime);
  off();
}

void pattern3(int delaytime) {
  digitalWrite(yellow, HIGH);
  delay(delaytime);
  digitalWrite(green1, HIGH);
  digitalWrite(green2, HIGH);
  delay(delaytime);
  digitalWrite(red1, HIGH);
  digitalWrite(red2, HIGH);
  delay(delaytime);
  digitalWrite(blue1, HIGH);
  digitalWrite(blue2, HIGH);
  delay(delaytime);

  digitalWrite(blue1, LOW);
  digitalWrite(blue2, LOW);
  delay(100);
  digitalWrite(red1, LOW);
  digitalWrite(red2, LOW);
  delay(100);
  digitalWrite(green1, LOW);
  digitalWrite(green2, LOW);
  delay(100);
  digitalWrite(yellow, LOW);
  delay(100);
}
