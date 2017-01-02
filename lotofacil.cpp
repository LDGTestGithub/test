#include "lotofacil.h"

#define NUM_JOGOS_ATUAIS 1454
#define NUM_POSSIVEIS_JOGOS 966
#define RODADA_VERIFICACAO 634  /* Rodada a que se quer estimar os resultados */

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
        cout << "I: " << i << "\n";
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

void Lotofacil::verificaIrregularidadeAcertos()
{
    /*  Criação da lista que contém o número dos jogos e a quantidade de rodadas
        que estão sem acertos. */
    structures::LinkedList<JogosSemCair*> *listaJogosSemCair = new structures::LinkedList<JogosSemCair*>();

    /*  Abre o arquivo que contém todos os Acertos dos Possíveis Jogos. */
    ifstream file;
    file.open("dados/Acertos.txt");

    /*  Count marca a rodada de sorteio sendo verificada pelo laço while,
        e resultado é o "1" ou "0", do Acerto. */
    unsigned count = 0, numeroJogoSorteado = 0, resultado = 0;
    string date;

    /*  Cria todos os elementos da Lista de Jogos Sem Cair, com base no
        número de Possíveis Jogos. */
    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
        JogosSemCair *jogo = new JogosSemCair();
        jogo->setNumeroJogo(i);
        listaJogosSemCair->push_back(jogo);
    }

    /*  Este laço percorre todos os PossiveisJogos, incrementando (ou zerando)
        suas rodadas que estão sem acertos com base na tabela de Acertos, indo
        da rodada 1 até a rodada definida pelo usuário. */
    while (count < RODADA_VERIFICACAO) {
        file >> numeroJogoSorteado >> date;
        for (int i = 0; i < listaJogosSemCair->size(); i++) {

            /*  Lê o resultado da tabela de Acertos e incrementa/reseta o
                número de rodadas sem cair de cada Possível Jogo. */
            file >> resultado;
            if (resultado == 0)
                listaJogosSemCair->at(i)->setJogosSemCair(listaJogosSemCair->at(i)->getJogosSemCair() + 1);
            else {
                listaJogosSemCair->at(i)->setJogosSemCair(0);
            }
        }
        count++;
    }

    /*  Bloco de código para verificar qual o Jogo com o maior número de rodadas sem um acerto.
        Irrelevante, e será retirado ao longo do desenvolvimento desta implementação. */
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
    int test = 0, jogoComMaiorTempoSemCair = 0;
    for (int i = 0; i < listaJogosSemCair->size(); i++) {
        if (listaJogosSemCair->at(i)->getJogosSemCair() > test) {
            test = listaJogosSemCair->at(i)->getJogosSemCair();
            jogoComMaiorTempoSemCair = listaJogosSemCair->at(i)->getNumeroJogo();
        }
    }

    cout << "Até o jogo 500, o jogo com mais jogos sem cair é o jogo de número: " << jogoComMaiorTempoSemCair << "\ncom jogos sem cair: " << test << endl;
    cout << "Números Jogados: ";
    for (int i = 0; i < 15; i++) {
        cout << listaPossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados()[i] << " ";
    }
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

    /*  Bloco de código para verificar, após a rodada atual, quantas rodadas passarão
        até o jogo com maior numero de rodadas obter um acerto.
        Irrelevante, e será retirado ao longo do desenvolvimento desta implementação. */
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */
    /* Testando o jogo com maior tempo sem cair para ver em quantas rodadas ele vai acertar */
    bool acerto = false;
    int numerosCertos = 0;
    int *numerosJogados = new int[15];
    int jogoGanho = 0;
    numerosJogados = listaPossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados();

    for (int i = 634; i < NUM_JOGOS_ATUAIS; i++) {
        int *numerosSorteados = new int[15];
        numerosSorteados = listaJogosSorteados->at(i)->getNumerosSorteados();
        // for (int j = 0; j < 15; j++) {
        //     if (numerosJogados[j] == numerosSorteados[j])
        //         numerosCertos++;
        //     else {
        //         numerosCertos = 0;
        //         break;
        //     }
        // }
        for (int k = 0; k < 15; k++) {
            for (int l = 0; l < 15; l++) {
                if (numerosJogados[l] == numerosSorteados[k]) {
                    numerosCertos++;
                    break;
                }
            }
        }
        if (numerosCertos >= 11) {
            cout << "\nJogo ganho: " << endl;
            for (int m = 0; m < 15; m++) {
                cout << listaJogosSorteados->at(i)->getNumerosSorteados()[m] << " ";
            }
            acerto = true;
            jogoGanho = i;
            numerosCertos = 0;
            break;
        }
        numerosCertos = 0;
    }

    cout << "Jogo ganho: " << jogoGanho << endl;
    cout << "Numeros sorteados: ";
    int *numerosSorteados = new int[15];
    numerosSorteados = listaJogosSorteados->at(jogoGanho)->getNumerosSorteados();
    for (int i = 0; i < 15; i++) {
        cout << numerosSorteados[i] << " ";
    }
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
    ofstream sorteiosNaoCoincidentes;
    sorteiosNaoCoincidentes.open("Sorteios não coincidentes na linha 634.txt");

    sorteiosNaoCoincidentes << "Jogo 634\n";
    // for (int i = 0; i < lista->size(); i++) {
    //     sorteiosNaoCoincidentes << i << " ";
    // }
    // sorteiosNaoCoincidentes << "\n634 ";
    for (int i = 0; i < listaJogosSemCair->size(); i++) {
        sorteiosNaoCoincidentes << i << " " << listaJogosSemCair->at(i)->getJogosSemCair() << endl;
    }
    sorteiosNaoCoincidentes.close();

    // int arrayJogos = new int[16];
    int arrayJogos[] = {651, 111, 809, 645, 130, 813, 34, 674, 274, 384, 951, 277, 205, 249, 427, 665};
    int acertos = 0;
    double numAcertos = 0.0;
    cout << endl;

    for (int i = 0; i < 16; i++) {
        int *jogo = new int[15];
        jogo = listaPossiveisJogos->at(arrayJogos[i])->getNumerosSorteados();

        for (int j = 634; j < NUM_JOGOS_ATUAIS; j++) {
            for (int k = 0; k < 15; k++) {
                for (int l = 0; l < 15; l++) {
                    if (jogo[l] == listaJogosSorteados->at(j)->getNumerosSorteados()[k]) {
                        acertos++;
                        break;
                    }
                }
            }
            if (acertos >= 11) {
                cout << "Jogo "  << arrayJogos[i] << " acertou na rodada " << j << " - " << j-634 <<
                        " Acertos: " << acertos << endl;
                numAcertos++;
                acertos = 0;
                break;
            }
            acertos = 0;
        }
    }

    cout << endl << endl << "Taxa de acertos: " << numAcertos/16 << endl;
    /* XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX */

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
