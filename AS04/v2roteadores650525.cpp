/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS04 - Grafos
 * Complexidade: O(n^2*m)
 */

/* ANALISE
 * A resolucao do problema tem complexidade = O(n^2*m)
 * Inicialmente é preciso montar o grafo, que entra em uma repeticao
 * O(n) => sendo n o numero de vertices
 * Depois insere as arestas com custo linear para cada insercao, mas
 * repetindo o processo linear n vezes, fazendo um processo O(n) => sendo n o numero de arestas
 * Por fim, a resulução do problema utiliza o algortmo de prim, com um loop O(n) que tem um outro 
 * loop O(n) interno, que por sua vez possui um loop O(m) interno => n = numero de vertices, 
 * m = numero de arestas de um determinado vertice escolhido. Assim, a solução em seu pior caso
 * seria O(n^2*m)
 */

#include <iostream>
#include <climits>

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
         * @param int vertice1, int vertice2, int preco
         */
        void ligarRoteador(int vertice1, int vertice2, int preco){
            struct Aresta* a = this->vertices[vertice1];

            // Adiconando aresta no vertice1
            a = this->vertices[vertice1]->proximo;
            this->vertices[vertice1]->proximo = criarAresta(vertice2, preco);
            this->vertices[vertice1]->proximo->proximo = a;
        
            // Adiconando aresta no vertice2
            a = this->vertices[vertice2]->proximo;
            this->vertices[vertice2]->proximo = criarAresta(vertice1, preco);
            this->vertices[vertice2]->proximo->proximo = a;

        }

        /* Funcao que utiliza o algoritmo de prim (MST) para retornar
         * o menor custo de cabos
         * O(n^2+m)
         * @return int menor custo
         */
        int getMenorCusto(){
            // Vetor para marcar vertices que estao na arvore
            bool incluidoArv[this->numVertices]; 
            int soma = 0;
            int menor = 0;
            int verticeEscolhido;

            // Iniciar arvore vazia
            for(int i = 1; i < this->numVertices; i++) 
                incluidoArv[i] = false;
            
            // Adicionar um vertice inicial na arvore
            incluidoArv[0] = true; 

            /* Repeticao para montar arvore geradora minima
             * for interno n repeticoes | externo n repeticoes
             * n = this->numVertices 
             */
            for(int i = 0; i < this->numVertices; i++){
                soma += menor; // somar menor custo selecionado
                menor = INT_MAX; // menor = maior inteiro possivel
                verticeEscolhido = 0; // Variavel para 
                for(int j = 0; j < this->numVertices; j++){

                    /* Verificar menor aresta do conjunto de vertices que esta na 
                     * arvore e que conecta alguem que nao esta na arvore
                     */
                    if(incluidoArv[j]){
                        // Repeticao O(n), sendo n = numero de arestas de this->vertices[j]
                        for(Aresta* a = this->vertices[j]->proximo; a != NULL; a = a->proximo){
                            /* Se aresta conecta alguem que nao esta na arvore e tem valor
                             * menor que o menor escolhido, entao trocar menor valor e 
                             * vertice que sera adicionado na arvore 
                             */
                            if(!incluidoArv[a->vertice] && a->valor < menor){
                                menor = a->valor;
                                verticeEscolhido = a->vertice;
                            }

                        }
                    }
                }
                incluidoArv[verticeEscolhido] = true; // Adicionando vertice escolhido no conjunto da arvore
            }
           
            return soma;
        }

        
    private:
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
         Aresta* criarAresta(int vertice, int valor){  
            Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
            nova->valor = valor;
            nova->vertice = vertice;
            nova->proximo = NULL;
            return nova;
        }
};



int main(){
    int numRoteadores;
    int numCabos;
    int roteador1;
    int roteador2;
    int preco;

    cin >> numRoteadores;
    cin >> numCabos;

    // Criando grafo
    // numRoteadores = numVertices | numCabos = numArestas
    Grafo* grafo = new Grafo(numRoteadores);

    // Leitura ligacao cabo - roteador
    for(int i = 0; i < numCabos; i++){
        cin >> roteador1;
        cin >> roteador2; 
        cin >> preco;

        grafo->ligarRoteador(--roteador1, --roteador2, preco);
    }
    cout << grafo->getMenorCusto() << endl;

    return 0;
}

