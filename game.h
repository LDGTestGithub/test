

using namespace std;

class Game
{
public:
    Game(unsigned _game, int *_numeros_sorteados, Date *_date)
    {
        game = _game;
        numeros_sorteados = _numeros_sorteados;
        date = _date;
    }

    unsigned getNumberGame()
    {
        return game;
    }

    int* getNumerosSorteados()
    {
        return numeros_sorteados;
    }

    Date* getDate()
    {
        return date;
    }

    double getDistanciaMedia()
    {
        return distanciaMedia;
    }

    void setDistanciaMedia(double _distanciaMedia)
    {
        distanciaMedia = _distanciaMedia;
    }

    double getDiferencaDistanciaTotal()
    {
        return diferencaDistanciaTotal;
    }

    void setDiferencaDistanciaTotal(double _diferencaDistanciaTotal)
    {
        diferencaDistanciaTotal = _diferencaDistanciaTotal;
    }

    int getJogosSemCair()
    {
        return jogosSemCair;
    }

    void setJogosSemCair(int _jogosSemCair)
    {
        jogosSemCair = _jogosSemCair;
    }

private:
    unsigned game;
    int *numeros_sorteados = new int[15];
    Date *date;
    double distanciaMedia = 0;
    double diferencaDistanciaTotal = 0;
    int jogosSemCair = 0;
};
