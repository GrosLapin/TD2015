#include "tourelle.hpp"

Tourelle::Tourelle(auto degatsAttaque_, auto &case_) : degatsAttauque(degatsAttaque_), saCase(case_) {}

Tourelle::Tourelle(auto tour, auto &case_)
{
    this.Tourelle(tour.getDegatsAttauqe, case_)
}

auto getDegatsAttaque() const { return degatsAttaque; }
auto& getCase() { return saCase; }
