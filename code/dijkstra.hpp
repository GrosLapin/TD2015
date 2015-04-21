#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

/// reflechir a comment on a les cases via les coordonn�e
///             OU
/// comment on fait si les cases& s'invalide
/// Note : on devrait demander � la case combien elle "pese", a voir plus tard


template <class CaseConcepte, class CoordConcepte>
class Dijkstra{

    // y a moyen de faire un truc int�ligent qui me fait ma num�rotation direcement :D
    struct CasePoint {
        CaseConcepte& laCase;
        size_t point;
        CasePoint(CaseConcepte& uneCase) : laCase(uneCase) , point(0) {}
        CasePoint(CaseConcepte& uneCase, size_t nombre) : laCase(uneCase) , point(nombre) {}
    };
    bool invalide;

    // a reflechir
    CaseConcepte& debut, fin;

    public :
    Dijkstra (CaseConcepte& leDebut,CaseConcepte& laFin) : debut(leDebut), fin(laFin) , invalide(false) {
        calculChemin();
    }

    void calculChemin()
    {
        std::vector<CasePoint> chemin;
        chemin.push_back({debut});

        int distance = 1;
    }

};
#endif // DIJKSTRA_HPP
