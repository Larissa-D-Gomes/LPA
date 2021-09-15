/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS06 - Penalizacao
 */

#include <iostream>
#include <string>
#include <climits>

using namespace std;


class Grafo{

    public:
        int** matrizAdj;
        int numVertices;
        int teletransporte;

        // Construtor
        // @param int p_numVertices
        Grafo(int p_numVertices){
            this->numVertices = p_numVertices;
            alocarMatriz();
        }

        /* Metodo para adicionar aresta entre vertice 1 e 2
         * @param int vert1, int vert2, int val
         */
        void adicionarAresta(int vert1, int vert2, int val){
            this->matrizAdj[vert1][vert2] = val;
            this->matrizAdj[vert2][vert1] = val;
        }

        void printGrafo(){
            cout << "   ";
            for(int i = 0; i < this->numVertices; i++)
                cout << i << "  ";

            cout << endl;
            for(int i = 0; i < this->numVertices; i++){
                cout << i << " ";

                //Iniciando grafo sem arestas
                for(int j = 0; j < this->numVertices; j++){
                    cout << this->matrizAdj[i][j] << " ";
                }
                cout << endl;
            }
        }

        
        void calcularMenoresCaminhos(){

            // Copiar matriz de adjacencia
            int matrizAux[this->numVertices][this->numVertices];
            bool vistados[this->numVertices];
            int count = 0;

            int tempoTotal = 0;

            for(int i = 0; i < this->numVertices; i++){
                vistados[i] = false;
                for(int j = 0; j < this->numVertices; j++){
                    if(i == j)
                        matrizAux[i][j] = 0;
                    else
                        matrizAux[i][j] = this->matrizAdj[i][j];
                }
            }
            

            for(int i = 0; i < this->numVertices; i++)
                for(int j = 0; j < this->numVertices; j++)
                    for(int k = 0; k < this->numVertices; k++)
                        if( matrizAux[j][i] + matrizAux[i][k] < matrizAux[j][k])
                            matrizAux[j][k] = matrizAux[j][i] + matrizAux[i][k];
            
            int atual = 0;
            int prox = 0;
            vistados[0] = true;
            bool visitou;
            while(count < this->numVertices){
                int menorCaminho = INT_MAX;
                visitou = false;
                for(int j = 0; j < this->numVertices; j++){
                    if( !vistados[j] && menorCaminho > matrizAux[atual][j] && matrizAux[atual][j] < 30010){
                        prox = j;
                        
                        menorCaminho = matrizAux[atual][j];
                        visitou = true;
                    }
                }
                vistados[atual] = true;
                if(!visitou)
                    cout << "n" << endl;
                count++;
                atual = prox;
                tempoTotal += menorCaminho;
            }
            cout << tempoTotal << " AQUI" << endl;
                        
        }
            /*cout << "   ";
            for(int i = 0; i < this->numVertices; i++)
                cout << i << "  ";

            cout << endl;
            for(int i = 0; i < this->numVertices; i++){
                cout << i << " ";

                //Iniciando grafo sem arestas
                for(int j = 0; j < this->numVertices; j++){
                    cout << matrizAux[i][j] << " ";
                }
                cout << endl;
            }*
        }/

    private:
        /* Metodo para alocar matriz de adjacencia
         * que ira representar o grafo
         * O(n^2) sendo n = this->numVertice 
         */
        void alocarMatriz(){
            // Alocando linhas
            this->matrizAdj = (int**) malloc(sizeof(int*) * this->numVertices);

            // Alocando colunas
            for(int i = 0; i < this->numVertices; i++){
                this->matrizAdj[i] = (int*) malloc(sizeof(int) * this->numVertices);

                //Iniciando grafo sem arestas
                for(int j = 0; j < this->numVertices; j++)
                    this->matrizAdj[i][j] = 30010;
            }
        }
};


int main(){
    int casosDeTeste;
    int aresta;
    int vertice;
    int teletransporte;
    int vertice1;
    int vertice2;
    int valor;

    cin >> casosDeTeste;

    for(int i = 1; i <= casosDeTeste; i++){
        cin >> vertice;
        cin >> aresta;

        // Alocando grafo com
        Grafo* g = new Grafo(vertice);
        cin >>  g->teletransporte;
                
        for(int j = 0; j < aresta; j++){
            cin >> vertice1;
            cin >> vertice2;
            cin >> valor;

            g->adicionarAresta(--vertice1, --vertice2, valor);
        }
        g->calcularMenoresCaminhos();
    }
    

    return 0;
}

