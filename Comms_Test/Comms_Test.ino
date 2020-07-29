
int number = 0;
int value;
bool working;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("The Number Is:");
  Serial.println(number);

  delay(500);
  number++;

  if (Serial.available()) {
    working = true;
    value = 0;
    while (working){
      char ch = Serial.read();
      if (ch >= '0' && ch <= '9') {
        value = (value * 10) + (ch - '0');
        } 
        else if (ch == 10) {
          number = value;
          working = false;
          Serial.print("Going to: ");
          Serial.println(number);
          delay(250);
        }
      }
    }
  
}
