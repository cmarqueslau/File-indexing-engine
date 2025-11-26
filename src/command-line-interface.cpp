#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include "index/index.hpp"
#include "indexer/indexer.hpp"
#include "query-processor/query-processor.hpp"
#include "serializer/serializer.hpp"
#include "text-processor/text-processor.hpp"
using namespace std;
int main(int argc, char* argv[]){
	cout << "-------------------------------------------------------------" << endl;
	cout << "\033[35mBem vindo ao indexador de arquivos!\033[0m" << endl;
	cout << "\033[35mComandos disponiveis:\033[0m" << endl;
	cout << "1. Modo Indexação: \033[92m indice construir <caminho_do_diretorio>\033[0m" << endl;
	cout << "2. Modo Busca: \033[92m indice buscar <termo_de_busca>\033[0m" << endl;
	cout << "-------------------------------------------------------------" << endl;
	if(argc < 4){
		cerr << "\033[31mErro: Nenhum comando especificado.\033[0m" << endl;
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
		cout << "\033[0mÍndice criado com sucesso!\033[0m" << endl;
	} else if(argv[2] == string("buscar")){
		/*Este comando deve primeiro verificar se o arquivo de índice existe na pasta atual. Se não, deve
		informar ao usuário para executar a indexação primeiro. Se o índice existir, ele deve ser carregado
		em memória. A busca deve ser realizada e os nomes dos arquivos relevantes, impressos na tela.*/
		Serializer serializer;
		Index index = serializer.carregar();
		if(!index.indiceCriado){
			cerr << "\033[31mErro: Nenhum índice encontrado. Por favor, execute a indexação primeiro.\033[0m" << endl;
			return 1;
		}
		/*Essa hash do tipo map armazenará a quantidade de palavras buscadas presentes em cada arquivo*/
		unordered_map<string, int> incidenciaDasBuscas;
		for(int i = 3; i < argc; i++){
			string termo_de_busca = argv[i];
			QueryProcessor queryProcessor;
			vector<string> arquivos = queryProcessor.buscar(termo_de_busca, index);
			if(arquivos.size() == 0){
				cout << "\033[31mNenhum arquivo encontrado para o termo '" << termo_de_busca << "'.\033[0m" << endl;
			}else{
				cout << "\033[33mArquivos encontrados para o termo '" << termo_de_busca << "':\033[0m" << endl;
				for(string& arquivo : arquivos){
					cout << "- " << arquivo << endl;
					incidenciaDasBuscas[arquivo]++;
				}
			}
			cout << endl;
		}
		if (argc>4){
			cout << "\033[33mArquivos que possuem todos os termos buscados:\033[0m" << endl;
			cout << "\033[33m(Caso nenhum arquivo seja listado, significa que não há nenhum arquivo que contenha todos os termos buscados.)\033[0m" << endl;
			for(const auto& [chave, valor] : incidenciaDasBuscas){
				if(valor == argc - 3){
					cout << "- " << chave << endl;
				}
			}
		}
		

	} else {
		cerr << "\033[31mErro: Comando desconhecido '" << argv[1] << "'.\033[0m" << endl;
		return 1;
	}
	cout << endl;
	return 0;
}