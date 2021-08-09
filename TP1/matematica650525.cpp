/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: TP1 - Matematica
 * Complexidade: O(n*m)
 */

#include <iostream>

using namespace std;

/* Funcao iterativa para calculo fatorial
 * Complexidade O(n) n = num 
 * Comparações = n - 1 | Atribuições = 2 + 2 * (n-1) | Mutiplicacoes = n-1 (n > 1) | Soma = n-1 (n > 1)
 * @param long long int num
 * @return long long int calculo fatorial de num
 */
long long int  fatorial(long long int  num){
    long long int  fact = 1;

    // interacao => num - 1
    // a cada iteracao 1 soma, 1 multiplicacao, 2 atribuicao, 1 comparacao
    for(long i = 2; i <= num; i++)
        fact *= i;

    return fact;
}

int main(){
    long long int m;
    long long int n;
    
    /* Complexidade while O(n) n = numero de entradas
     * Leituras = n*2 | Somas = n
     */
    while(cin >> n){ // Verificacao EOF
        cin >> m; 
        cout << fatorial(n) + fatorial(m) << endl;
    }

    return 0;
}

/* A funcao main faz m*2 (m = numero de entrada) chamadas 
 * a funcao fatorial, que tem complexidade O(n), logo a 
 * partir da funcao main, temos um algoritmo de complexidade
 * O(m*n) 
 */

