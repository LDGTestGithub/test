

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

private:
    unsigned game;
    int *numeros_sorteados = new int[15];
    Date *date;
};
