#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <boost/geometry.hpp>

/**
\class Terrain
\brief Le Terrain gere comme il le souhaite les cases. On peut imaginer un terrain classique (plat) ou non a plusieurs étages, rond...
\details Le terrain gere les indices des cases. Si bien qu'il n'y a pas de contraintes sur la géométrie des cases.

*/

/*

Pour pouvoir monter a des gens on garde la version de test avec le terrain ayant une dimention
namespace bg = boost::geometry ;
template <std::size_t recursion >
void displayRecursif (bg::model::point<int,2,bg::cs::cartesian> point)
{
    std::cout << point.get<recursion-1>() <<std::endl;
    displayRecursif<recursion-1>(point);
}
template <>
void displayRecursif<0> (bg::model::point<int,2,bg::cs::cartesian> point)
{
    std::cout << "fin :)" <<std::endl;
}
*/

//template< std::size_t dimention>
class Terrain
{


    public :
        //using Coordonnee = bg::model::point<int,dimention,bg::cs::cartesian>;
        using Coordonnee = bg::model::point<int,dimention,bg::cs::cartesian>;

        // Le parcourt des cases
        using iterator = std::vector<Case>::iterator;
        inline iterator begin() { return cases.begin(); }
        inline iterator end() { return cases.end(); }

        // l'ajout de case
        inline void addCase (bg::model::point<int,dimention,bg::cs::cartesian> coord) {
            // displayRecursif<dimention>(coord);
            // l'ajouts d'une case doit se faire sur un case vide :D

            // 1 ) la creation de la case dans le vecteur
            cases.push_back(Case());
            int indice = cases.size()-1;
            // 2) le liens entre les coordonnée et la case
           // mapCoordonneeToIndice[coo]
        };
        template <class InputIterator>
        inline void addCase (InputIterator debut, InputIterator fin)
        {
            for (InputIterator it = debut ; it< fin; it++)
            {
                addCase(*it);
            }
        };


// le terrain à la gestion de la mémoire des case
        std::vector<Case> cases;
        // il me faut un map pour faire le liens entre une "coordonée" et l'indice dans laquelle est stoqué la case
       // std::map<Coordonnee,size_t> mapCoordonneeToIndice;
    private :





};

#endif // TERRAIN_HPP
