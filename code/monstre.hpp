#ifndef MONSTRE_HPP_INCLUDED
#define MONSTRE_HPP_INCLUDED

/**
\class Monstre

*/

class Monstre
{
    public :

    Monstre(auto vie_, auto vitesse_);
    Monstre(auto monstre);
    ~Monstre();

    inline void perdreVie(const auto degats);

    auto getVie() const;
    auto getVitesse() const;

    private :

    size_t vie;
    size_t vitesse;
};

#endif // MONSTRE_HPP_INCLUDED
