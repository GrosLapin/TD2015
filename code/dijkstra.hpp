#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <map>
#include <functional>
#include <limits>

#include "terrain.hpp"

// Version vraiment pas modulable :D

class Dijkstra{

    static const int infranchissable = std::numeric_limits<int>::max();

    // on a besoin de garder le distance de chaque case à l'origine
    struct CaseDistance {
        const Case& laCase;
        int distance;
        CaseDistance (const Case& c) :laCase(c),  distance(infranchissable-1) {}
    };

    // Le terrain et Dijkstra on le meme ordre de case ce qui vos nous simplifier grandement la vie
    const Terrain& terrain;
    std::vector<CaseDistance> cases;

    int distanceVoisinMin (CaseDistance& uneCaseDistance)
    {
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

    /// Modification a faire ici pour tenir compte des cases infranchissable / poids des cases
    /// Probleme : comment faire ça bien xD
    void calculedistance (CaseDistance& uneCaseDistance) {
          uneCaseDistance.distance = distanceVoisinMin(uneCaseDistance) + 1;
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
    size_t nextCase(size_t indiceDebut, size_t indiceFin ) {
        ///TODO
    }
    void calculChemin(size_t indiceDebut, size_t indiceFin )
    {
        /// Prendre dans l'autre sens et c'est reglé
    }
    void calculPoidsCases(size_t indiceDebut, size_t indiceFin )
    {
        // vérification
        if ( indiceDebut >= cases.size() || indiceFin >= cases.size() )
        {
            throw std::logic_error("Indice hors tableau dans le calcul de chemin");
        }

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
    Dijkstra(const Terrain& leTerrain) : terrain(leTerrain){
        synchronisationWithTerrain();
    }


};

#endif // DIJKSTRA_HPP
