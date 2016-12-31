#include <iostream>
#include <fstream>
#include <string>
#include "date.h"
#include "game.h"
#include "linked_list.h"
#include "combinacao.h"
#include "comb15.h"

using namespace std;

class Lotofacil
{
public:
    void readTable();
    void verificaPadrao();
    void Combinacoes15();
    void Combinacoes12();
    void incidencia();
    void montaTabelaDeJogosAleatoriosESeusAcertos();
    void verificaAcertosDosPossiveisJogos();
    void ordenaLotofacil();
    void bubbleSort(int *vetor);

    structures::LinkedList<Game*> *listaDePossiveisJogos = new structures::LinkedList<Game*>();

private:
    void formatDate(string dateString, Date *date);
    structures::LinkedList<Game*> *list_of_games = new structures::LinkedList<Game*>();
};
