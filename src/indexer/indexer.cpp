#include <iostream>
#include "indexer.hpp"
#include <filesystem>
#include <fstream>
#include "index/index.hpp"
#include "text-processor/text-processor.hpp"

Index Indexer::construir(string diretorio){
	TextProcessor textProcessor;
	Index index;
	/*Este comando deve varrer o diretório especificado e construir o índice invertido*/
	filesystem::path caminho = diretorio;
	if (!exists(caminho))
	{
		cout << "Diretório não encontrado" << endl;
		index.indiceCriado = false;
		return index;
	}
	// Percorre os arquivos do diretório
	for (const auto &entry : filesystem::directory_iterator(caminho))
	{
		// Verifica se é arquivo .txt
		if (entry.is_regular_file() && entry.path().extension() == ".txt"){
			cout << "Indexando arquivo: " << entry.path().string() << endl;
			ifstream file(entry.path());
			if (!file.is_open()){
				cout << "Erro ao abrir o arquivo!" << endl;
				continue; // vai para o próximo arquivo
			}
			// Lê o conteúdo linha por linha
			string linha;
			while (getline(file, linha)){
				vector<string> palavras = textProcessor.processar(linha);
				for (auto &palavra : palavras){
					index.adicionar(palavra, filesystem::absolute(entry.path()).string());
				}
			}
			file.close();
		}
	}
	return index;
}
