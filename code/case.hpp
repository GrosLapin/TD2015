#ifndef CASE_HPP
#define CASE_HPP
#include <vector>
#include <functional>

#include "iterateurFoncteur.hpp"

class Case
{
public :
     public :

    using iterator = FoncteurIterator<std::vector<std::reference_wrapper<Case>>::iterator,UnWrappe<Case>>;
    iterator begin() { return iterator(voisins.begin());}
    iterator end() { return iterator(voisins.end());}

    void addVoisin(Case& voisin){ voisins.push_back({voisin}) ;};

    private :
        std::vector<std::reference_wrapper<Case>> voisins;
};
#endif // CASE_HPP
