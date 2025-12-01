# Construção de um mecanismo de indexação de arquivos
Desenvolver uma aplicação de linha de comando que simula um mecanismo de busca para documentos de texto. 
1. Indexação: Ler uma coleção de arquivos de texto (.txt) de um diretório, processar seu
conteúdo e construir um índice invertido em memória. Ao final, este índice deve ser serializado
e salvo em um arquivo no disco.
2. Busca: Carregar o índice previamente salvo no disco (desserialização) e permitir que o usuário
realize buscas por palavras-chave, retornando de forma eficiente a lista de documentos que
contêm os termos pesquisados.

## Como compilar
<pre>make</pre>

## Modo de execução

### Modo Indexação
<pre>./output/main indice construir caminho_do_diretorio</pre>
Este comando varre o diretório especificado, constroi o índice invertido e o salva em um
arquivo padrão index.dat no diretório atual

### Modo Busca
<pre>./output/main indice buscar termos_de_busca</pre>
Este comando primeiro verifica se o arquivo de índice existe na pasta atual. Se não,
informa ao usuário para executar a indexação primeiro. Se o índice existir, ele é carregado
em memória, a busca é realizada e os nomes dos arquivos relevantes são impressos na tela.

## Como funciona o processamento das palavras
O programa é capaz de ler arquivos de texto, processar o conteúdo para remover pontuações,
converter para minúsculas e eliminar stop words. A lista de stop words está no arquivo stopwords.txt

