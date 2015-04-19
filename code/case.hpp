#ifndef CASE_HPP
#define CASE_HPP
#include <vector>
#include <functional>
#include <algorithm>

#include "iterateurFoncteur.hpp"

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

    inline void addVoisin(Case& voisin){ voisins.push_back({voisin}) ;};
    inline void removeVoisin(Case& voisin)
    {
        auto position = std::find(voisins.begin(),voisins.end(),std::ref(voisin));
        if ( position != voisins.end())
        {
            voisins.erase(position);
        }
    };
    private :
        std::vector<std::reference_wrapper<Case>> voisins;
};


#endif // CASE_HPP
