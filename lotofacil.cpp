#include "lotofacil.h"

#define NUM_JOGOS_ATUAIS 1454 // 1454
#define NUM_POSSIVEIS_JOGOS 966
#define RODADA_VERIFICACAO 1000  /* Rodada a que se quer estimar os resultados */

void Lotofacil::leJogosSorteados()
{
    ifstream file;
    /*  Abre arquivo File. */
    file.open("dados/lotofacilOrdenada.txt");

    /* Descobre a posição do fim do arquivo e adiciona em END_FILE */
    file.seekg(0, file.end);
    unsigned END_FILE = file.tellg();
    file.seekg(0, file.beg);

    /*  Enquanto não chegar ao fim do arquivo, cada linha lida torna-se um
        objeto do tipo Game e é adicionada na Lista de Jogos Sorteados. */
    while(file.tellg() < END_FILE - 2) {

        /* Objeto do tipo Date, para ser inserida no Game */
        Date *date = new Date();
        /* Array para armazenar os números sorteados */
        int *numeros_sorteados = new int[15];
        /*  Recebe o número do jogo. */
        unsigned number_game = 0;
        /*  Recebe a data do jogo no formato de string. */
        string dateString;

        /*  Escreve o número do jogo e sua data nas respectivas variáveis. */
        file >> number_game >> dateString;

        /* Formata a data para o objeto. */
        formatDate(dateString, date);

        /* Adiciona os números sorteados no array. */
        for (int i = 0; i < 15; i++) {
            file >> numeros_sorteados[i];
        }

        /*  Cria um objeto Game com os seus parâmetros retirados do arquivo. */
        Game *game = new Game(number_game, numeros_sorteados, date);
        /*  Insere o jogo na Lista de Jogos Sorteados. */
        listaJogosSorteados->push_back(game);
    }

    /*  Fecha o arquivo utilizado. */
    file.close();
}

void Lotofacil::lePossiveisJogos()
{
    /*  numeroJogo recebe o número do jogo, sendo incrementado a medida que o
        laço while percorre o arquivo de Possíveis Jogos.   */
    int numeroJogo = 0;
    /* dataString recebe uma data nula, pois seu uso não será necessário. */
    string dataString = "00/00/00";

    /* Abre o arquivo de Possíveis Jogos. */
    ifstream file;
    file.open("dados/PossiveisJogos.txt");

    /* Procura a marcação de fim do arquivo. */
    file.seekg(0, file.end);
    int END_FILE = file.tellg();
    file.seekg(0, file.beg);

    /* O laço while percorre todo o arquivo de Possíveis Jogos */
    while (numeroJogo < NUM_POSSIVEIS_JOGOS) {

        /* Cria um novo array para os numeros jogados e um objeto Date. */
        int *numerosJogados = new int[15];
        Date *date = new Date();

        /* Incrementa a variável de parada do laço */
        numeroJogo++;

        /* Formata a data para o objeto */
        formatDate(dataString, date);

        /* Insere os números no array */
        for (int i = 0; i < 15; i++) {
            file >> numerosJogados[i];
        }

        /* Cria o jogo enviando como parâmetro seu número, o array com os
           números jogados e sua data, depois adiciona na lista de possíveis
           jogos.
        */
        Game *game = new Game(numeroJogo, numerosJogados, date);
        listaPossiveisJogos->push_back(game);
    }

    file.close();
}

void Lotofacil::escreveAcertos()
{
    /* Abre o arquivo de Acertos para a escrita */
    ofstream file;
    file.open("dados/Acertos.txt");
    int acertos = 0;

    /* O laço externo percorre toda a Lista de Jogos Sorteados */
    for (int i = 0; i < listaJogosSorteados->size(); i++) {
        /* Início da linha, com o número do jogo e sua data */
        file << listaJogosSorteados->at(i)->getNumberGame() << " "
             << listaJogosSorteados->at(i)->getDate()->getDay() << "/"
             << listaJogosSorteados->at(i)->getDate()->getMonth() << "/"
             << listaJogosSorteados->at(i)->getDate()->getYear() << " ";

        /* Cria um array para armazenar os números sorteados */
        int *numerosSorteados = new int[15];
        numerosSorteados = listaJogosSorteados->at(i)->getNumerosSorteados();

        /*  O laço do meio percorre toda a Lista de Possíveis Jogos */
        for (int j = 0; j < listaPossiveisJogos->size(); j++) {
            /* Cria um array para armazenar os números jogados */
            int *numerosJogados = new int[15];
            numerosJogados = listaPossiveisJogos->at(j)->getNumerosSorteados();

            /*  E os dois laços mais internos verificam se o jogo atual obteve
                um acerto de 11 ou mais números. */
            for (int k = 0; k < 15; k++) {
                for (int l = 0; l < 15; l++) {
                    if (numerosJogados[l] == numerosSorteados[k]) {
                        acertos++;
                        break;
                    }
                }
            }

            /*  Se acertos for igual ou maior do que 11, escreve "1" no arquivo,
                senão escreve "0", representando um acerto ou uma falha. */
            if (acertos > 10)
                file << "1 ";
            else
                file << "0 ";

            /*  Reseta acertos para 0 */
            acertos = 0;

        }
        /*  Escreve uma quebra de linha no arquivo. */
        file << endl;
        cout << "Escrevendo tabela de acertos, linha " << i << " | " << NUM_JOGOS_ATUAIS-1 << "\n";
    }
    file.close();
}

