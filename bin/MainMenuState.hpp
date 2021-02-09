#ifndef MAINMENUSTATE_HPP_INCLUDED
#define MAINMENUSTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "GameState.hpp"

namespace engine
{
    class MainMenuState : public State
    {
    public:
        MainMenuState( GameDataRef data );

        void init();

        void handleInput();
        void update( float dt );
        void draw( float dt );

    private:
        GameDataRef m_data;

        sf::Sprite m_background;
        sf::Sprite m_playButton;
        sf::Sprite m_playButtonOuter;
        sf::Sprite m_title;

    };
}


#endif // MAINMENUSTATE_HPP_INCLUDED
