/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: AS03 - Estrutura de Dados
 * Complexidade: O(n)
 */

/* O problema de verificar subsequencias e O(n) que verifica se ume 
 * query e subsequencia de uma sequencia. 
 * O problema e linear, resolvido com 1 while que pode repetir
 * tamanho da sequencia vezes ou tamanho da query vezes.
 * No pior caso O(n) | n + 2 comparacoes | 2*n subtracoes + 2| 
 */

#include <iostream>
#include <string>

using namespace std;

/* Metodo O(n) que verifica se query e subsequencia de
 * sequencia. Exemplo sequencia = "ABCAD" query = "ABCD"
 * ABCAD -> sequencia
 * ABC D -> query -> verdadeiro
 * @param string sequencia, string query
 * @return bool
 */
bool isSubsequencia(string sequencia, string query) {
    // comercar deslocamento da ultima posicao de cada string
	int deslocamentoQuery = query.length() - 1;
	int deslocamentoSequencia = sequencia.length() - 1;

    // Repeticao que percorre toda string de sequencia ou percorre
    // a sequencia ate encontrar todo o padrao da query
    // Repeticao no pior caso O(n) | 2n + 1 comparacoes | 2*n subtracoes
    // N = deslocamentoQuery ou deslocamentoSequencia
	while(deslocamentoQuery >= 0 && deslocamentoSequencia >= 0){
        // So ira deslocar na query quando encontrar o proximo caracter da
        // subsequencia query na sequencia 
		if (query[deslocamentoQuery] == sequencia[deslocamentoSequencia])
			deslocamentoQuery--; // deslocando na query
        deslocamentoSequencia--; // deslocando na sequencia
    }

    // Se deslocamento query = -1 entao todos os caracteres
    // da query foram encontrados na sequencia e a query 
    // e subssequencia
	if (deslocamentoQuery == -1)
		return true;
	
    // Nem todos caracteres da query foram encontrados,
    // A query nao e subsequencia
    return false;

}

int main(){
    int numCasosTeste;
    int numQueries;
    cin >> numCasosTeste;
    
    string sequencia;
    string query;

    //Repeticao de N casos de teste conforme 
    //Inteiro lido na primeira leitura
    for(; numCasosTeste > 0; numCasosTeste--){
        // leitura de sequencia principal
        cin >> sequencia;
        // leitura de quantidade de queries (pesquisa) para sequencia
        cin >> numQueries;
        
        // Repeticao para leitura e teste das queries lidas
        for(; numQueries > 0; numQueries--){
            // leitura de padrao que sera pesquisado
            cin >> query;

            if(isSubsequencia(sequencia, query))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }

    }

    return 0;
}

