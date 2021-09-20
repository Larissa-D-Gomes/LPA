/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS07 - Forca Bruta
 * Complexidade: O(n^2) Desconsiderando leitura de pontos
 */

 /* Complexidade O(N^2)
  * O metodo calculaParMenor, recebe uma matriz de pontos e a quantidade de pontos.
  * A matriz funciona como um vetor de pontos, pois as linhas armazenam X e Y de cada 
  * ponto. 
  * A partir dessa matriz um primeir for seleciona um ponto i, esse ponto i ira ter sua 
  * distancia calculada entre todos os pontos j, que comecam de i + 1 ate o total de
  * pontos. A abordagem forca bruta e esta, ja que todos os pontos sao calculados com 
  * todos os outros pontos. 
  * Como um for varia de 0 ate n, e o for interno de i + 1 ate n, sendo n o numero de pontos, 
  * a solucao do problema e O(n^2).
  */


#include <iostream>
#include <string>
#include <cfloat>
#include <math.h>
#include <iomanip>  

using namespace std;

/* Metodo para calcular a menor distancia entre os ponto presentes em um
 * conjunto de pontos recebido como parametro. Os pontos sao armazendos em 
 * uma estrutura de matriz em que as linhas representa X e Y e as colunas cada ponto.
 * Ex: pontos[0][1] - X do ponto 1, pontos[1][3] - Y do ponto 3
 * O metodo utiliza a abordagem forca bruta, em que calcula a distancia
 * de todos os pontos com todos os pontos. Para isso se utiliza um for
 * aninhado a outro que percorrem n elementos, obtendo uma complexidade O(n^2), 
 * sendo n a quantidade de pontos.
 * @param double** pontos, int quantPontos
 * @return double menorDistancia
 */
double calculaMenorPar(double** pontos, int quantPontos){
    double menor = DBL_MAX; // Menor = Infinito
    double distancia;

    // Repticao O(n^2) -> Forca Bruta
    // Selecionar um ponto i 
    for(int i = 0; i < quantPontos; i++){
        // Selecionar um ponto j que nao foi calculado com i
        for(int j = i + 1; j < quantPontos; j++){
            // Calculando distancia entre dois pontos
            // distancia = raizquadrada((pontojX - pontoiX)^2 +  (pontojY - pontoiY)^2)
            distancia = pow( 
                      (
                         pow(pontos[0][j] - pontos[0][i], 2) + pow(pontos[1][j] - pontos[1][i], 2)
                      ),
                  0.5); 

            // Se nova distancia distancia calculada e menor que a anterior
            // trocar menor 
            if(distancia < menor)
                menor = distancia;
        }
    }

    return menor;
}

int main(){
    int numCasosTeste;

    double result;
    // Alocar espaco para x e y em linhas de cada ponto
    double** pontos = (double**) malloc(sizeof(double*) * 2); 
    
    cin >> numCasosTeste;

    while(numCasosTeste != 0){ 

        // Aloca quantidade de pontos
        pontos[0] = (double*) malloc(sizeof(double) * numCasosTeste); // Quantidade de x
        pontos[1] = (double*) malloc(sizeof(double) * numCasosTeste); // Quantidade de y

        // Lendo pontos
        for(int i = 0; i < numCasosTeste; i++){
            cin >> pontos[0][i]; // Lendo x
            cin >> pontos[1][i]; // Lendo y
        }
        
        // Calcular menor par
        result = calculaMenorPar(pontos, numCasosTeste);

        // se resultado >= 10000, imprimir INFINITY
        // std::fixed << std::setprecision(4) -> setar precisao de casas decimais no print
        result < 10000.0 ? cout << std::fixed << std::setprecision(4) << result << endl : cout << "INFINITY" << endl; 
        
        cin >> numCasosTeste;        
    }

    return 0;
}

