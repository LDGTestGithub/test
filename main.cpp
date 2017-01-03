#include "lotofacil.h"

int main()
{
    Lotofacil *lotofacil = new Lotofacil();

    lotofacil->leJogosSorteados();
    lotofacil->lePossiveisJogos();
    lotofacil->escreveAcertos();
    // lotofacil->ordenaJogosSorteados();
    // lotofacil->verificaIrregularidadeAcertos();
    int rodadaInicioVerificacao = 1000, numRodadasVerificacao = 10;
    double mediaTotal = 0, mediaMaxima = 0, mediaMinima = 1, aux = 0;
    for (int i = rodadaInicioVerificacao; i < rodadaInicioVerificacao+numRodadasVerificacao; i++) {
        aux = lotofacil->estrategiaDiferencaMedia(numRodadasVerificacao, i);
        mediaTotal += aux;

        if (aux > mediaMaxima)
            mediaMaxima = aux;
        if (aux < mediaMinima)
            mediaMinima = aux;
    }

    mediaTotal = mediaTotal/10;

    cout << "\nA taxa de acerto em 5 jogos, de " << numRodadasVerificacao << " testes realizados, é de " << mediaTotal*100 << "%.\n"
         << "Com média máxima de " << mediaMaxima*100 << "%. E mínima de " << mediaMinima*100 << "%.\n\n";

    delete lotofacil;

    // lotofacil->incidencia();
    // lotofacil->verificaPadrao();
    // lotofacil->Combinacoes15();
    // lotofacil->Combinacoes12();
}
