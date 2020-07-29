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

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available()) {
    Serial.println("Reciving!");
    reciving = true;
    value = 0;
    LeftPos = true;
    RightPos = true;
    
    while (reciving) {
      char ch = Serial.read();
      
      if (ch >= '0' && ch <= '9') {
        value = (value * 10) + (ch - '0');
        }
        
      else if (ch == '-') {
      LeftPos = false;
      }
      
      else if (ch == ' ') {
        Serial.println(value);
        Serial.println(LeftPos);
        if (LeftPos) {
          leftSpeed = value;
          }
        else {
            leftSpeed = -value;
            }
        Serial.println(leftSpeed);   
        value = 0;
        while (reciving) {
          char ch = Serial.read();
          
          if (ch >= '0' && ch <= '9') {
            value = (value * 10) + (ch - '0');
            }
          else if (ch == '-') {
            RightPos = false;
            }
          else if (ch == 10) {
            Serial.println(value);
            Serial.println(RightPos);
            if (RightPos) {
              rightSpeed = value;
              }
            else {
              rightSpeed = -value;
              }
              Serial.println(rightSpeed);
              reciving = false;
            }
          }
        }
      }
    }

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
