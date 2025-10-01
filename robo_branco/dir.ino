void parar() {
    MihuCore::setMotorPin(M1, 0);
    MihuCore::setMotorPin(M2, 0);
  } 

  void tras(int vel, float tempo) {
    MihuCore::setMotorPin(M1, vel);
    MihuCore::setMotorPin(M2, vel);
   delay(tempo);
  } 

   void frente(int vel, float tempo) {
    MihuCore::setMotorPin(M1, -vel);
    MihuCore::setMotorPin(M2, -vel);
   delay(tempo);
  } 

     void frente_sempre(int vel) {
    MihuCore::setMotorPin(M1, -vel);
    MihuCore::setMotorPin(M2, vel);
  } 

   void esq(int vel, float tempo) {
    MihuCore::setMotorPin(M1, vel);
    MihuCore::setMotorPin(M2, -vel);
   delay(tempo);
  } 
void dir(int velInicial, float tempo) {
  unsigned long tempoInicial = millis();          // Marca o início
  unsigned long tempoAtual;
  float duracao = tempo;                          // tempo total em milissegundos
  int velAtual;

  while ((tempoAtual = millis() - tempoInicial) < duracao) {
    // Calcula a velocidade diminuindo linearmente com o tempo
    float fator = 1.0 - (float)tempoAtual / duracao; // de 1 até 0
    velAtual = velInicial * fator;

    // Aplica a velocidade atual aos motores
    MihuCore::setMotorPin(M1, velAtual);
    MihuCore::setMotorPin(M2, -velAtual);

    delay(10);  // pequeno atraso para evitar travamento da CPU
  }

  // Para o motor ao final do tempo
  MihuCore::setMotorPin(M1, 0);
  MihuCore::setMotorPin(M2, 0);
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
    MihuCore::setServo(girar_esq, 180);
  delay(1000);
  MihuCore::setServo(braco_esq, 150); //BRACO LEVANTADO
  delay(2000);
  // MihuCore::setServo(braco_esq, 130); //BRACO LEVANTADO
  // delay(500);
}

void voltar_dir() {
  MihuCore::setServo(ombro_dir, 10);
MihuCore::setServo(braco_dir, 80);//RETO PRA BAIXO
  delay(1500);
}

void voltar_esq() {
  MihuCore::setServo(ombro_esq, 170);
MihuCore::setServo(braco_esq, 80);
delay(1500);
}

void peito_dir() { 
  MihuCore::setServo(ombro_dir, 80);
  delay(1500);
    MihuCore::setServo(girar_dir, 20);
  delay(1000);
  MihuCore::setServo(braco_dir, 170);
  delay(2000);
  //MihuCore::setServo(braco_dir, 80);
  //delay(500);
}

void dois_peitos() {
  MihuCore::setServo(ombro_dir, 110);
  MihuCore::setServo(ombro_esq, 80);
  delay(1500);
    MihuCore::setServo(ombro_dir, 20);
    MihuCore::setServo(girar_esq, 180);
  delay(1500);
  MihuCore::setServo(braco_dir, 170);
  MihuCore::setServo(braco_esq, 80);
  delay(500);
  MihuCore::setServo(braco_dir, 90);
  MihuCore::setServo(braco_esq, 160);
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

void bater_tambor() {
   MihuCore::setServo(ombro_esq, 130);
  MihuCore::setServo(ombro_dir, 70);
  delay(1500);
  MihuCore::setServo(girar_esq, 180);
  MihuCore::setServo(girar_dir, 20);
  delay(700);
    MihuCore::setServo(girar_esq, 130);
    MihuCore::setServo(girar_dir, 80);
  delay(700);
  MihuCore::setServo(braco_esq, 130); //BRACO LEVANTADO
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
  MihuCore::setServo(braco_esq, 150);
  delay(500);
  MihuCore::setServo(braco_dir, 80);
  MihuCore::setServo(braco_esq, 80);
  delay(1000);
  MihuCore::setServo(braco_dir, 130);
  MihuCore::setServo(braco_esq, 50);
  delay(500);
}