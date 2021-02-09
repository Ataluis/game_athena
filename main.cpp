#include <SFML/Graphics.hpp>
#include <iostream>
#include "bin/Game.hpp"
#include "bin/DEFINITIONS.hpp"


int main()
{
    engine::Game( SCREEN_WIDTH, SCREEN_HEIGHT, "ATHENA");
    return EXIT_SUCCESS;
}
