#ifndef TEST_HPP
#define TEST_HPP

#include<iostream>
#include "failTestError.hpp"

inline void erreur (const std::string& msg){
    throw FailTestError("Erreur : " + msg );
};

inline void testUnitaire (bool condition,const std::string& msg)
{
    if ( ! condition )
    {
        erreur(msg);
    }
};

#endif
