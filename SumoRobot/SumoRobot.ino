#include <Ultrasonic.h> //Biblioteca para trabalhar com o sensor ultrassônico

#define TRIGGER 13 //Trigger do sensor de distância ultrassônico
#define ECHO 12 //Echo do sensor de distância ultrassônico
#define INFRA_DIR 1 //Sensor infravermelho
#define INFRA_ESQ 2 //Sensor infravermelho

#define M1_F 10 //Pino para o movimento de avanço do motor direito
#define M1_A 9 //Pino para o movimento de retrocesso do motor direito
#define M2_F 6 //Pino para o movimento de avanço do motor esquerdo
#define M2_A 5 //Pino para o movimento de retrocesso do motor esquerdo

#define TVOLTA0 2100 //Tempo de uma volta completa com uma roda em movimento e 100% de duty cycle e outra em 50% de duty cycle em relação ao duty cycle de 255
#define COR_BORDA 'b' //Cor da borda, 'b' para branca e 'p' para preta
#define DCMAX 255 //pwm máximo do ataque e referência para os demais
#define DISTMAX 10//distância máxima na varredura em cm

unsigned long int TEMPOVOLTA = (255/DCMAX)*TVOLTA0;

Ultrasonic ultrasonic(TRIGGER, ECHO); //declaração dos pinos de trigger e echo


void setup() {
  // put your setup code here, to run once:

  //Definição dos pinos
  
  //pinMode(ECHO, INPUT);
  pinMode(INFRA_DIR, INPUT);
  pinMode(INFRA_ESQ, INPUT);
  
  //pinMode(TRIGGER, OUTPUT);
  pinMode(M1_F, OUTPUT);
  pinMode(M1_A, OUTPUT);
  pinMode(M2_F, OUTPUT);
  pinMode(M2_A, OUTPUT);

  delay(5000); //Tempo para que o robô comece a operar após ser ligado pelo usuário, como definido pelas regras da competição
  
  }

void loop() {
  // put your main code here, to run repeatedly:

atacar();

if(detectar_borda(COR_BORDA))
{  
  frear();
  andar('r', 500, DCMAX);
  varredura();
}
  
} //Fim do Loop


//Funções de combate

void atacar()
{
    analogWrite(M1_F, DCMAX);
    analogWrite(M1_A, 0);
    analogWrite(M2_F, DCMAX);
    analogWrite(M1_A, 0);
}

void varredura ()
{

   analogWrite(M1_A, DCMAX);
   analogWrite(M1_F, 0);
   analogWrite(M2_F, DCMAX);
   analogWrite(M2_A, 0);

   delay(0.2*TEMPOVOLTA);
   
   float distancia;
   long int tsom = ultrasonic.timing();
   unsigned long int t0 = micros();

   while( (micros() -t0) < (0.4*TEMPOVOLTA))   
   {
    distancia = ultrasonic.convert(tsom, Ultrasonic::CM);
    
    if( distancia < DISTMAX )
     {
      atacar(); 
      break;
     }
   }
   
   atacar();
}


//Funções de movimento

void andar(char sentido, int tempo, int dutycycle)
{
  //'f' --> para frente, 'r' -->de ré
  // duty cycle: 0-->0%, 127 -->50% e 255 -->100%
  //tempo em milisegundos
  if(sentido == 'f')
  {
    digitalWrite(M1_A, LOW);
    digitalWrite(M2_A, LOW);
    analogWrite(M1_F, dutycycle);
    analogWrite(M2_F, dutycycle);
  }
  else if(sentido == 'r')
  {
    digitalWrite(M1_F, LOW);
    digitalWrite(M2_F, LOW);
    analogWrite(M1_A, dutycycle);
    analogWrite(M2_A, dutycycle);
  }
 delay(tempo);
}

void virar(int tempo, int dc1f, int dc1a, int dc2f, int dc2a)
{
  //dc1f é para M1_F, dc1a é para M1_A, dc2f é para M2_F e dc2a é para M2_A, duty cycle: 0-->0%, 127 -->50% e 255 -->100%
  //tempo em milisegundos
    analogWrite(M1_F, dc1f);
    analogWrite(M2_F, dc2f);
    analogWrite(M1_A, dc1a);
    analogWrite(M2_A, dc2a);
delay(tempo);
}

void frear()
{
    digitalWrite(M1_F, LOW);
    digitalWrite(M2_F, LOW);
    digitalWrite(M1_A, HIGH);
    digitalWrite(M2_A, HIGH);
    delay(200);
    digitalWrite(M1_F, LOW);
    digitalWrite(M2_F, LOW);
    digitalWrite(M1_A, LOW);
    digitalWrite(M2_A, LOW);
    
}


//Funções dos sensores

bool detectar_borda(char borda)
{
  //retorna 0 para o robô ainda na arena, 'a' para ambos os sensores na borda branca, 'd' para apenas o direito e 'e' para apenas o esquerdo
  bool reflexo_dir = digitalRead(INFRA_DIR);
  bool reflexo_esq = digitalRead(INFRA_ESQ);
  if(borda == 'b')
  {
    if( reflexo_dir == false && reflexo_esq == false)
    {
      return true;
    }
    else
    {
       return false;
    }
  }

  if(borda == 'p')
  {    
    if( reflexo_dir == true && reflexo_esq == true)
    {
      return true;
    }
    else
    {
       return false;
    }  
  }
  
}