void Lotofacil::formatDate(string dateString, Date *date)
{

    /*  Variáveis auxiliares para percorrer a string de data, onde "m" é o
        índice da string data, e "n" é o índice da variavel auxiliar de
        formatação . */
    unsigned m = 0, n = 0;

    /* Variáveis auxiliares para a formatação da data. */
    string day_, month_, year_;

    /*  Enquanto ele não encontrar uma "/" na string data, ele continua
        procurando e vai adicionando os caracteres na variável auxiliar. */
    while (dateString[m] != '/') {
        day_[n] = dateString[m];
        m++;
        n++;
    }

    /* Converte o dia de string para int, e insere no objeto Date. */
    int day = stoi(day_);
    date->setDay(day);

    /*  Incrementa o índice da string data, e reseta o índice da variável de
        formatação. */
    m++;
    n = 0;

    /*  Enquanto ele não encontrar uma "/" na string data, ele continua
        procurando e vai adicionando os caracteres na variável auxiliar. */
    while (dateString[m] != '/') {
        month_[n] = dateString[m];
        m++;
        n++;
    }

    /* Converte o mês de string para int, e insere no objeto Date. */
    int month = stoi(month_);
    date->setMonth(month);

    /*  Incrementa o índice da string data, e reseta o índice da variável de
        formatação. */
    m++;
    n = 0;

    /*  Enquanto ele não encontrar um "\0" na string data, ou seja, o fim da
        string, ele continua procurando e vai adicionando os caracteres na
        variável auxiliar. */
    while (dateString[m] != '\0') {
        year_[n] = dateString[m];
        m++;
        n++;
    }

    /* Converte o ano de string para int, e insere no objeto Date. */
    int year = stoi(year_);
    date->setYear(year);
}

void Lotofacil::ordenaJogosSorteados()
{
    /*  Input e Output são os arquivos de leitura e escrita, respectivamente.
        NumeroJogo é a variável para armazenar o número do jogo, e Count é
        o contador para controlar o laço while. */
    fstream input, output;
    int numeroJogo = 0, count = 0;
    string data;

    /* Abertura dos arquivos de entrada e saída. */
    input.open("dados/lotofacil.txt");
    output.open("dados/lotofacilOrdenada.txt");

    /* Percorre o arquivo de entrada, com a ajuda do contador "count". */
    while (count < NUM_JOGOS_ATUAIS) {
        /* Cria um array para armazenar os números jogados. */
        int *numerosJogados = new int[15];

        count++;

        /*  Lê o número do jogo e a data e armazena em suas respectivas
            variáveis. */
        input >> numeroJogo >> data;

        /*  Lê os números do arquivo de entrada e escreve no array. */
        for (int i = 0; i < 15; i++) {
            input >> numerosJogados[i];
        }

        /* Chama o método bubbleSort e passa por parâmetro o array de números
            jogados, que será ordenado e será retornado por referência. */
        bubbleSort(numerosJogados);

        /* Escreve o número do jogo e seu resultado no arquivo de saída. */
        output << numeroJogo << " " << data << " ";
        for (int i = 0; i < 15; i++) {
            output << numerosJogados[i] << " ";
        }
        output << endl;

    }
}

/*  Consiste basicamente em selecionar, dentre o número de combinações
    possíveis, uma determinada quantidade de jogos que possuem a maior
    diferença entre sua distância média e a distância média total de todos os
    possíveis jogos disponíveis. */
