/*Rotacoes que devem ser implementadas 
Os parametros e retorno sao de escolha do aluno
	rotation_LL(); 
	rotation_RR();  
	rotation_LR();  
	rotation_RL();
Obs: facam uma funcao para cada rotacao
Obs2: Essas funcoes sao exclusivas do avl.c, pois o usuario
NAO DEVE poder fazer uma dessas operacoes (ele pode apenas
inserir e remover na arvore). Assim, esses prototipos nao devem ir
no avl.h*/

#include "avl.h"

//Funcoes de impressao da arvore ja implementadas
void print_tab(int level){
  int i;
  for (i = 0; i < level; i++ )
    printf("\t");
}

void print_tree( Nodo_AVL *current, int level ){
  if ( current == NULL ) {
    print_tab(level );
    printf("~\n");
  } else {
    print_tree( current->right, level + 1 );
    print_tab(level);
    printf ("%d\n", current->key );
    print_tree( current->left, level + 1 );
  }
}


Nodo_AVL *rotation_LL(Nodo_AVL *raiz);
Nodo_AVL *rotation_RR(Nodo_AVL *raiz);
Nodo_AVL *rotation_LR(Nodo_AVL *raiz);
Nodo_AVL *rotation_RL(Nodo_AVL *raiz); 

Nodo_AVL *avl_insert(Nodo_AVL *current, int key){
  
  if(current == NULL)                                     							  //arvore nao foi criada ainda,entao eh criada
  {
    current = malloc(sizeof(Nodo_AVL));
    if(current == NULL) exit(1);
    current->right = NULL;
    current->left = NULL;
    current->key = key; 
    current->height = 0;
    return current;
  }

  
  if(key > current->key)                                                              //key eh maior q a key do nodo current,
  {                                                                                   //entao move para a direita

    current->right = avl_insert(current->right, key);
    if(current->right != NULL)
    {
      int balanceFactor = avl_height(current->left) - avl_height(current->right);     //calcula o fator de balanceamento do nodo current
      if(balanceFactor <= -2)                                                         //caso for menor q -2, balanceia por RR ou RL
      {
        if(key > current->right->key)                                                 //se a key eh maior q a key do nodo a direita
          current = rotation_RR(current);                                             //de current, realiza uma rotação RR,  
        else                                                                          //caso contrário uma RL
          current = rotation_RL(current);
      }
    }
  }
  else
    if(key < current->key)                                                            //key eh menor q a key do nodo current,
    {                                                                                 //entao move para a esquerda                                                                       
      current->left = avl_insert(current->left, key);
      if(current->left != NULL)                                                       
      {
        int balanceFactor = avl_height(current->left) - avl_height(current->right);   //calcula o fator de balanceamento do nodo current
        if(balanceFactor >= 2)                                                        //caso for maior q 2, balanceia por LL ou LR
        {
          if(key < current->left->key)                                                //se a key eh menor q a key do nodo a esquerda
            current = rotation_LL(current);                                           //de current, realiza uma rotação LL,
          else                                                                        //caso contrário uma LR
            current = rotation_LR(current);
        }   
      }
    }
    current->height = avl_height(current);
    return current;

}


Nodo_AVL *avl_delete(Nodo_AVL *current, int key){
	if(current == NULL)
	{
		return NULL;
	}

	Nodo_AVL* holdCurrent = current;
	Nodo_AVL* previous = current;
	
	if(key > current->key)                                                             	//se a key passada como parametro for maior que a key
	{                                                                                  	//do nodo atual, move para a sub-arvore direita
		current->right = avl_delete(current->right,key);
	}
	else                                                                             
		if(key < current->key)                                                         	//se a key passada como parametro for menor que a key
		{                                                                              	//do nodo atual, move para a sub-arvore direita
			current->left = avl_delete(current->left,key);
		}
		else
			if(key == current->key)                                                     //se a key passada como parametro for igual a key
			{                                                                           //do nodo atual, deleta o nodo
				if(current->left == NULL || current->right == NULL)
				{                                                                       //se o nodo possui nenhum ou 1 filho, o atual recebe seu
																						//filho nao nulo,se existir,estando uma variavel auxilar 
					Nodo_AVL* nodeDel = current;                                   		//guardando sua referencia para depois liberar da memoria  

					if(current->left != NULL)
						current = current->left;
					else
						current = current->right;
					free(nodeDel);
				}
				else
				{
					Nodo_AVL* aux1 = current->right;                                    //se o nodo possui 2 filhos, itera sobre sua sub-arvore
					Nodo_AVL* aux2 = aux1->left;                                        //direita a procura da key mais a esquerda
					while(aux2 != NULL)
					{
						aux1 = aux2;
						aux2 = aux2->left;				
					}
					
					current->key = aux1->key;                                           //a key do nodo atual eh substituida pela key do nodo  
					current->right = avl_delete(current->right,current->key);           //mais a esquerda da sub-arvore a direita, e o nodo
					                                                                    //correspondente a key mais a esquerda eh deletado
					
				}
					
			}

      if(current == NULL) return NULL;													//se o nodo atual for nulo,retorna nulo


     int balanceFactor = avl_height(current->left) - avl_height(current->right);
     int BFRight;
     int BFLeft;

     if(current->right == NULL)															//se a sub arvore da direita de current for nula,
     	BFRight = 0;																	//entao seu fator de balanceamento eh setado para 0
     else
		BFRight = avl_height(current->right->left) - avl_height(current->right->right); 
	if(current->left == NULL)
		BFLeft = 0;
	else
		BFLeft = avl_height(current->left->left) - avl_height(current->left->right);


	if (balanceFactor >= 2)																//se o fator de balanceamento do nodo current
	{																					//eh maior ou igual a 2, deve rebalancear por 
		if(BFLeft >=0)																	//rotacoes L
			current = rotation_LL(current);												//se o fator de balanceamerento da sub arvore a 
		else																			//esquerda for maior ou igual a 0, sua subarvore
			current = rotation_LR(current);												//esquerda tem mais ou o mesmo numero de nodos 
	}																					//que sua sub arvore direita,logo,para balncea-la
																						//eh necessaria realizar uma rotacao LL		
																						//caso contrario,realiza uma LR

	if (balanceFactor <= -2)															//se o fator de balanceamento do nodo current
	{																					//eh menor ou igual a -2, deve rebalancear por
		if(BFRight <= 0)																//rotacoes R
			current = rotation_RR(current);												
		else																			//se o fator de balanceamento da sub arvore a
			current = rotation_RL(current);												//direita for menor ou igual a 0, sua subarvore
	}																					//direita tem mais ou o mesmo numero de nodos 
																						//que sua sub arvore esquerda, entao eh necessaria
     current->height = avl_height(current);												//uma rotacao RR para balancea-la
     return current;																	//caso contrario, realiza uma RL
}

