#include <iostream>
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
}
