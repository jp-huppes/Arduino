#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <string.h>
//Keypad e LCD
const byte numLinhas = 4;
const byte numColunas = 4;
byte linhas[numLinhas] = {11, 10, 9, 8};
byte colunas[numColunas] = {7, 6, 5, 4};
char teclas[numLinhas][numColunas] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
Keypad teclado = Keypad(makeKeymap(teclas), linhas, colunas, numLinhas,numColunas);
const byte MAX_CARACTERES = 5;
LiquidCrystal_I2C lcd(0x20, 16,2);

//contadores e luzes;
byte ha_senha = 0;
const int luz_vermelha = 2;
const int luz_verde = 3;

void setup(){
	lcd.init();
	lcd.clear();
	lcd.backlight(); //liga o led que ja esta no modulo
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
}
String senha;
void loop(){
    byte tentativas;
    //criando uma senha
    while (ha_senha == 0){
        digitalWrite(2,HIGH);
        digitalWrite(3,HIGH);
        lcd.setCursor(0,0);
        lcd.print("Crie uma senha:");
        senha = ler_do_teclado();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Senha escolhida:");
        lcd.setCursor(0,1);
        lcd.print(senha);
        delay(2500);
        lcd.clear();
        digitalWrite(2,LOW);
        digitalWrite(3,LOW);
        ha_senha = 1;
        tentativas = 3;
    }
    //tentando entrar no programa (com a senha)
    lcd.setCursor(0,0);
    lcd.print("Digite sua senha:");
	String texto = ler_do_teclado();
	Serial.println(texto);
    lcd.setCursor(0,0);
    lcd.print("Senha inserida:");
    lcd.setCursor(0,1);
	lcd.print(texto);
    if (texto == senha){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Bem vindo!");
        digitalWrite(3,HIGH);
        delay(60000);
        lcd.clear();
        lcd.print("até a próxima!");
        digitalWrite(3,LOW);
        delay(2000);
    }
    else if (texto == "AAAAA"){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("CODE: AAAAA");
        lcd.setCursor(0,1);
        lcd.print("mude de Senha!");
        delay(2000);
        lcd.clear();
        ha_senha = 0;
    }
    else if (texto != senha){
        digitalWrite(2,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Senha incorreta");
        lcd.setCursor(0,1);
        if (tentativas == 3)
            lcd.print("2 tentativas");
        else if (tentativas == 2)
            lcd.print("1 tentativas");
        else if (tentativas == 1){
            lcd.print("0 tentativas");
            delay(2000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Tente novamente");
            lcd.setCursor(0,1);
            lcd.print("mais tarde!");
            delay(30000);
            tentativas = 4;
        }
        tentativas --;
        delay(2000);
        digitalWrite(2,LOW);
        lcd.clear();
    }
}



String ler_do_teclado(){
	String valorRetornado;
	char valorLido;
	byte contador = 0;
    byte coluna = 0;
    int ativador = 0;
    do{
        int size = valorRetornado.length(); 
        valorLido = teclado.waitForKey();
        if(valorLido != '#' && valorLido != 'B'){
            lcd.setCursor(coluna++,1);
            lcd.print(valorLido);
            if (ativador >= 1){
                valorRetornado[size-ativador] = valorLido;
                ativador--;
            }
            else{
                valorRetornado += valorLido;
            }
			contador++;
			// Verifica se atingiu o limite máximo
			if(contador >= MAX_CARACTERES){
                break;
            }
        }
        else if(valorLido == 'B'){
            ativador++;
            valorRetornado[size-ativador] = '\0';
      		lcd.setCursor(coluna-- -1,1);
      		lcd.print('_'); 
      		contador--; 

        }
    }while(valorLido != '#');
    return valorRetornado;
}
