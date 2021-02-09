#ifndef GAMEOVERSTATE_HPP_INCLUDED
#define GAMEOVERSTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"
#include <fstream>

namespace engine
{
    class GameOverState : public State
    {
        public:
            GameOverState( GameDataRef data );

            void init();

            void handleInput();
            void update( float dt );
            void draw( float dt );

        private:
            GameDataRef m_data;
            sf::Sprite m_background;
            sf::Text m_final;
            sf::Text m_finalscore;
            sf::Text m_retry;
            std::string m_score;
    };
}


#endif // GAMEOVERSTATE_HPP_INCLUDED
