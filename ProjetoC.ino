/*
#-------------------------#
|       ATENDIMENTO       |
|      Igor Marinho       |
|      Bruno Dobelin      |
|      Vinicius Mariano   |
|      Vinicius Alves     |
#-------------------------#
*/
void setup(){
  pinMode(13, INPUT);
  pinMode(12, INPUT);
}

void loop()
{
  if(digitalRead(12) == 1){

  }
  if(digitalRead(13) == 1){
    
  }  
}

struct Senha{ //strutura de senhas
	int id; // id da senha, serve para identicar a senha
	int senha; // a senha propriamente dita
	int prioridade;  // a prioridade que pode ser 0 - normal | 1 - prioridade
	Senha *next; // ponteiro para a proxima senha
};

//função para inicializar a fila de senhas
Senha* inicializaSenha(){
	return NULL;
}

void gerarSenha(Senha **senha, int qtdNormal, int qtdPrioridade, int prioridade = 0){
	//O operador Seta (->) existe para acessar os membros da estrutura ou sindicatos por meio de ponteiros.
    Senha* s = (Senha*) malloc(sizeof(Senha)); //ponteiro para guardar uma senha, alocando memoria
	s->id =  (qtdNormal + qtdPrioridade)+1; // atribuindo um id para a senha
	s->prioridade = prioridade; //atribuindo a prioridade a senha
	if(prioridade){ // caso tenha prioridade
		s->senha = ++qtdPrioridade; //a senha é o próximo numero da sequencia de senhas prioritarias
	}else{ // se não
		s->senha = ++qtdNormal; // a senha é a próximo número da seguência de senhas normais
	}
	s->next = NULL; // esse ponteiro deve apontar para o NULL pois ele deve ser adicionado em ultimo lugar na fila
	if(*senha == NULL){ // se a fila for vazia
		*senha = s; // ele adiciona no inicio
	}else{ // se não
		Senha* aux = *senha; // cria um ponteiro auxiliar para senha
		while(aux->next != NULL){ // usamos um loop para percorrer todos realocando todos uma pocisão a cima
			aux = aux->next;
		}// ao sair do looping pegaremos o ultimo lugar
		aux->next = s; //então apontamos ele para a nova senha assim colocando ela no final da fila
	}
}
