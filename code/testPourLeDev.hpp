#pragma once


template<class... T>
class affichageTypeParErreurCompilateur;


template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())>
{};
// For generic types, directly use the result of the signature of its 'operator()'

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
// we specialize for pointers to member function
{
    enum { arity = sizeof...(Args) };
    // arity is the number of arguments.


    affichageTypeParErreurCompilateur<ClassType,ReturnType,Args...> d;
    typedef ReturnType result_type;

    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
    };
};




template <class IteratorTemplate, class FoncteurTemplate>
class testDeduction
{
    static_assert(is_iterator<IteratorTemplate>::value,"Le type T doit etre un itérateur");

     private :
        using typeDeRetour = decltype(std::declval<FoncteurTemplate>()(*(IteratorTemplate())));
        using typeDuParam  = typename IteratorTemplate::value_type;

        IteratorTemplate iterateur;
        std::function<typeDeRetour (typeDuParam ) > foncteur;

    public:

};

