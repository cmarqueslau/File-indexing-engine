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
void Index::criarArquivoIndex()
{
	ofstream arquivo("index.dat", ios::binary);
	if (!arquivo.is_open())
	{
		cout << "Erro ao criar o arquivo index.dat" << endl;
		return;
	}
	for (const auto &p : indice)
	{
		arquivo << p.first << ":";
		for (auto id : p.second)
			arquivo << id << ",";
		arquivo << "\n";
	}
	arquivo.close();
	ofstream arquivoIds("ids.dat", ios::binary);
	if (!arquivoIds.is_open())
	{
		cout << "Erro ao criar o arquivo ids.dat" << endl;
		return;
	}
	for (const auto &[chave, valor] : idParaArquivo)
	{
		arquivoIds << chave << ":" << valor << "\n";
	}
	arquivoIds.close();
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