#include <iostream>

using namespace std;

struct Struktura {
    int defvar; // defaultni viditelnost public
};

class Trida {
    int defvar; // defaultni viditelnost private
public:
    Trida() {cout<<"Konstruktor Tridy"<< endl;} // neparametricky konstruktor
    Trida(int x); // deklarace parametrickeho konstruktoru
    ~Trida() {cout<<"Destrktor Tridy"<<endl;}
    int get_defvar() {return this->defvar;}
    void set_defvar(int x) {defvar = x;}
    int a;
};

Trida::Trida(int x) {
    defvar = x;
    cout<<"Parametricky Konstruktor Tridy"<<endl;
}


int main() {
    Struktura sa;   // staticka alokace
    sa.defvar = 10;

    Struktura *ps = new Struktura(); // dynamicka alokace
    ps->defvar = 11;

    Trida ta;
    //ta.defvar = 12; // nelze, protoze je private
    ta.a = 12;
    ta.set_defvar(20);

    Trida *pt = new Trida(15); // dynamicka alokace
    pt->a = 14;

    cout << "sa.defvar = " << sa.defvar << endl;
    cout << "ps->defvar = " << ps->defvar << endl;
    cout << "ta.a = " << ta.a << endl;
    cout << "ta.defvar = " << ta.get_defvar()<< endl; // neprijme zjisteni hodnoty private promenne
    cout << "pt->a = " << pt->a << endl;
    cout << "pt->defvar = " << pt->get_defvar() << endl; // neprijme zjisteni hodnoty private promenne

    delete pt;

    return 0;
}