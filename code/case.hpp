#ifndef CASE_HPP
#define CASE_HPP
#include <vector>
#include <functional>
#include <algorithm>

#include "iterateurFoncteur.hpp"
#include "fonctionsConteneur.hpp"
#include "terrain.hpp"
/**
\bug Ca serait bien puisque la case est li� au terrain qu'elle connaisse ses coordonn�e ...
*/
class Case
{
public :

    public :

    /// Je suis pas sur de moi, mais j'ai l'impression qu'autoriser la copie peut nous mettre dedans
        Case ( Case && quiVaMourir) : refTerrain(quiVaMourir.refTerrain){
            voisins = std::move(quiVaMourir.voisins);
        }
        Case & operator= ( Case && quiVaMourir ) {
            refTerrain = quiVaMourir.refTerrain;
            voisins = std::move(quiVaMourir.voisins);
            return *this;
        }
        Case(const Case&) = delete;
        Case& operator=(const Case&) = delete;
    /// fin pas sur

    friend void Terrain::test() ;
    Case(Terrain& unTerrain) : refTerrain(unTerrain) {}


    // si on a pas �a, on peut pas faire de find.
    inline bool operator==(const Case& autre ){
        return this == &autre;
    }


    inline void addVoisin(Case& voisin)
    {
        // On passe la main � la fonction qui prend un int
        int indice = refTerrain.get().getIndice(voisin);
        addVoisin(indice);
    };
    inline void addVoisin(size_t indice)
    {
        size_t notreIndice = refTerrain.get().getIndice(*this);

        // v�rification d'usage
        if ( indice == notreIndice ) {
            throw std::logic_error("Une case ne peut pas etre un de ses voisins");
        }

        if ( contains(voisins,indice)) {
            throw std::logic_error("Ajout d'un voisin deja pr�sent dans la liste des voisins");
        }

        // 1) on reconnait cette case comme un voisin
        voisins.push_back(indice) ;
        // 2) le voisin aussi
        Case& voisin =refTerrain.get().getCase(indice);
        voisin.voisins.push_back(notreIndice);
    }

    inline void removeVoisin(Case& voisin)
    {
        // On passe la main � la fonction qui prend un int
        size_t indice = refTerrain.get().getIndice(voisin);
        removeVoisin(indice);
    }
    inline void removeVoisin(size_t indice)
    {
        // Dans un sens
        auto position = std::find(voisins.begin(),voisins.end(),indice);
        if ( position != voisins.end())
        {
            voisins.erase(position);
        }

        // et dans l'autre
        size_t notreIndice = refTerrain.get().getIndice(*this);
        Case& voisin = refTerrain.get().getCase(indice);

        position = std::find(voisin.voisins.begin(),voisin.voisins.end(),notreIndice);
        if ( position != voisin.voisins.end())
        {
            voisin.voisins.erase(position);
        }

    };

    /// TODO : reflechir si on veut iterer sur les indices ou sur les cases
    // using iterator = FoncteurIterator<std::vector<std::reference_wrapper<Case>>::iterator,indiceToCase>;
     using iterator =  std::vector<std::size_t>::iterator;
    iterator begin() { return voisins.begin();}
    iterator end() { return voisins.end();}

    private :
        std::vector<std::size_t> voisins;
        std::reference_wrapper<Terrain> refTerrain;
};


#endif // CASE_HPP
