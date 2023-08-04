#include <Arduino.h>
#include <Servo.h>
Servo servo_left;
Servo servo_right;
Servo servo_center;
Servo servo_kep;
bool toggle = 1;
byte goc_left;
byte goc_right;
byte goc_center;
byte goc_kep;

#define servoleft    12
#define servoright   13
#define servocenter  8
#define servokep     2


int IN1 = 5; //IN1 L298N
int IN2 = 6; //IN2 L298N
int IN3 = 9; //IN3 L298N
int IN4 = 11;//IN4 L298N

#define Toc_do HIGH
#define aa0 LOW
//int Toc_do = 200; // Toc do dong co (0-255)
void setup() {
  Serial.begin(9600); //Chuan ket noi bluetooth
  pinMode(IN1, OUTPUT); // Xuat ra ouput vao L298N
  pinMode(IN2, OUTPUT); // Xuat ra ouput vao L298N
  pinMode(IN3, OUTPUT); // Xuat ra ouput vao L298N
  pinMode(IN4, OUTPUT); // Xuat ra ouput vao L298N

  servo_left.attach(servoleft); 
  servo_right.attach(servoright);
  servo_center.attach(servocenter);
  servo_kep.attach(servokep); 
  
  auto_home();

}
int flagg; 
//char* flagg = "S";
char flag = 'S';
void loop() {
  if (Serial.available())
  {
    flagg = Serial.read();
    Serial.println(flagg);  
    flag = (char)flagg;
    Serial.println(flag);  
    
  }
//  Serial.println("aaa");
  if (flag == 'L') { //re trai
    digitalWrite(IN4, Toc_do);
    digitalWrite(IN2, aa0);
    digitalWrite(IN3, aa0);
    digitalWrite(IN1, Toc_do);
  }
  if (flag == 'R') { //re phai
    digitalWrite(IN4, aa0);
    digitalWrite(IN2, Toc_do);
    digitalWrite(IN3, Toc_do);
    digitalWrite(IN1, aa0);
  }
  if (flag == 'S') { //Dung
    digitalWrite(IN4, aa0);
    digitalWrite(IN2, aa0);
    digitalWrite(IN3, aa0);
    digitalWrite(IN1, aa0);
  }
  if (flag == 'F') { //chay thuan
    digitalWrite(IN4, Toc_do);
    digitalWrite(IN2, Toc_do);
    digitalWrite(IN3, aa0);
    digitalWrite(IN1, aa0);
  }

  if (flag == 'B') { //Chay nguoc  
    digitalWrite(IN4, aa0);
    digitalWrite(IN2, aa0);
    digitalWrite(IN3, Toc_do);
    digitalWrite(IN1, Toc_do);
  }

  left();
  right();
  center();
  control_kep();
  gohome();
}



void auto_home()
{
  servo_left.write(70); //70 - 150
  servo_right.write(90);  //30-180
  servo_center.write(80); //
  servo_kep.write(130); // 30-130
}

void gohome(){
  if(flag == '7')
  {
     auto_home();
  }  
}

void left()
{ 
  goc_left = servo_left.read();
  if(flag == '1') //Nut A
  {
    if(goc_left < 150)
    {
      goc_left = goc_left + 1;
      servo_left.write(goc_left);
      delay(10);
    }
    else  servo_left.write(150);
  }

  if(flag == '2') //Nut C
  {
    if(goc_left > 70)
    {
      goc_left = goc_left - 1;
      servo_left.write(goc_left);
      delay(10);
    }
    else  servo_left.write(70);
  }  

//  Serial.print(" - left: "); Serial.print(servo_left.read());
} 

void right()
{ 
  goc_right = servo_right.read();
  if(flag == '3') //Nut C
  {
    if(goc_right < 180)
    {
      goc_right = goc_right + 1; 
      servo_right.write(goc_right);
      delay(10);
    }
    else  servo_right.write(180);
  }

  if(flag == '4') //Nut D
  {
    if(goc_right > 90)
    {
      goc_right = goc_right - 1;
      servo_right.write(goc_right);
      delay(10);
    }
    else  servo_right.write(90);
  }  

//  Serial.print(" - right: "); Serial.print(servo_right.read());
} 

void center()
{ 
  goc_center = servo_center.read();
  if(flag == '5') //Nut C
  {
    if(goc_center < 180)
    {
      goc_center = goc_center + 1; 
      servo_center.write(goc_center);
      delay(10);
    }
    else  servo_center.write(180);
  }

  if(flag == '6') //Nut D
  {
    if(goc_center > 1)
    {
      goc_center = goc_center - 1;
      servo_center.write(goc_center);
      delay(10);
    }
    else  servo_center.write(1);
  }  

//  Serial.print(" - center: "); Serial.print(servo_center.read());
} 

void control_kep(){ 
  goc_kep = servo_kep.read(); 
  if(flag == '8'){ 
    if(goc_kep < 180)
    {
      goc_kep = goc_kep + 1; 
      servo_kep.write(goc_kep);
      delay(10);
    }
    else  servo_kep.write(180);
  }
  if(flag == '9') //Nut D
  {
    if(goc_kep > 1)
    {
      goc_kep = goc_kep - 1;
      servo_kep.write(goc_kep);
      delay(10);
    }
    else  servo_kep.write(1);
  }  
}

//void control_kep(){ 
//  goc_kep = servo_kep.read(); 
//  if(flag == '8'){ 
//    if(toggle){
//      goc_kep = goc_kep + 1;
//      toggle = 0;
//      return;
//    }
//    else {
//      servo_kep.write(100);
//      delay(50);
//      servo_kep.write(90);
//      delay(50);
//      servo_kep.write(30);
//      toggle = 1;
//      return;
//    }
//    while(flag == '8'){}
//  }
//}
