

using namespace std;

class JogosSemCair
{
public:
    unsigned getNumeroJogo()
    {
        return numeroJogo;
    }

    unsigned getJogosSemCair()
    {
        return jogosSemCair;
    }

    void setNumeroJogo(unsigned _numeroJogo)
    {
        numeroJogo = _numeroJogo;
    }

    void setJogosSemCair(unsigned _jogosSemCair)
    {
        jogosSemCair = _jogosSemCair;
    }

private:
    unsigned numeroJogo = 0;
    unsigned jogosSemCair = 0;
};
