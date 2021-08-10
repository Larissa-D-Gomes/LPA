/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS02 - Strings
 * Complexidade: 0(n)
 */

/* Analise de complexidade para resolver o problema
 * de quantidade de leds
 * O problema foi resolvido com duas funcoes, uma contante e 
 * outra itertiva, com uma itercao simples. A funcao mais 
 * complexa e a iterativa O(n), por isso o problema e resolvido
 * com a complexidade O(n)
 */

 #include <iostream>
 #include <string>

using namespace std;

/* Funcao que retorna um array preechido com a quantidade de 
 * leds acessos por algarismo de 0-9 posições. Ex: 
 * arrayLed[1] = 2 -> 2 leds necessarios para o numero 1 
 *   |
 *   |
 * arrayLed[2] = 5 -> 5 leds necessarios para o numero 2
 *  _
 *  _|
 * |_
 * @return int* arrayLed
 * COMPLEXIDADE: O(1) -> Constante nao ha iteracoes, sempre acontecem 
 * 11 atribuicoes
 */
int* getNumLedsPorAlgarismo(){
    int* arrayLed =  (int*) malloc (10 * sizeof(int)); // alocacao de memoria 

    // 10 atribuicoes
    arrayLed[0] = 6;
    arrayLed[1] = 2;
    arrayLed[2] = 5;
    arrayLed[3] = 5;
    arrayLed[4] = 4;
    arrayLed[5] = 5;
    arrayLed[6] = 6;
    arrayLed[7] = 3;
    arrayLed[8] = 7;
    arrayLed[9] = 6;

    return arrayLed;
}

/* Funcao que ira contar o numero de leds necessarios 
 * para o numero aramazenado em string
 * COMPLEXIDADE: O(n) -> n = tamanho da string numero
 * iteracao simples para analiser leds para cada algarismo
 * Atribuicoes = tamanho da string numero * 2 + 2 | 
 * Soma = tamanho da string numero
 * @param int* arrayLed, string numero
 * @return int somaLeds -> total de leds necessarios 
 */
int somatorioLeds(int* arrayLed, string numero){
    int somaLeds = 0;
    int tamString = numero.length();

    // Somar quantidade de leds de cada algarismo para total do
    // numero atribuicao na soma e no for
    for(char algarismo : numero){
        // somaLeds = arrayLed[char algarismo convertido para numero numero] 
        somaLeds += arrayLed[stoi(&algarismo)];
    }

    return somaLeds;
}

int main(){

    int entradas = 0;
    string leitura;
    cin >> entradas;

    int* arrayLed = getNumLedsPorAlgarismo();

    //leitura de entradas conforme numero lido na primeira entrada
    for(; entradas > 0 ; entradas--){
        cin >> leitura; // leitura de numero como string para facilitar iteracao de contagem de leds

        //chamada e print de retorno da funcao que ira contar os leds do numero lido
        cout << somatorioLeds(arrayLed, leitura) << " leds" << endl;
    }

    return 0;
}

