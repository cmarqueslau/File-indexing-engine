# Construção de um mecanismo de indexação de arquivos
Desenvolver uma aplicação de linha de comando que simula um mecanismo de busca para documentos de texto. 
1. Indexação: Ler uma coleção de arquivos de texto (.txt) de um diretório, processar seu
conteúdo e construir um índice invertido em memória. Ao final, este índice deve ser serializado
e salvo em um arquivo no disco.
2. Busca: Carregar o índice previamente salvo no disco (desserialização) e permitir que o usuário
realize buscas por palavras-chave, retornando de forma eficiente a lista de documentos que
contêm os termos pesquisados.