double Lotofacil::estrategiaDiferencaMedia(int numJogos, int rodadaVerificacao)
{
    ifstream file;
    file.open("dados/Acertos.txt");

    /*  Construção da tabela de Acertos em memória, através de uma Lista
        Encadeada Principal, que contém a Lista de Acertos e Falhas de cada
        combinação possível. */
    structures::LinkedList<structures::LinkedList<int>*> *tabelaDeFalhasAcertos = new structures::LinkedList<structures::LinkedList<int>*>();

    int numeroJogo = 0, resultado = 0;
    string dataJogo;

    /*  Preenche a tabela de falhas e acertos, com todas as "linhas" sendo
        listas das falhas e acertos de cada possível jogo, contando as falhas
        e acertos ATÉ A RODADA DE VERIFICAÇÃO, ou seja, a rodada que se quer
        verificar o acerto. */
    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
        structures::LinkedList<int> *listaDeFalhasAcertos = new structures::LinkedList<int>();
        tabelaDeFalhasAcertos->push_back(listaDeFalhasAcertos);
    }

    for (int i = 0; i < rodadaVerificacao; i++) {

        file >> numeroJogo >> dataJogo;

        for (int j = 0; j < NUM_POSSIVEIS_JOGOS; j++) {
            file >> resultado;
            tabelaDeFalhasAcertos->at(j)->push_back(resultado);
        }

        // cout << "Criando tabela de falhas e acertos. Jogo " << i << " | " << rodadaVerificacao-1 << " ...\n";
    }

    /* Contagem da distância entre cada acerto para cada possível jogo. */
    structures::LinkedList<structures::LinkedList<int>*> *tabelaSequenciaFalhas = new structures::LinkedList<structures::LinkedList<int>*>();

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
        structures::LinkedList<int> *listaSequenciaFalhas = new structures::LinkedList<int>();
        tabelaSequenciaFalhas->push_back(listaSequenciaFalhas);

        listaSequenciaFalhas->push_back(0);

        for (int j = 0; j < tabelaDeFalhasAcertos->at(i)->size(); j++) {
            if (tabelaDeFalhasAcertos->at(i)->at(j) == 0)
                listaSequenciaFalhas->at(listaSequenciaFalhas->size()-1)++;
            else
                listaSequenciaFalhas->push_back(0);
        }

        // cout << "Criando tabela das sequências de falhas da combinação " << i << " | " << NUM_POSSIVEIS_JOGOS-1 << " ... \n";
    }

    /*  Calcula a média das distâncias entre cada acerto. */
    double mediaSucessaoDeFalhas = 0, mediaDistanciaEntreAcertos = 0;
    double mediaTotalSucessaoDeFalhas = 0;

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {

        /*  Calcula o valor médio das sucessões de falhas. */
        double aux = 0, numSequenciaFalhas = 0;
        for (int j = 0; j < tabelaSequenciaFalhas->at(i)->size(); j++) {
            aux += tabelaSequenciaFalhas->at(i)->at(j);

            if (tabelaSequenciaFalhas->at(i)->at(j) != 0)
                numSequenciaFalhas++;
        }

        /*  Calcula o valor médio da distância entre cada acerto. */
        double aux2 = 0;
        for (int j = 0; j < tabelaDeFalhasAcertos->at(i)->size(); j++) {
            aux2 += tabelaDeFalhasAcertos->at(i)->at(j);
        }

        /*  Atribui o valor correto a cada variável que representa a média. */
        mediaSucessaoDeFalhas = aux/numSequenciaFalhas;
        mediaDistanciaEntreAcertos = NUM_JOGOS_ATUAIS/aux2;

        mediaTotalSucessaoDeFalhas += mediaSucessaoDeFalhas;

        /*  Foi adotado, por padrão, a média de sucessão de falhas, sendo
            incluída em cada objeto Game, na Lista Principal de Possíveis
            Jogos. */
        listaPossiveisJogos->at(i)->setDistanciaMedia(mediaSucessaoDeFalhas);
        // cout << "Calculando a média das sequências de falhas da combinação " << i << " | " << NUM_POSSIVEIS_JOGOS-1 << " ...\n";
    }
    mediaTotalSucessaoDeFalhas = mediaTotalSucessaoDeFalhas/NUM_POSSIVEIS_JOGOS;

    /*  Seta a diferença entre a média e a média total de cada possível jogo. */
    for (int i = 0; i < listaPossiveisJogos->size(); i++) {
        double diferenca = listaPossiveisJogos->at(i)->getDistanciaMedia() - mediaTotalSucessaoDeFalhas;
        listaPossiveisJogos->at(i)->setDiferencaDistanciaTotal(diferenca);
        // cout << "Setando a diferença da média da distância total da combinação " << i << " | " << listaPossiveisJogos->size() << " ...\n";
    }

    /*  Ordena a lista de acordo com a diferença entre a média e a média total.
        Quanto maior a diferença, maior a chance desta sequência cair no
        próximo jogo sorteado, desde que ela esteja a um bom tempo sem cair. */
    Game *aux;

    for (int i = 0; i < listaPossiveisJogos->size(); i++) {
        for (int j = i+1; j < listaPossiveisJogos->size(); j++) {
            if (listaPossiveisJogos->at(i)->getDiferencaDistanciaTotal() < listaPossiveisJogos->at(j)->getDiferencaDistanciaTotal()) {
                aux = listaPossiveisJogos->at(i);
                listaPossiveisJogos->at(i) = listaPossiveisJogos->at(j);
                listaPossiveisJogos->at(j) = aux;
            }
        }
        // cout << "Ordenando a lista de possíveis jogos. " << i << " | " << listaPossiveisJogos->size() << " ...\n";
    }

    /*  Insere os 25 primeiros elementos na lista de Jogos Selecionados, ou
        seja, os 25 jogos com a maior diferença entre a média e a média total,
        e chama a subrotina verificaTaxaAcerto, para retornar as chances destes
        jogos serem sorteados nas próximas rodadas. */
    structures::LinkedList<Game*> *listaJogosSelecionados = new structures::LinkedList<Game*>();

    for (int i = 0; i < numJogos; i++) {
        // cout << listaPossiveisJogos->at(i)->getNumberGame() << " - " << listaPossiveisJogos->at(i)->getDiferencaDistanciaTotal() << " | " << listaPossiveisJogos->at(i)->getDistanciaMedia() << " - " << mediaTotalSucessaoDeFalhas << "\n";
        listaJogosSelecionados->push_back(listaPossiveisJogos->at(i));
    }

    return verificaTaxaAcerto(listaJogosSelecionados, rodadaVerificacao);

}

