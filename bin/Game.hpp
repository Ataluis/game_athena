#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace engine
{
    struct GameData
    {
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game
    {
    public:
        Game( int width, int height, std::string title );

    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock m_clock;
        GameDataRef m_data = std::make_shared<GameData>();

        void run();
    };

}


#endif // GAME_HPP_INCLUDED
