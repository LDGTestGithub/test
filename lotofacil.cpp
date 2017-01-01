#include "lotofacil.h"

#define NUM_JOGOS_ATUAIS 1454
#define NUM_POSSIVEIS_JOGOS 966

void Lotofacil::readTable()
{
    ifstream file;
    file.open("dados/lotofacilOrdenada.txt");
    int line = 0;
    file.seekg(0, file.end);
    unsigned END_FILE = file.tellg();
    file.seekg(0, file.beg);

    while(file.tellg() < END_FILE - 2) {
        cout << "Tellg: " << file.tellg() << endl;
        Date *date = new Date();
        int *numeros_sorteados = new int[15];
        unsigned number_game, number, count = 0;
        string dateString;

        file >> number_game >> dateString;

        /* Formata a data para o objeto */
        formatDate(dateString, date);

        /* Adiciona os números sorteados no array */

        for (int i = 0u; i < 15; i++) {
            file >> numeros_sorteados[i];
        }

        cout << "Game: " << number_game << " Date: ";
        date->printDate();
        cout << endl;
        for (int j = 0u; j < 15; j++)
            cout << numeros_sorteados[j] << " ";
        cout << endl;

        Game *game = new Game(number_game, numeros_sorteados, date);
        listaJogosSorteados->push_back(game);
    }
    cout << "ListSize = " << listaJogosSorteados->size() << endl;
    file.close();
}

void Lotofacil::montaTabelaDeJogosAleatoriosESeusAcertos()
{
    int numeroJogo = 0;
    string dataString = "02/03/04";
    int count = 0;

    ifstream file;
    file.open("dados/PossiveisJogos.txt");

    /* Procura a marcação de fim do arquivo */
    file.seekg(0, file.end);
    int END_FILE = file.tellg();
    file.seekg(0, file.beg);

    while (count < NUM_POSSIVEIS_JOGOS) {
        int *numerosJogados = new int[15];
        count++;
        Date *date = new Date();

        numeroJogo++;
        cout << file.tellg() << " | " << END_FILE << endl;

        /* Formata a data para o objeto */

        formatDate(dataString, date);


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

void Lotofacil::verificaAcertosDosPossiveisJogos()
{
    ofstream file;
    file.open("dados/Acertos.txt");
    int acertos = 0;

    for (int i = 0; i < listaJogosSorteados->size(); i++) {
        /* Início da linha, com o número do jogo e sua data */
        file << listaJogosSorteados->at(i)->getNumberGame() << " "
             << listaJogosSorteados->at(i)->getDate()->getDay() << "/"
             << listaJogosSorteados->at(i)->getDate()->getMonth() << "/"
             << listaJogosSorteados->at(i)->getDate()->getYear() << " ";

        int *numerosSorteados = new int[15];
        numerosSorteados = listaJogosSorteados->at(i)->getNumerosSorteados();

        for (int j = 0; j < listaPossiveisJogos->size(); j++) {
            int *numerosJogados = new int[15];
            numerosJogados = listaPossiveisJogos->at(j)->getNumerosSorteados();

            for (int k = 0; k < 15; k++) {
                for (int l = 0; l < 15; l++) {
                    if (numerosJogados[l] == numerosSorteados[k]) {
                        acertos++;
                        break;
                    }
                }
            }
            if (acertos > 10)
                file << "1 ";
            else
                file << "0 ";
            acertos = 0;
        }
        file << endl;
        cout << "I: " << i << "\n";
    }
    file.close();
}

void Lotofacil::formatDate(string dateString, Date *date)
{
    unsigned m = 0, n = 0;
    string day_, month_, year_;

    while (dateString[m] != '/') {
        day_[n] = dateString[m];
        m++;
        n++;
    }

    int day = stoi(day_);
    date->setDay(day);

    m++;
    n = 0;
    while (dateString[m] != '/') {
        month_[n] = dateString[m];
        m++;
        n++;
    }
    int month = stoi(month_);
    date->setMonth(month);

    m++;
    n = 0;
    while (dateString[m] != '\0') {
        year_[n] = dateString[m];
        m++;
        n++;
    }
    int year = stoi(year_);
    date->setYear(year);
}

void Lotofacil::ordenaLotofacil()
{
    fstream input, output;
    int numeroJogo;
    string data;
    int count = 0;

    input.open("dados/lotofacil.txt");
    output.open("dados/lotofacilOrdenada.txt");

    while (count < NUM_JOGOS_ATUAIS) {
        count++;

        input >> numeroJogo >> data;
        int *numerosJogados = new int[15];
        for (int i = 0; i < 15; i++) {
            input >> numerosJogados[i];
            cout << numerosJogados[i] << " ";
        }
        cout << endl;

        bubbleSort(numerosJogados);

        output << numeroJogo << " " << data << " ";
        for (int i = 0; i < 15; i++) {
            output << numerosJogados[i] << " ";
        }
        output << endl;

    }


}

void Lotofacil::verificaJogosQueEstaoHaMaisTempoSemCair()
{
    structures::LinkedList<JogosSemCair*> *lista = new structures::LinkedList<JogosSemCair*>();

    ifstream file;
    file.open("dados/Acertos.txt");
    unsigned count = 0, numeroJogoSorteado;
    unsigned resultado;
    string date;

    for (int i = 0; i < NUM_POSSIVEIS_JOGOS; i++) {
        JogosSemCair *jogo = new JogosSemCair();
        jogo->setNumeroJogo(i);
        lista->push_back(jogo);
    }

    while (count < 634) {
        file >> numeroJogoSorteado >> date;
        for (int i = 0; i < lista->size(); i++) {
            file >> resultado;
            if (resultado == 0)
                lista->at(i)->setJogosSemCair(lista->at(i)->getJogosSemCair() + 1);
            else {
                lista->at(i)->setJogosSemCair(0);
            }
        }
        cout << "Count: " << count << endl;
        count++;
    }

    int test = 0, jogoComMaiorTempoSemCair = 0;
    for (int i = 0; i < lista->size(); i++) {
        if (lista->at(i)->getJogosSemCair() > test) {
            test = lista->at(i)->getJogosSemCair();
            jogoComMaiorTempoSemCair = lista->at(i)->getNumeroJogo();
        }
    }

    cout << "Até o jogo 500, o jogo com mais jogos sem cair é o jogo de número: " << jogoComMaiorTempoSemCair << "\ncom jogos sem cair: " << test << endl;
    cout << "Números Jogados: ";
    for (int i = 0; i < 15; i++) {
        cout << listaPossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados()[i] << " ";
    }

    /* Testando o jogo 1971 para ver em quantas rodadas ele vai acertar */
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

    /*  ///////////////////////////////////////////////########################################## */

    ofstream sorteiosNaoCoincidentes;
    sorteiosNaoCoincidentes.open("Sorteios não coincidentes na linha 634.txt");

    sorteiosNaoCoincidentes << "Jogo 634\n";
    // for (int i = 0; i < lista->size(); i++) {
    //     sorteiosNaoCoincidentes << i << " ";
    // }
    // sorteiosNaoCoincidentes << "\n634 ";
    for (int i = 0; i < lista->size(); i++) {
        sorteiosNaoCoincidentes << i << " " << lista->at(i)->getJogosSemCair() << endl;
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

    /*  ///////////////////////////////////////////////########################################## */


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
