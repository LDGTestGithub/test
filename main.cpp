#include "lotofacil.h"

int main()
{
    Lotofacil *lotofacil = new Lotofacil();

    lotofacil->leJogosSorteados();
    lotofacil->lePossiveisJogos();
    lotofacil->escreveAcertos();
    // lotofacil->ordenaJogosSorteados();
    // lotofacil->verificaIrregularidadeAcertos();
    double mediaTotal = 0;
    for (int i = 0; i < 10; i++)
        mediaTotal += lotofacil->estrategiaDiferencaMedia(10, i);

    mediaTotal = mediaTotal/25;

    cout << "A taxa de acerto em 5 jogos, de 10 testes realizados, é de " << mediaTotal*100 << "%.\n";

    delete lotofacil;

    // lotofacil->incidencia();
    // lotofacil->verificaPadrao();
    // lotofacil->Combinacoes15();
    // lotofacil->Combinacoes12();
}