/*  Analisa os atributos dos jogos que conseguiram acerto de 11 ou mais números
    em determinado jogo sorteado, como:
        - Número de jogos sem cair;
        - Média da distância entre acertos;
        - Diferença da distância média total de acertos;
*/
void Lotofacil::estrategiaAnaliseAcertos(int rodadaVerificacao)
{

    // /*  Calcula a média das distâncias entre cada acerto. */
    // double mediaSucessaoDeFalhas = 0, mediaDistanciaEntreAcertos = 0;
    // double mediaTotalSucessaoDeFalhas = 0;
    //
    // for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
    //
    //     /*  Calcula o valor médio das sucessões de falhas. */
    //     double aux = 0, numSequenciaFalhas = 0;
    //     for (int j = 0; j < tabelaSequenciaFalhas->at(i)->size(); j++) {
    //         aux += tabelaSequenciaFalhas->at(i)->at(j);
    //
    //         if (tabelaSequenciaFalhas->at(i)->at(j) != 0)
    //             numSequenciaFalhas++;
    //     }
    //
    //     /*  Calcula o valor médio da distância entre cada acerto. */
    //     double aux2 = 0;
    //     for (int j = 0; j < tabelaDeFalhasAcertos->at(i)->size(); j++) {
    //         aux2 += tabelaDeFalhasAcertos->at(i)->at(j);
    //     }
    //
    //     /*  Atribui o valor correto a cada variável que representa a média. */
    //     mediaSucessaoDeFalhas = aux/numSequenciaFalhas;
    //     mediaDistanciaEntreAcertos = NUM_JOGOS_ATUAIS/aux2;
    //
    //     mediaTotalSucessaoDeFalhas += mediaSucessaoDeFalhas;
    //
    //     /*  Foi adotado, por padrão, a média de sucessão de falhas, sendo
    //         incluída em cada objeto Game, na Lista Principal de Possíveis
    //         Jogos. */
    //     listaPossiveisJogos->at(i)->setDistanciaMedia(mediaSucessaoDeFalhas);
    //     // cout << "Calculando a média das sequências de falhas da combinação " << i << " | " << NUM_POSSIVEIS_JOGOS-1 << " ...\n";
    // }
    // mediaTotalSucessaoDeFalhas = mediaTotalSucessaoDeFalhas/NUM_POSSIVEIS_JOGOS;

    // /*  Seta a diferença entre a média e a média total de cada possível jogo. */
    // for (int i = 0; i < listaPossiveisJogos->size(); i++) {
    //     double diferenca = listaPossiveisJogos->at(i)->getDistanciaMedia() - mediaTotalSucessaoDeFalhas;
    //     listaPossiveisJogos->at(i)->setDiferencaDistanciaTotal(diferenca);
    //     // cout << "Setando a diferença da média da distância total da combinação " << i << " | " << listaPossiveisJogos->size() << " ...\n";
    // }
    //
    // /*  Ordena a lista de acordo com a diferença entre a média e a média total.
    //     Quanto maior a diferença, maior a chance desta sequência cair no
    //     próximo jogo sorteado, desde que ela esteja a um bom tempo sem cair. */
    // Game *aux;
    //
    // for (int i = 0; i < listaPossiveisJogos->size(); i++) {
    //     for (int j = i+1; j < listaPossiveisJogos->size(); j++) {
    //         if (listaPossiveisJogos->at(i)->getDiferencaDistanciaTotal() < listaPossiveisJogos->at(j)->getDiferencaDistanciaTotal()) {
    //             aux = listaPossiveisJogos->at(i);
    //             listaPossiveisJogos->at(i) = listaPossiveisJogos->at(j);
    //             listaPossiveisJogos->at(j) = aux;
    //         }
    //     }
    //     // cout << "Ordenando a lista de possíveis jogos. " << i << " | " << listaPossiveisJogos->size() << " ...\n";
    // }

    /* ##################################################################################################################################################### */

    ifstream file;
    file.open("dados/Acertos.txt");

    /*  Cria a tabela de falhas e acertos, com todas as "linhas" sendo listas
        dos jogos sorteados e os resultados dos possíveis jogos. */
    structures::LinkedList<structures::LinkedList<int>*> *tabelaDeFalhasAcertosPorSorteio = new structures::LinkedList<structures::LinkedList<int>*>();

    int numeroJogo = 0, resultado = 0;
    string dataJogo;

    for (int i = 0; i < NUM_JOGOS_ATUAIS; i++) {
        structures::LinkedList<int> *listaDeFalhasAcertos = new structures::LinkedList<int>();
        tabelaDeFalhasAcertosPorSorteio->push_back(listaDeFalhasAcertos);

        file >> numeroJogo >> dataJogo;

        for (int j = 0; j < NUM_POSSIVEIS_JOGOS; j++) {
            file >> resultado;
            listaDeFalhasAcertos->push_back(resultado);
        }
    }

    /*  Preenche a tabela de falhas e acertos, com todas as "linhas" sendo
        listas das falhas e acertos de cada possível jogo. */
    file.seekg(0, file.beg);
    structures::LinkedList<structures::LinkedList<int>*> *tabelaDeFalhasAcertosPorJogo = new structures::LinkedList<structures::LinkedList<int>*>();

    int numeroJogo2 = 0, resultado2 = 0;
    string dataJogo2;

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
        structures::LinkedList<int> *listaDeFalhasAcertos = new structures::LinkedList<int>();
        tabelaDeFalhasAcertosPorJogo->push_back(listaDeFalhasAcertos);
    }

    for (int i = 0; i < rodadaVerificacao; i++) {
        file >> numeroJogo2 >> dataJogo2;

        for (int j = 0; j < NUM_POSSIVEIS_JOGOS; j++) {
            file >> resultado2;
            tabelaDeFalhasAcertosPorJogo->at(j)->push_back(resultado2);
            // cout << "Resultado 2: " << resultado2 << "\n";
        }
        cout << "Criando tabela de falhas e acertos. Jogo " << i << " | " << rodadaVerificacao-1 << " ...\n";
    }

    /*  Procura cada jogo que obteve acerto no jogo sorteado escolhido e o
        adiciona em uma lista. */
    structures::LinkedList<Game*> *listaJogosVencedores = new structures::LinkedList<Game*>();

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {

        if (tabelaDeFalhasAcertosPorSorteio->at(rodadaVerificacao)->at(i) == 1) {
            listaJogosVencedores->push_back(listaPossiveisJogos->at(i));
            cout << listaJogosVencedores->at(listaJogosVencedores->size()-1)->getNumberGame() << endl;
        }
    }

    /*  Analisa o número de jogos sem cair dos jogos vencedores. */
    for (int i = 0; i < listaJogosVencedores->size(); i++) {
        int numeroJogosSemCair = 0;
        for (int j = 0; j < rodadaVerificacao; j++) {
            if (tabelaDeFalhasAcertosPorJogo->at(listaJogosVencedores->at(i)->getNumberGame())->at(j) == 0)
                numeroJogosSemCair++;
            else
                numeroJogosSemCair = 0;
        }
        listaJogosVencedores->at(i)->setJogosSemCair(numeroJogosSemCair);
        cout << listaJogosVencedores->at(i)->getJogosSemCair() << endl;
    }

