#include <iostream>

#include "utilitaire/fonctionTest/test.hpp"
#include "testClass.hpp"
#include "exemple/exemple_iterateurFoncteur.hpp"
#include "exemple/exemple_paramInfo.hpp"

/**
\file main.cpp
\brief Fichier de lancement de l'application
\author Martin M
\bug Soon :D
*/

#include "testPourLeDev.hpp"
using namespace std;


int main ()
{

    TestClass::testDijkstra();
    exempleIterateurFoncteur();
    exempleParamInfo();

}
