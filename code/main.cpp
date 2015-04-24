#include <iostream>
#include "case.hpp"
#include "terrain.hpp"
#include "dijkstra.hpp"
/**
\file main.cpp
\brief Fichier de lancement de l'application
\author Martin M
\bug Soon :D
*/

using namespace std;





int main ()
{
    auto hello = []() { cout << "Vous etez bien en c++0X ou plus" << endl;};
    hello();

    Point3 p(1,0,0) , p2(0,4,0);
    cout << (p<p2) << " " << (p2 < p) << endl;
    //Terrain::test();
    cout << "----------------------------" << endl;
    Dijkstra::test();


}
