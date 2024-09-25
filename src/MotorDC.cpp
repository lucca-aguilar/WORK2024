#include "MotorDC.h"
#include "Arduino.h"
#include "Wire.h"
#include "Tempo.h"

//* Esse arquivo contém a implementação da classe MotorDC, que é responsável por controlar o motor DC do robô
//* e fornecer os valores de velocidade e direção de giro do motor

// MotorDC* MotorDC::instance = nullptr;/

// Construtor da classe MotorDC
MotorDC::MotorDC(const int ENCA, const int ENCB, const int PWM, const int IN1, const int IN2)
{
  this->ENCA = ENCA;
  this->ENCB = ENCB;
  this->PWM = PWM;
  this->IN1 = IN1;
  this->IN2 = IN2;
  pinMode(ENCA, INPUT);
  pinMode(PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  // instance = this;
}

void MotorDC::configurar(int ticks_por_volta, float kp, float ki, float kd)
{
  this -> encoder_volta = ticks_por_volta;
  this -> kp = kp;
  this -> ki = ki;
  this -> kd = kd;
}

// Função para ligar o motor e definir a direção e a velocidade
void MotorDC::ligar_motor(int direcao, int pwmVal)
{

  dir = direcao;
  analogWrite(PWM, pwmVal); // (pino do pwm, valor do pwm (máximo = 255))
  if (dir == 1)
  { // 1 para frente
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else if (dir == -1)
  { // -1 para trás
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
  else
  { // 0 para parar
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
  }
}

// Função para ler o encoder do motor
void MotorDC::ler_encoder()
{
  posi += dir;
}

// Função para resetar o encoder do motor
void MotorDC::resetar_encoder()
{
  posi = 0;
  eprev = 0;
  eintegral = 0;
  voltas = 0;
  voltas_anterior = 0;
}

void MotorDC::andar_reto(int velocidade_rpm)
{

  rpm_referencia = velocidade_rpm; // Velocidade de referência

  volatile double posi_atual = 0;      // posição atual do encoder
  noInterrupts();              // desabilita interrupções
  posi_atual = posi;          // atualiza a posição atual do encoder
  interrupts();               // reabilita interrupções

  voltas_anterior = voltas; // atualiza o número de voltas anterior

  voltas = posi_atual / encoder_volta;            // calcula o número de voltas do motor
  rps = (voltas - voltas_anterior) / dt; // calcula a velocidade do motor em rps

  double e = rpm_referencia - (rps * 60); // calcula o erro da velocidade em rpm

  float p = kp * e;

  eintegral += e * dt;

  float i = ki * eintegral;

  float d = kd * ((e - eprev) / dt);

  float u = p + i + d; //p + (ki * eintegral*dt) + d;

  float pwmVal = fabs(u); // valor do pwm que será enviado ao motor

  if (pwmVal > 255) // Limita o valor do pwm para 255
  {
    pwmVal = 255;
  }

  // Define a direção do motor com base no valor de u
  if (u > 0)
  {
    dir = 1;
  }
  else if (u < 0)
  {
    dir = -1;
  }
  else
  {
    dir = 0;
  }

  if (velocidade_rpm != 0) {
    ligar_motor(dir, pwmVal);
  } else {
    ligar_motor(0, 0);
  }


  eprev = e;
  
}