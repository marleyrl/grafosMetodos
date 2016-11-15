/***********************************************************************
* Pontificia Universidade Catolica de Minas Gerais 
* Ciencia da Computacao 
* Grafos e Teoria da Complexidade
* Prof. Max do Val Machado
************************************************************************/


//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


using namespace std;


//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_VERTICE		 		500
#define MAX_INT         		0x7FFFFFFF
#define NULO						-1

#define BRANCO						0
#define PRETO						1
#define CINZA						2
#define INF                                             1000000


//=====================================================================
// DEFINICAO DE TIPOS
//=====================================================================
typedef short boolean;

typedef int Vertice;
typedef int Peso;

struct Aresta{
  Vertice vi, vj;
  Peso peso;
};

class Celula{
private:
	//variável inteira para guardar o índice do vértice;
	int elemento;
public:
	//Ponteiro para a pŕoxima Celula
	Celula *seguinte, *anterior;

	//Construtor
	Celula(){}
	Celula(int elemento, Celula *anterior,Celula *seguinte){
		this->elemento = elemento;
		this->anterior = anterior;
		this->seguinte = seguinte;
	}

	//Destrutor
	~Celula(){}

	int getElemento(){
		return elemento;
	}

	void setElemento(int elemento){
		this->elemento = elemento;
	}
};

class Lista{
private:
	int quantidade;
public:
	Celula *sentinela;

	//Construtor
	Lista(){
		sentinela = new Celula(-1,NULL,NULL);
		sentinela->anterior = sentinela;
		sentinela->seguinte = sentinela;
		quantidade = 0;
	}

	//Destrutor
	~Lista(){}

	void inserirInicio(int elemento){
		if(!pesquisar(elemento)){
			Celula *nova = new Celula(elemento,sentinela,sentinela->seguinte);
			nova->seguinte->anterior = nova;
			nova->anterior->seguinte = nova;
			quantidade++;
		}
	}

	int removerFim(){
		if(quantidade > 0){
			Celula *aux = sentinela->anterior;
			int retorno = aux->getElemento();
			aux->anterior->seguinte = aux->seguinte;
			aux->seguinte->anterior = aux->anterior;
			delete aux;
			quantidade--;
			return retorno;
		}else{
			return -1;
		}
	}

	void esvaziar(){
		while(quantidade > 0){
			removerFim();
		}
	}

	int getQuantidade(){
		return quantidade;
	}

	void mostrar(){
		for(Celula *i = sentinela->seguinte; i != sentinela; i = i->seguinte){
			cout << i->getElemento() << " ";
		}
		cout << "\n";
	}

	bool pesquisar(int elemento){
		bool encontrou = false;
		for(Celula *i = sentinela->seguinte; i != sentinela && !encontrou; i = i->seguinte){
			encontrou = (elemento == i->getElemento());
		}
		return encontrou;
	}
};

class Fila{
private:
	Lista *l;

public:
	//Construtor
	Fila(){
		l = new Lista;
	}

	void enfileirar(int i){
		l->inserirInicio(i);
	}

	int desenfileirar(){
		return l->removerFim();
	}

	int getQuantidade(){
		return l->getQuantidade();
	}
};

class CelulaA{
	private:
		int aresta, vertice;
	public:
		CelulaA *seguinte;

		//Construtor vazio
		CelulaA(){}

		//Construtor 2
		CelulaA(int vertice, int aresta, CelulaA *seguinte){
			this->aresta = aresta;
			this->vertice = vertice;
			this->seguinte = seguinte;
		}

		//Destrutor
		~CelulaA(){}

		/*Getters and setters*/
		int getAresta(){
			return aresta;
		}

		int getVertice(){
			return vertice;
		}

		void setAresta(int aresta){
			this->aresta = aresta;
		}

		void setVertice(int vertice){
			this->vertice = vertice;
		}
};

class ListaA{

	private:
		int quantidade;
	public:
	CelulaA *primeiro, *ultimo;

	//Construtor
	ListaA(){
		primeiro = new CelulaA(NULO, NULO, NULL);
		ultimo = primeiro;
		quantidade = 0;
	}


