#include "serializer.hpp"
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

// Escreve um tipo primitivo (int, unsigned, size_t, etc.) em binário
template<typename T>
void writePrimitive(ofstream& out, const T& value) {
    out.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

// Lê um tipo primitivo (int, unsigned, size_t, etc.) em binário
template<typename T>
void readPrimitive(ifstream& in, T& value) {
    in.read(reinterpret_cast<char*>(&value), sizeof(T));
}

// Escreve uma string com tamanho + conteúdo
void writeString(ofstream& out, const string& texto) {
    size_t tamanho = texto.size();
    writePrimitive(out, tamanho);      // salva o tamanho
    out.write(texto.c_str(), tamanho); // salva o conteúdo
}

// Lê uma string salva como tamanho + conteúdo
string readString(ifstream& in) {
    size_t tamanho;
    readPrimitive(in, tamanho);

    string texto(tamanho, ' ');
    in.read(&texto[0], tamanho);
    return texto;
}

void Serializer::salvar(Index& index) {
    ofstream arquivoIndice("index.dat", ios::binary);
    if (!arquivoIndice) {
        cout << "Erro ao abrir 'index.dat' para escrita.\n";
        return;
    }

    auto& indiceInverso = index.getIndice();
    size_t quantidadeEntradas = indiceInverso.size();

    // salva o número total de palavras indexadas
    writePrimitive(arquivoIndice, quantidadeEntradas);

    // salva cada palavra e seus IDs
    for (auto& [palavra, conjuntoIds] : indiceInverso) {

        writeString(arquivoIndice, palavra);               // salva a palavra
        writePrimitive(arquivoIndice, conjuntoIds.size()); // salva qtd de IDs

        for (auto id : conjuntoIds)
            writePrimitive(arquivoIndice, id);            // salva cada ID
    }

    ofstream arquivoIds("ids.dat", ios::binary);
    if (!arquivoIds) {
        cout << "Erro ao abrir 'ids.dat' para escrita.\n";
        return;
    }

    auto& mapaIdParaArquivo = index.getIdParaArquivo();
    quantidadeEntradas = mapaIdParaArquivo.size();

    // salva número total de arquivos indexados
    writePrimitive(arquivoIds, quantidadeEntradas);

    // salva cada par (id, nomeArquivo)
    for (auto& [id, nomeArquivo] : mapaIdParaArquivo) {
        writePrimitive(arquivoIds, id);        // salva ID
        writeString(arquivoIds, nomeArquivo);  // salva caminho completo
    }
}

Index Serializer::carregar() {
    Index index;
    ifstream arquivoIndice("index.dat", ios::binary);
    if (!arquivoIndice) {
        index.indiceCriado = false;
        return index;
    }

    size_t quantidadeEntradas;
    readPrimitive(arquivoIndice, quantidadeEntradas);

    unordered_map<string, unordered_set<unsigned>> indiceInverso;

    // ler cada palavra + conjunto de IDs
    while (quantidadeEntradas--) {

        string palavra = readString(arquivoIndice);

        size_t quantidadeIds;
        readPrimitive(arquivoIndice, quantidadeIds);

        unordered_set<unsigned> ids;

        while (quantidadeIds--) {
            unsigned id;
            readPrimitive(arquivoIndice, id);
            ids.insert(id);
        }

        indiceInverso[palavra] = move(ids);
    }

    index.popularIndiceDeArquivo(indiceInverso);
    ifstream arquivoIds("ids.dat", ios::binary);
    if (!arquivoIds) {
        index.indiceCriado = false;
        return index;
    }

    readPrimitive(arquivoIds, quantidadeEntradas);

    unordered_map<unsigned, string> mapaIdParaArquivo;

    // ler cada par ID + nomeArquivo
    while (quantidadeEntradas--) {

        unsigned id;
        readPrimitive(arquivoIds, id);

        string nomeArquivo = readString(arquivoIds);

        mapaIdParaArquivo[id] = nomeArquivo;
    }

    index.popularIdParaArquivo(mapaIdParaArquivo);

    index.indiceCriado = true;
    return index;
}
