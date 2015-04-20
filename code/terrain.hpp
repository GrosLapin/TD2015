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

/// Arnaud, si tu veux perdre une heure de ta vie, vire l'ouverture du namespace std et cherche le bug...
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

class Terrain
{


    public :
        //using Coordonnee = bg::model::point<int,dimention,bg::cs::cartesian>;


        // Le parcourt des cases
        using iterator = std::vector<Case>::iterator;
        inline iterator begin() { return cases.begin(); }
        inline iterator end() { return cases.end(); }

        // l'ajout et la suppression de case
        inline void addCase (Point3 coord) {
            // displayRecursif<dimention>(coord);

            // l'ajouts d'une case doit se faire sur un case vide :D
            if ( contains(mapPoint3ToIndice,coord) ) {
                // pb de tostring avec ("+coord.get<0>()+","+coord.get<1>()+","+coord.get<2>()+")
                throw std::logic_error ("Ajout de la coordonnee alors que celle ci existe deja");
            }

            // 1 ) la creation de la case dans le vecteur
            cases.push_back(Case());
            Case& nouvelleCase = cases.back(); // Danger : ne prendre une ref qu'apres avoir modifier la liste
            int indice = cases.size()-1;
            // 2) le liens entre les coordonnée et la case
            mapPoint3ToIndice[coord] = indice;

            // 3) faire les cases voisines
            std::vector<Point3> voisinsPotentiels = calculeVoisins (coord);
            // pour tous les indices possible dans ce type de grille (carre, exa...)
            for (auto const point : voisinsPotentiels )
            {
                // on regarde si le terrain connait cette coordonnee
                if (contains(mapPoint3ToIndice,point))
                {
                    // si c'est le cas, on ajoute à la case qu'on vient de créer son voisin.
                    // le voisin se trouve dans la lsite de case "cases" à l'indice contenu dans la map coord => indice
                  //  nouvelleCase.addVoisin(cases[mapPoint3ToIndice[point]);
                }
            }
        };
        inline void addCase (Point2 coord) { addCase(Point3(coord.get<0>(),coord.get<1>(),0)); }

        inline void removeCase(Point3 coord) {
          /*  // 1 trouver la case
            if ( contains(mapPoint3ToIndice,coord) )
            {
                // 1) chopé une ref sur la case a supprimer
                int indice = mapPoint3ToIndice[point];
                Case& aDelete = cases[indice];

                // 2) trouver tout ces voisins dans la grille
                std::vector<Point3> voisinsPotentiels = calculeVoisins (coord);
                for (auto const point : voisinsPotentiels )
                {
                    // on regarde si le terrain connait cette coordonnee
                    if (contains(mapPoint3ToIndice,point))
                    {
                        // si c'est le cas, on ajoute à la case qu'on vient de créer son voisin.
                        // le voisin se trouve dans la lsite de case "cases" à l'indice contenu dans la map coord => indice
                        aDelete.removeVoisin(cases[mapPoint3ToIndice[point]);
                    }
                }

                // 3) gerer la suppression
                cases.erase(cases.begin()+indice);
                mapPoint3ToIndice.erase(coord);

                //4) maintenant toutes les paire qui pointaient sur une case apres elle dans le tableau sont plus a jours
                for (auto& paire : mapPoint3ToIndice )
                {
                    // le cas == ne doit pas se produire car on a supprimer cette case dans le point 3
                    if (paire.second >= indice )
                    {
                        paire.second--;
                    }
                }

            }*/

        }
        inline void removeCase(Point2 coord) { removeCase(Point3(coord.get<0>(),coord.get<1>(),0)); }
        // le terrain à la gestion de la mémoire des case
        std::vector<Case> cases;
        // il me faut un map pour faire le liens entre une "Point3" et l'indice dans laquelle est stoqué la case
        std::map<Point3,size_t> mapPoint3ToIndice;
    private :

        /// TODO  détacher cette méthode de la classe pour qu'on puisse faire un terrain a case exagonal ou carré simplement
        inline std::vector<Point3> calculeVoisins (Point3 point) {
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



};



#endif // TERRAIN_HPP
