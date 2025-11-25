#pragma once
#include <iostream>
#include "../index/index.hpp"
using namespace std;

class Indexer{
	public:
	Index construir(string diretorio);
	/*Este comando deve varrer o diretório especificado, construir o índice invertido e salvá-lo em um
	arquivo padrão index.dat no diretório atual*/
};