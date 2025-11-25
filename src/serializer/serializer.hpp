#pragma once
#include <iostream>
#include <vector>
#include <index.hpp>
using namespace std;

class Serializer{
	public:
	void salvar(Index index, string arquivo);
	Index carregar();
};