/*  ########################################################################################################################################################## */

    /*  Contagem da distância entre cada acerto para cada possível jogo,
        criação da Tabela de Sequencia de Falhas.   */
    structures::LinkedList<structures::LinkedList<int>*> *tabelaSequenciaFalhas = new structures::LinkedList<structures::LinkedList<int>*>();

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
        structures::LinkedList<int> *listaSequenciaFalhas = new structures::LinkedList<int>();
        tabelaSequenciaFalhas->push_back(listaSequenciaFalhas);

        listaSequenciaFalhas->push_back(0);

        for (int j = 0; j < tabelaDeFalhasAcertosPorJogo->at(i)->size(); j++) {
            if (tabelaDeFalhasAcertosPorJogo->at(i)->at(j) == 0)
                listaSequenciaFalhas->at(listaSequenciaFalhas->size()-1)++;
            else
                listaSequenciaFalhas->push_back(0);
        }

        cout << "Criando tabela das sequências de falhas da combinação " << i << " | " << NUM_POSSIVEIS_JOGOS-1 << " ... \n";
    }

/*  ########################################################################################################################################################## */

    /*  Procura a média entre acertos de todos os possíveis jogos. */
    double mediaSucessaoDeFalhas = 0, mediaDistanciaEntreAcertos = 0;
    double mediaTotalSucessaoDeFalhas = 0;

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {

        /*  Calcula o valor médio das sucessões de falhas. */
        double aux = 0, numSequenciaFalhas = 0;
        for (int j = 0; j < tabelaSequenciaFalhas->at(i)->size(); j++) {
            aux += tabelaSequenciaFalhas->at(i)->at(j);

            if (tabelaSequenciaFalhas->at(i)->at(j) != 0)
                numSequenciaFalhas++;
        }

        /*  Calcula o valor médio da distância entre cada acerto. */
        double aux2 = 0;
        for (int j = 0; j < tabelaDeFalhasAcertosPorJogo->at(i)->size(); j++) {
            aux2 += tabelaDeFalhasAcertosPorJogo->at(i)->at(j);
        }

        /*  Atribui o valor correto a cada variável que representa a média. */
        mediaSucessaoDeFalhas = aux/numSequenciaFalhas;
        mediaDistanciaEntreAcertos = NUM_JOGOS_ATUAIS/aux2;

        mediaTotalSucessaoDeFalhas += mediaSucessaoDeFalhas;

        /*  Foi adotado, por padrão, a média de sucessão de falhas, sendo
            incluída em cada objeto Game, na Lista Principal de Possíveis
            Jogos. */
        listaPossiveisJogos->at(i)->setDistanciaMedia(mediaSucessaoDeFalhas);
        cout << "Calculando a média das sequências de falhas da combinação " << i << " | " << NUM_POSSIVEIS_JOGOS-1 << " ...\n";
    }
    mediaTotalSucessaoDeFalhas = mediaTotalSucessaoDeFalhas/NUM_POSSIVEIS_JOGOS;

    /*  Seta a diferença entre a média e a média total de cada possível jogo. */
    for (int i = 0; i < listaPossiveisJogos->size(); i++) {
        double diferenca = listaPossiveisJogos->at(i)->getDistanciaMedia() - mediaTotalSucessaoDeFalhas;
        listaPossiveisJogos->at(i)->setDiferencaDistanciaTotal(diferenca);
        cout << "Setando a diferença da média da distância total da combinação " << i << " | " << listaPossiveisJogos->size() << " ...\n";
    }

    /*  ########################################################################################################################################################## */

    /* Imprime o relatório das características dos jogos vencedores. */

    cout << "Número Jogo | Rodadas sem cair | Distância média entre acertos | Diferença média" << endl;
    for (int i = 0; i < listaJogosVencedores->size(); i++) {
        cout << listaJogosVencedores->at(i)->getNumberGame() << " " << listaJogosVencedores->at(i)->getJogosSemCair() << " "
             << listaJogosVencedores->at(i)->getDistanciaMedia() << " " << listaJogosVencedores->at(i)->getDiferencaDistanciaTotal() << "\n";
    }


}



