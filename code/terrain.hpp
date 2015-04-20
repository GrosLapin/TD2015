#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <boost/geometry.hpp>
#include <string>
#include "fonctionsConteneur.hpp"

/**
\class Terrain
\brief Le Terrain gere comme il le souhaite les cases. On peut imaginer un terrain classique (plat) ou non a plusieurs étages, rond...
\details Le terrain gere les indices des cases. Si bien qu'il n'y a pas de contraintes sur la géométrie des cases.

*/

namespace bg = boost::geometry ;
/*

Pour pouvoir monter a des gens on garde la version de test avec le terrain ayant une dimention

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


using Point3 = bg::model::point<int,3,bg::cs::cartesian>;
using Point2 = bg::model::point<int,2,bg::cs::cartesian>;

/// Arnaud, si tu veux perdre une heure de ta vie, vire les namespaces et cherche le bug...
// la fonction à pas vraiment de sens en terme de comparaison.
// il faut plus voir ça comme une fonction de hash
namespace boost {
    namespace geometry {
        namespace model {
            inline bool operator < (const Point3& un, const Point3& deux){
                return un.get<0>()*1024+un.get<1>()*256+un.get<2>() < deux.get<0>()*1024+deux.get<1>()*256+deux.get<2>();
            }
        }
    }
}
//template< std::size_t dimention>

class Case;

 inline std::vector<Point3> calculeVoisinsExa (Point3 point) {
    std::vector<Point3> retour;
    int x = point.get<0>();
    int y = point.get<1>();
    int z = point.get<2>();

    // les 6 cases dans le meme plan
    retour.push_back(Point3 (x+1,y,z) );
    retour.push_back(Point3 (x,y+1,z) );
    retour.push_back(Point3 (x-1,y,z) );
    retour.push_back(Point3 (x,y-1,z) );
    retour.push_back(Point3 (x+1,y+1,z) );
    retour.push_back(Point3 (x-1,y-1,z) );

    // les case sur le plan du dessus et du dessou
    retour.push_back(Point3 (x,y,z+1) );
    retour.push_back(Point3 (x,y,z-1) );

    return retour;
}

class Terrain
{
    public :

        Terrain( std::function<std::vector<Point3>(Point3 point)> leCalculDesVoisins = calculeVoisinsExa ) : calculeVoisins(leCalculDesVoisins) {}
        // devrait etre const mais j'arrive pas a l'ecrire
        int getIndice(Case& uneCase);
        Case& getCase(int indice);

        // Le parcourt des cases
        using iterator = std::vector<Case>::iterator;
        inline iterator begin() { return cases.begin(); }
        inline iterator end() { return cases.end(); }

        void addCase (Point3 coord);
        inline void addCase (Point2 coord) { addCase(Point3(coord.get<0>(),coord.get<1>(),0)); }

        void removeCase(Point3 coord);
        inline void removeCase(Point2 coord) { removeCase(Point3(coord.get<0>(),coord.get<1>(),0)); }

    private :
        // il me faut un map pour faire le liens entre une "Point3" et l'indice dans laquelle est stoqué la case
        std::map<Point3,size_t> mapPoint3ToIndice;
        std::vector<Case> cases;

        // l'utilisation d'une fonction nous permet d'avoir la modularité de l'héritage sans la lourdeur de celle-ci
        std::function<std::vector<Point3> (Point3 point)> calculeVoisins;

};



#endif // TERRAIN_HPP
