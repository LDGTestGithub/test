#include "lotofacil.h"

int main()
{
    Lotofacil *lotofacil = new Lotofacil();

    lotofacil->readTable();
    lotofacil->montaTabelaDeJogosAleatoriosESeusAcertos();
    lotofacil->verificaAcertosDosPossiveisJogos();
    // lotofacil->ordenaLotofacil();
    lotofacil->verificaJogosQueEstaoHaMaisTempoSemCair();

    // lotofacil->incidencia();
    // lotofacil->verificaPadrao();
    // lotofacil->Combinacoes15();
    // lotofacil->Combinacoes12();
}
