#include <iostream>
#include <fstream>
#include <string>
#include "date.h"
#include "game.h"
#include "linked_list.h"
#include "combinacao.h"
#include "comb15.h"
#include "jogosSemCair.h"

using namespace std;

class Lotofacil
{
public:

    /*  Destrutor. */
    ~Lotofacil() {
        delete listaPossiveisJogos;
        delete listaJogosSorteados;
    }

    /*  Lê os jogos já sorteados pela Lotofácil de um arquivo em disco,
        formata cada jogo para um objeto do tipo Game, e os lista em uma
        lista encadeada.

        Lista Encadeada de Jogos: listaJogosSorteados (variável global)
        Arquivo de Leitura: lotofacilOrdenada.txt
    */
    void leJogosSorteados();

    /*  Similar ao método anterior, ele lê as combinações de possíveis jogos
        em disco, formata cada um para um objeto do tipo Game, e os lista em
        uma lista encadeada.

        Lista Encadeada de Jogos: listaPossiveisJogos (variável global)
        Arquivo de Leitura: PossiveisJogos.txt
    */
    void lePossiveisJogos();

    /*  Compara a Lista de Jogos Sorteados com a Lista de Possíveis Jogos, e
        escreve em disco uma tabela com o os acertos de cada possível jogo para
        cada um dos jogos já sorteados.

        Arquivo de Escrita: Acertos.txt
    */
    void escreveAcertos();

    /*  Método auxiliar para ordenar os números de jogos sorteados, utilizado
        para agilizar a ordenação e comparação dos Jogos Sorteados.
    */
    void ordenaJogosSorteados();


    double verificaTaxaAcerto(structures::LinkedList<Game*> *listaJogosSelecionados, int rodadaVerificacao);


    void estrategiaAnaliseAcertos(int rodadaVerificacao);

    void estrategiaAleatoriedade(int rodadaVerificacao, int numRodadas, int numJogos);

    void testaEstrategiaDiferencaMedia(int rodadaVerificacao, int numRodadas, int numJogos);

    void testaEstrategiaDiferencaMediaEMaiorSequenciaFalha(int rodadaVerificacao, int numRodadas, int numJogos);

    void testaProporcaoParesImpares();

    void testaProporcaoRepetidosNaoRepetidos();

    void testaRepeticaoNumerosMultiplos();

    void testaRepeticaoLinhas();

    void testaSistemaDePorcentagem();

    void testaSistemaLotofacil(int rodadaVerificacao);

private:
    double estrategiaDiferencaMediaEMaiorSequenciaFalha(int rodadaVerificacao, int numJogos);

    double estrategiaDiferencaMedia(int rodadaVerificacao, int numJogos);
    /*  Método auxiliar para ordenação de um dado vetor em ordem crescente.
        Utiliza o método de ordenação BubbleSort.
    */
    void bubbleSort(int *vetor);

    /*  Método auxiliar para a formatação das datas dos jogos. Recebe como
        parâmetro uma string com a data e um objeto do tipo Date, onde será
        retornado por referência com os respectivos dados retirados da string.
    */
    void formatDate(string dateString, Date *date);

    /*  Lista encadeada que contém os objetos de todos as Combinações de
        Possíveis Jogos.
    */
    structures::LinkedList<Game*> *listaPossiveisJogos = new structures::LinkedList<Game*>();

    /*  Lista encadeada que contém os objetos de todos os Jogos Sorteados.
    */
    structures::LinkedList<Game*> *listaJogosSorteados = new structures::LinkedList<Game*>();
};
