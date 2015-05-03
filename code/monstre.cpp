#include "monstre.hpp"

/**
\class Monstre

*/

Monstre::Monstre(auto vie_, auto vitesse_) : vie(vie_), vitesse(vitesse_) {}
Monstre::Monstre(auto monstre)
{
    this.Monstre(monstre.getVie, monstre.getVitesse);
}

Monstre::~Monstre()
{

}

inline void Monstre::perdreVie(degats)
{
    vie > degats ? vie -= degats : delete this; // #troll
}

auto getVie() const     { return vie; }
auto getVitesse() const { return vitesse; }
