#include "Game.hpp"
#include "SplashState.hpp"

namespace engine
{
    Game::Game( int width, int height, std::string title )
    {
        m_data->window.create( sf::VideoMode( width, height ), title, sf::Style::Close | sf::Style::Titlebar );
        m_data->machine.addState( StateRef( new SplahState( this->m_data ) ) );
        this->run();
    }

    void Game::run()
    {
        float newTime, TimeDiff;

        float currentTime = this->m_clock.getElapsedTime().asMilliseconds();

        while( this->m_data->window.isOpen() )
        {
            this->m_data->machine.processStateChanges();

            newTime = this->m_clock.getElapsedTime().asMilliseconds();

            do
            {
                TimeDiff = this->m_clock.getElapsedTime().asMilliseconds() - newTime;
            }
            while( TimeDiff < dt );

            this->m_data->machine.getActiveState()->handleInput();
            this->m_data->machine.getActiveState()->update( dt );
            this->m_data->machine.getActiveState()->draw( dt );
        }
    }
}
