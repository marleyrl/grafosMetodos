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
#include <stdio.h>
#include <vector>
#include <list>

using namespace std;


//=====================================================================
// DEFINICAO DE CONSTANTES
//=====================================================================
#define MAX_VERTICE		 		500
#define MAX_INT         		0x7FFFFFFF
#define NULO					-1

//=====================================================================
// DEFINICAO DE TIPOS
//=====================================================================
typedef short boolean;
typedef int Peso;

struct Aresta {
    int v1;
    int v2;
    Peso p;
};

class Vertice
{
public:
    int vertice;
    int peso;

    Vertice ()
    {
        vertice = -1;
        peso = -1;
    }

    Vertice (int v)
    {
        this->vertice = v;
    }

    Vertice (int v,int p)
    {
        vertice = v;
        peso = p;
    }

    bool operator==(const Vertice &v)
    {
        return this->vertice == v.vertice;
    }
};

//=====================================================================
// CLASSE GRAFO
//=====================================================================
class Grafo
{
private:
    int numVertice,
    numAresta;
    vector< list<Vertice *> > vertices;

public:
    //--------------------------------------------------------------------
    // Construtor
    //--------------------------------------------------------------------
    Grafo()
    {
        numVertice = 0;
    }//-------------------------------------------------------------------


    //--------------------------------------------------------------------
    // Destrutor
    //--------------------------------------------------------------------
    ~Grafo()
    {
    }//-------------------------------------------------------------------


