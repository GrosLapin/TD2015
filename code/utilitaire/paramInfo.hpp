#pragma once
#ifndef param_info_hpp
#define param_info_hpp

#include <iostream>
#include <tuple>


template <class... T>
class TD;

template <class... T>
class ERREUR;

template <class T>
struct informationParam{
    struct LeParamNestPasUneFonction {};
    ERREUR<LeParamNestPasUneFonction> erreur;
};

// operateur () PAS !!! const
template <typename ClassType, typename ReturnType, typename... Args>
struct informationParam<ReturnType(ClassType::*)(Args...) >
{
    constexpr static size_t arity = sizeof...(Args);
    using  result_type = ReturnType;
    // je suis obligué de passer par une struct, si non je sais pas faire le static assert sur le using
    template <size_t i>
    struct arg
    {
        static_assert ((i < arity ), "La fonction à moins de param que ce que vous demandez" );
        using leType =  typename std::tuple_element<i, std::tuple<Args...>>::type ;
    };
    template <size_t i> using type = typename arg<i>::leType;
};

// operateur () const
template <typename ClassType, typename ReturnType, typename... Args>
struct informationParam<ReturnType(ClassType::*)(Args...) const>
{
    constexpr static size_t arity = sizeof...(Args);
    using  result_type = ReturnType;
    // je suis obligué de passer par une struct, si non je sais pas faire le static assert sur le using
    template <size_t i>
    struct arg
    {
        static_assert ((i < arity ), "La fonction à moins de param que ce que vous demandez" );
        using leType =  typename std::tuple_element<i, std::tuple<Args...>>::type ;
    };
    template <size_t i> using type = typename arg<i>::leType;
};

// pointeur de fonction
template < typename ReturnType, typename... Args>
struct informationParam<ReturnType(*)(Args...)>
{
    constexpr static size_t arity = sizeof...(Args);
    using  result_type = ReturnType;
    // je suis obligué de passer par une struct, si non je sais pas faire le static assert sur le using
    template <size_t i>
    struct arg
    {
        static_assert ((i < arity ), "La fonction à moins de param que ce que vous demandez" );
        using leType =  typename std::tuple_element<i, std::tuple<Args...>>::type ;
    };
    template <size_t i> using type = typename arg<i>::leType;
};


template    <
                class T,
                class U = typename std::enable_if < ! std::is_class<T>::value >::type
            >
informationParam<T> getInformationParam (T t);/*
{
    // normalement j'ai pas besoin (ni envie d'avoir un corps de fonction mais ça sert pour les debugs
    std::cout << "fonction" << std::endl;
    return informationParam<T>();
}*/

template <class T>
informationParam<decltype(&T::operator())> getInformationParam (T t);/*
{
    // normalement j'ai pas besoin (ni envie d'avoir un corps de fonction mais ça sert pour les debugs
    std::cout << "class" << std::endl;

    return informationParam<decltype(&T::operator())>();
}
*/


template<class T>
constexpr size_t nbParam(T fonction)
{
    return decltype(getInformationParam(fonction))::arity;
}

template<size_t nb,class T>
constexpr typename decltype(getInformationParam(std::declval<T>()))::template type<nb> typeParam(T fonction );


template<class T>
constexpr typename decltype(getInformationParam(std::declval<T>()))::result_type typeRetour(T fonction );




#endif

