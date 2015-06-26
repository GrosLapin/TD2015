#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <map>
#include <functional>
#include <limits>

#include "terrain.hpp"
#include "case.hpp"
#include "fonctionTest/test.hpp"
#include "illegalArgumentError.hpp"

// Version vraiment pas modulable :D
/// Il faut integer indice debut(ou actuel) et indice fin dans la classe.
class Dijkstra{
 public :

    bool operator == (const Dijkstra& other ) const { return &other == this; };
    bool operator != (const Dijkstra& other ) const { return !operator==(other); };


    size_t indiceProchaineCase(size_t indiceDebut, size_t indiceFin ) {
        if (aVerifier)
        {
            using namespace std;
            synchronisationWithTerrain();
            calculPoidsCases(indiceDebut,indiceFin);
            calculChemin(indiceDebut,indiceFin);
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

    Dijkstra(Terrain& leTerrain) : terrain(leTerrain), aVerifier(true){
        terrain.addDijkstra(*this);
    }

    Dijkstra(const Dijkstra& dij) : terrain(dij.terrain),
                                    aVerifier(dij.aVerifier),
                                    cases(dij.cases.begin(), dij.cases.end()),
                                    indiceChemin(dij.indiceChemin.begin(), dij.indiceChemin.end())
    {

        terrain.addDijkstra(*this);
    }


    virtual ~Dijkstra() {
        terrain.removeDijkstra(*this);
    }


    ///Version naive, on recalcul tout.
    void addCase(const Case& uneCase) { aVerifier = true; }
    void removeCase(const Case& uneCase) { aVerifier = true; }

    private :
    friend class TestClass;
    static const int infranchissable = std::numeric_limits<int>::max();
    static const int notVisited = std::numeric_limits<int>::max()-1;

    // on a besoin de garder le distance de chaque case à l'origine
    struct CaseDistance {
        const Case& laCase;
        int distance;
        CaseDistance (const Case& c) :laCase(c),  distance(notVisited) {}
    };

    // Le terrain et Dijkstra on le meme ordre de case ce qui va nous simplifier grandement la vie
    Terrain& terrain;
    bool aVerifier;
    std::vector<CaseDistance> cases;
    std::vector<std::size_t> indiceChemin; // indiceChemin.front() == indice de la case ou on souhaite aller


    // retourne la distance la plus petites parmis les distances de ces voisins
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

    // calcul l'indice de la case suivante, en suposant que la case actuelle a déja le bon indice.
    // ce qui veut dire qu'on a juste a chercher la case ayant le distance la plus petite parmis les distance plus grand que celle
    // de cette case
    size_t indiceCaseSuivanteDansChemin(CaseDistance& uneCaseDistance)
    {
        if ( ! uneCaseDistance.laCase.haveVoisins()) {
            throw std::logic_error("indiceCaseSuivanteDansChemin : Recherche d'un voisin sur une cases sans voisin: "
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
            throw IllegalArgumentError("Indice hors tableau dans le calcul de chemin");
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


};

#endif // DIJKSTRA_HPP
