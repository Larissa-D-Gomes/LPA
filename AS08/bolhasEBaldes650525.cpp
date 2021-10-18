/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS08 - Divisão e Conquista
 * Complexidade: O(n log(n))
 */

/* ANALISE DE COMPLEXIDADE
 * Para se resolver o problema, utiliza-se o metodo mergesort, que trabalha com o
 * conceito de divisao e conquista para ordenar a sequencia.
 * O metodo mergersort divide o vertor recursivamente no meio ate conseguir varios 
 * vetores de tamanho 2, sendo assim, a complexidade da recursao e log n, sendo n 
 * o tamanho do vetor. Apos ordenar vetores muito pequenos, o merge sort faz a 
 * ordenacao de vetores maiores, que seria a combinacao de dois vetors pequenos.
 * Posterior mente o metodo merge, que ordena o vetor por intercalacao e chamado,
 * esse metodo possui complexidade O(n), sendo n o tamanho dos subvetores. 
 * Dessa forma, chamando um metodo O(n) log n vezes, o problema e resolvido
 * com uma complexidade 0(n log n)
 */

#include <iostream>
#include <climits> 

using namespace std;

/* Metodo para intercalar subarrays gerados pelo merge sorte
 * A intercalacao ordenar dois sub vetores gerando um vetor maior
 * Metodo O(n), sendo n a soma de tamanhos dos subarrays
 * @param int* sequencia, int init, int meio, int fim
 * @return contador de trocas 
 */
int merge(int* sequencia, int init, int meio, int fim){
    int contTrocas = 0;

    // Tamanho dos vetores
    int tamMet1 = meio + 1 - init;
    int tamMet2 = fim - meio;

    // Vetores para copiar a primeira e segunda metade do
    // vetor sequencia
    int metade1[tamMet1 + 1];
    int metade2[tamMet2 + 1];

    // Copiando metade1 da sequencia
    for(int i = 0; i < tamMet1; i++){
      metade1[i] = sequencia[init + i];
    }
    
    // Copiando metade2 da sequencia
    for(int j = 0; j < tamMet2; j++){
      metade2[j] = sequencia[meio + j + 1];
    }
    // Evitar comparações caso um vertor seja copiado inteiramente 
    // antes do outro durante a intercalacao
    // Ultima posicao = infinito, logo ela nunca sera escolhida
    metade1[tamMet1] = INT_MAX;
    metade2[tamMet2] = INT_MAX;
    
    // Variavei para caminhar nos vetores de metade
    int m1, m2;
    // Variavel para armazenar intercalacao ordenada no verto sequencia
    int i = init;

    // Ordenacao por intercalacao
    for(m1 = 0, m2 = 0; i <= fim ; i++){
        if(metade2[m2] < metade1[m1]){
            //Aramazenar menor valor na sequancia
            sequencia[i] =  metade2[m2++];
            // Numero de trocas para armazenar o valor metade2[m2] na sequencia 
            // equivale ao quantidade de elementos da metade 1 que nao foram
            // armazenados na sequencia
            contTrocas += tamMet1 - m1;
        } else{
           sequencia[i] = metade1[m1++]; 
        }
    }

    return contTrocas;
}

/* Metodo recursivo merge sort
 * O metodo divide um problema maior (sequencia) em problemas menores
 * dividido a sequencia em vario sub sequencia ate atingir um tamanho muito pequeno,
 * que o programa consiga ordenar, depois volta recursivamente ordernando os problemas
 * menores resolvidos.
 * Metodo mergesort -> chama logn vezes o metodo merge que e o n, sendo n o tamanho da sequencia
 * Complexidade  O(n logn)
 * @param int* sequencia, int init, int fim
 * @return int contador de trocas em todas intercalacoes
 */
int mergeSort(int* sequencia, int init, int fim){
    int contTrocas = 0;
    // Base da recursao
    if(fim <= init)
        return contTrocas;

    // Dividir vertores
    int meio = (init+fim)/2;
    contTrocas += mergeSort(sequencia, init, meio);
    contTrocas += mergeSort(sequencia, meio + 1, fim); 
    
    // Ordenacao
    contTrocas += merge(sequencia, init, meio, fim);
    return contTrocas;
}


int main(){
    int tamSeq;
    int numTrocas;
    //Lendo tamanho da primeira sequencia
    cin >> tamSeq;

    // Leitura ate tamanho da sequencia ser igual a 0
    while(tamSeq != 0){
        // Alocando sequencia
        int sequencia[tamSeq];
        // Lendo sequencia O(n) | n = tamSeq
        for(int i = 0; i < tamSeq; i++)
            cin >> sequencia[i];

        numTrocas = mergeSort(&sequencia[0], 0, tamSeq-1);    
        
         if(numTrocas % 2 == 0)
            cout << "Carlos" << endl;
        else
            cout << "Marcelo" << endl;

        cin >> tamSeq;
    }

    return 0;
}

