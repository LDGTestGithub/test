class Comb15
{
public:
    Comb15(int _a, int _b, int _c, int _d, int _e, int _f, int _g, int _h, int _i,
            int _j, int _k, int _l, int _m, int _n, int _o) {
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        e = _e;
        f = _f;
        g = _g;
        h = _h;
        i = _i;
        j = _j;
        k = _k;
        l = _l;
        m = _m;
        n = _n;
        o = _o;
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
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o;
    int incidencia = 0;
};
