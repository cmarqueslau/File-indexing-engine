#include <iostream>
#include "indexer.hpp"
#include <filesystem>
#include <fstream>
#include "text-processor/text-processor.hpp"
#include "index/index.hpp"
;
Index Indexer::construir(string diretorio){
	TextProcessor textProcessor;
	Index index;
	/*Este comando deve varrer o diretório especificado, construir o índice invertido e salvá-lo em um
	arquivo padrão index.dat no diretório atual*/
	filesystem::path caminho = diretorio;
	if (!exists(caminho))
	{
		cout << "Diretório não encontrado" << endl;
		return;
	}
	// Percorre os arquivos do diretório
	for (const auto &entry : filesystem::directory_iterator(caminho))
	{
		// Verifica se é arquivo .txt
		if (entry.is_regular_file() && entry.path().extension() == ".txt")
		{
			ifstream file(entry.path());
			if (!file.is_open())
			{
				cout << "Erro ao abrir o arquivo!" << endl;
				continue; // vai para o próximo arquivo
			}
			// Lê o conteúdo linha por linha
			string linha;
			while (getline(file, linha))
			{
				vector<string> palavras = textProcessor.processar(linha);
				for (auto &palavra : palavras)
				{
					index.adicionar(palavra, entry.path().string());
				}
			}
			file.close();
		}
	}
	return index;
}
