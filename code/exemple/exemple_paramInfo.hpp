#pragma once

#include <iostream>
#include <string>
int foo (double i, int a) { return 42;}

class foncteur
{
    public :
        int operator() (int,int,std::string) ;
};

void exempleParamInfo()
{
    using namespace std;
    cout << endl << "Debut de exempleParamInfo" << endl;
    auto lambda = [](int i) { return long(i*10); };


   foncteur f;


   assert ( nbParam(f) == nbParam<foncteur>() );
   assert ( nbParam(foo) == nbParam<decltype(foo)>() );
   assert ( nbParam(lambda) == nbParam<decltype(lambda)>() );

    static_assert( std::is_same<decltype(typeParam<0>(foo)),decltype(typeParam<0,decltype(foo)>())>::value, "erreur ");
    static_assert( std::is_same<decltype(typeParam<0>(f)),decltype(typeParam<0,decltype(f)>())>::value, "erreur ");
    static_assert( std::is_same<decltype(typeParam<0>(lambda)),decltype(typeParam<0,decltype(lambda)>())>::value, "erreur ");


    static_assert( std::is_same<decltype(typeRetour(foo)),decltype(typeRetour<decltype(foo)>())>::value, "erreur ");
    static_assert( std::is_same<decltype(typeRetour(f)),decltype(typeRetour<decltype(f)>())>::value, "erreur ");
    static_assert( std::is_same<decltype(typeRetour(lambda)),decltype(typeRetour<decltype(lambda)>())>::value, "erreur ");

    cout << nbParam(f)<<endl;
    cout << nbParam(foo)<<endl;
    cout << nbParam(lambda)<<endl;

    decltype(typeParam<0>(foo)) d = 5;
    decltype(typeParam<0>(f)) dd = 5;
    decltype(typeParam<0>(lambda)) ddd = 5;

}
