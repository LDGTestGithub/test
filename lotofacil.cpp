#include "lotofacil.h"
#define NUM_JOGOS_ATUAIS 1454
#define NUM_POSSIVEIS_JOGOS 966

void Lotofacil::readTable()
{
    // structures::LinkedList<Game*> *list = new structures::LinkedList<Game*>();
    ifstream file;
    file.open("lotofacilOrdenada.txt");
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
        list_of_games->push_back(game);
    }
    cout << "ListSize = " << list_of_games->size() << endl;
    file.close();

    // /* Verifica incidência */
    // int *incidencia = new int[25];
    //
    // /* Zera o array de incidencia */
    // for (int i = 0; i < 25; i++) {
    //     incidencia[i] = 0;
    // }
    // int *array_aux = new int[15];
    //
    // /* Preenche array de incidencia */
    // for (int i = 0; i < list_of_games->size(); i++) {
    //     Game *game = list_of_games->at(i);
    //     array_aux = game->getNumerosSorteados();
    //
    //     cout << "game number: " << game->getNumberGame() << endl;
    //
    //     for (int k = 0; k < 15; k++) {
    //         cout << array_aux[k] << " ";
    //     }
    //     cout << endl;
    //
    //     for (int j = 0; j < 15; j++) {
    //         incidencia[array_aux[j]-1]++;
    //     }
    //
    // }
    //
    // for (int k = 0; k < 25; k++) {
    //     cout << incidencia[k] << " ";
    // }

}

void Lotofacil::montaTabelaDeJogosAleatoriosESeusAcertos()
{
    int numeroJogo = 0;
    string dataString = "02/03/04";
    int count = 0;

    ifstream file;
    file.open("PossiveisJogos.txt");

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
        listaDePossiveisJogos->push_back(game);

        // int *array = new int[15];
        // array = listaDePossiveisJogos->at(listaDePossiveisJogos->size()-1)->getNumerosSorteados();
        // cout << listaDePossiveisJogos->at(listaDePossiveisJogos->size()-1)->getNumberGame() << " - ";
        // for (int i = 0; i < 15; i++) {
        //     cout << array[i] << " ";
        // }
        // cout << endl;
    }

    file.close();

    /* Impressão da lista de PossiveisJogos */
    // int *array = new int[15];
    // for (int i = 0; i < listaDePossiveisJogos->size(); i++) {
    //     array = listaDePossiveisJogos->at(i)->getNumerosSorteados();
    //     for (int j = 0; j < 15; j++) {
    //         cout << array[j] << " ";
    //     }
    //     cout << endl;
    // }

}

