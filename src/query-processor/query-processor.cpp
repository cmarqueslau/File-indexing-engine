#include "query-processor.hpp"

vector<string> QueryProcessor::buscar(string consulta, Index& index) {
	vector<string> resultados = index.getArquivosPorPalavra(consulta);
	return resultados;
}