#include "text-processor.hpp"
#include <unordered_map>
#include <unordered_set>
;
static const unordered_set<string> set_acentos = {"á", "à", "ã", "â", "Á", "À", "Ã", "Â", "é", "ê", "É", "Ê", "í", "Í", "ó", "ô", "õ", "Ó", "Ô", "Õ", "ú", "Ú", "ç", "Ç"};
static const unordered_map<string, string> mapa_acentos = {
    {"Á", "á"},
    {"À", "à"},
    {"Ã", "ã"},
    {"Â", "â"},
    {"É", "é"},
    {"Ê", "ê"},
    {"Í", "í"},
    {"Ó", "ó"},
    {"Ô", "ô"},
    {"Õ", "õ"},
    {"Ú", "ú"},
    {"Ç", "ç"},
};
string next_utf8_char(const string &s, size_t &i){
	unsigned char c = s[i];
	size_t len = 1;
	if ((c & 0xE0) == 0xC0)
		len = 2;
	else if ((c & 0xF0) == 0xE0)
		len = 3;
	else if ((c & 0xF8) == 0xF0)
		len = 4;
	std::string ch = s.substr(i, len);
	i += len;
	return ch;
}
vector<string> TextProcessor::processar(string texto){
	vector<string> aux;
	string palavra;
	bool is_word = false;

	size_t i = 0;
	while (i < texto.size())
	{
		string ch = next_utf8_char(texto, i);
		if (mapa_acentos.count(ch)){
			palavra += mapa_acentos.at(ch);
			is_word = true;
			continue;
		}
		if (set_acentos.count(ch)){
			palavra += ch; 
			is_word = true;
			continue;
		}
		if (ch.size() == 1 && isalpha((unsigned char)ch[0])){
			palavra += (char)tolower(ch[0]);
			is_word = true;
			continue;
		}
		if (ch == " " || ch == "\n" || ch == "\t"){
			if (is_word){
				aux.push_back(palavra);
				palavra.clear();
			}
			is_word = false;
			continue;
		}
	}

	if (!palavra.empty()) aux.push_back(palavra);

	return aux;
}