    //--------------------------------------------------------------------
    // lerGrafo: Realiza a leitura do grafo no arquivo.
    //--------------------------------------------------------------------
    bool lerGrafo()
    {
        bool resp;
        int temp;

        //Ler o numero de vertices
        cin >> temp;
        setNumVertice(temp);

        resp = (numVertice > 0) ? true : false;

        for(int i = 0; i < numVertice; i++)
        {
            vertices.push_back (list<Vertice*>());
        }
        for(int i = 0; i < numVertice; i++)
        {
            inserirAresta(i, i, NULO);
            for(int j = i+1; j < numVertice; j++)
            {
                cin >> temp;
                inserirAresta(i, j, temp);
            }
        }
        return resp;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // imprimir: imprime o grafo na tela
    //--------------------------------------------------------------------
    void imprimir ()
    {
	int i;
        for ( i=0; i<vertices.size(); i++)
        {
            cout<<"["<<i<<"] = ";
            for (list<Vertice*>::iterator it= vertices[i].begin(); it != vertices[i].end(); ++it)
            {
                cout<<"["<<(*it)->vertice<<"] ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }

    //--------------------------------------------------------------------
    // getNumVertice: retorna o numero de vestices do grafos
    // -------------------------------------------------------------------
    int getNumVertice()
    {
        return numVertice;
    }//--------------------------------------------------------------------

    //--------------------------------------------------------------------
    // getNumAresta: retorna o numero de arestas do grafo
    // -------------------------------------------------------------------
    int getNumAresta()
    {
        return numAresta;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // isCiclico: Verifica se o grafo possui circuito
    // -------------------------------------------------------------------
    bool isCiclico ()
    {
        Grafo temp = *this;
        while (temp.removerVerticesPendentes())
        {
            temp.removerVerticesPendentes();
        }
        return temp.numVertice > 2;
    }//-------------------------------------------------------------------

    
    //---------------------------------------------------------------------
    // imprimirNumeroCutVertice : imprime a quantidades de cutvertices
    // no grafo
    //---------------------------------------------------------------------
    void imprimirNumeroCutVertice (){
        int cutVertices = 0;
        if (isConexo()==true){
           
		for (int i =0;i<this->numVertice;i++){
		    Grafo temp =  *this;
		    temp.removerVertice(i);
		    // 1 vertice isolado e o grafo
		    if (temp.getNumComponentes() > 2){
		        cutVertices++;
		    }
			
		}
		cout<<cutVertices<<"\n";
      	}
    }






    //---------------------------------------------------------------------
    // kruskal : Executa o kruskal e imprime a ordem em que os vértices
    // sao adicionados na agm
    //---------------------------------------------------------------------
    void kruskal (){
        if (isConexo()==true){

		Grafo temp = *this;
		Grafo * agm = new Grafo ();
		int n = this->numVertice;
		//adicionar vértices a agm
		for (int i=0; i<n; i++)
		    agm->vertices.push_back (list<Vertice*>());
		while (agm->numVertice != n){
		    Aresta a = temp.getArestaMenorPeso();
		    if (a.p == -1)
		        break;
		    agm->inserirAresta(a.v1,a.v2,a.p);
		    if (agm->isCiclico()){
		        agm->excluirAresta(a.v1,a.v2);
		    }else{
		        //caso o vértice seja novo na agm , imprimir o mesmo
		        // e atualizar o número de vértices na mesma
		        if (agm->vertices.at(a.v1).size() == 1){
		            agm->numVertice++;
		            cout<<a.v1<<" ";
		        }
		        if (agm->vertices.at(a.v2).size() == 1){
		            agm->numVertice++;
		            cout<<a.v2<<" ";
		        }
		    }
		    temp.excluirAresta(a.v1,a.v2);
		}
		cout<<"\n";
	}
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // prim: retorna o grafo com a árvore geradora mínima
    // -------------------------------------------------------------------
    Grafo * prim ()
    {
        if (isConexo()==true){

		Grafo temp = *this;
		Grafo * agm = new Grafo ();
		int n = this->numVertice;
		//adicionar vértices a agm
		for (int i=0; i<n; i++)
		    agm->vertices.push_back (list<Vertice*>());

		//executar o primeiro passo manualmente
		int menorAresta = this->getArestaMenorPeso(0);
		agm->inserirAresta(0,menorAresta);
		temp.excluirAresta(0,menorAresta);
		agm->numVertice = 2;
			cout<<0<<" "<<menorAresta<<" ";
		while (agm->numVertice != n)
		{
		    menorAresta = -1;
		    int indice = -1;
		    for (int i=0; i<n; i++)
		    {
		        if (!agm->vertices[i].empty())
		        {
		            int aresta = temp.getArestaMenorPeso(i);
		            if (menorAresta == -1 ||
		                    ( aresta > 0 && temp.getAresta(i,aresta) < temp.getAresta(menorAresta,indice)))
		            {
		                menorAresta = aresta;
		                indice = i;
		            }
		        }
		    }
		    if (menorAresta != -1)
		    {
		        if (agm->vertices[indice].size() == 0 || agm->vertices[menorAresta].size() == 0)
		            agm->numVertice++;
		        agm->inserirAresta(menorAresta,indice);
		        if (agm->isCiclico())
		        {
		            agm->excluirAresta(menorAresta,indice);
		            temp.setAresta(indice,menorAresta,9999);
		            if (agm->vertices[indice].size() == 0 || agm->vertices[menorAresta].size() == 0)
		                agm->numVertice--;
		        }
		        else
		        {
		            temp.excluirAresta(menorAresta,indice);
		            cout<<menorAresta<<" ";
					}
		    }
		}
		cout<<"\n";
		return agm;
	}
    }//-------------------------------------------------------------------

private:

    //--------------------------------------------------------------------
    // isArvore: Verifica se o grafo é uma ávore
    //--------------------------------------------------------------------
    bool isArvore ()
    {
        return (isConexo() && (( this->numAresta + 1) == this->numVertice));
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // removerVerticesPendentes: Remove todos os vértices pendentes do grafo
    // -------------------------------------------------------------------
    bool removerVerticesPendentes ()
    {
        bool removeu = false;
        for (unsigned int i=0; i<vertices.size(); i++)
        {
            if (vertices.at(i).size() == 1)
            {
                removerVertice(i);
                removeu = true;
            }
        }
        return removeu;
    }

    //--------------------------------------------------------------------
    // removerVertice: Remove um vértice do grafo
    // -------------------------------------------------------------------
    void removerVertice (int v)
    {
        list<Vertice *> vizinhos = vertices.at(v);
        list<Vertice *>::iterator it;
        for (it=vizinhos.begin(); it!=vizinhos.end(); ++it)
        {
            int vertice = (*it)->vertice;
            list<Vertice *>::iterator it2;
            for (it2=vertices[vertice].begin(); it2!=vertices[vertice].end(); ++it2)
            {
                if((*it2)->vertice == v)
                {
                    vertices[vertice].erase(it2);
                    numAresta--;
                    break;
                }
            }
        }
        vertices[v].clear();
        this->numVertice--;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // getArestaMenorPeso: Retorna a aresta no grafo que possui o menor peso
    // a menor a aresta
    // -------------------------------------------------------------------
    Aresta getArestaMenorPeso (){
        Aresta a;
        a.v1 = -1;
        a.v2 = -1;
        a.p = -1;
	int i;
	int j;
        for ( i = 0; i < vertices.size();i++){
            for ( j = i; j < vertices.size();j++){
                if ( isAresta(i,j) && (a.p == -1 || getAresta(i,j) < a.p) ){
                    a.v1 = i;
                    a.v2 = j;
                    a.p = getAresta(i,j);
                }

            }
        }
        return a;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // getArestaMenorPeso: retorna o vértice adjacente a v que possui
    // a menor a aresta
    // -------------------------------------------------------------------
    int getArestaMenorPeso (int v)
    {
        int peso = MAX_INT;
        int menor = -1;
        for (list<Vertice*>::iterator it= vertices[v].begin(); it != vertices[v].end(); ++it)
        {
            if ((*it)->peso < peso)
            {
                menor = (*it)->vertice;
                peso =  (*it)->peso;
            }
        }
        return menor;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // getNumComponentes: Retorna o número de componentes no grafo
    //--------------------------------------------------------------------
    int getNumComponentes()
    {
        //cada indice corresponde a um vertice
        int * componentes = new int [vertices.size()];
        int numComponentes = 0;
	int i;
        for (i=0; i<vertices.size(); i++)
        {
            // -1 , diz que o vertice ainda não tem componente definida
            componentes[i] = -1;
        }
        for ( i=0; i<vertices.size(); i++)
        {
            //se o vertice não tem componente ainda, definir as mesmas
            if (componentes[i] == -1)
            {
                definirComponentes(i,numComponentes++,componentes);
            }
        }
        delete [] componentes;
        return numComponentes;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // definirComponentes: define as componentes em profundidade
    // recursivamente
    //--------------------------------------------------------------------
    void definirComponentes (int v,int componente,int * componentes)
    {
        componentes[v] = componente;
        list<Vertice *>::iterator it;
        list<Vertice *>vizinhos = vertices[v];
        for (it=vizinhos.begin() ; it != vizinhos.end(); it++ )
        {
            if (componentes[(*it)->vertice] == -1)
            {
                definirComponentes((*it)->vertice,componente,componentes);
            }
        }
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // isConexo: verifica se o grado é conexo
    //--------------------------------------------------------------------
    bool isConexo ()
    {
        return getNumComponentes() == 1;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // inserirAresta: Insere uma nova aresta.
    //--------------------------------------------------------------------
    void inserirAresta(int v1, int v2)
    {
        inserirAresta(v1,v2,1);
    }


    //--------------------------------------------------------------------
    // inserirAresta: Insere uma nova aresta.
    //--------------------------------------------------------------------
    void inserirAresta(int v1, int v2, Peso peso)
    {
        if (peso == NULO)
            return;
        if(v1 > MAX_VERTICE)
        {
            printf("ERRO! Vertice %i nao existe no grafico", v1);
            return;
        }
        if(v2 > MAX_VERTICE)
        {
            printf("ERRO! Vertice %i nao existe no grafico", v2);
            return;
        }
        vertices.at(v1).push_back (new Vertice(v2,peso));
        if(!isAresta(v2,v1))
        {
            vertices.at(v2).push_back (new Vertice(v1,peso));
            numAresta++;
        }


    }//-------------------------------------------------------------------


    //--------------------------------------------------------------------
    // isAresta: Retorna true se existe a aresta.
    //--------------------------------------------------------------------
    boolean isAresta(int v1, int v2)
    {
        list <Vertice*> vizinhos = vertices[v1];
        list <Vertice*>::iterator it;
        for (it=vizinhos.begin(); it!=vizinhos.end(); ++it)
        {
            if ((*it)->vertice == v2)
            {
                return true;
            }
        }
        return false;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // getAresta: Retorna o peso da aresta.
    //--------------------------------------------------------------------
    Peso getAresta(int v1, int v2)
    {
        list <Vertice*> vizinhos = vertices[v1];
        list <Vertice*>::iterator it;
        for (it=vizinhos.begin(); it!=vizinhos.end(); ++it)
        {
            if ((*it)->vertice == v2)
            {
                return (*it)->peso;
            }
        }
        return -1;
    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // setAresta: Retorna o peso da aresta.
    //--------------------------------------------------------------------
    void setAresta(int v1, int v2,int peso)
    {
        list <Vertice*> vizinhos = vertices[v1];
        list <Vertice*>::iterator it;
        for (it=vizinhos.begin(); it!=vizinhos.end(); ++it)
        {
            if ((*it)->vertice == v2)
            {
                (*it)->peso = peso;
            }
        }
        vizinhos = vertices[v2];
        for (it=vizinhos.begin(); it!=vizinhos.end(); ++it)
        {
            if ((*it)->vertice == v1)
            {
                (*it)->peso = peso;
            }
        }

    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // excluirAresta: Exclui uma aresta.
    //--------------------------------------------------------------------
    void excluirAresta(int v1, int v2)
    {
        if(v1 > numVertice)
        {
            printf("ERRO! Vertice %i nao existe no grafico",v1);
            return;
        }

        if(v2 > numVertice)
        {
            printf("ERRO! Vertice %i nao existe no grafico",v2);
            return;
        }
        list<Vertice *>::iterator it;
        for (it=vertices[v1].begin(); it!=vertices[v1].end(); ++it)
        {
            if((*it)->vertice == v2)
            {
                it  = vertices[v1].erase(it);
            }
        }
        for (it=vertices[v2].begin(); it!=vertices[v2].end(); ++it)
        {
            if((*it)->vertice == v1)
            {
                it  = vertices[v2].erase(it);
            }
        }

    }//-------------------------------------------------------------------

    //--------------------------------------------------------------------
    // setNumVertice: Altera a variavel numVertice.
    //--------------------------------------------------------------------
    void setNumVertice(int nVertice)
    {

        if(nVertice > MAX_VERTICE)
        {
            printf("ERRO: Numero de vertices\n");
            return;
        }
        numVertice = nVertice;
    }//-------------------------------------------------------------------
public:
void questao1(){
     if(isArvore()==false){
    printf("O grafo nao uma Arvore\n");
    }
    else{
        printf("O grafo e uma Arvore\n");
    }
 }
void questao2(){
    prim();
 }

void questao3(){
    kruskal();
 }
void questao4(){
    imprimirNumeroCutVertice();
 }


};


//=====================================================================
// FUNCAO PRINCIPAL
//=====================================================================
int main(int argc, char **argv)
{

    Grafo *g = new Grafo;
    vector<Grafo *> grafos;
    while (g->lerGrafo() == true)
    {
        grafos.push_back(g);

	g->questao1();
	g->questao2();
	g->questao3();
	g->questao4();

	cout << "//---------------------------------------------\n\n";
g = new Grafo;

    }
    
    delete g;

    return 0;
}//--------------------------------------------------------------------























