#include <sstream>
#include "SplashState.hpp"
#include <iostream>
#include "MainMenuState.hpp"

#include "DEFINITIONS.hpp"

namespace engine
{
    SplahState::SplahState( GameDataRef data ) : m_data(data)
    {

    }

    void SplahState::init()
    {
        this->m_data->assets.loadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH );
        this->m_background.setTexture( this->m_data->assets.getTexture( "Splash State Background" ) );
    }

    void SplahState::handleInput()
    {
        sf::Event event;
        while( this->m_data->window.pollEvent( event ) )
        {
            if( sf::Event::Closed == event.type )
            {
                this->m_data->window.close();
            }
        }
    }

    void SplahState::update( float dt )
    {
        if( this->m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME )
        {
            this->m_data->machine.addState( StateRef( new MainMenuState( m_data ) ), true );
        }
    }

    void SplahState::draw( float dt )
    {
        this->m_data->window.clear( sf::Color::Black );

        this->m_data->window.draw( this->m_background );

        this->m_data->window.display();
    }
}
