/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS06 - Penalizacao
 * Complexidade: O(2^n * n^2)
 */
 
/* Analise de complexidade:
 * A oprecao mais complexa deste algoritmo e o metodo da resolucao
 * do problema de caixeiro vaijante, sendo O(2^n * n^2). Como
 * o caixeiro viajante implementado utilza uma abordagem dinamica, ele impede
 * que seja feitas O(n!), reduzindo a complexidade para fatorial para exponencial
 * Outros metodos menos complexos, O(n^3), para Floyd-Warshall e iniciar matriz de 
 * estado sao utilizados para resolver o problema
 */ 

#include <iostream>
#include <string>
#include <climits>
#include <bits/stdc++.h>

using namespace std;

class Grafo{

    public:
        int** matrizAdj;
        int** fwMatriz;
        int numVertices;
        int teletransporte;
        int verticesVisitados; 
        int calculosFeitos[16][6][65536];
        
        // Construtor
        // @param int p_numVertices
        Grafo(int p_numVertices){
            this->numVertices = p_numVertices; 
            this->verticesVisitados = 0;
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

        /* Encapsulamento para chamda do caixeiro viajante
         * chama metodo calcularMenorCaminho para calcular menor caminho
         * entre todos os pares de vertice com algoritmo de Floyd-Warshall
         * inicia a matriz de 3 dimensoes para ter o controle de estados ja calculados
         * @return int -> menor caminho encontrado a partir do algoritmo de caixeiro 
         * viajante partindo vertice 0
         */
        int menorTempo(){
            // calcular distancia entre
            // todos os pares de vertice com algoritmo de Floyd-Warshall
            calcularMenorCaminho();
            // Matriz para controle de eestados ja calculados
            iniciarCalculosFeitos();

            // Marcar verice 0 como ja visitado
            this->verticesVisitados = this->verticesVisitados | 1 << 0;
            // caixeiro viajante a partir do vertice 1
            return caixeiroViajante(0, 1, this->teletransporte);
        }


    private:
    /* Algoritmo recurivo caixeiro viajante dinamico com teletranposte
     * Ira percorrer todos os estados, sem calcular repetidamente ja calculados,
     * para definir o menor caminho para visitar todos os vertices a partir de um
     * inicial. Ajustado para fazer teletransportes.
     * Compexidade:  O(2^n * n^2) -> exponencial sendo n numero de vertices
     * Como o algoritmo dinamico evita calcular estados ja calculados, o caixeiro
     * viajante tem sua complexidadde O(n!) reduzida para exponencial
     * @param int atual, int numVisitados, int teleportes
     * @return menor caminho
     */
    int caixeiroViajante(int atual, int numVisitados, int teleportes){
        // Se houve tentariva de teletransporte para 
        // vertive atual, mas todos ja foram gastos, retornar infinito 
        if(teleportes < 0){
            return 100000;
        }
        
        // base da recursao, todos vertices visitado
        if(this->numVertices == numVisitados){
            return 0;
        }
        // menor = valor calculado para estado atual
        int menor = calculosFeitos[atual][teleportes][this->verticesVisitados];
        
        // Se resultado de menor for diferente de -1,
        // entao o estado ja foi calculado
        // Retornar menor valor calculado
        if(menor != -1){
            return menor;
        }

        // Se nao foi calculado, menor = infinito
        menor = 100000;

        // Variaveis para guardar caminhos
        int c1;
        int c2;

        // Guardar estado atual de visitado, antes de
        // entrar na recursao
        int aux = this->verticesVisitados;

        for(int i = 0; i < this->numVertices; i++){
            // marcar vetice i como visitado
            this->verticesVisitados = ( this->verticesVisitados | 1 << i);

            // Se i nao foi visitado, entao 
            // comecar busca recursiva.
            // Caso ele tenha sido visitado, nao fazer nenhuma busca
            // para evitar passar por ele mais uma vez 
            if(!(aux & 1 << i)){
                // Se aresta >= que infinito, entao a aresta na verdade
                // nao existe, o vertice i e possivel apenas com teletranposte
                if(fwMatriz[atual][i] >= 100000){
                    // vistar i com teletransporte
                    c1 = caixeiroViajante(i, numVisitados + 1, teleportes - 1);
                    // se caminho c1 for menor que todos ate agora, atualizar menor
                    if(c1 < menor)
                        menor = c1;
                }else{
                    // vistar i com teletransporte
                    c1 = caixeiroViajante(i, numVisitados + 1, teleportes - 1);

                    // vistar sem teletrasporte, valor da aresta sera considerado nesse caso
                    c2 = caixeiroViajante(i, numVisitados + 1, teleportes) + fwMatriz[atual][i];
                    
                    // se caminho c1 for menor que todos ate agora, atualizar menor
                    if(c1 < menor)
                        menor = c1;
                    // se caminho c2 for menor que todos ate agora, atualizar menor 
                    if(c2 < menor)
                        menor = c2;
                }
                // Remover vertice i da lista de visitados para que ele possa
                // ser visitado nas proximas recursoes
                this->verticesVisitados = aux;
            }
                    
        }
        // Atualiza estado 
        this->calculosFeitos[atual][teleportes][this->verticesVisitados] = menor;
        return menor;
    }

    
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
                    this->matrizAdj[i][j] = 100000;
            }
        }

        
        /* Metodo para calcular menor caminho entre todos os pares de vertice
         * Ele cria um grafo completo adicionando arestas entre vertices com o 
         * valor do menor caminho. O grafo sera armazenado na matriz fwMatriz
         * complexidade O(n^3)
         */
        void calcularMenorCaminho(){

            // Matriz auxiliar para calcular menor caminho com Floyd-Warshall 
            this->fwMatriz = (int**) malloc(sizeof(int*) * this->numVertices);
            int count = 1;

            // Copiar matriz de adjacencia
            for(int i = 0; i < this->numVertices; i++){
                this->fwMatriz [i] = (int*) malloc(sizeof(int) * this->numVertices);
             
                for(int j = 0; j < this->numVertices; j++){
                    if(i == j)
                         this->fwMatriz [i][j] = 0; // diagonal = 0
                    else
                         this->fwMatriz [i][j] = this->matrizAdj[i][j]; // copiando posicoes matrizAdj para auxiliar 
                }
            }
            
            /* Calculo do algortmo de Floyd-Warshall, encontra
             * o menor caminho entre cada par de vertice que 
             * a aprtir da soma so peso de arestas 
             */
            for(int i = 0; i < this->numVertices; i++)
                for(int j = 0; j < this->numVertices; j++)
                    for(int k = 0; k < this->numVertices; k++)
                        if( ( this->fwMatriz [j][i] +  this->fwMatriz [i][k]) <  this->fwMatriz [j][k])
                             this->fwMatriz [j][k] =  this->fwMatriz [j][i] +  this->fwMatriz [i][k];
        }

        /* Metodo o n^3, para
         * iniciar todos estados como nao calculados 
         */
        void iniciarCalculosFeitos(){
            for(int i = 0; i < 16; i++)
             for(int j = 0; j < 6; j++)
                for(int k = 0; k < 65536; k++)
                   calculosFeitos[i][j][k] = -1;
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


        // Criando grafo 
        Grafo* g = new Grafo(vertice);
        cin >>  g->teletransporte;
                
        for(int j = 0; j < aresta; j++){
            cin >> vertice1;
            cin >> vertice2;
            cin >> valor;

            g->adicionarAresta(--vertice1, --vertice2, valor);
        }
       int menor =  g->menorTempo();
       if( g->menorTempo()  >= 30010) 
       cout << -1  << endl;
       else
       cout << menor << endl;
    }
    

    return 0;
}