	//Destrutor
	~ListaA(){}

	void setQuantidade(int quantidade){
		this->quantidade = quantidade;
	}

	int getQuantidade(){
		return this->quantidade;
	}

	bool pesquisar(int vertice){
		bool encontrou = false;
		for(CelulaA *i = primeiro->seguinte; i != NULL && !encontrou; i = i->seguinte){
			encontrou = (i->getVertice() == vertice);
		}

		return encontrou;
	}

	CelulaA** pesquisarCelula(int vertice){
		bool encontrou = false;
		CelulaA** retorno = new CelulaA*[2];
        retorno[0] = NULL;
        retorno[1] = NULL;
		if(ultimo == primeiro){
			return retorno;
		}else{
			for(CelulaA *i = primeiro; i->seguinte != NULL && !encontrou; i = i->seguinte){
				if(encontrou = (i->seguinte->getVertice() == vertice)){
					retorno[0] = i;
					retorno[1] = i->seguinte;
				}
			}
		}
		return retorno;
	}

	void inserirAresta(int vertice, int aresta){
		if(aresta == NULO){
			return;
		}
		CelulaA* nova = new CelulaA(vertice, aresta, primeiro->seguinte);
		primeiro->seguinte = nova;
		if(getQuantidade() == 0){
			ultimo = nova;
		}
		quantidade++;
	}

	int getAresta(int vertice){
		CelulaA** aux = pesquisarCelula(vertice);
		if(aux[1] != NULL){
			return aux[1]->getAresta();
		}else{
			return NULO;
		}
	}

	void esvaziar(){
		while(quantidade > 0){
			removerInicio();
		}
	}

	int removerInicio(){
		if(ultimo == primeiro){
			return NULO;
		}else{
			CelulaA *aux = primeiro->seguinte;
			int retorno = aux->getAresta();
			primeiro->seguinte = aux->seguinte;
			delete aux;
			if(quantidade == 1){
				ultimo = primeiro;
			}
			quantidade--;
			return retorno;
		}
	}

	int removerAresta(int vertice){
		if(ultimo == primeiro){
			return NULO;
		}else{
			int aresta;
			CelulaA **aux = pesquisarCelula(vertice);
			if(aux[1] == NULL){
				aresta = NULO;
			}else{
				aresta = aux[1]->getAresta();
				aux[0]->seguinte = aux[1]->seguinte;
				delete aux[1];
				quantidade--;
			}
			return aresta;
		}
	}

	ListaA* clone(){
		ListaA *retorno = new ListaA;
		for(CelulaA  *i = primeiro->seguinte; i != NULL; i = i->seguinte){
			retorno->inserirAresta(i->getVertice(),i->getAresta());
		}
		return retorno;
	}
};

//=====================================================================
// CLASSE GRAFO
//=====================================================================
class Grafo {
   private:
      int numVertice,
          numAresta, numComponentes;
	  bool componentesFlag;
	  bool enable[MAX_VERTICE];

	  ListaA lista[MAX_VERTICE];

   public:

      //--------------------------------------------------------------------
      // Construtor
      //--------------------------------------------------------------------
      Grafo(){
         numVertice = 0;
		 numAresta = 0;
	 numComponentes = 0;
		for(int i = 0; i < MAX_VERTICE; i++){ enable[i] = false;}
         excluirTodasArestas();
		componentesFlag = false;
      }//-------------------------------------------------------------------

	  Grafo* clone(){
			Grafo *retorno = new Grafo;
			retorno->numVertice = numVertice;
			retorno->numAresta = numAresta;
			retorno->numComponentes = numComponentes;
			retorno->componentesFlag = componentesFlag;
			for(int i = 0; i < MAX_VERTICE; i++){
				retorno->enable[i] = enable[i];
				retorno->lista[i] = *lista[i].clone();
			}
			return retorno;
	  }


