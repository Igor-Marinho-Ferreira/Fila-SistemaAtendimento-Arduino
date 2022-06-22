/*
#-------------------------#
|       ATENDIMENTO       |
|      Igor Marinho       |
|      Bruno Dobelin      |
|      Vinicius Mariano   |
|      Vinicius Alves     |
#-------------------------#
*/

#include <U8glib.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display = Adafruit_SSD1306();
#define limit 10
#define limitP 10

struct fila_struct {
  int position[limit];
  int initial_position;
  int end_position;
};

struct fila_struct fila;
int num_atendimento = 0;
int num_atendimentoP = 0;
int num = 0;

int senha = 0;
int senhaP = 0;
bool sair = true;
char buff[35];
char buff1[35];
char buff2[35];

void setup(){
  pinMode(12, INPUT);
  pinMode(4, OUTPUT);
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}

void loop()
{
  fila.initial_position = 0;
  fila.end_position = 0;
  
  if(digitalRead(13) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    retirar_senha();
    display.print(buff); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(150);
  } 
  if(digitalRead(12) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    retirar_senhaP();
    display.print(buff2); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(150);
  }
  if(digitalRead(2) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    fila_decrement();
    display.print(buff1); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(150); 
  }
  if(digitalRead(4) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    fila_decrementP();
    display.print(buff1); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(150); 
  }
}
void fila_increment(int senha){
  if (fila.end_position == limit) {
  }
  else {
    fila.position[fila.end_position] = senha;
    fila.end_position++;
  }
}

void fila_incrementP(int senhaP){
  if (fila.end_position == limit) {
  }
  else {
    fila.position[fila.end_position] = senhaP;
    fila.end_position++;
  }
}

void retirar_senhaP(){
  int sua_senha;
  if (validar() == 1) {
    sua_senha = senhaP + 1;
    sprintf(buff2,"Sua senha: %dP", sua_senha);
    senhaP++;
    fila_incrementP(sua_senha);
  } else if(senhaP == 10) {
    sprintf(buff2,"A fila ja esta completa");
  }
  display.clearDisplay();
  display.display();
}

void retirar_senha(){
  int sua_senha;
  if (validar() == 1) {
    sua_senha = senha + 1;
    sprintf(buff,"Sua senha: %dN", sua_senha);
    senha++;
    fila_increment(sua_senha);
  } else if(senha == 10) {
    sprintf(buff,"A fila ja esta completa");
  }
  display.clearDisplay();
  display.display();
}

void fila_decrement(){
  for (int i=0; i<limitP -1; i++) {
     fila.position[i] = fila.position[i+1];
  }
  fila.position[fila.end_position] = 0;
  fila.end_position--;
  num_atendimento++;
  sprintf(buff1,"SENHA: %dN \n", num_atendimento);
  display.clearDisplay();
  display.display();
}

void fila_decrementP(){
  for (int i=0; i<limit -1; i++) {
     fila.position[i] = fila.position[i+1];
  }
  fila.position[fila.end_position] = 0;
  fila.end_position--;
  num_atendimentoP++;
  sprintf(buff1,"SENHA: %dP \n", num_atendimentoP);
  display.clearDisplay();
  display.display();
}

int validar(){
  if (senha == limit || senhaP == limit) {
    return -1;
  }
  else if(senha <= limit || senhaP <= limit) {
    return 1;
  }
  
}
