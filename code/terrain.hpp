#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <boost/geometry.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include "fonctionsConteneur.hpp"

/**
\class Terrain
\brief Le Terrain gere comme il le souhaite les cases. On peut imaginer un terrain classique (plat) ou non a plusieurs étages, rond...
\details Le terrain gere les indices des cases. Si bien qu'il n'y a pas de contraintes sur la géométrie des cases.

*/

namespace bg = boost::geometry ;
using Point3 = bg::model::point<int,3,bg::cs::cartesian>;
using Point2 = bg::model::point<int,2,bg::cs::cartesian>;

/// Patch du fait que mon compilo soit a chier, à deplacer
namespace std_fix {
    template <class T>
    std::string to_string (const T& t)
    {
         std::ostringstream stream;
         stream << t;
         return std::string (stream.str());
    }
}
/// Arnaud, si tu veux perdre une heure de ta vie, vire les namespaces et cherche le bug...
namespace boost {
    namespace geometry {
        namespace model {
            /// DANGER : mieux a faire ?
            // la fonction à pas vraiment de sens en terme de comparaison.
            // il faut plus voir ça comme une fonction de hash
            inline bool operator < (const Point3& un, const Point3& deux){
                return un.get<0>()*1000000+
                       un.get<1>()*1000+
                       un.get<2>()      <
                       deux.get<0>()*1000000+
                       deux.get<1>()*1000+
                       deux.get<2>();
            }

            inline std::string to_string (const Point3& point) {
                return  "[x=" + std_fix::to_string(point.get<0>()) + " y=" +std_fix::to_string(point.get<1>()) +  " z=" + std_fix::to_string(point.get<2>())+ "]";
            }
            inline std::ostream& operator << ( std::ostream& flux , const Point3& point){
                flux << to_string (point) ;
                return flux;
            }
            inline std::string operator+ (const std::string s,const Point3& point)
            {
                return std::string (s+to_string(point));
            }

            inline bool operator == (const Point3& un, const Point3& deux) {
                return (un.get<0>() == deux.get<0>() ) &&(un.get<1>() == deux.get<1>() ) &&(un.get<2>() == deux.get<2>() ) ;
            }
        }
    }
}

inline Point3 point3to2 (Point2 p2) { return Point3(p2.get<0>(),p2.get<1>(),0); }
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
    retour.push_back(Point3 (x-1,y+1,z) );
    retour.push_back(Point3 (x+1,y-1,z) );

    // les case sur le plan du dessus et du dessou
    retour.push_back(Point3 (x,y,z+1) );
    retour.push_back(Point3 (x,y,z-1) );

    return retour;
}

class Terrain
{
    public :

        bool operator == (const Terrain& other ) const { return &other == this; };
        bool operator != (const Terrain& other ) const { return !operator==(other); };
        Terrain( std::function<std::vector<Point3>(Point3 point)> leCalculDesVoisins = calculeVoisinsExa ) : calculeVoisins(leCalculDesVoisins) {}


        int getIndice(const Case& uneCase) const ;
        // devrait etre const mais j'arrive pas a l'ecrire
        /// Note : en fait je pense aps qu'il faut que ça soit const, mais je pense qu'on devrait
        /// ecrire deux vertion de chaques
        Case& getCase (size_t indice) ;
        Case& getCase (Point3 coord) ;
        inline  Case& getCase(Point2 coord)  { return getCase(point3to2(coord)); };
        inline  Case& getCase(int x, int y)  { return getCase(Point3(x,y,0)); };
        inline  Case& getCase(int x, int y, int z)  { return getCase(Point3(x,y,z)); };

        // Le parcourt des cases
        using iterator = std::vector<Case>::iterator;
        using const_iterator = std::vector<Case>::const_iterator;

        inline iterator begin() { return cases.begin(); }
        inline const_iterator begin() const { return cases.begin(); }

        inline iterator end() { return cases.end(); }
        inline const_iterator end() const{ return cases.end(); }

        void addCase (Point3 coord);
        inline void addCase (int x, int y, int z = 0) {addCase(Point3(x,y,z)); }
        inline void addCase (Point2 coord) { addCase(point3to2(coord)); }

        void removeCase(Point3 coord);
        inline void removeCase(Point2 coord) { removeCase(point3to2(coord)); }

        void static test();
    private :
        // il me faut un map pour faire le liens entre une "Point3" et l'indice dans laquelle est stoqué la case
        std::map<Point3,size_t> mapPoint3ToIndice;
        std::vector<Case> cases;

        // l'utilisation d'une fonction nous permet d'avoir la modularité de l'héritage sans la lourdeur de celle-ci
        std::function<std::vector<Point3> (Point3 point)> calculeVoisins;

};



#endif // TERRAIN_HPP
