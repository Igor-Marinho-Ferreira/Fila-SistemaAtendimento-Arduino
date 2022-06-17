/*
#-------------------------#
|       ATENDIMENTO       |
|      Igor Marinho       |
|      Bruno Dobelin      |
|      Vinicius Mariano   |
|      Vinicius Alves     |
#-------------------------#
*/
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

struct Senha{ //strutura de senhas
  int id; // id da senha, serve para identicar a senha
  int senha; // a senha propriamente dita
  int prioridade;  // a prioridade que pode ser 0 - normal | 1 - prioridade
  Senha *next; // ponteiro para a proxima senha
};

void gerarSenha(Senha **senha, int qtdNormal, int qtdPrioridade, int prioridade = 0){
  Senha* s = (Senha*) malloc(sizeof(Senha)); //ponteiro para guardar uma senha, alocando memoria 
  s->id =  (qtdNormal + qtdPrioridade)+1; // atribuindo um id para a senha, ela é a soma de todas as senhas +1 
}
