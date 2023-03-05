//
// Created by pantom on 23.02.2023.
//
#include <stdio.h>
#include <iostream>

using namespace std;
//using namespace test;


int main(){

    std::cout << "Ahoj z C++" << std::endl;

    int a = 45;

    std::cout << "a = " << a << std::endl;

    cout << "a = " << a << endl;


    
    /*
    std::cout - standardni vystup
    std::cerr - standardni chybivy vystup
    std::cin - standarni vstup
    std::clog - standardni logovaci vstup
    */

   //Nacitani vstupu
    
    cout << "Zadejte cislo typu int" << endl;

    cin >> a;

    if (cin.good())
    {
        cout << "datovy typ spravne" << a << endl;
    }
    else{
        cout << "error" << endl;
    }

    
    
    
    return 0;
}
