#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <map>
#include <functional>
#include <limits>

#include "terrain.hpp"

// Version vraiment pas modulable :D

class Dijkstra{


    static const int infranchissable = std::numeric_limits<int>::max();
    struct CasePoids {
        const Case& laCase;
        int poids;
        CasePoids (const Case& c) :laCase(c),  poids(infranchissable-1) {}
    };

    const Terrain& terrain;
    std::vector<CasePoids> cases;

    inline void miseAjourCases()
    {
        cases.clear();
        for (const Case& c : terrain)
        {
            cases.push_back(CasePoids(c));
        }
    }
    public :
    void calculChemin(size_t indiceDebut, size_t indiceFin )
    {
        // vérification
        if ( indiceDebut >= cases.size() || indiceFin >= cases.size() )
        {
            throw std::logic_error("Indice hors tableau dans le calcul de chemin");
        }

        // la case du debut vaut 0
        CasePoids& debut = cases[indiceDebut];
        debut.poids = 0 ;

        std::vector<size_t> indiceAVisiter (debut.laCase.begin(), debut.laCase.end());
    }
    Dijkstra(const Terrain& leTerrain) : terrain(leTerrain){

        // on recopi
    }
/*
    struct CasePoint {
        Case& laCase;
        std::vector<CasePoint> voisin;

        size_t point;
        CasePoint(Case& uneCase) : laCase(uneCase) , point(0) {
            mapIdRefCaseConcepte [getId(laCase)] = std::ref(laCase);

            // je cr
            for (auto& voisin : laCase){
                voisin.emplace_back(voisin)
            }
        }*/
};
/*
// il faudra surcharger cette methode
template <class T, class Retour = std::reference_wrapper<T>>
Retour getId(T& uneRef) { return std::ref(uneRef) ;  }
// par exemple avec un truc du genre
struct MaCase {
    size_t getIndice() { static size_t indice =0 ; return indice++ ;};
};
template <>
size_t getId<MaCase>(MaCase& uneRef) { return uneRef.getIndice(); }

template <class CaseConcepte, class CoordConcepte>
class Dijkstra{

    using TypeIdentifiant = decltype(getId(std::declval<CaseConcepte>()) );

    // La je fais un truc generique avec une map (pour que ça soit simple au debut pour moi)
    // a regarder si un version spécialisé pour MES Cases serais pas plus performant
    std::map<TypeIdentifiant,std::reference_wrapper<CaseConcepte>> mapIdRefCaseConcepte;


    struct CasePoint {
        CaseConcepte& laCase;
        std::vector<CasePoint> voisin;

        size_t point;
        CasePoint(CaseConcepte& uneCase) : laCase(uneCase) , point(0) {
            mapIdRefCaseConcepte [getId(laCase)] = std::ref(laCase);

            // je cr
            for (auto& voisin : laCase){
                voisin.emplace_back(voisin)
            }
        }

        CasePoint(CaseConcepte& uneCase) : laCase(uneCase) , point(0) {
            mapIdRefCaseConcepte [getId(laCase)] = std::ref(laCase);
        }
    };
    bool invalide;

    // a reflechir
    CaseConcepte& debut, fin;

    public :
    Dijkstra (CaseConcepte& leDebut,CaseConcepte& laFin) : debut(leDebut), fin(laFin) , invalide(false) {
        calculChemin();
    }

    void calculChemin()
    {
        std::vector<CasePoint> chemin;
        chemin.push_back({debut});

        int distance = 1;
    }

};
*/
#endif // DIJKSTRA_HPP