void print_inOrder(Nodo_AVL *current){

  if(current != NULL)
  {
  	print_inOrder(current->left);														//chama recursivamente a sub arvore a esquerda
    printf("%d ",current->key);															//depois imprime a key da raiz e chama  
    print_inOrder(current->right);														//recursivamente a sub arvore a direita 
  }																						//afim de imprimi-la em ordem

}


void avl_destroy(Nodo_AVL *current){

  Nodo_AVL* auxleft,*auxright;
  auxleft = current->left;                                                        		//armazena a subarvore a esquerda
  auxright = current->right;                                                      		//armazena a subarvore a direita

  if(current != NULL)
  {
    free(current);                                                                		//libera o nodo atual se nao for nulo

    if(auxleft!=NULL) avl_destroy(auxleft);                                       		//chama novamente a funcao para as subarvores se elas
    if(auxright!=NULL) avl_destroy(auxright);                                     		//nao chegaram as folhas 
  }
}


Nodo_AVL *avl_search(Nodo_AVL *current, int key){

  while(current != NULL)                                                            	//enquanto nao chegar a uma folha da arvore, 
  {                                                                                 	//itera sobre ela

    if(key == current->key)                                                         	//se encontrar o valor desejado de key na arvore,
      return current;                                                               	//retorna o nodo atual/current correspondente a ele

    else if(key > current->key)                                                     	//aponta para o nodo a direita de current se a key
            current = current->right;                                               	//passada como parametro for maior que a key 
          else                                                                      	//do nodo atual, e aponta para o nodo a esquerda 
            current = current->left;                                                	//de current caso contrario
  }
  return NULL;                                                                      	//retorna NULL se chegou a uma folha sem encontrar  
}                                                                                   	//nenhum elemento ou se a arvore nao foi criada ainda


int avl_height(Nodo_AVL *raiz){
  
  int leftHeight, rightHeight;                                                      

  if(raiz == NULL) return -1;                                                       	//se chegou a uma folha da arvore ou se ela ainda nao foi
                                                                                    	//criada, retorna -1

  leftHeight = avl_height(raiz->left);                                              	//determina recursivamente a altura a esquerda da arvore
  rightHeight = avl_height(raiz->right);                                            	//determina recursivamente a altura a direita da arvore
                                                                                    	//essas recursoes recalculam a altura de cada um dos 
  if(leftHeight > rightHeight)                                                      	//nodos inferiores aquele passado primariamente a funcao 
    return leftHeight + 1;
  else
    return rightHeight + 1;
 
}

Nodo_AVL *rotation_LL(Nodo_AVL *raiz)
{
  Nodo_AVL* newRoot = raiz->left;                                                   	//a nova raiz passa a ser o nodo a esquerda da raiz 
  raiz->left = newRoot->right;                                                      	//passada como parametrp

  newRoot->right = raiz;                                                            	//a nodo a direita da nova raiz passa a ser a antiga
  raiz->height = avl_height(raiz);														//raiz
  newRoot->height = avl_height(newRoot);											
  return newRoot;                                                                   
}

Nodo_AVL *rotation_RR(Nodo_AVL *raiz)
{                                                                                   
  Nodo_AVL* newRoot = raiz->right;                                                  	//a nova raiz passa a ser o nodo a direita da raiz
  raiz->right = newRoot->left;                                                      	//passada como parametro

  newRoot->left = raiz;                                                             	//a nodo a esquerda da nova raiz passa a ser a antiga
  raiz->height = avl_height(raiz);														//raiz
  newRoot->height = avl_height(newRoot);                                                             
  return newRoot;                                                                   
}

Nodo_AVL *rotation_LR(Nodo_AVL *raiz)
{																						//newRoot recebe raiz para que possa realizar 
																						//as rotacoes
  Nodo_AVL* newRoot = raiz;																//realiza uma rotacao dupla: primeiro RR 
  newRoot->left = rotation_RR(newRoot->left);											//e depois uma LL
  newRoot = rotation_LL(newRoot);

  return newRoot;
}

Nodo_AVL *rotation_RL(Nodo_AVL *raiz)
{
  Nodo_AVL* newRoot = raiz;
  newRoot->right = rotation_LL(newRoot->right);											//realiza uma rotacao dupla: primeiro LL 
  newRoot = rotation_RR(newRoot);														//e depois uma RR

  return newRoot;
} 
