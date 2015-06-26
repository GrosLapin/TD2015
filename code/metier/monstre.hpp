#ifndef MONSTRE_HPP_INCLUDED
#define MONSTRE_HPP_INCLUDED

/**
\class Monstre

*/
#include<iostream>
class Monstre
{
    public :
        Monstre(std::size_t vie_, std::size_t vitesse_) : vie(vie_), vitesse(vitesse_) {}
        Monstre(const Monstre& monstre) : vie(monstre.vie), vitesse(monstre.vitesse) {}

        inline void perdreVie(const std::size_t degats)
        {
            if ( vie < degats )
            {
                delete this;
            }
            else
            {
                vie -= degats;
            }
        }

        std::size_t getVie() const { return vie; }
        std::size_t getVitesse() const{ return vitesse; }

    private :
        std::size_t vie;
        std::size_t vitesse;
};

#endif // MONSTRE_HPP_INCLUDED
