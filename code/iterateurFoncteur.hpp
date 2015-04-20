#ifndef ITERATEUR_FONCTEUR_HPP
#define ITERATEUR_FONCTEUR_HPP


/**
\class FoncteurIterator
\brief Classe permétant d'ajouter une méthode dans le déférancement de l'itérateur
\details Innitalement concus pour itérer sur un conteneur de ref_wrap sans avoir à faire le .get()
*/

// tout ça c'est pour un static assert qui marche pas comme il devrait.
// je garde en attente de l'avis d'un pro :p
template<typename T, typename = void>
struct is_iterator
{
   static constexpr bool value = false;
};

template<typename T>
struct is_iterator<T, typename std::enable_if<
                                                !std::is_same<
                                                        typename std::iterator_traits<T>::value_type, void
                                                        >::value
                                                    >::type
                                            >
{
   static constexpr bool value = true;
};

template <class IteratorTemplate, class FoncteurTemplate>
class FoncteurIterator
{
    static_assert(is_iterator<IteratorTemplate>::value,"Le type T doit etre un itérateur");

    public:
        // on veux itérer sur une conteneur sans avoir a re-coder son comportement, du coup on le garde en
        // attribut et on l'intéroge à chaque opération.
        FoncteurIterator(IteratorTemplate a):  iterateur(a){

        };

        // les méthodes ou on fait rien de particulier
        bool operator!=(FoncteurIterator &i2) const { return iterateur != i2.iterateur; }
        void operator++() { iterateur++; }
        void operator+=(int b) { iterateur += b; }
        decltype(IteratorTemplate()-IteratorTemplate()) operator-(const FoncteurIterator &i2) const { return iterateur - i2.iterateur; }

        // les méthodes qui utilisent les foncteurs
        decltype(FoncteurTemplate()(*(IteratorTemplate())))& operator*() const {
            return FoncteurTemplate()(*iterateur);
        }
        decltype(FoncteurTemplate()(*(IteratorTemplate())))& operator->() {
            return operator*();
        }


    private :
        IteratorTemplate iterateur;
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

// on a besoin de l'opérateur == pour faire des truc comme find sur un vecteur<wrap>
// il faut aussi que T ait ==;
template<class T>
bool operator==(std::reference_wrapper<T> un, std::reference_wrapper<T> deux)
{
    return un.get()==deux.get();
}
#endif // ITERATEUR_FONCTEUR_HPP
