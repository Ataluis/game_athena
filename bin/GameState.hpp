#ifndef GAMESTATE_HPP_INCLUDED
#define GAMESTATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include "State.hpp"
#include "GameOverState.hpp"
#include "Game.hpp"
#include "Character.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Collision.hpp" //from the SFML wiki, for

namespace engine
{

    class GameState : public State
    {
        public:
            GameState( GameDataRef data );

            void init();

            void handleInput();
            void update( float dt );
            void draw( float dt );

        private:
            GameDataRef m_data;

            sf::Clock m_clock;

            std::string m_score_string;
            sf::Text m_score;
            sf::Sprite m_background;
            sf::RectangleShape m_health;

            Character m_spaceship;
            std::vector<Character> m_enemy;
            std::vector<int> m_spawning_time;
            std::vector<int> m_spawning_counter;
            std::vector<bool> m_active;

            std::vector<sf::Sprite> m_laser_red;
            std::vector<sf::Sprite> m_laser_green;

    };

    std::vector<float> enemy_path();
}

#endif // GAMESTATE_HPP_INCLUDED
