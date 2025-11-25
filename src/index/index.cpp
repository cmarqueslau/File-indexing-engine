#include "index.hpp"
#include <filesystem>
#include <fstream>

void Index::adicionar(const string &palavra, const string &nome_arquivo){
	filesystem::path caminho = nome_arquivo;
	if(!filesystem::exists(caminho)){
		idParaArquivo[proximoId] = nome_arquivo;
		arquivoParaId[nome_arquivo] = proximoId;
		indice[palavra].insert(proximoId);
		proximoId++;
	}else{
		indice[palavra].insert(arquivoParaId[nome_arquivo]);
	}
	ofstream file(caminho, ios::app);
	if(!file.is_open()){
		cout << "Erro ao abrir o arquivo " << nome_arquivo << endl;
		return;
	}
	file << palavra << endl;
	file.close();
}
vector<string> Index::getArquivosPorPalavra(string &palavra){
	vector<string> arquivos;
	for(auto& id : indice[palavra]){
		arquivos.push_back(idParaArquivo[id]);
	}
	return arquivos;
}
void Index::criarArquivoIndex(){
	ofstream arquivo("index.dat", ios::binary);
	if (!arquivo.is_open()){
		cout << "Erro ao criar o arquivo index.dat" << endl;
		return;
	}
	for (const auto &p : indice){
		arquivo << p.first << ":";
		for (auto id : p.second)
			arquivo << id << ",";
		arquivo << "\n";
	}
	arquivo.close();
}

void Index::popularIndiceDeArquivo(unordered_map<string, unordered_set<unsigned int>> indiceDoArquivo){
	indice = indiceDoArquivo;
}