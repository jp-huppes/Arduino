// Here we go again....
int led = 3;
int ldr = A0;
int valorldr = 0;
const int sensorPin = A1;
const int Trig = 5;
const int Echo = 4;
float valorSensor, temperaturaC;
float duracao, distancia;

void setup(){
  pinMode(led, OUTPUT);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  Serial.begin(9600);
  Serial.println(valorldr);
  delay(1000);
}
void loop(){
  int ativador = 0;
  //caso 1 -- Luz o-o
  valorldr = analogRead(ldr);
  if (valorldr < 400){
    ativador += 1;
  }
  
  // caso 2 -- temperatura (ui frio)
  valorSensor = analogRead(sensorPin);
  temperaturaC = ((valorSensor / 1023) * 5) - 0.5;
  temperaturaC = temperaturaC * 100;
  delay(1000);
  if (temperaturaC < 25) {
    ativador += 1;
  }
  
  // caso 3 -- tem alguem ai?
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  duracao = pulseIn(Echo, HIGH);
  if (duracao < 19000) { 
    distancia = duracao / 58;
    if (distancia <= 150) {
      ativador += 1;  
    }
  }
  Serial.println(ativador);
  // HAJA LUZ... ou nao
  if (ativador == 3) { // Vê se todas as condições acontecem, se sim, liga.
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  
  delay(100);
}
