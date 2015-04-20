#include <iostream>
#include "case.hpp"
#include "terrain.hpp"
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


    cout << "iterator " <<  is_iterator<vector<int>::iterator>::value << endl;
    cout << "int " <<  is_iterator<int>::value << endl;
    Case a,b,c,non;
    a.addVoisin(b);

    a.addVoisin(c);

    Terrain terrain;
    terrain.addCase(Point2(1,2));
    /*
    terrain.addCase(Terrain<2>::Coordonnee(1,2));*/



/*    terrain.addCase(a);
    terrain.addCase(b);*/


  cout << terrain.cases.size() << endl;


}
