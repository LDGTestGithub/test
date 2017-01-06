#include "lotofacil.h"

int main()
{
    Lotofacil *lotofacil = new Lotofacil();

    lotofacil->leJogosSorteados();
    // lotofacil->lePossiveisJogos();
    // lotofacil->escreveAcertos();
    //
    //
    // // lotofacil->testaEstrategiaDiferencaMedia(1000, 10, 10);
    // lotofacil->testaEstrategiaDiferencaMediaEMaiorSequenciaFalha(1000, 10, 5);

    // lotofacil->testaProporcaoParesImpares();
    // lotofacil->testaProporcaoRepetidosNaoRepetidos();
    // lotofacil->testaRepeticaoNumerosMultiplos();
    // lotofacil->testaRepeticaoLinhas();
    // lotofacil->testaSistemaDePorcentagem();
    lotofacil->testaSistemaLotofacil(500);

    delete lotofacil;

    // lotofacil->incidencia();
    // lotofacil->verificaPadrao();
    // lotofacil->Combinacoes15();
    // lotofacil->Combinacoes12();
}
