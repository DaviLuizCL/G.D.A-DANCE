
#include <Servo.h>

Servo tampa;
Servo tampa2;

Servo braco_esq;
Servo braco_dir;

int pin_prox = 8; 
int prox = 0;   

const int rele = 4;

void setup() {

  pinMode(rele, OUTPUT);
  digitalWrite(rele, HIGH);

  pinMode(pin_prox, INPUT);
  
  tampa.attach(9);
  tampa2.attach(10); 
  
  braco_esq.attach(7);
  braco_dir.attach(6);

  braco_esq.write(0);
  braco_dir.write(130);
  delay(200);

  
  tampa.write(35);   
  tampa2.write(35); 
  delay(1000);
}

void loop() {

  prox = digitalRead(pin_prox);

  if(prox == LOW){

    tampa.write(130);
    tampa2.write(130);
    delay(2000);

    braco_esq.write(60);
    braco_dir.write(60);
    delay(1500);

    for(int x = 0; x < 11; x++) {
      digitalWrite(rele, LOW);
      delay(42);
      digitalWrite(rele, HIGH);
      delay(100);
    }
    digitalWrite(rele, HIGH);
    delay(100);

    while(1){
      braco_esq.write(135);
      braco_dir.write(20);
      delay(1000);
      braco_esq.write(60);
      braco_dir.write(60);
      delay(1000);
      braco_esq.write(60);
      braco_dir.write(130);
      delay(1000);
      

    }


  }

  /*
//myservo.write(150);   
  //  myservo2.write(150); 
    //delay(5000);
braco_esq.write(130);
braco_dir.write(130);
delay(200);

//for(int x = 0; x < 11; x++) {
  //digitalWrite(rele, LOW);
  //delay(42);
  //digitalWrite(rele, HIGH);
  //delay(100);
//}
    

    
              // tell servo to go to position in variable 'pos' */
}
