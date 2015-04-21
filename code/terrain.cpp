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


Case& Terrain::getCase(size_t indice)
{
    //  comparison of unsigned expression < 0 is always false
    if ( indice >= cases.size() ) {
        throw std::logic_error("Tentative de lire a un indice invalide dans Terrain.cases");
    }
    return cases[indice];
}

Case& Terrain::getCase(Point3 coord)
{
    if ( ! contains(mapPoint3ToIndice,coord) ) {
        throw std::logic_error("Tentative de lire une case dont les coordonnées ne sont pas dans la map de coordonnées");
    }

    return cases[mapPoint3ToIndice[coord]];
}


void Terrain::addCase (Point3 coord)
{
    // l'ajouts d'une case doit se faire sur un case vide :D
    if ( contains(mapPoint3ToIndice,coord) ) {
        // pb de tostring avec ("+coord.get<0>()+","+coord.get<1>()+","+coord.get<2>()+")
        throw std::logic_error ("Ajout de la coordonnee alors que celle ci existe deja");
    }

    // 1 ) la creation de la case dans le vecteur
    cases.emplace_back(std::ref(*this));
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
        size_t indice = mapPoint3ToIndice[coord];
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

void Terrain::test()
{
    #ifndef NDEBUG
        using namespace std;
        Terrain terrain; // constructeur par defaut

        auto erreur = [&](std::string msg){
            cout << "\n Erreur : " << msg << endl;
        };
        auto test = [&] (bool condition, std::string msg)
        {
            if ( ! condition )
            {
                erreur(msg);
            }
        };
        cout << "Debut validation calcul point voisin par defaut " << endl;
        std::vector<Point3> pointsVoisinsTheorique, pointsVoisinsReel ;
        pointsVoisinsTheorique.push_back(Point3(1,0,0));
        pointsVoisinsTheorique.push_back(Point3(0,1,0));
        pointsVoisinsTheorique.push_back(Point3(-1,0,0));
        pointsVoisinsTheorique.push_back(Point3(0,-1,0));
        pointsVoisinsTheorique.push_back(Point3(1,-1,0));
        pointsVoisinsTheorique.push_back(Point3(-1,1,0));
        pointsVoisinsTheorique.push_back(Point3(0,0,1));
        pointsVoisinsTheorique.push_back(Point3(0,0,-1));
        pointsVoisinsReel = terrain.calculeVoisins(Point3(0,0,0));

        test( pointsVoisinsReel.size() == pointsVoisinsTheorique.size(),
              "calcul voisin donne " +  std_fix::to_string(pointsVoisinsReel.size()) + " au lieu de " +  std_fix::to_string(pointsVoisinsTheorique.size()) );

        for (auto& p : pointsVoisinsReel)
        {
            test ( contains(pointsVoisinsTheorique,p) , ""+p+" n'est pas dans les points voisins théoriques" );
        }
        for (auto& p :pointsVoisinsTheorique)
        {
            test ( contains(pointsVoisinsReel,p), ""+p + " n'a pas etait trouvé par la recherche de voisin" );
        }

        cout << "Debut validation add case " << endl;
        terrain.addCase(Point2(0,0));
        terrain.addCase(Point3(1,0,0));
        terrain.addCase(Point3(1,0,1));
        terrain.addCase(Point3(0,0,1));
        terrain.addCase(Point3(1,1,1));
        // on vérifie que les cases sont bien ajouté dans le vec de case
        test (terrain.cases.size() == 5, "la taille du vec de cases est de " + std_fix::to_string(terrain.cases.size()) +" au lieux d'etre de 5");

        // on vérifie l'echec d'un ajout sur une case existante
        bool execptionLevee = false;
        try { terrain.addCase(Point2(0,0)); }
        catch (...) {execptionLevee = true;}
        test (execptionLevee, "le double ajout de (0,0) n'a pas levé d'execption ");

        Case& case00 = terrain.getCase(1);
        test ( case00.voisins.size() == 2 , "La case 00 devrait avoir 2 voisins");

        Case& case101 = terrain.getCase(Point3(1,0,1));
        test ( case101.voisins.size() == 3 , "La case101 devrait avoir 3 voisin");

        Case& case111 = terrain.getCase(Point3(1,1,1));
        test ( case111.voisins.size() == 1 , "La case111 devrait avoir 1 voisin");

        cout << "Un petit test sur la cohérence des deux getCase " <<endl;
        for (auto& paire : terrain.mapPoint3ToIndice )
        {
            auto coord = paire.first;
            int indice = terrain.mapPoint3ToIndice[coord];
            test ( terrain.getCase(indice) == terrain.getCase(coord) , " le getCase indice et coord ne sont pas cohérent "+ std_fix::to_string(indice) + coord );

        }

        /// TODO : test de suppression de case
    #endif
}


