#ifndef ITERATEUR_FONCTEUR_HPP
#define ITERATEUR_FONCTEUR_HPP


/**
\class FoncteurIterator
\brief Classe permétant d'ajouter une méthode dans le déférancement de l'itérateur
\details Innitalement concus pour itérer sur un conteneur de ref_wrap sans avoir à faire le .get()
*/
template <class T,class U>
class FoncteurIterator
{
    public:
        // on veux itérer sur une conteneur sans avoir a re-coder son comportement, du coup on le garde en
        // attribut et on l'intéroge à chaque opération.
        FoncteurIterator(T a):  iterateur(a){};

        // les méthodes ou on fait rien de particulier
        bool operator!=(FoncteurIterator &i2) const { return iterateur != i2.iterateur; }
        void operator++() { iterateur++; }
        void operator+=(int b) { iterateur += b; }
        decltype(T()-T()) operator-(const FoncteurIterator &i2) const { return iterateur - i2.iterateur; }

        // les méthodes qui utilisent les foncteurs
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
\brief Classe foncteur qui retourne la référence contenu dans le wrapper passé en param
\details La class sert à "dé-wrapper" un wrapper, si vous avez un bon nom je suis preneur.
*/
template<class T>
struct UnWrappe
{
    typedef T value_type;
    T& operator()(std::reference_wrapper<T> refWrap ) { return refWrap.get(); }
};


#endif // ITERATEUR_FONCTEUR_HPP
