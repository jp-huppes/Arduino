const int interruptor = 8; //Define a porta do interruptor 
const int LED = 7; //Define a porta do LED
  
void setup(){
  pinMode(interruptor, INPUT);
  pinMode(LED, OUTPUT);
}

void loop(){
  if(digitalRead(interruptor) == HIGH){ //Faz com que o sistema somente reaja ao clique do botão.
    digitalWrite(LED, !digitalRead(LED)); // Alterna o estado do LED quando o botão é pressionado.
    delay(200); // Debounce.
  }
}
