/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema
 */

#include <iostream>
#include <string>

using namespace std;

class Grafo{
    int** matrizAdj;
    int numVertices;

    public:
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
                    this->matrizAdj[i][j] = -1;
            }
        }
};

int main(){

    Grafo* g = new Grafo(5);
    g->adicionarAresta(0, 0, 5);
    g->printGrafo();
    return 0;
}

