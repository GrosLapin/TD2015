#include <iostream>

#include "utilitaire/fonctionTest/test.hpp"
#include "testClass.hpp"
#include "exemple/exemple_iterateurFoncteur.hpp"
#include "exemple/exemple_paramInfo.hpp"

/**
\file main.cpp
\brief Fichier de lancement de l'application
\author Martin M
\bug Soon :D
*/

#include "testPourLeDev.hpp"
using namespace std;

#include <SFML/Graphics.hpp>
#include "thoth/window.hpp"

int main()
{
    thoth::window window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    TestClass::testDijkstra();
    exempleIterateurFoncteur();
    exempleParamInfo();

    return 0;
}
