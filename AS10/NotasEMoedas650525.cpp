/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS10 - Algoritmos Gulosos
 * Complexidade: O(1)
 */

 /* ANALISE DE COMPLEXIDADE
  * Para resolver o problema, utiliza-se um metodo
  * O(1), que indepente do valor recebido ira executar 10 divisoes,
  * 10 subtracoes, 10 multiplicoes e 12 prints, para definir a quantidade
  * minima de moedas e notas para ter um valor em dinheiro.
  */

#include <iostream>

using namespace std;

/* Metodo que utiliza um algoritmo guloso para definir a menor quantidade
 * de cada valor de notas e moedas necessarias para atingir um valor 
 * recebido como parametro. O algoritmo sempre escolhe a maior quantidade
 * da maior nota possivel em um certo momento, logo depois desconta a soma
 * do valor das notas escolhidas do valor total. O metodo funciona, pois 
 * todas as notas e moedas sao maiores que 2 vezes as notas menores, logo
 * para atingir o valor de uma de 50, por exemplo, sera descartado o uso
 * de 2 notas de 20 e uma de 10, pois assim aumentara algo que o metodo
 * quer minimizar.
 * @param int valorInteiro, int valorFrac
 */
void verificarQuantidadeNotasEMoedas(int valorInteiro, int valorFrac){
    int quantidadeNotas, quantidadeMoedas;

    cout << "NOTAS:" << endl;

    // Divisao no mundo dos inteiros, ira retornar a 
    // quantidade inteira de notas de 100 que "cabem"
    // em valorInteiro
    quantidadeNotas = valorInteiro/100;
    cout << quantidadeNotas << " nota(s) de R$ 100.00" << endl; 
    valorInteiro = valorInteiro - 100 * quantidadeNotas; // Atualizar vaor inteiro

    quantidadeNotas = valorInteiro/50;
    cout << quantidadeNotas << " nota(s) de R$ 50.00" << endl; 
    valorInteiro = valorInteiro - 50 * quantidadeNotas;

    quantidadeNotas = valorInteiro/20;
    cout << quantidadeNotas << " nota(s) de R$ 20.00" << endl; 
    valorInteiro = valorInteiro - 20 * quantidadeNotas;

    quantidadeNotas = valorInteiro/10;
    cout << quantidadeNotas << " nota(s) de R$ 10.00" << endl; 
    valorInteiro = valorInteiro - 10 * quantidadeNotas;

    quantidadeNotas = valorInteiro/5;
    cout << quantidadeNotas << " nota(s) de R$ 5.00" << endl; 
    valorInteiro = valorInteiro - 5 * quantidadeNotas;

    quantidadeNotas = valorInteiro/2;
    cout << quantidadeNotas << " nota(s) de R$ 2.00" << endl; 
    valorInteiro = valorInteiro - 2 * quantidadeNotas;

    cout << "MOEDAS:" << endl;
    // Nao ha necessidade de dividir por 1 
    cout << valorInteiro << " moeda(s) de R$ 1.00" << endl;

    quantidadeMoedas = valorFrac/50;
    cout << quantidadeMoedas << " moeda(s) de R$ 0.50" << endl; 
    valorFrac = valorFrac - 50 * quantidadeMoedas;

    quantidadeMoedas = valorFrac/25;
    cout << quantidadeMoedas << " moeda(s) de R$ 0.25" << endl; 
    valorFrac = valorFrac - 25 * quantidadeMoedas;

    quantidadeMoedas = valorFrac/10;
    cout << quantidadeMoedas << " moeda(s) de R$ 0.10" << endl; 
    valorFrac = valorFrac - 10 * quantidadeMoedas;

    quantidadeMoedas = valorFrac/5;
    cout << quantidadeMoedas << " moeda(s) de R$ 0.05" << endl; 
    valorFrac = valorFrac - 5 * quantidadeMoedas;
    
    // Nao ha necessidade de dividir por 1 
    cout << valorFrac << " moeda(s) de R$ 0.01" << endl; 
    
}

int main(){
    int valorInteiro, valorFrac;    
    char ponto;
    
    // Leitura parte inteira (Notas e moeda de 1 real)
    cin >> valorInteiro;
    // Leitura do ponto para limpar buffer 
    cin >> ponto;    
    // Leitura parte fracionaria (Moedas menores que 1 real)
    cin >> valorFrac;

    verificarQuantidadeNotasEMoedas(valorInteiro, valorFrac);

    return 0;
}

