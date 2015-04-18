#include <iostream>
#include "case.hpp"
/**
\file main.cpp
\brief Fichier de lancement de l'application
\author Martin M
\bug Soon :D
**/
using namespace std;

int main ()
{
    auto hello = []() { cout << "Vous etez bien en c++0X ou plus" << endl;};
    hello();

    Case a,b,c;
    a.addVoisin(b);
    a.addVoisin(c);
    for (auto v: a)
        cout << "test" << endl;
}
