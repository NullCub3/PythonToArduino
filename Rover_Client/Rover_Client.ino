#define enA 10
#define enB 5
#define in1 9
#define in2 8
#define in3 7
#define in4 6

int rightSpeed;
int leftSpeed;
bool LeftPos;
bool RightPos;

bool reciving;
int value;


void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  Serial.begin(230400);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Grabs input from the serial port
  if (Serial.available()) { // Checks to see if there is any new serial input
//    Serial.println("Reciving!"); // Debug

    // Resetting variables
    reciving = true;
    value = 0;
    LeftPos = true;
    RightPos = true;

    // Loop to grab the input from the serial port and convert into integers.
    while (reciving) {
      char ch = Serial.read(); // Gets the next character in the input from the serial port

      // Checks to see if the input is a number
      if (ch >= '0' && ch <= '9') {
        value = (value * 10) + (ch - '0');
        }

      // If there is a negative sign, it sets a variable to change how the number is applied to the motor speed.
      else if (ch == '-') {
      LeftPos = false;
      }

      // If there's a space, then thats the end of the first value for the left side. Applies the value to the motor speed and moves onto the next value.
      else if (ch == ' ') {
//        Serial.println(value); // Debug
//        Serial.println(LeftPos); // Debug
        
        // Makes the value negative if there was a negative sign, and applies it to the motor speed.
        if (LeftPos) {
          leftSpeed = value;
          }
        else {
            leftSpeed = -value;
            }
//        Serial.println(leftSpeed); // Debug
        value = 0; // Resets the value
        
        // Loop for the right side, same as above.
        while (reciving) {
          char ch = Serial.read();
          
          if (ch >= '0' && ch <= '9') {
            value = (value * 10) + (ch - '0');
            }
          else if (ch == '-') {
            RightPos = false;
            }
          else if (ch == 10) {
//            Serial.println(value); // Debug
//            Serial.println(RightPos); // Debug
            if (RightPos) {
              rightSpeed = value;
              }
            else {
              rightSpeed = -value;
              }
//              Serial.println(rightSpeed); // Debug
              reciving = false; // Breaks the loop.
            }
          }
        }
      }
    }

  //Sets Right Motor speeds
  if (rightSpeed > 0){ // If the value is positive
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, rightSpeed);
    }
   else if (rightSpeed < 0){ // if the value is negative
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, -rightSpeed);
    }
    else { // if at zero than disconnect the motor
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);
      }

  //Sets Left Motor speeds, same as above, but for the left.
  if (leftSpeed > 0){
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, leftSpeed);
    }
   else if (leftSpeed < 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, -leftSpeed);
    }
    else {
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enB, 0);
      }
  
}

// Hey thats the end of the program!
