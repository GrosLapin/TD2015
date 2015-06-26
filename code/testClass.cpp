#include "testClass.hpp"


void TestClass::testDijkstra ()
{
    using namespace std;
    Terrain terrain;
    terrain.addCase(0,0);   //0
    terrain.addCase(0,1);   //1
    terrain.addCase(0,2);   //2
    terrain.addCase(0,3);   //3
    terrain.addCase(0,4);   //4

    terrain.addCase(1,0);   //5
    terrain.addCase(2,0);   //6
    terrain.addCase(3,0);   //7
    terrain.addCase(4,0);   //8

    terrain.addCase(4,1);   //9
    terrain.addCase(4,2);   //10
    terrain.addCase(4,3);   //11
    terrain.addCase(4,4);   //12

    terrain.addCase(3,4);   //13
    terrain.addCase(2,4);   //14
    terrain.addCase(1,4);   //15

    Dijkstra dij(terrain);
    size_t indiceNext = dij.indiceProchaineCase (terrain.getIndice(terrain.getCase(0,0)),
                                             terrain.getIndice(terrain.getCase(4,4)));
    size_t indiceSolution1 = terrain.getIndice(terrain.getCase(0,1));
    size_t indiceSolution2 = terrain.getIndice(terrain.getCase(1,0));

    cout << "Debut test dijkstra" << endl;
    testUnitaire((indiceNext == indiceSolution1 || indiceNext == indiceSolution2), "La case suivante doit etre 0,1 ou 1,0");
    testUnitaire(dij.indiceChemin.size() == 8, "Le chemin dois se faire en 8 coups pas en " + std_fix::to_string(dij.indiceChemin.size()));
    cout << "fin test dijkstra" << endl;

    Dijkstra test = std::move(dij);

}

