#ifndef TOURELLE_HPP_INCLUDED
#define TOURELLE_HPP_INCLUDED

#include "case.hpp"

class Tourelle
{
    public :
    Tourelle(auto degatsAttaque_, auto case_);
    Tourelle(auto tour, auto case_);

    auto getDegatsAttaque() const;
    auto& getCase();

    private :
    size_t degatsAttaque;
    Case& saCase;
};

#endif // TOURELLE_HPP_INCLUDED
