#include <Servo.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial sim(14, 15);//tx //rx
int _timeout;
String _buffer;
String number = "+8801682343293";
Servo myservo11;
Servo myservo12;
Servo myservo21; 
Servo myservo22;
int pos = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//lcd+soner
LiquidCrystal lcd2(22, 23, 24, 25, 26, 27); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
const int trigPin = A8;
const int echoPin = A9;

const int trigPin1 = A10;
const int echoPin1 = A11;
long duration1;
float distanceCm1;

long duration2;
float distanceCm2;

////////////////

int analogPin = A0;
int moisture;
int percentage;

int map_low = 350;
int map_high = 200;

int ena =10;
int in1 =9;
int in2 =8;

int period = 1000;
unsigned long time_now=0;

void motorOff();
void motorOn();
void Vupdate();
void sonar();

void setup() {
  lcd.begin(16, 2);
  pinMode (ena, OUTPUT);
  pinMode (in1, OUTPUT);
  pinMode (in2, OUTPUT);
  myservo11.attach(7);
  myservo12.attach(28);
  myservo21.attach(30);
  myservo22.attach(31);
////lcd+soner
lcd2.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);

/////////////
  
  Serial.begin(9600);
   myservo11.write(0);
   myservo12.write(0);
   myservo21.write(0);
   myservo22.write(0);






  
}

 
void loop() {
  // put your main code here, to run repeatedly:
  Vupdate();
int  p=40;
int  q=45;

  if (percentage<35)
{
  Vupdate();
   motor_On_D();
   motor_On();
   
   if(distanceCm1*10 > p)
   {     
        myservo11.write(90);
   }
   if(distanceCm2*10 > p)
   {
   myservo12.write(90);
   }     
}
else
{
   Vupdate();
   myservo12.write(0);
   myservo11.write(0);
   motor_On_D();
   
}
//delay(5000);
   if(distanceCm1*10 <= p )
      {
       myservo11.write(0);
      }
   if(distanceCm2*10 <= p )
        {
           myservo12.write(0);            
        }
   if(distanceCm1*10 <= p &&distanceCm1*10 >= q && distanceCm2*10 <= p &&distanceCm2*10 >= q)
       {
           motor_Off();
           motor_Off_D();
           delay(10000);
       }
          
   if(distanceCm1*10 < 45)
   {     
        myservo21.write(90);
   }
   else
    {     
        myservo21.write(0);
   }
   if(distanceCm2*10 < 45)
   {
   myservo22.write(90);
   }  
     else
    {     
        myservo22.write(0);
   }  
        
}
 void motor_Off_D() // disp
{
   lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MOTOR OFF");
      lcd.setCursor(0,1);
      lcd.print("Percentage :");
      lcd.print(percentage);
      lcd.print("%");
}

void motor_On_D() //disp
{
   lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MOTOR ON");
      lcd.setCursor(0,1);
      lcd.print("Percentage :");
      lcd.print(percentage);
      lcd.print("%");
}

void Vupdate()
{
  moisture = analogRead(analogPin);
  Serial.print("Raw: ");
  Serial.print(moisture);
  percentage = map(moisture, map_low, map_high, 0, 100);
  Serial.print(" | Percentage: ");
  Serial.print(percentage);
  Serial.println("%");
  //delay(50);
  sonar();

}
void sonar()
{
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin1, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin, HIGH);
duration2 = pulseIn(echoPin1, HIGH);
distanceCm1= duration1*0.034/2;
distanceCm2= duration2*0.034/2;
lcd2.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
lcd2.print("Distance1: "); // Prints string "Distance" on the LCD
lcd2.print(distanceCm1*10); // Prints the distance value from the sensor
lcd2.print(" cm");
lcd2.setCursor(0,1); // Sets the location at which subsequent text written to the LCD will be displayed
lcd2.print("Distance2: "); // Prints string "Distance" on the LCD
lcd2.print(distanceCm2*10); // Prints the distance value from the sensor
lcd2.print(" cm");
//delay(10);

//Serial.println(distanceCm*10);
//delay(100);
/*if (distanceCm*10 >= 5.00)
    { 
        myservo.write(0);
    }
    else
    {
        myservo.write(180);
    }*/

}
void motor_On()
{
  //turns on motor
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(ena, 200);
}
void motor_Off()
{
  //turns on motor
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(ena, 0);
}



  
