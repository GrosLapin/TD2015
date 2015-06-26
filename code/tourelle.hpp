#ifndef TOURELLE_HPP_INCLUDED
#define TOURELLE_HPP_INCLUDED

#include "case.hpp"

class Tourelle
{
    public :
    Tourelle(size_t degatsAttaque_, int case_) : degatsAttaque(degatsAttaque_), saCase(case_) {}
    Tourelle(const Tourelle& tour) : degatsAttaque(tour.degatsAttaque),saCase(tour.saCase) {}

    size_t getDegatsAttaque() const { return degatsAttaque; }
    int getCase(){ return saCase; }

    private :
    size_t degatsAttaque;
    int saCase;
};

#endif // TOURELLE_HPP_INCLUDED
