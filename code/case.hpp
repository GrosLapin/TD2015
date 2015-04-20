#ifndef CASE_HPP
#define CASE_HPP
#include <vector>
#include <functional>
#include <algorithm>

#include "iterateurFoncteur.hpp"
#include "fonctionsConteneur.hpp"

/**
\bug Les cases on comme voisin des references car elle ne gerent pas la mémoire
La mémoire est geré par le terrain qui a un vecteur de case... you see my point ? :/
*/
class Case
{
public :
     public :

    using iterator = FoncteurIterator<std::vector<std::reference_wrapper<Case>>::iterator,UnWrappe<Case>>;
    iterator begin() { return iterator(voisins.begin());}
    iterator end() { return iterator(voisins.end());}

    // si on a pas ça, on peut pas faire de find.
    inline bool operator==(const Case& autre ){
        return this == &autre;
    }

    inline void addVoisin(Case& voisin)
    {
        // vérification d'usage
        if ( voisin == *this ) {
            throw std::logic_error("Une case ne peut pas etre un de ses voisins");
        }
        if ( contains(voisins,std::ref(voisin)) ){
            throw std::logic_error("Ajout d'un voisin deja présent dans la liste des voisins");
        }
        // 1) on reconnait cette case comme un voisin
        voisins.push_back({voisin}) ;
        // 2) le voisin aussi
        voisin.voisins.push_back({*this});
    };



    inline void removeVoisin(Case& voisin)
    {
        // Dans un sens
        auto position = std::find(voisins.begin(),voisins.end(),std::ref(voisin));
        if ( position != voisins.end())
        {
            voisins.erase(position);
        }

        // et dans l'autre
        position = std::find(voisin.voisins.begin(),voisin.voisins.end(),std::ref(*this));
        if ( position != voisin.voisins.end())
        {
            voisin.voisins.erase(position);
        }

    };
    private :
        std::vector<std::reference_wrapper<Case>> voisins;
};


#endif // CASE_HPP
