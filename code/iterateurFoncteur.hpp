#ifndef ITERATEUR_FONCTEUR_HPP
#define ITERATEUR_FONCTEUR_HPP


/**
\class FoncteurIterator
\brief Classe perm�tant d'ajouter une m�thode dans le d�f�rancement de l'it�rateur
\details Innitalement concus pour it�rer sur un conteneur de ref_wrap sans avoir � faire le .get()
*/
template <class T,class U>
class FoncteurIterator
{
    public:
        // on veux it�rer sur une conteneur sans avoir a re-coder son comportement, du coup on le garde en
        // attribut et on l'int�roge � chaque op�ration.
        FoncteurIterator(T a):  iterateur(a){};

        // les m�thodes ou on fait rien de particulier
        bool operator!=(FoncteurIterator &i2) const { return iterateur != i2.iterateur; }
        void operator++() { iterateur++; }
        void operator+=(int b) { iterateur += b; }
        decltype(T()-T()) operator-(const FoncteurIterator &i2) const { return iterateur - i2.iterateur; }

        // les m�thodes qui utilisent les foncteurs
        typename U::value_type& operator*() const {
            return iterateur->get();
        }
        typename U::value_type& operator->() {
            return operator*();
        }


    private :
        T iterateur;
};

/**
\class UnWrappe
\brief Classe foncteur qui retourne la r�f�rence contenu dans le wrapper pass� en param
\details La class sert � "d�-wrapper" un wrapper, si vous avez un bon nom je suis preneur.
*/
template<class T>
struct UnWrappe
{
    typedef T value_type;
    T& operator()(std::reference_wrapper<T> refWrap ) { return refWrap.get(); }
};


#endif // ITERATEUR_FONCTEUR_HPP
