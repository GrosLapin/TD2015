#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <map>
#include <functional>
#include <limits>

#include "terrain.hpp"

// Version vraiment pas modulable :D

class Dijkstra{

    static const int infranchissable = std::numeric_limits<int>::max();
    static const int notVisited = std::numeric_limits<int>::max()-1;

    // on a besoin de garder le distance de chaque case à l'origine
    struct CaseDistance {
        const Case& laCase;
        int distance;
        CaseDistance (const Case& c) :laCase(c),  distance(notVisited) {}
    };

    // Le terrain et Dijkstra on le meme ordre de case ce qui vos nous simplifier grandement la vie
    const Terrain& terrain;
    bool aVerifier;
    std::vector<CaseDistance> cases;
    std::vector<std::size_t> indiceChemin;
    int distanceVoisinMin (CaseDistance& uneCaseDistance)
    {
        if (! uneCaseDistance.laCase.haveVoisins()) {
             throw std::logic_error("distanceVoisinMin : Recherche d'un voisin sur une cases sans voisin: "
                + std_fix::to_string(uneCaseDistance.laCase.getCoordonnees()));
        }
        int min = infranchissable;
        for (const size_t& voisin : uneCaseDistance.laCase )
        {
            int distanceVoisin = cases[voisin].distance;
            if ( min > distanceVoisin )
            {
                min = distanceVoisin;
            }
        }
        return min;
    }
    size_t indiceVoisinDistanceMin(CaseDistance& uneCaseDistance)
    {
        if ( ! uneCaseDistance.laCase.haveVoisins()) {
            throw std::logic_error("indiceVoisinDistanceMin : Recherche d'un voisin sur une cases sans voisin: "
                + std_fix::to_string(uneCaseDistance.laCase.getCoordonnees()));
        }
        size_t indice = uneCaseDistance.laCase.getIndice();
        int min = infranchissable;
        for (const size_t& voisin : uneCaseDistance.laCase )
        {
            int distanceVoisin = cases[voisin].distance;
            if ( min > distanceVoisin )
            {
                min = distanceVoisin;
                indice = cases[voisin].laCase.getIndice();
            }
        }
        return indice;
    }

    size_t indiceCaseSuivanteDansChemin(CaseDistance& uneCaseDistance)
    {
        if ( ! uneCaseDistance.laCase.haveVoisins()) {
            throw std::logic_error("indiceVoisinDistanceMin : Recherche d'un voisin sur une cases sans voisin: "
                + std_fix::to_string(uneCaseDistance.laCase.getCoordonnees()));
        }
        size_t indice = uneCaseDistance.laCase.getIndice();
        int min = infranchissable;
        for (const size_t& voisin : uneCaseDistance.laCase )
        {
            int distanceVoisin = cases[voisin].distance;
            if ( min > distanceVoisin && distanceVoisin > uneCaseDistance.distance )
            {
                min = distanceVoisin;
                indice = cases[voisin].laCase.getIndice();
            }
        }
        return indice;
    }


    /// Modification a faire ici pour tenir compte des cases infranchissable / poids des cases
    /// Probleme : comment faire ça bien xD
    void calculedistance (CaseDistance& uneCaseDistance) {
          uneCaseDistance.distance = distanceVoisinMin(uneCaseDistance) + 1;
    }

    void checkInput(size_t indiceDebut, size_t indiceFin ){
        // vérification
        if ( indiceDebut >= cases.size() || indiceFin >= cases.size() )
        {
            throw std::logic_error("Indice hors tableau dans le calcul de chemin");
        }
    }
    inline void synchronisationWithTerrain()
    {
        cases.clear();
        for (const Case& c : terrain)
        {
            cases.push_back(CaseDistance(c));
        }
    }

    public :
    static void test (){
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
        size_t indice = dij.indiceProchaineCase (0,12);

        cout << "La permiere case pour allée en 4 , 4 est : "<<indice << endl;
        cout << " il faudra : " << dij.indiceChemin.size() << " pour y aller"<< endl;

    }
    size_t indiceProchaineCase(size_t indiceDebut, size_t indiceFin ) {
        if (aVerifier)
        {
            using namespace std;
            synchronisationWithTerrain();
            cout << "synchronisationWithTerrain fait" <<  endl;
            calculPoidsCases(indiceDebut,indiceFin);
            cout << "calculPoidsCases fait" <<  endl;
            calculChemin(indiceDebut,indiceFin);
            cout << "calculChemin" <<  endl;
            aVerifier =false;
        }
        // si on a pas de chemin ou retourne la case de debut
        // Todo : reflechir a une autre solution ? -1 / execption
        if (indiceChemin.empty())
        {
            return indiceDebut;
        }
        return indiceChemin.back();
    }
    void retirerPremiereCase()
    {
        indiceChemin.pop_back();
    }
    void calculChemin(size_t indiceDebut, size_t indiceFin )
    {
        // comme d'ab
        checkInput(indiceDebut,indiceFin);
        indiceChemin.clear();

        // si le debut n'est pas visité c'est qu'il y a pas de chemin
        CaseDistance& debut = cases[indiceDebut];
        if (debut.distance == notVisited ) {
            return;
        }

        indiceChemin.push_back(indiceFin);
        while(cases[indiceChemin.back()].laCase.getIndice() != indiceDebut)
        {
            std::cout << cases[indiceChemin.back()].laCase.getCoordonnees() << " distance : "<<cases[indiceChemin.back()].distance <<std::endl;
            int indice = indiceCaseSuivanteDansChemin(cases[indiceChemin.back()]);
            std::cout << cases[indice].laCase.getCoordonnees() << " distance : "<<cases[indice].distance  <<std::endl;
            indiceChemin.push_back(indiceCaseSuivanteDansChemin(cases[indiceChemin.back()]));

        }

        /// A vérifier mais à priorie on veut pas que le debut soit dans le chemin
        indiceChemin.pop_back();
    }
    void calculPoidsCases(size_t indiceDebut, size_t indiceFin )
    {
        checkInput(indiceDebut,indiceFin);

        // la case du debut vaut 0
        CaseDistance& fin = cases[indiceFin];
        fin.distance = 0 ;

        std::vector<size_t> vecIndiceAVisiter (fin.laCase.begin(), fin.laCase.end());

        while ( ! vecIndiceAVisiter.empty() )
        {
            size_t indiceEnCour = vecIndiceAVisiter.back();
            vecIndiceAVisiter.pop_back();

            CaseDistance& caseEnCour = cases[indiceEnCour];
            calculedistance(caseEnCour);

            for (size_t indice : caseEnCour.laCase )
            {
                if ( cases[indice].distance > caseEnCour.distance+1 )
                {
                    vecIndiceAVisiter.push_back(indice);
                }
            }
        }
    }
    Dijkstra(const Terrain& leTerrain) : terrain(leTerrain), aVerifier(true){

    }


};

#endif // DIJKSTRA_HPP
