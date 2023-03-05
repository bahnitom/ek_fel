#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.141592;
    double pj = 65.1681312546;
    double pk = 84322.4488448848;

    std::cout << pi << ' ' << pj << ' ' << pk << std::endl;

    std::cout << std::setprecision(2); // precision udava pocet platnych mist
    std::cout << pi << ' ' << pj << ' ' << pk << std::endl;

    std::cout << std::fixed; // precision ted udava pocet desetinnych mist
    std::cout << pi << ' ' << pj << ' ' << pk << std::endl;

    std::cout << std::setprecision(5); 
    std::cout << pi << ' ' << pj << ' ' << pk << std::endl;

    std::cout << std::scientific; 
    std::cout << pi << ' ' << pj << ' ' << pk << std::endl;

    //nastaveni do default nastaveni
    std::cout.unsetf(std::ios_base::floatfield);
    std::cout << std::setprecision(6); //default precision je 6
    std::cout << pi << ' ' << pj << ' ' << pk << std::endl;


    std::cout << std::setw(20) << pi << ' ' << pj << ' ' << std::setw(100) << pk << std::endl;
    //setw nastavuje sirku nasledujiciho vypisu, neni persistentni

    return 0;
}