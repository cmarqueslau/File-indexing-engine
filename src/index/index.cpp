#include "index.hpp"
#include <filesystem>
#include <fstream>

void Index::adicionar(const string &palavra, const string &nome_arquivo){
	if(arquivoParaId.count(nome_arquivo) == 0){
		arquivoParaId[nome_arquivo] = proximoId;
		idParaArquivo[proximoId] = nome_arquivo;
		proximoId++;
	}
	indice[palavra].insert(arquivoParaId[nome_arquivo]);
}
vector<string> Index::getArquivosPorPalavra(string &palavra)
{
	vector<string> arquivos;
	for (auto &id : indice[palavra])
	{
		arquivos.push_back(idParaArquivo[id]);
	}
	return arquivos;
}

void Index::popularIndiceDeArquivo(unordered_map<string, unordered_set<unsigned int>> indiceDoArquivo)
{
	indice = indiceDoArquivo;
}
void Index::popularIdParaArquivo(unordered_map<unsigned int, string> ids)
{
	idParaArquivo = ids;
	arquivoParaId.clear();
	for (const auto &p : ids)
	{
		arquivoParaId[p.second] = p.first;
	}
}