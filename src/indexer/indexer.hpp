#pragma once
#include <iostream>
#include "../index/index.hpp"
using namespace std;

class Indexer{
	public:
	Index construir(string diretorio);
	/*Este comando deve varrer o diretório especificado e construir o índice invertido*/
};