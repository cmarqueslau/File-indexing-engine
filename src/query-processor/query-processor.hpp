#pragma once
#include <iostream>
#include <vector>
using namespace std;

class QueryProcessor{
	public:
	vector<string> buscar(string consulta);
	/*Este comando deve primeiro verificar se o arquivo de índice existe na pasta atual. Se não, deve
	informar ao usuário para executar a indexação primeiro. Se o índice existir, ele deve ser carregado
	em memória. A busca deve ser realizada e os nomes dos arquivos relevantes, impressos na tela.*/
};