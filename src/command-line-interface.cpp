#include <iostream>
#include "index/index.hpp"
#include "indexer/indexer.hpp"
#include "query-processor/query-processor.hpp"
#include "serializer/serializer.hpp"
#include "text-processor/text-processor.hpp"
using namespace std;
int main(int argc, char* argv[]){
	cout << "Bem vindo ao indexador de arquivos!" << endl;
	cout << "Comandos disponiveis:" << endl;
	cout << "1. Modo Indexação: indice construir <caminho_do_diretorio>" << endl;
	cout << "2. Modo Busca: indice buscar <termo_de_busca>" << endl;
	if(argc < 4){
		cerr << "Erro: Nenhum comando especificado." << endl;
		return 1;
	}
	if(argv[2] == string("construir")){
		/*Este comando deve varrer o diretório especificado, construir o índice invertido e salvá-lo em um
		arquivo padrão index.dat no diretório atual.*/
		string caminho_diretorio = argv[3];
		Indexer indexer;
		Index index = indexer.construir(caminho_diretorio);
		Serializer serializer;
		serializer.salvar(index);
		cout << "Índice criado com sucesso!" << endl;
	} else if(argv[2] == string("buscar")){
		/*Este comando deve primeiro verificar se o arquivo de índice existe na pasta atual. Se não, deve
		informar ao usuário para executar a indexação primeiro. Se o índice existir, ele deve ser carregado
		em memória. A busca deve ser realizada e os nomes dos arquivos relevantes, impressos na tela.*/
		Serializer serializer;
		Index index = serializer.carregar();
		if(!index.indiceCriado){
			cerr << "Erro: Nenhum índice encontrado. Por favor, execute a indexação primeiro." << endl;
			return 1;
		}
		for(int i = 3; i < argc; i++){
			string termo_de_busca = argv[i];
			QueryProcessor queryProcessor;
			vector<string> arquivos = queryProcessor.buscar(termo_de_busca, index);
			if(arquivos.size() == 0){
				cout << "Nenhum arquivo encontrado para o termo '" << termo_de_busca << "'." << endl;
			}else{
				cout << "Arquivos encontrados para o termo '" << termo_de_busca << "':" << endl;
				for(string& arquivo : arquivos){
					cout << "- " << arquivo << endl;
				}
			}
		}

	} else {
		cerr << "Erro: Comando desconhecido '" << argv[1] << "'." << endl;
		return 1;
	}
	return 0;
}