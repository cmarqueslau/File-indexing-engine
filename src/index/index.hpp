#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Index{
	public:
	void adicionar(const string& palavra, const string& nome_arquivo);
	vector<string> getArquivosPorPalavra(string& palavra);
	void popularIndiceDeArquivo(unordered_map<string, unordered_set<unsigned int>> indiceDoArquivo);
	void popularIdParaArquivo(unordered_map<unsigned int, string> ids);
	unordered_map<string, unordered_set<unsigned int>>& getIndice() { return indice; }
	unordered_map<unsigned int, string>& getIdParaArquivo() { return idParaArquivo; }
	bool indiceCriado = false;
	private:
	unordered_map<string, unordered_set<unsigned int>> indice;
	unordered_map<unsigned int, string> idParaArquivo;
	unordered_map<string, unsigned int> arquivoParaId;
	unsigned int proximoId = 0;
};