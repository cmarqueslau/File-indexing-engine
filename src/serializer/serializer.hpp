#pragma once
#include <iostream>
#include <vector>
#include "index/index.hpp"
using namespace std;

class Serializer{
	public:
	void salvar(Index index);
	Index carregar();
};