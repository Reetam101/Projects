/* Arduino based Bluetooth controlled car. 
Bluetooth module = HC05, L293D motor driver, Arduino UNO */
int IN1 = 8;
int IN2 = 12;
int IN3 = 7;
int IN4 = 4;
char btVal;
void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  while(Serial.available()>0)
  {
    btVal = Serial.read();
    Serial.print("BlueTooth Value ");
    Serial.println(btVal);
    if(btVal == 'F')
    {
      forward();
    }
    if(btVal == 'B')
    {
      backward();
    }
    if(btVal == 'L')
    {
      left();
    }
    if(btVal == 'R')
    {
      right();
    }
    if(btVal == 'S')
    {
      stop();
    }
  }
}

void forward()
{
  digitalWrite(IN1, HIGH); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); 
  digitalWrite(IN4, LOW);
  delay(100);
}
void backward()
{
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); 
  digitalWrite(IN4, HIGH);
  delay(500);
}

void left()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(100);
}

void right()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}

void stop()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  delay(100);
}
