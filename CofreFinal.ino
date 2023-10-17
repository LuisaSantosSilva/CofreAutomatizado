#include <Relay.h>

#include <Key.h>
#include <Keypad.h>

// C++ code
const int ledVermelho = 12; //PINO EM QUE ESTÁ CONECTADO O LED VERMELHO
const int ledVerde = 13; //PINO EM QUE ESTÁ CONECTADO O LED VERDE
#define relay 2

const char* password = "777"; //SENHA CORRETA PARA DESTRANCAR A FECHADURA
int position = 0; //VARIÁVEL PARA LEITURA DE POSIÇÃO DA TECLA PRESSIONADA
const byte ROWS = 4; //NUMERO DE LINHAS DO TECLADO
const byte COLS = 3; //NUMERO DE COLUNAS DO TECLADO
char keys[ROWS][COLS] = { //DECLARAÇÃO DOS NUMEROS, LETRAS E CARACTERES DO TECLADO
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'} 
};
 
byte rowPins[ROWS] = { 8, 7, 6, 5 }; // PINOS DE CONEXAO DAS LINHAS DO TECLADO
byte colPins[COLS] = { 9, 10, 11 }; //PINOS DE CONEXAO DAS COLUNAS DO TECLADO
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );//AS VARIAVEIS rowPins E colPins RECEBERÃO O VALOR DE LEITURA DOS PINOS DAS LINHAS E COLUNAS RESPECTIVAMENTE
 
void setup(){
  pinMode(ledVermelho, OUTPUT); //DECLARA O PINO COMO SAÍDA
  pinMode(ledVerde, OUTPUT); //DECLARA O PINO COMO SAÍDA
  pinMode(relay, OUTPUT); //DECLARA O PINO COMO SAÍDA
  setLocked(false); //ESTADO INICIAL DA FECHADURA (TRANCADA)
}
 
void loop(){
  char key = keypad.getKey(); //LEITURA DAS TECLAS PRESSIONADAS 
  if (key == '*' || key == '#') { //SE A TECLA PRESSIONADA POR IGUAL A CARACTERE "*" OU "#", FAZ
      position = 0; //POSIÇÃO DE LEITURA DA TECLA PRESSIONADA INICIA EM 0
      setLocked(false); //FECHADURA TRANCADA
}
if (key == password[position]){ //SE A TECLA PRESSIONADA CORRESPONDER A SEQUÊNCIA DA SENHA, FAZ
      position ++;//PULA PARA A PRÓXIMA POSIÇÃO
}
if (position == 3){ // SE VARIÁVEL FOR IGUAL A 3 FAZ (QUANDO AS TECLAS PRESSIONADAS CHEGAREM A 3 POSIÇÕES, SIGNIFICA QUE A SENHA ESTÁ CORRETA)
      setLocked(true); //FECHADURA DESTRANCADA
}
delay(100);//INTERVALO DE 100 MILISSEGUNDOS
}
void setLocked(int locked){ //TRATANDO O ESTADO DA FECHADURA
if (locked){ //SE FECHADURA TRANCADA, FAZ
    digitalWrite(ledVermelho, LOW);// LED VERMELHO
    digitalWrite(ledVerde, HIGH);// LED VERDE
    digitalWrite(relay, LOW);// relay
    
}
else{ //SENÃO, FAZ
    digitalWrite(ledVerde, LOW);// LED VERDE 
    digitalWrite(ledVermelho, HIGH);// LED VERMELHO
    digitalWrite(relay, HIGH);// Relay 
}
}