void Lotofacil::verificaIrregularidadeAcertos()
{
    /*  Bloco de código para verificar qual o Jogo com o maior número de rodadas sem um acerto.
        Irrelevante, e será retirado ao longo do desenvolvimento desta implementação. */
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
    // int test = 0, jogoComMaiorTempoSemCair = 0;
    // for (int i = 0; i < listaJogosSemCair->size(); i++) {
    //     if (listaJogosSemCair->at(i)->getJogosSemCair() > test) {
    //         test = listaJogosSemCair->at(i)->getJogosSemCair();
    //         jogoComMaiorTempoSemCair = listaJogosSemCair->at(i)->getNumeroJogo();
    //     }
    // }
    //
    // cout << "Até o jogo 500, o jogo com mais jogos sem cair é o jogo de número: " << jogoComMaiorTempoSemCair << "\ncom jogos sem cair: " << test << endl;
    // cout << "Números Jogados: ";
    // for (int i = 0; i < 15; i++) {
    //     cout << listaPossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados()[i] << " ";
    // }
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

    /*  Bloco de código para verificar, após a rodada atual, quantas rodadas passarão
        até o jogo com maior numero de rodadas obter um acerto.
        Irrelevante, e será retirado ao longo do desenvolvimento desta implementação. */
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
    /* Testando o jogo com maior tempo sem cair para ver em quantas rodadas ele vai acertar */
    // bool acerto = false;
    // int numerosCertos = 0;
    // int *numerosJogados = new int[15];
    // int jogoGanho = 0;
    // numerosJogados = listaPossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados();
    //
    // for (int i = 634; i < NUM_JOGOS_ATUAIS; i++) {
    //     int *numerosSorteados = new int[15];
    //     numerosSorteados = listaJogosSorteados->at(i)->getNumerosSorteados();
    //     // for (int j = 0; j < 15; j++) {
    //     //     if (numerosJogados[j] == numerosSorteados[j])
    //     //         numerosCertos++;
    //     //     else {
    //     //         numerosCertos = 0;
    //     //         break;
    //     //     }
    //     // }
    //     for (int k = 0; k < 15; k++) {
    //         for (int l = 0; l < 15; l++) {
    //             if (numerosJogados[l] == numerosSorteados[k]) {
    //                 numerosCertos++;
    //                 break;
    //             }
    //         }
    //     }
    //     if (numerosCertos >= 11) {
    //         cout << "\nJogo ganho: " << endl;
    //         for (int m = 0; m < 15; m++) {
    //             cout << listaJogosSorteados->at(i)->getNumerosSorteados()[m] << " ";
    //         }
    //         acerto = true;
    //         jogoGanho = i;
    //         numerosCertos = 0;
    //         break;
    //     }
    //     numerosCertos = 0;
    // }
    //
    // cout << "Jogo ganho: " << jogoGanho << endl;
    // cout << "Numeros sorteados: ";
    // int *numerosSorteados = new int[15];
    // numerosSorteados = listaJogosSorteados->at(jogoGanho)->getNumerosSorteados();
    // for (int i = 0; i < 15; i++) {
    //     cout << numerosSorteados[i] << " ";
    // }
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

    /*  Bloco de código utilizado para esboçar uma ideia, onde se analisa, dentre um
        determinado número de jogos selecionados devido sua alta chance de acerto,
        quantas rodadas se passarão até cada jogo obter um acerto.

        Será generalizado para um método de retorno de Taxa de Acerto.

        Os jogos serão selecionados a partir da sua distância média entre acertos.
        Todos os jogos que possuírem a distância média menor do que a distância
        média global, e estiverem há várias rodadas sem acerto, terão uma alta
        chance de acerto dentro das próximas 5 rodadas, e o método de Taxa de
        Acerto retornará a taxa para cada uma das estratégias testadas e
        escolhidas. */
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
    // ofstream sorteiosNaoCoincidentes;
    // sorteiosNaoCoincidentes.open("Sorteios não coincidentes na linha 634.txt");
    //
    // sorteiosNaoCoincidentes << "Jogo 634\n";
    // // for (int i = 0; i < lista->size(); i++) {
    // //     sorteiosNaoCoincidentes << i << " ";
    // // }
    // // sorteiosNaoCoincidentes << "\n634 ";
    // for (int i = 0; i < listaJogosSemCair->size(); i++) {
    //     sorteiosNaoCoincidentes << i << " " << listaJogosSemCair->at(i)->getJogosSemCair() << endl;
    // }
    // sorteiosNaoCoincidentes.close();
    //
    // // int arrayJogos = new int[16];
    // int arrayJogos[] = {651, 111, 809, 645, 130, 813, 34, 674, 274, 384, 951, 277, 205, 249, 427, 665};
    // int acertos = 0;
    // double numAcertos = 0.0;
    // cout << endl;
    //
    // for (int i = 0; i < 16; i++) {
    //     int *jogo = new int[15];
    //     jogo = listaPossiveisJogos->at(arrayJogos[i])->getNumerosSorteados();
    //
    //     for (int j = 634; j < NUM_JOGOS_ATUAIS; j++) {
    //         for (int k = 0; k < 15; k++) {
    //             for (int l = 0; l < 15; l++) {
    //                 if (jogo[l] == listaJogosSorteados->at(j)->getNumerosSorteados()[k]) {
    //                     acertos++;
    //                     break;
    //                 }
    //             }
    //         }
    //         if (acertos >= 11) {
    //             cout << "Jogo "  << arrayJogos[i] << " acertou na rodada " << j << " - " << j-634 <<
    //                     " Acertos: " << acertos << endl;
    //             numAcertos++;
    //             acertos = 0;
    //             break;
    //         }
    //         acertos = 0;
    //     }
    // }
    //
    // cout << endl << endl << "Taxa de acertos: " << numAcertos/16 << endl;
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

}

