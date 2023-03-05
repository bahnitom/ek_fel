#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream in ("01.C++");
    ofstream out ("COPY-OF-01.C++");

    if(in.good())
        cout << "podarilo se nacist\n";

        string s;

        while(getline(in,s)){
            cout << s << std::endl;
            out << s << std::endl;
        }
    return 0;
}