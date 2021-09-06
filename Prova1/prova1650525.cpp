/* Aluna: Larissa Domingues Gomes
 * Matrícula: 650525
 * Professor: Wladmir Brandao
 * Disciplina: LPA G01 - PUC-MG - CC
 * Problema: Prova 1
 * Complexidade: O(n) SEM ANALISAR ENTRADA
 */

 #include <iostream>
 #include <string>
 #include <cstring>
 #include <cstdio>
 
 using namespace std;

 /* O problema e linear, resolvido com 1 while que repete
  * tamanho da sequencia vezes, fazendo 9 comparacoes 
  * e 3 somas no pior caso em cada repeticao + 1 comparacao
  * na ultima repeticao 
  * No pior caso O(n), sendo n o tamanho da sequencia 
  */



using namespace std;

/* Metodo O(n) que verifica vencedor de acertos entre string repeticao 1
 * e repeticao 2 na string sequencia
 * metodo retorna quem acertou mais, caso tenha empate retorna quem
 * errou pela primeira vez por ultimo
 * @param string sequencia, string repeticao1, string repeticao2
 * @return int time vencedor    0-> nao houve vencedor
 */
int verificarAcertos(string sequencia, string repeticao1, string repeticao2) {

	int deslocamento = 0;

    // Variavel para contar numero de acertos
    int numAcertos1 = 0;
    int numAcertos2 = 0;

    // Auxiliares desempate
    // marcar se errou na posicao analisada
    bool t1acertou = true;
    bool t2acertou = true;
    // marcar se ja desempatou
    bool desempatou = false;

    // marcar vencedor do desempate
    int desempate = 0;

    int tamStrings = repeticao2.length();

    // Repeticao que percorre todas string para contar quantos acertos
    // cada time teve
    // Repeticao no pior caso O(n) | 5*n +1 comparacoes | 3*n somas 
    // N = deslocamento
	while( deslocamento <  tamStrings){
        // So ira contar caracteres iguais quando na mesma posicao tiver char iguais
		if (sequencia[deslocamento] == repeticao1[deslocamento]){
			numAcertos1++;
            t1acertou = true;
        }else{
            t1acertou = false; // t1 errou nessa posicao
        }

        // So ira contar caracteres iguais quando na mesma posicao tiver char iguais
        if (sequencia[deslocamento] == repeticao2[deslocamento]){
			numAcertos2++;
            t2acertou = true;
        }else{
            t2acertou = false; // t2 errou nessa posicao
        }

        // Desempate para ver quem errou primeiro 
        // Se nao houve desempate, e algum errou enquanto o
        // outro acertou, entao esse time foi o primeiro  errar
        if(!desempatou && t2acertou && !t1acertou){
            desempate = 2; // 2 vencedor do desempate, t1 errou primeiro
            desempatou = true; // marcar que ja houve desempate
        }
        else if(!desempatou && t1acertou && !t2acertou){
            desempate = 1; // 1 vencedor do desempate, t2 errou primeiro
            desempatou = true; // marcar que ja houve desempate
        }
        
        deslocamento++; // deslocando na sequencia
    }

    // Se algum time acertou mais, ele eh o vencedor
    if(numAcertos1 > numAcertos2)
        return 1;
    else if(numAcertos2 > numAcertos1)
        return 2;

    // se nao houve vencedor e o quem errou depois pela primeira vez
    return desempate;

}


 int main(){
    int quantidadeTeste;
    cin >> quantidadeTeste;

    string sequencia; // Sequencia original
    string repeticaoT1; // Repeticao do time 1
    string repeticaoT2; // Repeticao do time 2

    int vencedor; // Acertos do time 1 
    int acertost2; // Acertos do time 2

    getline(cin, sequencia);
    for(int i = 0 ; i < quantidadeTeste; i++){
        getline(cin, sequencia);
        getline(cin, repeticaoT1);
        getline(cin, repeticaoT2); 

        vencedor = verificarAcertos(sequencia, repeticaoT1, repeticaoT2);

        cout << "Instancia " << i+1 << endl;
        if(vencedor == 1)
            cout << "time 1" << endl; 
        else if(vencedor == 2)
            cout << "time 2" << endl;
        else // retorno = 0, nao houve vencedor
            cout << "empate" << endl;
        
        if(i != quantidadeTeste -1)
            cout << "\n";
    }

    return 0;
 }