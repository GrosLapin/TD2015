#pragma once
#include "../utilitaire/iterateurFoncteur.hpp"

void exempleIterateurFoncteur ()
{
    using namespace std;
    // fonction d'affichage
    auto affichage = [](const auto& conteneur)
    {
        for (const auto& elem : conteneur ) {
            cout << elem << " ";
        }
        cout<< endl;
    };
    auto affichageFi = [](auto begin, auto end)
    {
         for ( ; begin != end ; ++begin )
        {
            cout << *begin << " ";
        }
        cout<< endl;
    };


    // exemple utilisation iterateurFoncteur
    vector<int> vec ({1,2,3,5,9,52,12563});
    // affichage classique
    affichage (vec);
    ///utilisation d'un iterateur foncteur
    {
        class testFoncteur {
        public :
            double operator() (int a)  { return a/2.0;}
        };

        cout << "On affiche le meme vecteur mais on passe un foncteur qui divise par deux a l'affichage" <<endl;
        FoncteurIterator<std::vector<int>::iterator, testFoncteur> vecBegin(vec.begin()), vecEnd(vec.end());
        affichageFi(vecBegin,vecEnd);
    }


    {
        cout << "On affiche le meme vecteur mais on passe une lambda qui divise par deux a l'affichage" <<endl;
        auto divise2 = [] (const int& a) -> double { return a/2.0 ; };
        FoncteurIterator<std::vector<int>::iterator, decltype(divise2) > vecBegin(vec.begin(),divise2), vecEnd(vec.end(),divise2);
        affichageFi(vecBegin,vecEnd);
    }

    {
        cout << endl << "Bien que ça soit pas pensé pour ça, la fonction peut modifier le contenue:" <<endl;
        cout << "On modifie le vecteur via une lambda qui multiplie par 4 le contenu" <<endl;
        auto fois4 = [](int& a) { a*=4; };
        FoncteurIterator<std::vector<int>::iterator, decltype(fois4) > vecBegin(vec.begin(),fois4), vecEnd(vec.end(),fois4);
        for ( ; vecBegin != vecEnd ; ++vecBegin )
        {
             (*vecBegin);
        }
        cout << "Et on affiche le vecteur" <<endl;
        affichage (vec);
    }

    /// cas d'utilisation dans la pratique
    // Le code est dans iterateurFoncteur
    /*template<class T>
    struct UnWrappe
    {
        typedef T value_type;
        T& operator()(std::reference_wrapper<T> refWrap ) { return refWrap.get(); }
    };
    */

    class classNeGerantPasLaMemoire {
        public :
            classNeGerantPasLaMemoire(std::vector<int>& vec){
                for (auto& elem : vec )
                {
                    vecRef.emplace_back(std::ref(elem));
                }
            }

            using iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::iterator,UnWrappe<int>>;
            using const_iterator = FoncteurIterator<std::vector<std::reference_wrapper<int>>::const_iterator,UnWrappe<int>>;


            inline iterator begin()             { return iterator(vecRef.begin()); }
            inline iterator end()               { return iterator(vecRef.end());}
            inline const_iterator begin() const { return const_iterator(vecRef.begin());  }
            inline const_iterator end() const   { return const_iterator(vecRef.end()); }
        private :
            std::vector<std::reference_wrapper<int>> vecRef;
    };

    cout << endl << "Création d'une classe ayant des references sur le vecteur" << endl << " (attention de ne pas invalider les references)" <<endl;
    classNeGerantPasLaMemoire exempleClass(vec);
    for (auto& elem : exempleClass )
    {
        cout << elem << " ";
    }
    cout << endl;

    cout << "Modification via la class (x+6)/3." <<endl;
    for (auto& elem : exempleClass )
    {
        elem = (elem +6)/3.;
    }

    cout << "Re affichage" <<endl;
    for (auto& elem : exempleClass )
    {
        cout << elem << " ";
    }
    cout << endl;

}
