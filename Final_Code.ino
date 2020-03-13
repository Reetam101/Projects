#include <Servo.h>
Servo myservo;
Servo myservo2;
int flame_detected;
int flame_sensor = 6;
int relay = 13;
int ENA = 3;
int IN1 = 2;
int IN2 = 4;
int ENB = 5;
int IN3 = 7;
int IN4 = 8;
const int trigPin = 12;
const int echoPin = 11 ;
int distance;
int duration;
int distanceR, distanceL;
void setup()
{
  Serial.begin(9600);
  pinMode(flame_sensor, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  myservo.attach(9);
  myservo2.attach(10);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
}

void loop()
{
  flame_detected = digitalRead(flame_sensor);
  Serial.println(flame_detected);
  //delay(1000);
  myservo.write(90);
  if (flame_detected == 0)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(relay, LOW);
    stopmotor();
    spraywater();
    delay(100); 
    
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    //delay(200);
    digitalWrite(relay, HIGH);
    runmotor();
    myservo.write(90);
    distance = finddistance();
    if(distance <= 25)
    {
      stopmotor();
      distanceR = lookRight();
      distanceL = lookLeft();
      if(distanceR > distanceL)
      {
        moveright();
        stopmotor();
      }
      else if(distanceR < distanceL)
      {
        moveleft();
        stopmotor();
        //delay(200);
      }
      else
      {
        rotate();
        stopmotor();
      }
    }
    Serial.println(distance);
    //delay(200);
  }
  //delay(1000);
}

void runmotor(){
  digitalWrite(IN1, HIGH); // Turn HIGH motor A
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255);
  digitalWrite(IN3, HIGH); // turn HIGH motor B
  digitalWrite(IN4, LOW);  // To set the turning speed to 200 out of possible range 0 to 255
  analogWrite(ENB, 255); 
  delay(100);
}
void stopmotor()
{
  digitalWrite(IN1, HIGH); // Turn HIGH motor A
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); // turn HIGH motor B
  digitalWrite(IN4, HIGH);  // To set the turning speed to 200 out of possible range 0 to 255 
  delay(500); 
}

int finddistance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    return distance;
}
int lookRight()
{
    myservo.write(0);
    delay(500);
    int d = finddistance();
    delay(100);
    myservo.write(90); 
    return d;
}

int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int d = finddistance();
    delay(100);
    myservo.write(90); 
    return d;
}

void moveright(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); 
    analogWrite(ENB, 255);
    delay(1000);
  }
  void moveleft(){
    digitalWrite(IN1, HIGH); // Turn HIGH motor A
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);
    digitalWrite(IN3, LOW); // turn HIGH motor B
    digitalWrite(IN4, LOW);  // To set the turning speed to 200 out of possible range 0 to 255
    delay(1000); 
  }
  void rotate()
  {
    digitalWrite(IN1, HIGH); // Turn HIGH motor A
    digitalWrite(IN2, LOW);
    analogWrite(ENA, 255);
    digitalWrite(IN3, LOW); // turn HIGH motor B
    digitalWrite(IN4, LOW);  // To set the turning speed to 200 out of possible range 0 to 255
    delay(2000); 
  }
  void spraywater()
  {
    myservo2.write(90);
    delay(50);
    myservo2.write(180);
    delay(50);
    myservo2.write(90);
    delay(50);
    myservo2.write(0);
    delay(50);
  }
