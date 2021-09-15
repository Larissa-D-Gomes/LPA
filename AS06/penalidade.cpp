/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS06 - Penalizacao
 */

#include <iostream>
#include <string>
#include <climits>
#include <bits/stdc++.h>

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
            if(this->matrizAdj[vert1][vert2] == 30010 || this->matrizAdj[vert1][vert2] > val){
                this->matrizAdj[vert1][vert2] = val;
                this->matrizAdj[vert2][vert1] = val;
            }
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

        
        int calcularMenoresCaminhos(){

            // Copiar matriz de adjacencia
            int matrizAux[this->numVertices][this->numVertices];
            int vistados[this->numVertices];
            int count = 1;

            int tempoTotal = 0;

            for(int i = 0; i < this->numVertices; i++){
                vistados[i] = -1;
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
                        if( (matrizAux[j][i] + matrizAux[i][k]) < matrizAux[j][k])
                            matrizAux[j][k] = matrizAux[j][i] + matrizAux[i][k];
            
            int atual = 0;
            int prox = 0;
            vistados[0] = 0;
            bool visitou;
            while(count < this->numVertices){
                int menorCaminho = INT_MAX;
                visitou = false;
                for(int j = 0; j < this->numVertices; j++){
                    if( vistados[j] == -1 && menorCaminho > matrizAux[atual][j] && matrizAux[atual][j] < 30010){
                        prox = j;
                        menorCaminho = matrizAux[atual][j];
                        visitou = true;
                    }
                }
                
                if(!visitou){
                    if(this->teletransporte == 0 )
                        return -1;
                        
                    for(int i = 0; i < this->numVertices; i++){
                        if(vistados[i] == -1){
                            prox = i;
                            this->teletransporte--;
                            i = this->numVertices;
                            vistados[prox] = 0;
                        }
                    }
                }else{
                    
                    vistados[prox] = menorCaminho;
                }
                cout << prox << " " << vistados[prox] << endl;
                count++;
                atual = prox;
                
            }

            sort(vistados, vistados +  this->numVertices);

            int remover = this->numVertices - 1;
            while(this->teletransporte > 0){
                vistados[remover] = 0;
                remover--;
                this->teletransporte--;
            }

            for(int i = 0; i < this->numVertices; i++){
                tempoTotal += vistados[i];
            }

           // return tempoTotal;
                        
        //}
            cout << "   ";
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
            }

             return tempoTotal;
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
        cout << vertice << "VER " << i << endl;
        cout << aresta << "VER"<< endl;
        // Alocando grafo com
        Grafo* g = new Grafo(vertice);
        cin >>  g->teletransporte;
                
        for(int j = 0; j < aresta; j++){
            cin >> vertice1;
            cin >> vertice2;
            cin >> valor;

            g->adicionarAresta(--vertice1, --vertice2, valor);
        }
       // g->printGrafo();
        cout << g->calcularMenoresCaminhos() << endl;
    }
    

    return 0;
}

