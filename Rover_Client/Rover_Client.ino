#define enA 10
#define enB 5
#define in1 9
#define in2 8
#define in3 7
#define in4 6

int RightInput = 255;
int LeftInput = 255;
int rightSpeed = RightInput;
int leftSpeed = LeftInput;


void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Sets Right Motor speeds
  if (rightSpeed > 0){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    analogWrite(enA, rightSpeed);
    }
   else if (rightSpeed < 0){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(enA, -rightSpeed);
    }
    else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      analogWrite(enA, 0);
      }

  //Sets left motor speeds
  if (leftSpeed > 0){
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(enB, rightSpeed);
    }
   else if (leftSpeed < 0){
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enB, -rightSpeed);
    }
    else {
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(enB, 0);
      }
  
}