double Lotofacil::verificaTaxaAcerto(structures::LinkedList<Game*> *listaJogosSelecionados, int rodadaVerificacao)
{
    double numJogosTestados = listaJogosSelecionados->size();
    double numAcertosAntesDe5Rodadas = 0;
    double numAcertosAntesDe7Rodadas = 0;
    double numAcertosDepoisDe7Rodadas = 0;

    for (int i = 0; i < listaJogosSelecionados->size(); i++) {
        int numAcertos = 0;
        int rodadas = 0;
        for (int j = RODADA_VERIFICACAO; j < NUM_JOGOS_ATUAIS; j++) {
            for (int k = 0; k < 15; k++) {
                for (int l = 0; l < 15; l++) {
                    if (listaJogosSelecionados->at(i)->getNumerosSorteados()[k] == listaJogosSorteados->at(j)->getNumerosSorteados()[l]) {
                        numAcertos++;
                        break;
                    }
                }
            }

            if (numAcertos >= 11)
                break;
            else
                rodadas++;
            numAcertos = 0;
        }

        if (rodadas <= 5)
            numAcertosAntesDe5Rodadas++;
        else if (rodadas <= 7)
            numAcertosAntesDe7Rodadas++;
        else
            numAcertosDepoisDe7Rodadas++;

        cout << "Jogo " << listaJogosSelecionados->at(i)->getNumberGame() << " foi sorteado após " << rodadas << " rodadas (" << rodadas+1+RODADA_VERIFICACAO << ").\n";
        for (int j = 0; j < 15; j++)
            cout << listaJogosSelecionados->at(i)->getNumerosSorteados()[j] << " ";
        cout << "\n\n";
    }

    double taxa5 = numAcertosAntesDe5Rodadas/numJogosTestados;
    double taxa5e7 = numAcertosAntesDe7Rodadas/numJogosTestados;
    double taxa7 = numAcertosDepoisDe7Rodadas/numJogosTestados;
    cout << "Taxa de Acertos em 5 jogos = " << taxa5*100 << "%. \n"
         << "Taxa de Acertos em 7 jogos = " << taxa5e7*100 << "%. \n"
         << "Taxa de Acertos depois de 7 jogos = " << taxa7*100 << "%. \n";

    return taxa5;
}

void Lotofacil::bubbleSort(int *vetor)
{
    int aux = 0;
    for (int i = 0; i < 15; i++) {
        for (int j = i+1; j < 15; j++) {
            if (vetor[i] > vetor[j]) {
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
    }
}
