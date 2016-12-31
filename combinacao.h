

class Combinacao
{
public:
    Combinacao(int _a, int _b, int _c) {
        a = _a;
        b = _b;
        c = _c;
    }

    int getA()
    {
        return a;
    }

    int getB()
    {
        return b;
    }

    int getC()
    {
        return c;
    }

    void incIncidencia()
    {
        incidencia++;
    }

    int getIncidencia()
    {
        return incidencia;
    }

private:
    int a, b, c;
    int incidencia = 0;
};
