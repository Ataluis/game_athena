#ifndef SPLASHSTATE_HPP_INCLUDED
#define SPLASHSTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace engine
{
    class SplahState : public State
    {
        public:
            SplahState( GameDataRef data );

            void init();

            void handleInput();
            void update( float dt );
            void draw( float dt );

        private:
            GameDataRef m_data;

            sf::Clock m_clock;

            sf::Sprite m_background;
    };
}

#endif // SPLASHSTATE_HPP_INCLUDED
