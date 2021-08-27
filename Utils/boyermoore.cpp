/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: Algortimo de Boyer-Moore
 */

#include <iostream>
#include <string>

using namespace std;

int* vetorOcorrenciaCharMaisADireita(string query, int tamQuery){
    // vetor com 58 posicoes, para considerar caracteres com letra maiuscula
    // diferente de minuscula 
    int* vetorOcorrencia = (int*)malloc(26*sizeof(int));

    //Preencher vetor com -1
    for(int i = 0; i < 58; i++)
        vetorOcorrencia[i] = -1;

    // Desconsiderar posicao mais a direita do ultimo caracter
    // Ela nao sera necessaria para relizar o deslocamento
    //tamQuery--;

    // Repeticao para preencher ultima posicao de cada caracter
    // o preenchimeto e feito por indice da tabela ascii 
    // considerando a posicao 65 como 0 no vetor
    for(int i = 0; i < tamQuery; i++)
        if((int)query[i] < 91)
            vetorOcorrencia[(int)query[i]-65] = i;
        else
            vetorOcorrencia[(int)query[i]-97] = i;

     //for(int i = 0; i < 58; i++)
       //  cout << char(i+65) << " " << vetorOcorrencia[i] << endl;

    return vetorOcorrencia;
}

bool boyerMoore(string sequencia, string query){
    int tamSequencia = sequencia.length();
    int tamQuery = query.length(); 
    int* vetorOcorrencias = vetorOcorrenciaCharMaisADireita(query, tamQuery);

    int deslocamento = 0;
    while(deslocamento <= (tamSequencia - tamQuery)){
        int i = tamQuery - 1;
        for(; i > -1 && query[i] == sequencia[deslocamento + i]; i--);

        if(i < 0)
            return true;

        if(i - vetorOcorrencias[sequencia[deslocamento+i-65]] > 1)
            deslocamento +=  i - vetorOcorrencias[sequencia[deslocamento + i-65]]-1;
        else
            deslocamento += 1;

    }

    return false;
}

string toUpper(string aux){
    string x = "";
    for(char i: aux)
        x += toupper(i);
    return x;
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

            if(boyerMoore(sequencia, query))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }

    }

    return 0;
}

