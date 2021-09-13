/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS05 - Componentes Conexos
 */

/* Para resolver o problema, uma grafo representado por uma matriz de 
 * adjacencia foi criado, a partir dele, comeca a se fazer uma busca em
 * profundidade para encontrar os componentes conexos. Cada vez que uma 
 * busca em profundidade nova comeca, todos os vertices de um componente 
 * conexo sao visitados, e marcados para nao serem visitados novamente.
 * No pior caso, o metodo sera O(V^2) (V = numero de vertices), pois 
 * por mais que a busca em profundidade seja O(E+V) (V = numero de vertices
 * E = numero de arestas), ha um loop quadratico para imprimir os vertices
 * encontrados em um componente conexo, ha tambem um custo linear para montar
 * o grafo, sendo O(E + V) (V = numero de vertices
 * E = numero de arestas)
 */

#include <iostream>
#include <string>

using namespace std;


struct Aresta{
    int valor;
    int vertice;
    Aresta* proximo;
};

typedef struct Aresta Aresta;

class Grafo{
    public:
        int numVertices; // cada vertice representa um roteador
        Aresta** vertices;
        bool* visitados;
        bool* visitadosIteracao;

        /* Construtor
         * COMPLEXIDADE: O(n), sendo n p_numVertice
         * Pois chama o metodo criaGrafo
         * @param int p_numVertice
         */
        Grafo(int p_numVertice){
            this->numVertices = p_numVertice;
            this->criarGrafo();
        }

        /* Liga dois roteadores por cabo que contem um preco
         * Cada roteador e um preco e cada cabo e uma aresta
         * COMPLEXIDADE: O(1) -> linear
         * @param int vertice1, int vertice2
         */
        void ligarVertices(int vertice1, int vertice2){
            struct Aresta* a = this->vertices[vertice1];

            // Adiconando aresta no vertice1
            a = this->vertices[vertice1]->proximo;
            this->vertices[vertice1]->proximo = criarAresta(vertice2);
            this->vertices[vertice1]->proximo->proximo = a;
        
            // Adiconando aresta no vertice2
            a = this->vertices[vertice2]->proximo;
            this->vertices[vertice2]->proximo = criarAresta(vertice1);
            this->vertices[vertice2]->proximo->proximo = a;

        }


        void printGrafo(){
            for(int i = 0; i < this->numVertices; i++){
                cout << i << " -> ";
                for(Aresta* a = this->vertices[i]->proximo; a != NULL; a = a->proximo){
                    cout << a->vertice << " -> ";
                }
                cout << endl; 
            }
        }
        
        /* Metodo para verificar os componentes conexos a partir de uma
         * busca em profundidade, em cada busca todos os vertices de um componete
         * conexo serao visitados. Caso um vertice nao seja entao ele nao esta no componente conexo
         * Complexidade BUSCA EM PROFUNDIDADE O(V + E) sendo V = numero de vertices
         * e E numero de arestas do grafo, pois ele irá visitar todos B
         * Complexidade Algoritmo com print O(V^2) -> Ira passa por todos os vertice
         * no pior caso para a busca em profundidade e para printar os componentes
         * as arestas passando por todos vértices do componente conexo
         * @return int numero de componentes conexos
         */
        int verificarComponentesConexos(){
            int cont = 0; // Conatdor componetes conexos

            // Vetor para marcar vretices visitados na dfs
            this->visitados = (bool*)malloc(sizeof(bool)*this->numVertices);
            // Vetor para marcar vertices do componete conexo, ou seja, vistados
            // durante uma iteracao
            this->visitadosIteracao = (bool*)malloc(sizeof(bool)*this->numVertices);

            // Iniciar todos os vertices como nao visitaods
            for(int i = 0; i < this->numVertices; i++){
                this->visitados[i] = false;
                this->visitadosIteracao[i] = false;
            }

            // Busca em profundidade
            for(int i = 0; i < this->numVertices; i++){
                if(!visitados[i]){ // Procurar componente nao visitado 
                    cont++; // Se encontrou, ha mais um componente conexo
                    DFS(i); // Busca em profunidade a partir do vertice nao visitado

                    // Pritar vertices visitados nessa iteracao, pois eles fazem parte
                    // do componente conexo descoberto nessa iteracao
                    for(int j = 0; j < this->numVertices; j++){
                        if(this->visitadosIteracao[j]){ // verificar se foi visitado
                            cout << (char) (j+97) << ",";
                            this->visitadosIteracao[j] = false; // limpar vetor
                        }
                    }
                    cout << endl;
                }
            }
            return cont;
        }
    private:
        /* Metodo recursivo para fazer busca em profundidade no grafo
         * Recebe como parametro o vertice inicial
         * Pior caso O(E) sendo E o numero de arestas
         * @param pos
         */
        void DFS(int pos){
            this->visitados[pos] = true; // Marcar como visitado
            this->visitadosIteracao[pos] = true; // Marcar como visitado nessa iteracao para
                                                // auxiliar no print
            
            // Visitando todas as arestas
            for(Aresta* a = this->vertices[pos]->proximo; a != NULL; a = a->proximo){
                if(!this->visitados[a->vertice]) // Se vertice que a aresta conecta nao foi visitada
                    DFS(a->vertice); // Visitar vertice vizinho
            }
        }

        /* Metodo para alocar memoria para lista encadeada
         * que ira representar o grafo
         * COMPLEXIDADE: O(n), sendo n this->numVertices
         * n + 1 alocacao de memoria | 2n + 2 atribuicoes | n somas
         */
        void criarGrafo(){
            //alocando vertices
            this->vertices =(Aresta**)malloc(sizeof(Aresta*) * this->numVertices);
            
            // Repeticao O(n)
            for(int i = 0; i < this->numVertices; i++)
                this->vertices[i] = (Aresta*) malloc(sizeof(Aresta)); // Alocando Head da lista
        }

        /* Metodo para criar uma nova aresta 
         * com o vertice de destino e valor
         * @param int vertice, int valor
         */
         Aresta* criarAresta(int vertice){  
            Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
            nova->vertice = vertice;
            nova->proximo = NULL;
            return nova;
        }
};


int main(){
    int casosDeTeste;
    int aresta;
    int vertice;
    char vertice1;
    char vertice2;

    cin >> casosDeTeste;

    for(int i = 1; i <= casosDeTeste; i++){
        cin >> vertice;
        cin >> aresta;

        // Alocando grafo com
        Grafo* g = new Grafo(vertice);

                
        for(int j = 0; j < aresta; j++){
            cin >> vertice1;
            cin >> vertice2;

            g->ligarVertices(vertice1-97, vertice2-97);
        }
        cout << "Case #" << i << ":" << endl;

        cout << g->verificarComponentesConexos() << " connected components\n" << endl;
    }


    return 0;
}