void Lotofacil::verificaAcertosDosPossiveisJogos()
{
    ofstream file;
    file.open("Acertos.txt");
    int acertos = 0;

    /* Print */
    // int *a = new int[15];
    // int *b = new int[15];
    //
    // a = list_of_games->at(0)->getNumerosSorteados();
    // b = listaDePossiveisJogos->at(0)->getNumerosSorteados();
    //
    // cout << "Números Sorteados: ";
    // for (int i = 0; i < 15; i++) {
    //     cout << a[i] << " ";
    // }
    //
    // cout << "Números Jogados: ";
    // for (int i = 0; i < 15; i++) {
    //     cout << b[i] << " ";
    // }
    /*    */

    for (int i = 0; i < list_of_games->size(); i++) {
        /* Início da linha, com o número do jogo e sua data */
        file << list_of_games->at(i)->getNumberGame() << " "
             << list_of_games->at(i)->getDate()->getDay() << "/"
             << list_of_games->at(i)->getDate()->getMonth() << "/"
             << list_of_games->at(i)->getDate()->getYear() << " ";

         int *numerosSorteados = new int[15];
         numerosSorteados = list_of_games->at(i)->getNumerosSorteados();
        //  cout << "Números Sorteados: ";
        //  for (int i = 0; i < 15; i++) {
        //      cout << numerosSorteados[i] << " ";
        //  }

        for (int j = 0; j < listaDePossiveisJogos->size(); j++) {
            int *numerosJogados = new int[15];
            numerosJogados = listaDePossiveisJogos->at(j)->getNumerosSorteados();
            // cout << "Números Jogados: ";
            // for (int i = 0; i < 15; i++) {
            //     cout << numerosJogados[i] << " ";
            // }

            for (int k = 0; k < 15; k++) {
                for (int l = 0; l < 15; l++) {
                    // cout << "if (" << numerosJogados[l] << " == " << numerosSorteados[k] << ")" << endl;
                    if (numerosJogados[l] == numerosSorteados[k]) {
                        acertos++;
                        // cout << "Acertos: " << acertos << endl;
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

void Lotofacil::verificaPadrao()
{
    /* A quantidade de números que se repetem em módulo 4 */
    // int *repeticoes = new int[25];
    // int *array = new int[15];
    // int *array_aux = new int[15];
    //
    // for (int i = 0; i < 25; i++) {
    //     repeticoes[i-1] = 0;
    //     array_aux = list_of_games->at(i)->getNumerosSorteados();
    //
    //     for (int j = 0; j < 25; j++) {
    //         if (array[j] == array_aux[j])
    //             repeticoes[i-1]++;
    //     }
    //
    //     cout << endl << "Repetições entre o jogo 1 e o jogo " << i+1 << ": " << repeticoes[i-1];
    // }

    /* Quais jogos possuem 10 numeros iguais aos do jogo 1 */
    // int *jogos = new int[200];
    // for (int i = 0; i < 200; i++)
    //     jogos[i] = 0;
    // int counter = 0;
    // int *numeros_jogo1 = new int[15];
    // int *array_aux = new int[15];
    // numeros_jogo1 = list_of_games->at(0)->getNumerosSorteados();
    //
    // for (int i = 1; i < list_of_games->size(); i++) {
    //     int count = 0;
    //     array_aux = list_of_games->at(i)->getNumerosSorteados();
    //     for (int j = 0; j < 15; j++) {
    //         for (int k = j; k < 15; k++) {
    //             if (numeros_jogo1[j] == array_aux[k])
    //                 count++;
    //             if (numeros_jogo1[j] < array_aux[k])
    //                 break;
    //         }
    //     }
    //     if (count > 10) {
    //         jogos[counter] = i;
    //         counter++;
    //     }
    // }
    //
    // /* Calcula distancia média entre os jogos com 11 números iguais */
    // int distancia = 0;
    // for (int i = 0; i < counter-1; i++) {
    //     distancia += jogos[i+1] - jogos[i];
    // }
    // cout << "\n\nDistancia média: " << distancia/counter << endl;
    //
    // cout << "\nNúmero de jogos com 11 números iguais ao jogo 1: " << counter << endl;
    //
    // for (int i = 0; i < counter; i++) {
    //     cout << jogos[i] << endl;
    // }
    //
    // /* Verifica quantos jogos terão 11 acertos ao longo do tempo */
    // int num_vitorias = 0;
    // int fator = 1;
    // int *numeros_jogados = new int[15];
    // int *aux = new int[15];
    // unsigned long dinheiro_gasto = 0, dinheiro_ganho = 0;
    // numeros_jogados =  list_of_games->at(0)->getNumerosSorteados();
    // int c = 0;
    //
    // for (int i = 1; i < 60; i++) {
    //     aux = list_of_games->at(i)->getNumerosSorteados();
    //     for (int j = 0; j < 15; j++) {
    //         for (int k = 0; k < 15; k++) {
    //             if (numeros_jogados[j] == aux[k]) {
    //                 c++;
    //                 break;
    //             }
    //
    //             // if (numeros_jogados[j] < aux[k])
    //             //     break;
    //         }
    //     }
    //     if (c < 11)
    //         fator = fator*3;
    //     if (c > 10) {
    //         dinheiro_ganho += 2*fator;
    //         num_vitorias++;
    //         fator = 1;
    //     }
    //     if (c > 11) {
    //         dinheiro_ganho += 2*fator;
    //         fator = 1;
    //     }
    //     if (c > 12) {
    //         dinheiro_ganho += 6*fator;
    //         fator = 1;
    //     }
    //     c = 0;
    //
    //     dinheiro_gasto += 2*fator;
    // }
    //
    // cout << "Ganho: " << dinheiro_ganho << " - Perdido: " << dinheiro_gasto << endl;
    // cout << "Vitorias = " << num_vitorias;

    /* Verifica o dinheiro ganho trocando, a cada jogada, o jogo apostado por 20 jogos
        anteriores ao atual */

//         int maior_lucro = 0, melhor_retorno = 0;
//     for (int m = 1; m < 800; m++) {
//
//         int *numeros_jogados = new int[15];
//         int *aux = new int[15];
//         int num_vitorias = 0;
//
//         int jogo_atual = 21;
//         int dinheiro_gasto = 0, dinheiro_ganho = 0;
//         int c = 0;
//
//         for (int i = m+1; i < list_of_games->size()-1; i++) {
//             numeros_jogados = list_of_games->at(i-m)->getNumerosSorteados();
//             aux = list_of_games->at(i)->getNumerosSorteados();
//             for (int j = 0; j < 15; j++) {
//                 for (int k = j; k < 15; k++) {
//                     if (numeros_jogados[j] == aux[k])
//                         c++;
//                     if (numeros_jogados[j] < aux[k])
//                         break;
//                 }
//             }
//                 if (c > 10) {
//                     dinheiro_ganho += 2;
//                     num_vitorias++;
//                 }
//                 if (c > 11)
//                     dinheiro_ganho += 2;
//                 if (c > 12)
//                     dinheiro_ganho += 6;
//
//                 dinheiro_gasto += 2;
//                 c = 0;
//
//                 if (dinheiro_ganho > maior_lucro) {
//                     maior_lucro = dinheiro_ganho;
//                     melhor_retorno = m;
//                 }
//         }
//
//         cout << "Ganho: " << dinheiro_ganho << " - Perdido: " << dinheiro_gasto << endl;
//         cout << "Vitórias: " << num_vitorias << endl;
// }
// cout << "Maior Lucro: " << maior_lucro << " Retornando: " << melhor_retorno << endl;

    /* Combinação de 3 números que se repetem mais vezes */
    int *incidencia = new int[25];
    int num_combinacoes = 0;
    int contador_acertos = 0;

    structures::LinkedList<Combinacao*> *list = new structures::LinkedList<Combinacao*>();
    for (int i = 1; i < 16; i++) {
        for (int j = i+1; j < 16; j++) {
            for (int k = j+1; k < 16; k++) {
                Combinacao *comb = new Combinacao(i, j, k);
                list->push_back(comb);
                num_combinacoes++;
            }
        }
    }
    cout << "\n\nNum Combinações: " << num_combinacoes << endl;

    /* Verifica se a combinação está no jogo, e incrementa um contador */

    int *aux = new int[15];

    for (int i = 0; i < list_of_games->size(); i++) {
        aux = list_of_games->at(i)->getNumerosSorteados();
        int count_aux = 0;

        for (int j = 0; j < list->size(); j++) {
            int a = list->at(j)->getA();
            int b = list->at(j)->getB();
            int c = list->at(j)->getC();

            for (int k = 0; k < 15; k++) {
                if (aux[k] == a)
                    count_aux++;
            }
            for (int k = 0; k < 15; k++) {
                if (aux[k] == b)
                    count_aux++;
            }
            for (int k = 0; k < 15; k++) {
                if (aux[k] == c)
                    count_aux++;
            }
            if (count_aux == 3)
                list->at(j)->incIncidencia();

        }
        // cout << "Jogo: " << i << endl;
    }

    /* Verifica com foi a combinação com maior incidencia */
    int maior_incidencia = 0;
    Combinacao *combinacao;

    for (int i = 0; i < list->size(); i++) {
        if (list->at(i)->getIncidencia() > maior_incidencia) {
            maior_incidencia = list->at(i)->getIncidencia();
            combinacao = list->at(i);
        }
    }

    structures::LinkedList<Combinacao*> *lista_ordenada = new structures::LinkedList<Combinacao*>();
    for (int i = 0; i < list->size(); i++) {
        cout << "Incidencia: " << list->at(i)->getIncidencia() << endl;
        lista_ordenada->insert_sorted(list->at(i));

    }

    cout << "Melhor combinação, A: " << combinacao->getA() <<
            " B: " << combinacao->getB() << " C: " << combinacao->getC() <<
            " com incidencia de " << combinacao->getIncidencia() << " vezes." << endl;

    /* Escreve todas as combinações de 3 algarismos (sem repetição) em arquivo */
    // ofstream file;
    // file.open("comb3.txt");

    // file << list->size() << endl;

    // for (int i = 0; i < list->size(); i++) {
    //     // cout << "I: " << i << endl;
    //     file << list->at(i)->getA() << " " << list->at(i)->getB() << " " << list->at(i)->getC() << '\n';
    // }

    // file.close();

    // cout << "A: " << lista_ordenada->at(0)->getA();

    cout << "Trios de números com maior incidência: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << "A: " << lista_ordenada->at(i)->getA() <<
                " B: " << lista_ordenada->at(i)->getB() <<
                " C: " << lista_ordenada->at(i)->getC() <<
                "Incidência: " << lista_ordenada->at(i)->getIncidencia() << endl;
    }

}

void Lotofacil::incidencia()
{
    int *aux = new int[15];
    int incidence_aux = 1, exclusao_aux = 1;
    bool incidence_bool = false, exclusao_bool = false, valor_anterior = false;
    structures::LinkedList<int> *incidence = new structures::LinkedList<int>();
    structures::LinkedList<int> *exclusao = new structures::LinkedList<int>();
    for (int i = 1; i < 26; i++) {
        for (int j = 0; j < list_of_games->size(); j++) {
            aux = list_of_games->at(j)->getNumerosSorteados();
            for (int k = 0; k < 15; k++) {
                if (aux[k] == i) {
                    incidence_bool = true;
                }
            }
            if (incidence_bool) {
                incidence->push_back(1);
            } else {
                incidence->push_back(0);
            }
            incidence_bool = false;
        }
    }

    // cout << "Incidências do número 1 em todos os jogos: " << endl;
    // for (int i = 0; i < incidence->size(); i++) {
    //     cout << incidence->at(i) << " ";
    // }

    structures::LinkedList<int> *incidencia = new structures::LinkedList<int>();
    structures::LinkedList<int> *ex = new structures::LinkedList<int>();
    int auxI = 0, auxE = 0;
    bool test;
    for (int i = 0; i < incidence->size()-1; i++) {
        if (incidence->at(i) == 1 && incidence->at(i+1) == 1)
            auxI++;
        else if (incidence->at(i) == 1 && incidence->at(i+1) == 0) {
            auxI++;
            incidencia->push_back(auxI);
            auxI = 0;
        }

        if (incidence->at(i) == 0 && incidence->at(i+1) == 0)
            auxE++;
        else if (incidence->at(i) == 0 && incidence->at(i+1) == 1) {
            auxE++;
            ex->push_back(auxE);
            auxE = 0;
        }
    }

    double soma = 0;
    for (auto i = 0; i < incidencia->size(); i++) {
        soma += incidencia->at(i);
        cout << incidencia->at(i) << " ";
    }

    cout << "Aparecimento médio do 1: " << soma / incidencia->size() << endl;

    soma = 0;
    for (auto i = 0; i < ex->size(); i++) {
        soma += ex->at(i);
        cout << ex->at(i) << " ";
    }

    cout << "Desaparecimento médio do 1: " << soma / ex->size() << endl;

}

void Lotofacil::ordenaLotofacil()
{
    fstream input, output;
    int numeroJogo;
    string data;
    int count = 0;

    input.open("lotofacil.txt");
    output.open("lotofacilOrdenada.txt");

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
    // struct jogos
    // {
    //     unsigned numeroJogo = 0;
    //     unsigned jogosSemCair = 0;
    // };



    structures::LinkedList<JogosSemCair*> *lista = new structures::LinkedList<JogosSemCair*>();

    ifstream file;
    file.open("Acertos.txt");
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
        // cout << "Número Jogo: " << lista->at(i)->getNumeroJogo() << "\nNúmero de jogos sem cair: " << lista->at(i)->getJogosSemCair() << endl;
    }

    cout << "Até o jogo 500, o jogo com mais jogos sem cair é o jogo de número: " << jogoComMaiorTempoSemCair << "\ncom jogos sem cair: " << test << endl;
    cout << "Números Jogados: ";
    for (int i = 0; i < 15; i++) {
        cout << listaDePossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados()[i] << " ";
    }

    /* Testando o jogo 1971 para ver em quantas rodadas ele vai acertar */
    bool acerto = false;
    int numerosCertos = 0;
    int *numerosJogados = new int[15];
    int jogoGanho = 0;
    numerosJogados = listaDePossiveisJogos->at(jogoComMaiorTempoSemCair)->getNumerosSorteados();

    for (int i = 634; i < NUM_JOGOS_ATUAIS; i++) {
        int *numerosSorteados = new int[15];
        numerosSorteados = list_of_games->at(i)->getNumerosSorteados();
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
                cout << list_of_games->at(i)->getNumerosSorteados()[m] << " ";
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
    numerosSorteados = list_of_games->at(jogoGanho)->getNumerosSorteados();
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
        jogo = listaDePossiveisJogos->at(arrayJogos[i])->getNumerosSorteados();

        for (int j = 634; j < NUM_JOGOS_ATUAIS; j++) {
            for (int k = 0; k < 15; k++) {
                for (int l = 0; l < 15; l++) {
                    if (jogo[l] == list_of_games->at(j)->getNumerosSorteados()[k]) {
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
