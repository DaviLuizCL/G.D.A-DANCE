void parar() {
    MihuCore::setMotorPin(M1, 0);
    MihuCore::setMotorPin(M2, 0);
  } 

  void frente(int vel, float tempo) {
    MihuCore::setMotorPin(M1, vel);
    MihuCore::setMotorPin(M2, vel);
   delay(tempo);
  } 

   void tras(int vel, float tempo) {
    MihuCore::setMotorPin(M1, -vel);
    MihuCore::setMotorPin(M2, -vel);
   delay(tempo);
  } 

     void frente_sempre(int vel) {
    MihuCore::setMotorPin(M1, vel);
    MihuCore::setMotorPin(M2, vel);
  } 


void dir(int vel, float tempo) { 
    MihuCore::setMotorPin(M1, vel);
    MihuCore::setMotorPin(M2, -vel);
   delay(tempo);
}

void esq(int vel, float tempo) { 
    MihuCore::setMotorPin(M1, -vel);
    MihuCore::setMotorPin(M2, vel);
   delay(tempo);
}

void articular_cotovelo() { 
  MihuCore::setServo(braco_esq, 120);
  delay(1500);
  MihuCore::setServo(braco_esq, 80); //COTOVELO_RETO
  delay(1500);
}

void peito_esq() { 
  MihuCore::setServo(ombro_esq, 80);
  delay(1500);
    MihuCore::setServo(girar_esq, 150);
  delay(1000);
  MihuCore::setServo(braco_esq, 60); //BRACO LEVANTADO
  delay(500);
  // MihuCore::setServo(braco_esq, 100); //BRACO LEVANTADO
  // delay(500);
}

void voltar_esq() {
    MihuCore::setServo(ombro_esq, 170);//RETO PRA BAIXO
  MihuCore::setServo(braco_esq, 105);//RETO PRA BAIXO
    MihuCore::setServo(girar_esq, 80);
  delay(1500);
}

void voltar_dir() {
  MihuCore::setServo(ombro_dir, 10);//RETO PRA BAIXO
  MihuCore::setServo(braco_dir, 80);//RETO PRA BAIXO
    MihuCore::setServo(girar_dir, 80);
  delay(1500);
}


void peito_dir() { 
  MihuCore::setServo(ombro_dir, 80);
  delay(1500);
    MihuCore::setServo(girar_dir, 20);
  delay(1000);
  MihuCore::setServo(braco_dir, 160);
  delay(500);
  // MihuCore::setServo(braco_dir, 160);
  // delay(500);
}

void dois_peitos() {
  MihuCore::setServo(ombro_dir, 80);
  MihuCore::setServo(ombro_esq, 80);
  delay(1500);
  MihuCore::setServo(girar_dir, 20);
  MihuCore::setServo(girar_esq, 180);
  delay(1500);
   MihuCore::setServo(braco_dir, 80);
   MihuCore::setServo(braco_esq, 60);
  delay(500);
  MihuCore::setServo(braco_dir, 160);
  MihuCore::setServo(braco_esq, 100);
  delay(500);
  }

void CimaBaixo_dir() {
    MihuCore::setServo(ombro_dir, 80);
  MihuCore::setServo(girar_dir, 90);
  delay(1500);
  MihuCore::setServo(braco_dir, 170);
  delay(500);
  MihuCore::setServo(braco_dir, 90);
  delay(500);
}

void CimaBaixo_esq() { // martelo 
      MihuCore::setServo(ombro_esq, 80);
    MihuCore::setServo(girar_esq, 90);
  delay(1500);
  MihuCore::setServo(braco_esq, 80); //BRACO LEVANTADO
  delay(1000);
  MihuCore::setServo(braco_esq, 130); //BRACO LEVANTADO
  delay(1000);
}

void levantar_bracos() {

      MihuCore::setServo(ombro_esq, 80);
    MihuCore::setServo(girar_esq, 90);
     MihuCore::setServo(ombro_dir, 80);
  MihuCore::setServo(girar_dir, 90);
  delay(1500);
  MihuCore::setServo(braco_esq, 80); 
  MihuCore::setServo(braco_dir, 170);
  delay(500);
  MihuCore::setServo(braco_esq, 130);
    MihuCore::setServo(braco_dir, 90);
  delay(500);
}

void bater_tambor(){
MihuCore::setServo(ombro_esq, 120);
  MihuCore::setServo(ombro_dir, 60);
  delay(1500);
  MihuCore::setServo(girar_esq, 130);
  MihuCore::setServo(girar_dir, 20);
  delay(700);
    MihuCore::setServo(girar_esq, 80);
    MihuCore::setServo(girar_dir, 80);
  delay(700);
  MihuCore::setServo(braco_esq, 60); //BRACO LEVANTADO
    MihuCore::setServo(braco_dir, 130); //BRACO LEVANTADo
  delay(500);
  }

unsigned long tempoAnterior = 0;
bool animacaoAtiva = false;

void danca_criminal() {
animacaoAtiva = true;
 if(recebido == "S"|| recebido == "s"){
      // depois de 1500ms, pode continuar
      peito_dir();
      peito_esq();
      voltar_dir();
      voltar_esq();

      animacaoAtiva = false; // terminou a dança
    }

  if (animacaoAtiva) {
    unsigned long agora = millis();

    if (agora - tempoAnterior < 1500) {
      // primeira parte da animação
      MihuCore::setServo(ombro_esq, 170);
      MihuCore::setServo(ombro_dir, 10);
      MihuCore::setServo(braco_esq, 80);
      MihuCore::setServo(braco_dir, 80);
      MihuCore::setServo(girar_dir, 80);
      MihuCore::setServo(girar_esq, 80);
    } 
  }
}

void danca_thriller() {
    MihuCore::setServo(ombro_esq, 50);
  MihuCore::setServo(ombro_dir, 130);
  delay(1500);
  MihuCore::setServo(girar_dir, 20);
  MihuCore::setServo(girar_esq, 150);
  delay(1500);
  MihuCore::setServo(braco_dir, 50);
  MihuCore::setServo(braco_esq, 50);
  delay(500);
  MihuCore::setServo(braco_dir, 80); //RETO
  MihuCore::setServo(braco_esq, 105); //RETO
  delay(1000);
  MihuCore::setServo(braco_dir, 130);
  MihuCore::setServo(braco_esq, 130);
  delay(500);
}