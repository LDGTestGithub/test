#include "lotofacil.h"

int main()
{
    Lotofacil *lotofacil = new Lotofacil();

    lotofacil->leJogosSorteados();
    lotofacil->lePossiveisJogos();
    lotofacil->escreveAcertos();
    // lotofacil->ordenaJogosSorteados();
    lotofacil->verificaIrregularidadeAcertos();

    delete lotofacil;

    // lotofacil->incidencia();
    // lotofacil->verificaPadrao();
    // lotofacil->Combinacoes15();
    // lotofacil->Combinacoes12();
}
