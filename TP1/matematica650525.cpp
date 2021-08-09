/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: TP1 - Matematica
 * Complexidade problema fatorial de dois numeros: O(n + m) -> Desconsiderando a leitura de entradas
 */


/* ANALISE DO CODIGO (Desconsiderando loop de entradas)
 * A complexidade da funcao do calculo do fatorial e O(n)
 * Como 2 fatoriais sao calculados teriamos uma problema resolvido com O(n + m)
 * pois os 2 loops simples serao excutados para que a soma dos fatoriais 
 * seja feita
 */
#include <iostream>

using namespace std;

/* Funcao iterativa para calculo fatorial
 * Complexidade O(n) n = num 
 * Comparações = n - 1 | Atribuições = 2 + 2 * (n-1) | Mutiplicacoes = n-1 (n > 1) | Soma = n-1 (n > 1)
 * @param long long int num
 * @return long long int calculo fatorial de num
 */
long long int  fatorial(long long int num){
    long long int fact = 1;

    /* interacao => num - 1
     * a cada iteracao 1 soma, 1 multiplicacao, 2 atribuicao, 1 comparacao
     * calculo para num >= 2 
     */
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

