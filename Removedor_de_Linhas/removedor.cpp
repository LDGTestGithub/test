#include <fstream>

using namespace std;

/* Remove as linhas em branco de um arquivo, escrevendo todo o conteúdo
   formatado em outro arquivo de texto.
 */

int main()
{
    ifstream input;
    ofstream output;
    string line;

    input.open("input.txt");
    output.open("output.txt");

    while (!input.eof()) {
        getline(input, line);
        if (line != "																")
            output << line << endl;
    }

    input.close();
    output.close();


}
