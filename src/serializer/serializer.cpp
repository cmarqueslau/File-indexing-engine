#include "serializer.hpp"
#include <fstream>
#include <filesystem>

void Serializer::salvar(Index index, string arquivo){
	index.criarArquivoIndex();
}
Index Serializer::carregar(){
	Index index;
	unordered_map<string, unordered_set<unsigned int>> indiceDoArquivo;
	ifstream arquivo("index.dat", ios::binary);
	if (!arquivo.is_open()){
		cout << "Erro ao abrir o arquivo index.dat" << endl;
		return;
	}
	string linha;
	while (getline(arquivo, linha)){
		size_t pos = linha.find(":");
		string palavra = linha.substr(0, pos);
		unordered_set<unsigned int> ids;
		size_t start = pos + 1;
		while (start < linha.size()){
			size_t end = linha.find(",", start);
			string idStr = linha.substr(start, end - start);
			unsigned int id = stoi(idStr);
			ids.insert(id);
			start = end + 1;
		}
		indiceDoArquivo[palavra] = ids;
	}
	index.popularIndiceDeArquivo(indiceDoArquivo);
	return index;
}