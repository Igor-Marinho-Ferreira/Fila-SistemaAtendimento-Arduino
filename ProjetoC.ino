/*
#-------------------------#
|       ATENDIMENTO       |
|      Igor Marinho       |
|      Bruno Dobelin      |
|      Vinicius Mariano   |
|      Vinicius Alves     |
#-------------------------#
*/

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display = Adafruit_SSD1306();

struct Senha{ //strutura de senhas
  int id; // id da senha, serve para identicar a senha
  int senha; // a senha propriamente dita
  int prioridade;  // a prioridade que pode ser 0 - normal | 1 - prioridade
  Senha *next; // ponteiro para a proxima senha
};

struct SenhasChamadas{ //strutura para guardar as senhas já chamadas
  Senha* senha; //ponteiro para a senha já chamada
  SenhasChamadas *next; // pontiro para a proxima senha
};

Senha* inicializaSenha(){
  return NULL;
}

void setup(){
  pinMode(12, INPUT);
  pinMode(4, OUTPUT);
  pinMode(13, INPUT);
  pinMode(2, OUTPUT);
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //INICIALIZA O DISPLAY COM ENDEREÇO I2C 0x3C
  display.setTextColor(WHITE); //DEFINE A COR DO TEXTO
  display.setTextSize(3); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}

void loop()
{
  Senha* senhas = inicializaSenha(); 
  int cp = 2; 
  int qtdPrioridade = 0; 
  int qtdNormal = 0; 
  if(digitalRead(12) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    gerarSenha(&senhas, qtdNormal, qtdPrioridade,0);
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(1500); //INTERVALO DE 1,5 SEGUNDOS
    display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  }
  if(digitalRead(13) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    display.print("jamais"); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(1500); //INTERVALO DE 1,5 SEGUNDOS
    display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  }
}

void gerarSenha(Senha **senha, int qtdNormal, int qtdPrioridade, int prioridade){
  Senha* s = (Senha*) malloc(sizeof(Senha)); //ponteiro para guardar uma senha, alocando memoria 
  s->id =  (qtdNormal + qtdPrioridade)+1; 
  s->prioridade = prioridade; 
  if(prioridade){ 
    s->senha = ++qtdPrioridade; 
  }else{ // se não
    s->senha = ++qtdNormal; 
  }
  s->next = NULL;
  display.print("\nSENHA: %s%d\nTIPO: %s\n", s->prioridade ? " P" : " N", s->senha, s->prioridade ? " PRIORITARIA" : " NORMAL");
  if(*senha == NULL){ // se a fila for vazia, ele adiciona ela no inicio
    *senha = s; 
  }else{ 
    Senha* aux = *senha; 
    while(aux->next != NULL){ // usamos um loop para percorrer todos realocando todos uma pocisão a cima
      aux = aux->next;
    }
    aux->next = s; 
  }
}

Senha* prioridade(Senha *senhas){
  Senha* s = senhas; // criamos um ponteiro para armazenar temporariamente a fila de senhas
  while (s != NULL) { 
    if (s->prioridade == 1) break; 
    s = s->next; 
  }
  if (s == NULL) return NULL; 
  return s; 
}

