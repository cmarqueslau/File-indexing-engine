#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Index{
	public:
	void adicionar(string palavra, string nome_arquivo);
	vector<string> getArquivosPorPalavra(string palavra);
	string getNomeArquivoPorId(int id);
};