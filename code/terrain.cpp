#include "terrain.hpp"
#include "case.hpp"

int Terrain::getIndice(Case& uneCase)
{
    if ( ! contains (cases,uneCase) )
    {
        throw std::logic_error("Recherche de l'indice d'une case qui n'est pas dans se terrain");
    }

    return std::find(cases.begin(),cases.end(),uneCase) - cases.begin();
}


Case& Terrain::getCase(int indice)
{
    if (indice < 0  || indice >= cases.size() ) {
        throw std::logic_error("Tentative de lire a un indice invalide dans Terrain.cases");
    }
    return cases[indice];
}


void Terrain::addCase (Point3 coord)
{
    // l'ajouts d'une case doit se faire sur un case vide :D
    if ( contains(mapPoint3ToIndice,coord) ) {
        // pb de tostring avec ("+coord.get<0>()+","+coord.get<1>()+","+coord.get<2>()+")
        throw std::logic_error ("Ajout de la coordonnee alors que celle ci existe deja");
    }

    // 1 ) la creation de la case dans le vecteur
    cases.push_back(Case(std::ref(*this)));
    Case& nouvelleCase = cases.back(); // Danger : ne prendre une ref qu'apres avoir modifier la liste

    // 2) le liens entre les coordonnée et la case
    mapPoint3ToIndice[coord] = cases.size()-1;

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
            nouvelleCase.addVoisin(mapPoint3ToIndice[point]);
        }
    }
};

void Terrain::removeCase(Point3 coord)
{
    // 1 trouver la case
    if ( contains(mapPoint3ToIndice,coord) )
    {
        // 1) chopé une ref sur la case a supprimer
        int indice = mapPoint3ToIndice[coord];
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
                aDelete.removeVoisin(mapPoint3ToIndice[point]);
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

    }

}