      //--------------------------------------------------------------------
      // Destrutor
      //--------------------------------------------------------------------
      ~Grafo(){
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // lerDigrafo: Realiza a leitura do grafo no arquivo.
      //--------------------------------------------------------------------
      bool lerDigrafo(){
         bool resp;
         int temp;

         excluirTodasArestas();

         //Ler o numero de vertices
         cin >> temp;
         setNumVertice(temp);

         resp = (numVertice > 0) ? true : false;

         for(int i = 0; i < numVertice; i++){
            enable[i] = true;
            for(int j = 0; j < numVertice; j++){
               cin >> temp;
               inserirAresta(i, j, temp);
               
            }
         }
		 componentesFlag = false;
         return resp;
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // imprimir: Imprime o grafo.
      //--------------------------------------------------------------------
      void imprimir(){
         int i = 0, j = 0;

         printf("\nN = (%i)\n\t",numVertice);
         for(i = 0; i < numVertice; i++){
            if (i >= 100){
               printf("\t(%i) ",i);
            }else if(i >= 10){
               printf("\t(0%i) ",i);
            }else{
               printf("\t(00%i) ",i);
            }
         }

         for(i = 0; i < numVertice; i++){
            if (i >= 100){
               printf("\n(%i) - ",i);
            }else if(i >= 10){
               printf("\n(0%i) - ",i);
            }else{
               printf("\n(00%i) - ",i);
            }

            for(j = 0; j < numVertice; j++){
               if(getAresta(i,j) == NULO){
                  printf("\t. ");
               }else{
                  printf("\t%i ",getAresta(i,j));
               }
            }
         }

         printf("\n");
      }//-------------------------------------------------------------------

   private:

      //--------------------------------------------------------------------
      // inserirAresta: Insere uma nova aresta.
      //--------------------------------------------------------------------
      void inserirAresta(Vertice v1, Vertice v2, Peso peso){

         if(v1 > MAX_VERTICE){
            printf("ERRO! Vertice %i nao existe no grafico", v1);
            return;
         }

         if(v2 > MAX_VERTICE){
            printf("ERRO! Vertice %i nao existe no grafico", v2);
            return;
         }

         if(lista[v1].getAresta(v2) == NULO){
		if(peso != NULO){
		lista[v1].inserirAresta(v2,peso);
		numAresta++;
		}
				
         }
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // isAresta: Retorna true se existe a aresta.
      //--------------------------------------------------------------------
      boolean isAresta(Vertice v1, Vertice v2){
         return (lista[v1].getAresta(v2) != NULO);
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // getAresta: Retorna o peso da aresta.
      //--------------------------------------------------------------------
      Peso getAresta(Vertice v1, Vertice v2){
         return (lista[v1].getAresta(v2));
      }//-------------------------------------------------------------------

	  bool getComponentesFlag(){
		return componentesFlag;
	  }

	  void setComponentesFlag(bool componentesFlag){
			this->componentesFlag = componentesFlag;
	  }

        void removerVertice(int vertice){
            for(int i = 0; i < numVertice; i++){
                if(i == vertice){
                    enable[i] = false;
                }else{
                    lista[i].removerAresta(vertice);
                }
            }
        }

      //--------------------------------------------------------------------
      // excluirAresta: Exclui uma aresta.
      //--------------------------------------------------------------------
      void excluirAresta(Vertice v1, Vertice v2){

         if(v1 > numVertice){
            printf("ERRO! Vertice %i nao existe no grafico",v1);
            return;
         }

         if(v2 > numVertice){
            printf("ERRO! Vertice %i nao existe no grafico",v2);
            return;
         }

         if(lista[v1].getAresta(v2) != NULO){
            lista[v1].removerAresta(v2);
            numAresta--;
         }
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // excluirTodasArestas: Exclui todas as arestas.
      //--------------------------------------------------------------------
      void excluirTodasArestas(){
         for(int i = 0; i < MAX_VERTICE; i++){
            lista[i].esvaziar();
            enable[i] = false;
         }
         numAresta = 0;
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // setNumVertice: Altera a variavel numVertice.
      //--------------------------------------------------------------------
      void setNumVertice(int nVertice){

         if(nVertice > MAX_VERTICE){
            printf("ERRO: Numero de vertices\n");
            return;
         }

         numVertice = nVertice;
      }//-------------------------------------------------------------------


   public:
      void imprimirVerticeAresta(){
         cout << numVertice << " " << numAresta << "\n";
      
      }
//----------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

int getNumVertice(){

	return numVertice;
}
//-----------------------------------------------------------
int getGrauEntrada(Vertice v){
        int grauEntrada = 0;
        for(Vertice i = 0; i < numVertice; i++){
            if(isAresta(i,v)){
                grauEntrada++;
            }
        }
        return grauEntrada;
    }
 //-------------------------------------------------------------------------
int getGrauSaida(Vertice v){
        int grauSaida = 0;
        for(Vertice i = 0; i < numVertice; i++){
            if(isAresta(v,i)){
                grauSaida++;
            }
        }
        return grauSaida;
    }
 //-------------------------------------------------------------------------
bool isBalanceado(){

	bool resp=true;
	for(int i=0; i<numVertice;i++){
	   if(getGrauEntrada(i) != getGrauSaida(i)){
		 resp=false;
	   }	
	}
	return resp;
}
//---------------------------------------------------------------------------------
bool isRegular(){
        int grauE = getGrauEntrada(0);
        int grauS = getGrauSaida(0);
        bool regular = (grauE == grauS);
        for(Vertice i = 1; i < numVertice && regular; i++){
            int grauE2 = getGrauEntrada(i);
            int grauS2 = getGrauSaida(i);
            regular = ((grauS == grauS2) && (grauE == grauE2));
        }
        return regular;
    }
//---------------------------------------------------------------------------------
bool isFortementeConexo(){
        bool *visitados = new bool[numVertice];
        for(Vertice i = 0; i < numVertice; i++){visitados[i] = false;}
        visitar(0,visitados);
        bool resp = true;
        for(Vertice i = 0; i < numVertice && resp; i++){
            resp = visitados[i];
        }
        return resp;
    }

	void visitar(Vertice v, bool *visitados){
        visitados[v] = true;
        int grau = getGrauSaida(v), cont = 0;
        for(Vertice i = 0; i < numVertice && cont < grau; i++){
            if(isAresta(v,i)){
                if(!visitados[i]){
                    visitar(i,visitados);
                }  
                cont++;
            }
        }
    }
//---------------------------------------------------------------------------------
  void profundidadebusca(){
    bool visitou[numVertice];
    for(int i=0; i<numVertice ;i++){
        visitou[i]=false;
    }
    for(int j=0;j<numVertice;j++){
       if(!visitou[j]){
        visitarProfundidade(j, visitou);

        }
    }
}

void visitarProfundidade(Vertice v, bool *visitados){
     
        for(Vertice i = 0; i < numVertice; i++){
           if(!visitados[v]){
			cout << v << " ";
		}
		visitados[v]=true;
		if(isAresta(v,i) && !visitados[i]){
                    visitarProfundidade(i,visitados);
              
            }
        }
    }
//---------------------------------------------------------------------------------
void buscaLargura(){
        bool *visitados = new bool[numVertice];
        int quantidade = 0;
        Fila *fila = new Fila;
        for(Vertice i = 0; i < numVertice; i++){visitados[i] = false;}
        for(int i = 0; i < numVertice; i++){
            if(!visitados[i]){
                visitarLargura(i,visitados,fila,quantidade);
            }
        }
 
        delete [] visitados;
        delete fila;
        cout << "\n";
    }


void visitarLargura(Vertice v,bool *visitados, Fila *fila, int &quantidade){
        cout << v;
        quantidade++;
        if(quantidade != numVertice){
            cout << " ";
        }
        visitados[v] = true;
        int cont = 0;
        for(int i = 0; i < numVertice; i++){
            if(isAresta(v,i)){
                cont++;
                if(!visitados[i]){
                    fila->enfileirar(i);
                }
            }
        }
        Vertice v2 = fila->desenfileirar();
 
        if(v2 != NULO){
            visitarLargura(v2,visitados,fila,quantidade);
        }
    }
//---------------------------------------------------------------------------------------------
void dijkstra(Vertice v0){
        if(v0 > MAX_VERTICE || v0 > numVertice){
            return;
        }
        int *distancias = new int[numVertice];
        bool *visitados = new bool[numVertice];
        for(int i = 0; i < numVertice; i++){
            if(i == v0){
                distancias[i] = 0;
            }else if(isAresta(v0,i)){
                distancias[i] = getAresta(v0,i);
            }else{
                distancias[i] = MAX_VERTICE;
            }
            visitados[i] = false;
        }
        visitados[v0] = true;
 
        int menor;
        if(v0 == 0){
            menor = 1;
        }else{
            menor = 0;
        }
        visitarDijkstra(visitados,distancias,v0,menor);
 
        for(int i = 0; i < numVertice; i++){
            if(i == 0){
                if(distancias[i] == MAX_VERTICE){
                    cout << "-1";
                }else{
                    cout << distancias[i];
                }
            }else{
                if(distancias[i] == MAX_VERTICE){
                    cout << " -1";
                }else{
                    cout << " " << distancias[i];
                }
            }
        }
        cout << endl;
    }
 
    void visitarDijkstra(bool *visitados, int *distancias, Vertice v0, int x){
        int i;
        for(i = 0; i < numVertice; i++){
            if(!visitados[i]){
                x = i;
                i = numVertice;
            }
        }
        for(i = x+1; i < numVertice; i++){
            if(distancias[i] < distancias[x] && !visitados[i]){
                x = i;
            }
        }
        visitados[x] = true;
        int cont = 0;
        for(int i = 0; i < numVertice; i++){
            if(isAresta(x,i)){
                cont++;
                if(!visitados[i]){
                    int dNova = distancias[x] + getAresta(x,i);
                    if(dNova < distancias[i]){
                        distancias[i] = dNova;
                    }
                }
            }
        }
 
        if(existeVertice(visitados)){
            visitarDijkstra(visitados,distancias,v0,x);
        }
    }
 
    bool existeVertice(bool *visitados){
        for(int i = 0; i < numVertice; i++){
            if(!visitados[i]){
                return true;
            }
        }
        return false;
    }


//--------------------------------------------------------------------------------- 
bool isEuleriano(){
        return (isFortementeConexo() && isBalanceado());
    }
//-------------------------------------------------------------------------------

void questao1(){
     if(isRegular()==false){
	printf("O grafo não e Regular\n");
	}
	else{
        printf("O grafo e Regular\n");
	}
	if(isBalanceado()==false){
	printf("O Digrafo Não e Balanceado\n");
	}
	else{
	printf("O Digrafo e Balanceado\n");
	}
	if(isEuleriano()==false){
	printf("O Digrafo Não e Euleriano\n");
	}
	else{
	printf("O Digrafo e Euleriano\n");
	}
	if(isFortementeConexo()==false){
	printf("O Digrafo Não e Fortemente Conexo\n");
	}
	else{
	printf("O Digrafo e Fortemente Conexo\n");
	}
	

 }//--------------------------------------------------------------------
	
	void questao2(){
		profundidadebusca();
		printf("\n");
	}

//--------------------------------------------------------------------------
	void questao3(){
		buscaLargura();
	}

//-----------------------------------------------------------------------------
	void questao4(){
		dijkstra(0);
	}

//----------------------------------------------------------------------
void complementar(){
	Grafo  *g = new Grafo;

	g->setNumVertice(getNumVertice());
	for(int i= 0 ; i <numVertice; i++){

		  for(int j=i+1; j<numVertice; j++){
			if(i!=j && isAresta(i,j) != true) 
			{
				g->inserirAresta(i,j,1);
				g->inserirAresta(j,i,4);				
			}
		
		  }
	}
	g->imprimir();

}

};

//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv){

   Grafo *g = new Grafo;

   while (g->lerDigrafo() == true){
      g->imprimir();
     //g->questao1();
     //g->questao2();
     //g->questao3();
       g->questao4();
     //g->imprimiAdjacente();	
     //g->imprimirtodograu();
     //g->imprimirVerticeAresta();
     //g->imprimirPendenteAndIsolado();
     //g->complementar();
     //g->questao5();
     //g->questao2();
     //g->questao3();
     //g->caixeiroViajante();		
      delete g;

      g = new Grafo;
   }

   delete g;

   return 0;
}//--------------------------------------------------------------------
