#ifndef INPUTMANAGER_HPP_INCLUDED
#define INPUTMANAGER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

namespace engine
{
    class InputManager
    {
    public:
        InputManager(){};
        ~InputManager(){};

        bool isSpriteClicked( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window );
        bool isTextClicked( sf::Text object, sf::Mouse::Button button, sf::RenderWindow& window );

        sf::Vector2i getMousePosition( sf::RenderWindow& window );
    };
}

#endif // INPUTMANAGER_HPP_INCLUDED
