#include <iostream>
#include <vector>
#include "text-processor/text-processor.hpp"
using namespace std;
int main(){
	TextProcessor tp;
	string texto = "Olá, você está aprendendo Algoritmos e Estruturas de Dados! muito bom, nÃo É?";
	cout << "Texto original:\n" << texto << "\n\nPalavras processadas:\n";
	vector<string> palavras = tp.processar(texto);
	for (const string &palavra : palavras){
		cout << palavra << endl;
	}
	return 0;
}