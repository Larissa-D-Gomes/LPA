/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: Prova 2 - Expensive subway
 * Complexidade:  O(n^2+m)
 */

/* Para se resolver o problema, utiliza-se dois algoritmos principais
 * DSF para verificar se o grafo e conexo, logo se e possivel visitar todas 
 * arestas e algoritmo de prim para encontrar a MST, logo o menor preco total
 * das passagens.
 * Verificar componentes conexos complexidade =  No pior caso, o metodo sera O(V^2) (V = numero de vertices), pois 
 * por mais que a busca em profundidade seja O(E+V) (V = numero de vertices
 * E = numero de arestas), ha um loop quadratico para imprimir os vertices
 * encontrados em um componente conexo, ha tambem um custo linear para montar
 * o grafo, sendo O(E + V) (V = numero de vertices
 * E = numero de arestas)
 * Algoritmo de Prim = No pior caso, O(n^2*m)
 * Inicialmente é preciso montar o grafo, que entra em uma repeticao
 * O(n) => sendo n o numero de vertices
 * Depois insere as arestas com custo linear para cada insercao, mas
 * repetindo o processo linear n vezes, fazendo um processo O(n) => sendo n o numero de arestas
 * Por fim, a resulução do problema utiliza o algortmo de prim, com um loop O(n) que tem um outro 
 * loop O(n) interno, que por sua vez possui um loop O(m) interno => n = numero de vertices, 
 * m = numero de arestas de um determinado vertice escolhido. Assim, a solução em seu pior caso
 * seria O(n^2*m)
 * Como o Algoritmo de Prim e mais custoso, o custo para se resolver o problema e O(n^2*m)
 */
#include <iostream>
#include <string>
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
        bool* visitados; // Controle no algoritmo de Prim

        /* Construtor
         * COMPLEXIDADE: O(n), sendo n p_numVertice
         * Pois chama o metodo criaGrafo
         * @param int p_numVertice
         */
        Grafo(int p_numVertice){
            this->numVertices = p_numVertice;
            this->criarGrafo();
        }

        /* Liga dois vertices
         * COMPLEXIDADE: O(1) -> linear
         * @param int vertice1, int vertice2, int valor
         */
        void adicionarAresta(int vertice1, int vertice2, int valor){
            struct Aresta* a = this->vertices[vertice1];

            // Adiconando aresta no vertice1
            a = this->vertices[vertice1]->proximo;
            this->vertices[vertice1]->proximo = criarAresta(vertice2, valor);
            this->vertices[vertice1]->proximo->proximo = a;
        
            // Adiconando aresta no vertice2
            a = this->vertices[vertice2]->proximo;
            this->vertices[vertice2]->proximo = criarAresta(vertice1, valor);
            this->vertices[vertice2]->proximo->proximo = a;

        }

        /* Funcao que utiliza o algoritmo de prim (MST) para retornar
         * o menor custo de passagens
         * O(n^2+m)
         * @return int menor custo
         */
        int getMenorCusto(){
            Grafo* g = new Grafo(this->numVertices);
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

        void printGrafo(){
            for(int i = 0; i< this->numVertices; i++){
                cout << i << " ";
                for(Aresta* a = vertices[i]->proximo; a != NULL; a = a->proximo )
                    cout << a->valor << " ";
                cout << endl;
            }
        }

        /* Metodo para verificar os componentes conexos a partir de uma
         * busca em profundidade.
         * Complexidade BUSCA EM PROFUNDIDADE O(V + E) sendo V = numero de vertices
         * e E numero de arestas do grafo, pois ele irá visitar todos B
         * Complexidade Algoritmo com print O(V^2) -> Ira passa por todos os vertice
         * no pior caso a busca em profundidade passa por todos vértices do componente conexo
         * @return int numero de componentes conexos
         */
        int verificarComponentesConexos(){
            int cont = 0; // Conatdor componetes conexos

            // Vetor para marcar vretices visitados na dfs
            this->visitados = (bool*)malloc(sizeof(bool)*this->numVertices);

            // Iniciar todos os vertices como nao visitaods
            for(int i = 0; i < this->numVertices; i++)
                this->visitados[i] = false;
            

            // Busca em profundidade
            for(int i = 0; i < this->numVertices; i++){
                if(!visitados[i]){ // Procurar componente nao visitado 
                    cont++; // Se encontrou, ha mais um componente conexo
                    DFS(i); // Busca em profunidade a partir do vertice nao visitado

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
         Aresta* criarAresta(int vertice, int valor){  
            Aresta* nova = (Aresta*) malloc(sizeof(Aresta));
            nova->valor = valor;
            nova->vertice = vertice;
            nova->proximo = NULL;
            return nova;
        }
};

int main(){
    // Leitura numero de estacoes e conexoes
    int numEstacoes;
    int numConections;

    cin >> numEstacoes;
    cin >> numConections;

    string ori;
    string dest;
    int posOri = -1;
    int posDest = -1;
    int cont = 0;
    int val = 0;

    string vertInicial;
    int posInicial = -1;

    while(numEstacoes != 0){
        Grafo* g = new Grafo(numEstacoes);
        string nomeEstacoes[numEstacoes];

        for(int i = 0; i < numEstacoes; i++){
            cin >> nomeEstacoes[i];
        }

        // Mapeamento string | posicao O(n^2)
        // Busca simples
        for(int i = 0; i < numConections; i++){
            cin >> ori;
            cin >> dest;
            // Procurando posicao da string no vertor de strings
            while(posOri == -1 || posDest == -1){
                if(nomeEstacoes[cont] == ori)
                    posOri = cont;
                if(nomeEstacoes[cont] == dest)
                    posDest = cont;
                cont++;
            }
            cin >> val;
            g->adicionarAresta(posOri, posDest, val);

            posOri = -1;
            posDest = -1;
            cont= 0 ;
        }
        cont = 0;
        cin >> vertInicial; // Leitura para mover cursor
        
        // Se grafo tiver mais de um componente conexo,
        // entao nao ha caminho entre todas estacoes
        if(g->verificarComponentesConexos() != 1)
            cout << "Impossible"<< endl;
        else
            cout << g->getMenorCusto() << endl;

        cin >> numEstacoes;
        cin >> numConections;

        // Limpar dados
        cont = 0;
        posOri = -1;
        posDest = -1;
        posInicial = -1;
    }
    return 0;
}

