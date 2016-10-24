


//=====================================================================
// BIBLIOTECAS
//=====================================================================
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>


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


//=====================================================================
// CLASSE GRAFO
//=====================================================================
class Grafo {
   private:
      int numVertice, 
          numAresta;
      
      
      int menorrota[MAX_VERTICE], rota[MAX_VERTICE];
      int custo,menorcusto;
      int visitas;
      int cor[MAX_VERTICE];
      int pred[MAX_VERTICE];

      Peso matriz[MAX_VERTICE][MAX_VERTICE];
      
   public:
      //--------------------------------------------------------------------
      // Construtor
      //--------------------------------------------------------------------
      Grafo(){
         numVertice = 0;
         excluirTodasArestas();
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // Destrutor
      //--------------------------------------------------------------------
      ~Grafo(){
      }//-------------------------------------------------------------------


      //--------------------------------------------------------------------
      // lerGrafo: Realiza a leitura do grafo no arquivo.
      //--------------------------------------------------------------------
      bool lerGrafo(){
         bool resp;
         int temp;

         excluirTodasArestas();

         //Ler o numero de vertices
         cin >> temp;
         setNumVertice(temp);

         resp = (numVertice > 0) ? true : false; 

         for(int i = 0; i < numVertice; i++){
            inserirAresta(i, i, NULO);
            for(int j = i+1; j < numVertice; j++){	
               cin >> temp;
               inserirAresta(i, j, temp);
               inserirAresta(j, i, temp);
            }
         }
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
               if(matriz[i][j] == NULO){
                  printf("\t. ");
               }else{
                  printf("\t%i ",matriz[i][j]);
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

        if(matriz[v1][v2] == NULO){
            matriz[v1][v2] = peso;
		if(matriz[v1][v2] != matriz[v2][v1]){
           		 numAresta++;
		}
        }      
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // isAresta: Retorna true se existe a aresta.
      //--------------------------------------------------------------------
      boolean isAresta(Vertice v1, Vertice v2){
         return (matriz[v1][v2] != NULO);
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // getAresta: Retorna o peso da aresta.
      //--------------------------------------------------------------------
      Peso getAresta(Vertice v1, Vertice v2){
         return (matriz[v1][v2]);
      }//-------------------------------------------------------------------



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

         if(matriz[v1][v2] != NULO){
            matriz[v1][v2] = NULO;
            numAresta--;
         }      
      }//-------------------------------------------------------------------



      //--------------------------------------------------------------------
      // excluirTodasArestas: Exclui todas as arestas.
      //--------------------------------------------------------------------
      void excluirTodasArestas(){
         for(int i = 0; i < MAX_VERTICE; i++){
            matriz[i][i] = NULO;
            for(int j = i + 1; j < MAX_VERTICE; j++){
               matriz[i][j] = matriz[j][i] = NULO;
            }
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
//-----------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
//Mostra o grafo complementar de um grafo G*

//---------------------------------------------------------------------------------
//Trabalho 								 
//---------------------------------------------------------------------------------

/*
		Para o método getComplementar, podemos considerar como operação relevante o número de acessos à matriz de adjacências,
		que neste método é são feitos pelos métodos isAresta e inserirAresta.
		O pior caso é quando o grafo é nulo, pois todos os vértices serão inseridos.
*/
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
//----------------------------------------------------------------------------------------------
/*
			Para o método getGrau, podemos considerar a operação relevante o número de somas dentro do for,
			que sempre será n, uma vez que precisamos percorrer todo o grafo para calcular o grau. Logo,
			a complexidade no pior caso terá comportamento O(n);
*/
int getGrau( int vertice ){
	int adjacente[numVertice];
	int cont = 0;
	for(int i=0;i<numVertice;i++){
	   if(isAresta(i, vertice)==true){
		cont++;
		}
	}
		return cont;
}
//---------------------------------------------------------------------------------------------


//Imprimir o Grau de todos os vértices do Grafo 

void imprimirtodograu (){
	for(int i=0; i< numVertice ; i++){

	
	printf("Grau do Vertice %i e %i \n", i,getGrau(i));

	}
}
//-----------------------------------------------------------------------------------------
        int imprimiGrau( int nvert ){

        int contador=0;

        for(int i= 0;  i < numVertice ; i++)

        {

          if(isAresta(nvert,i)){

           contador++;

            }
        }

        return contador;

     }
//---------------------------------------------------------------------------------------
/*
		Para o método isNulo, a operação relevante é o número de acessos à matriz de adjacências, que é feito pelo método getGrau.
		O pior caso é quando o grafo é nulo, pois passará por todas as iterações.
		Logo, é:
			T(n) = n(do for)*n(do getGrau);
			T(n) = n²
		Então o comportamento assintótico é de O(n²)
*/

 bool isNulo(){
	bool resposta = true;

	for(int i=0; i< numVertice; i++){

		if(getGrau(i)!=0){
		resposta=false;
	}

}

return resposta;
}
//----------------------------------------------------------------------------------------------------------------------------

/*
		Para o método isCompleto, a complexidade sempre será O(1), uma vez que o acesso é feito diretamente às variáveis.
*/

    bool isCompleto(){
	int nAresta=numVertice -1;
	bool resposta = true;
	for(int i=0;i<numVertice;i++){
		if(imprimiGrau(i) != nAresta){
			resposta=false;		
		
		}
	
	}
	
	return resposta;
}
//----------------------------------------------------------------------------------------------------------------------------
/*
		Para o método isRegular, a operação relevante é o número de acessos à matriz de adjacências, que é feito pelo método getGrau.
		O pior caso é quando o grafo é regular, pois passará por todas as iterações.
		Logo, é:
			T(n) = n + n*n
			T(n) = n² + n
		Então, o comportamento assintótico é de O(n²)
*/


    bool isRegular(){
	int regular=true;
	int grau =getGrau(0);
	for(int i=0; i<numVertice;i++)
	{
		if(grau !=getGrau(i)){
		regular = false;
		i=numVertice;
            }
	}


	return regular;

}
//------------------------------------------------------------------------------------------------------------
/*
			Para o método numPendentes, considerando a operação relevante o número de operação
			de incremento (++), o pior caso é quando o grafo é nulo, ou quando todos os vértices são isolados.
			Temos n iterações com n operações, e em cada iteração i, o método getGrau é chamado, que possui complexidade O(n).
			Logo, no pior caso, este método possui complexidade O(n²)
		*/


int numPendente(){
	int pendente =0;
	for(int i=0 ; i<numVertice; i++){
		if(getGrau(i)== 1){
		pendente++;
		}

	}
	
	return pendente;

}
//--------------------------------------------------------------------------------------------------------------------------
/*
			Para o método numIsolado, considerando a operação relevante o número de operação
			de incremento (++), o pior caso é quando o grafo é nulo, ou quando todos os vértices são isolados.
			Temos n iterações com n operações, e em cada iteração i, o método getGrau é chamado, que possui complexidade O(n).
			Logo, no pior caso, este método possui complexidade O(n²)
*/


int numIsolado(){
	int pendente =0;
	for(int i=0 ; i<numVertice; i++){
		if(getGrau(i)== 0){
		pendente++;
		}
	}	
	return pendente;

}
//---------------------------------------------------------------------------------------------------------------------------------------
/*

	Para o método NumComponentes, considerando a operação relevante o número de testes,a complexidade será T(n) = número de componentes * n², logo O(n²), pois usa o algoritmo 		     	     buscaEmProfundidade.

			T(n) = T(n-1) + n
			T(0) = 0
*/
int numComponentes(){
	bool visitou[numVertice];
	for(int i=0;i<numVertice;i++){
		visitou[i]=false;
	}
	int componentes=0;
	for(int j=0;j<numVertice;j++){
	   if(visitou[j] ==false){
		visite(j, visitou);
		componentes++;
		}
	}
return componentes;
}

/*
		O método visite, considerando a operação relevante o número de testes, que será n testes.
		T(n) = T(n-1) + n
		T(0) = 0
		Logo, no pior caso, será O(n²).
	*/
void visite(int neste , bool *visitou){
	for(int j=0 ; j<numVertice;j++){
		if(isAresta(neste,j) && visitou[j]==false){
			visitou[j]=true;
			visite(j,visitou);
		}
	
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------

//O método isConexo faz o return do método numComponentes que tem complexidade T(n) = número de componentes * n², logo O(n²) já que e utlizado o buscaemProfundidade

bool isConexo(){
	
	return numComponentes()==1;

	}	

//-----------------------------------------------------------------------------------------------------------------------------------

/*
		Para o método isEuleriano, podemos considerar a operação relevante o número de acessos à matriz,
		que é feito pelos métodos NumComponentes e pelo método getGrau.
		O pior caso é quando o grafo é euleriano, pois passará por todas as iterações.
		Logo, a função T(n) será:
			T(n) = O(n²)(do calculaNumComponentes) + n*n(do getGrau)
			T(n) = O(n²) + O(n²) = O(n²)
		Então, o comportamento assintótico será O(n²).
	*/
bool isEuleriano(){
	bool euleriano =false;
	if(isConexo()==true){
	euleriano=true;
	      for(int i=0;i<numVertice;i++){
			if(getGrau(i)%2 !=0){
				euleriano=false;
				i=numVertice;
			}
		}
	}
return euleriano;
}
//-----------------------------------------------------------------------------


/*
		Para o método isUnicursal, podemos considerar como operação relevante o número de acessos à matriz ,
		que neste método são feitos pelo método calculaNumComponentes e pelo getGrau.
		O pior caso é quando o grafo é conexo, pois sempre entrará no else e, consequentemente, fara todos os testes do getGrau.
		T(n) = O(n²)(do NumComponentes) + n*n(do getGrau)
		T(n) = O(n²)
*/

bool isUnicursal(){
	bool unicursal =false;
	int contador=0;
	if(isConexo()==true){
	      for(int i=0;i<numVertice;i++){
			if(getGrau(i)%2 !=0){
				contador++;
			}
		}
	
        }
          if(contador==2){
	    return true;
          }
 return unicursal;
}

//----------------------------------------------------------------------------------------
/*
		Para o método imprimirGrauEAdjacentes, se considerarmos a operação relevante o número de acesso à matriz, a complexidade será
		n vezes:
			n, do getGrau +
			n vezes 1, do isAresta
		Então...
		T(n) = n*(n + n), logo T(n) = 2n², que no pior caso será O(n²).
	*/
void questao4(){
printf("Grau e vertices Adjacentes\n");
//iniciamos dois loops para percorrer a matriz
   for(int i=0;i<numVertice;i++){
       cout<< getGrau(i);
//imprime-se o grau do vértice corrente	  
       for(int j=0;j<numVertice;j++){

		//se j for vizinho de i
		//imprime-se o índice de j
            if(isAresta(i,j)){
	       cout<< "--" <<j;
	   }
       
        }
	cout << "\n";
   }

}

//----------------------------------------------------------------------

//Método pedido pelo professor Max para ser entregue no dia da Primeira Prova 
void caixeiroViajante() {
   
   menorcusto=INF;
   custo=0;

   for(int i=0;i<numVertice ;i++){
    rota[i]=0;
    menorrota[i]=0;
  }
  
  VisitaEmProfundidade(matriz,numVertice);
  cout << "custo da viajem: " << menorcusto << "  e rota ";

  for (int i = 0; i <numVertice; i++) {
     cout << "-" << menorrota[i];
  }

}

void VisitaEmProfundidade(int ma[][MAX_VERTICE],int n){
  int register i,j,k;
  

   // inicializa vetores de cores e  precedentes
  for (i=0;i<n; i++){
    cor[i]=BRANCO;
    pred[i]=0;
  }
  visitas=0;
  Visita(0,ma,n);

}

void Visita(int u, int ma[][MAX_VERTICE],int n){
int v,i;
  
  cor[u]=CINZA; 

  rota[visitas]=u; 
  for(v=0;v<n;v++){
     if(isAresta(u, v)) {
        if(cor[v]==BRANCO){
           visitas++;
           custo=custo+ma[u][v];
           pred[v]=u;
           Visita(v,ma,n);
        }
     }
  }
  cor[u]=BRANCO;
  
  if (( visitas ==n-1) && (isAresta(u, 0))){
     //rota[visitas]=u;
     custo=custo+ma[u][0];

     if(custo<menorcusto){
        menorcusto=custo;
       memcpy(menorrota,rota,n*sizeof(int));

     }
     custo=custo-ma[u][0];
  }

  visitas--;
  custo=custo-ma[pred[u]][u];
}



//------------------------------------------------------------------------------------------------------------------

void questao1(){

	cout <<"\nNumero de Vertices:"<< numVertice <<"\nNumero de Arestas:"<< numAresta;
}

//---------------------------------------------------------------------
void questao2(){

	cout <<"\nNumero de Vertice Pendentes:"<< numPendente() <<"\nNumero de Vertice Isolados:"<< numIsolado();
}
//---------------------------------------------------------------------------

/*
			No método NumComponentes, a complexidade sempre será O(1), pois o acesso é direto à variável.
*/
void questao3(){

	cout <<"\nNumero de Componentes:"<< numComponentes();
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void questao5(){
     if(isNulo()==false){
	printf("O grafo não e Nulo\n");
	}
	else{
        printf("O grafo e Nulo\n");
	}
	if(isCompleto()==false){
	printf("O grafo Não e completo\n");
	}
	else{
	printf("O Grafo e Completo\n");
	}
	if(isRegular()==false){
	printf("O grafo Não e Regular\n");
	}
	else{
	printf("O Grafo e Regular\n");
	}
	if(isEuleriano()==false){
	printf("O grafo Não e Euleriano\n");
	}
	else{
	printf("O Grafo e Euleriano\n");
	}
	if(isUnicursal()==false){
	printf("O grafo Não e Unicursal\n");
	}
	else{
	printf("O Grafo e Unicursal\n");
	}

 }

void questao6(){

	complementar();

}


//--------------------------------------------------------------------

};

// getGrau(i)%2==0
//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv){

   Grafo *g = new Grafo;

   while (g->lerGrafo() == true){
      g->imprimir();
      g->imprimirtodograu();
      g->imprimirVerticeAresta();
     //g->imprimirPendenteAndIsolado();
     //g->questao1();
     //g->questao2();
     //g->questao3();
     //g->questao4();
     //g->questao5();
     //g->questao6();
     //g->questao7();
     //g->caixeiroViajante();		
      delete g;

      g = new Grafo;
   }

   delete g;

   return 0;
}//--------------------------------------------------------------------
