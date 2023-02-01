/*
 * Interface 7 LEDs to the 2560 controlled by 1 button
 * Short press - increases the frequency of the pattern
 * Long press - changes pattern
 * Using Interrupts
 */

int red1 = 7, red2 = 3, green1 = 5, yellow = 6, green2 = 8, blue1 = 4, blue2 = 11;
int buttonPin = 2;
int buttonVal;
int dt = 500, dt1 = 500, dt2 = 500, dt3 = 500;
int lastState = HIGH;
int count = 0;

long holdingTime;
long previousHoldingTime;
unsigned long firstButtonPressTime;

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
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonIsPressed, CHANGE);  
}

void loop() {
  blinkingLeds();
}

void buttonPress() {
  
  if (buttonVal == LOW && lastState == HIGH && (millis()- firstButtonPressTime) > 200) {
    firstButtonPressTime = millis();
  }
  holdingTime = (millis() - firstButtonPressTime);

  if (holdingTime > 50) {
    if (buttonVal == HIGH && lastState == LOW) {
      if (holdingTime <= 550) {
        Serial.println("This is a short press");
        if (count == 0) {
          dt1 += 200;
        }  
        else if (count == 1) {
          dt2 += 200;  
        }
        else if (count == 2) {
          dt3 += 200;
        }
      }
      else if (holdingTime > 550) {
        Serial.println("This is a long press");
        dt1 = 500;
        dt2 = 300;
        dt3 = 100;
        count += 1;
      }
    }
  }

  lastState = buttonVal;
  previousHoldingTime = holdingTime;
}

void buttonIsPressed() {
  buttonVal = digitalRead(buttonPin);
  buttonPress();
  //Serial.println(buttonPress());
}

void blinkingLeds() {
    if (count == 0) {
      pattern1(dt1);
    } else if (count == 1) {
      pattern2(dt2);
    } else if (count == 2) {
      pattern3(dt3); 
    } else if (count == 3) {
      count = 0;
    }
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
