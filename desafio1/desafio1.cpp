const int pino_vermelho = 2; //Semaforo Vermelho para os carros, verde para os pedestres
const int pino_amarelo = 3; // Semaforo Amarelo para os carros
const int pino_verde = 4; // Semaforo Verde para os carros
const int pino_laranja = 5; // Semaforo Vermelho para os pedestres

void setup()
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
}

void loop()
{
  digitalWrite(5,LOW); // Desliga o LED vermelho para pedestre
  digitalWrite(3,LOW); // Desliga o LED amarelo
  digitalWrite(4,HIGH); // Liga o LED vermelho e o LED verde para pedestre
  delay(10000); // O Semaforo fica "fechado", ou seja com LED vermelho e verde, por 10 segundos
  digitalWrite(4,LOW); // Desliga o LED vermelho
  digitalWrite(2,HIGH); // Liga o LED verde 
  digitalWrite(5,HIGH); //Liga o LED vermelho para pedestre
  delay(10000); // O Semaforo fica "aberto", ou seja com LED verde, por 10 segundos
  digitalWrite(2,LOW); // Desliga o LED verde
  digitalWrite(3,HIGH); // Liga o LED amarelo
  delay(3000); // A transição, ou estado de "atenção", ocorre em 3 segundos, ou seja LED amarelo ligado.
}
