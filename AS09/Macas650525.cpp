/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS09 - Programacao Dinamica
 * Complexidade:  O(2^n * n^2)
 */


/* Analise de complexidade:
 * O algoritmo utilizado para calcular o maximo de macas que podem ser
 * calculadas, se baseia no problema do caixeiro vaijante, com programacao
 * dinamica sendo assim, a complexidade para resolver o problema de forma
 * recursiva eh O(2^n * n^2). Como o algoritmo impede que estados ja calculados
 * com a programcao dinamica, o problema resolvido deixa de ser O(n!).
 */ 


#include <iostream>

using namespace std;


// Matriz tridimensional para amarmazenar posicao e tempo que cada maca caiu
int macas[21][21][2001];

// Matriz tridimensional para amarmazenar resultadosCalculados
// da funcao que busca o maximo de macas possiveis que podem ser capturadas
// Programacao dinamica -> evitar calcular o que ja foi calculado
int resultadosCalculados[21][21][2001];

// Variaveis globais para controle de posicao nas matrizes globais
int linhas, colunas, numMacas;


/* Funcao para calcular o maximo de macas que e possivel capturar
 * O metodo foi inpirado no caixeiro viajante dinamico, a partir de uma
 * posicao inicial, ha uma analise de quantas macas e possivel capturar
 * quando se mover para cada posicao possivel. O calculo para cada posicao
 * e tempo e armazenado em uma matriz tridimensional, que ira armazenar
 * o maximo de macas ja calculados para cada estado.
 * @param int linha, int coluna, int tempo
 * @return int maximoDeMacasCapturadas para estado recebido como parametro
 */
int calculaMaxMacas(int linha, int coluna, int tempo){

    // Calcular apenas para resultadosCalcmacasuladosicoes validas
     if(linha > 0 && linha <= linhas && coluna > 0 && coluna <= colunas){
        // Estado ainda nao calculado
        // Verificacao para evitar calcular o que ja foi calculado
        if(resultadosCalculados[linha][coluna][tempo] == -1){
            int aux;

            // Ficar no mesmo local
            int max = calculaMaxMacas(linha, coluna, tempo + 1);  

            // Mover para direita
            aux = calculaMaxMacas(linha + 1, coluna, tempo + 1);  
            max = max < aux ? aux : max; // Se aux maior que max, alterar max para aux
  
            // Mover para tras
            aux = calculaMaxMacas(linha, coluna + 1, tempo + 1);
            max = max < aux ? aux : max;

            // Mover para diagonal (direita/atras)
            aux = calculaMaxMacas(linha + 1, coluna + 1, tempo + 1); 
            max = max < aux ? aux : max;

            // Mover para esquerda
            aux = calculaMaxMacas(linha - 1, coluna, tempo + 1); 
            max = max < aux ? aux : max;

            // Mover para frente
            aux = calculaMaxMacas(linha, coluna - 1, tempo + 1); 
            max = max < aux ? aux : max;

            // Mover para diagonal (frente/esquerda)
            aux = calculaMaxMacas(linha - 1, coluna - 1, tempo + 1); 
            max = max < aux ? aux : max;

            // Mover para diagonal (direta/atras)
            aux = calculaMaxMacas(linha + 1, coluna - 1, tempo + 1); 
            max = max < aux ? aux : max;

            // Mover para diagonal (esquerda/frente)
            aux = calculaMaxMacas(linha - 1, coluna + 1, tempo + 1); 
            max = max < aux ? aux : max;

            // Armazenar melhor resutado calculado para esse estado -> max + maca no tempo e 
            // posicao atual
            resultadosCalculados[linha][coluna][tempo] = max + macas[linha][coluna][tempo];
            
        }
        // Retornar resultado calculado
        return resultadosCalculados[linha][coluna][tempo];

    }
    // Retornar 0, pois posicao nao existe, logo e impossivel
    // calcular macas capturadas 
    return 0;
}



int main(){
    int linha, coluna, tempo;

    cin >> linhas;

    while(linhas > 0){
        cin >> colunas;
        cin >> numMacas;

        // Matriz tridimensional para armazenar 
        // E tempo que cada maca caiu

        // Inicializando matriz de macas caidas com 0 macas
        // E matriz de resultado calculados, sem resultados calculados
        // Para todos estados
        for(int i = 0; i <= linhas; i++){
            for(int j = 0; j <= colunas; j++){
                for(int k = 0; k <= numMacas; k++){
                    macas[i][j][k]  = 0;
                    resultadosCalculados[i][j][k] = -1;
                }
            }
        }
        

        for(int i = 0; i < numMacas; i++){
            // Leitura do tempo e posicao em que cada maca caiu
            cin >> linha;
            cin >> coluna;
            cin >> tempo;
            
            macas[linha][coluna][tempo] = 1;
        }

        // Leitura posicoes iniciais
        cin >> linha;
        cin >> coluna;

        cout << calculaMaxMacas(linha, coluna, 0) << endl;
        cin >> linhas;
    }

    return 0;
}

