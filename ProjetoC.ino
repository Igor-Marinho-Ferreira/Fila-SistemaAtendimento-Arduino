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
char buff[40];
char buff1[40];
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

SenhasChamadas* inicializaSenhasChamadas(){
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
  display.setTextSize(1); //DEFINE O TAMANHO DA FONTE DO TEXTO
  display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
}

void loop()
{
  Senha* senhas = inicializaSenha(); 
  SenhasChamadas* senhasChamadas = inicializaSenhasChamadas();
  int cp = 2; 
  int qtdPrioridade = 0; 
  int qtdNormal = 0; 
  if(digitalRead(12) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    gerarSenha(&senhas, qtdNormal, qtdPrioridade,0);
    qtdNormal++;
    display.print(buff); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(1500); //INTERVALO DE 1,5 SEGUNDOS
    display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  }
  if(digitalRead(13) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    gerarSenha(&senhas, qtdNormal, qtdPrioridade, 1);
    qtdPrioridade++;
    display.print(buff); //ESCREVE O TEXTO NO DISPLAY
    display.display(); //EFETIVA A ESCRITA NO DISPLAY
    delay(1500); //INTERVALO DE 1,5 SEGUNDOS
    display.clearDisplay(); //LIMPA AS INFORMAÇÕES DO DISPLAY
  }
  if(digitalRead(2) == 1){
    display.setCursor(0,0); //POSIÇÃO EM QUE O CURSOR IRÁ FAZER A ESCRITA
    chamar(&senhas, &senhasChamadas, &cp);
    display.print(buff1); //ESCREVE O TEXTO NO DISPLAY
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
  sprintf(buff,"\nSENHA: %s%d\nTIPO: %s\n", s->prioridade ? " P" : " N", s->senha, s->prioridade ? " PRIORITARIA" : " NORMAL");
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

Senha* excluirsenha(Senha *senhas, int id){
  Senha* ant = NULL; 
  Senha* s = senhas; 

  while (s != NULL && s->id != id) { // criamos um looping para percorrer as senhas até o final da fila ou encontarar uma com o id que querermos
    ant = s; 
    s = s->next; 
  }
  if(s == NULL){
    return senhas; 
  }
  if (ant == NULL) { // se a senha anterior for NULL quer dizer que o que procuramos está no topo da fila
    senhas = s->next; 
  }else { 
    ant->next = s->next; 
  }
  free(s); // liberamos da memoria o ponteiro que criamos para percorrer as senhas
  return senhas;
}

void chamar(Senha** senhas, SenhasChamadas** senhasChamadas, int *cp){

  if(*senhas == NULL) return; // se a fila de senhas for NULL então a fila está vazia e encerramos a função

  Senha* s; // criamos um ponteiro para senhas
  if(*cp == 2){
    s = *senhas;
    *cp = 0; 
  }else{ 
    Senha* prioridades = prioridade(*senhas); // criamos um pontiro para senhas e inicializamos ele com a função de prioridade
    if(prioridades != NULL){ 
      s = prioridades; // então atrinuimos ela ao ponteiro de senhas que criamos e incrementamos o contador de senha com prioridades chamadas
      *cp = *cp + 1; 
    }else{ 
      s = *senhas; // então chamamos o proximo da fila, que sempre sera o primeiro
    }
  }

  SenhasChamadas* sc = (SenhasChamadas*) malloc(sizeof(SenhasChamadas)); // criamos um ponteiro para as senhas já chamadas e inicializamos alocando memoria 
  Senha *ant = (Senha*) malloc(sizeof(Senha));  // criamos um ponteiro para uma senha e alocamos memoria do tamannho de uma strutura Senha
  ant->id = s->id; 
  ant->prioridade = s->prioridade; 
  ant->senha = s->senha; 
  ant->next = NULL; 
  sc->senha = ant; 
  sc->next = *senhasChamadas; 
  *senhasChamadas = sc; 
  sprintf(buff1,"\nSENHA CHAMADA: %s%d\nTIPO: %s\n", s->prioridade ? " P" : " N", s->senha, s->prioridade ? " PRIORITARIA" : " NORMAL");
  *senhas = excluirsenha(*senhas, s->id); 
}



