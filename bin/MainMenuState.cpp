#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine
{
    MainMenuState::MainMenuState( GameDataRef data ) : m_data( data )
    {

    }

    void MainMenuState::init()
    {
        this->m_data->assets.loadTexture( "Background", MAIN_MENU_BACKGROUND_FILEPATH );
        this->m_data->assets.loadTexture( "PlayButton", MAIN_MENU_PLAY_BUTTON );
        this->m_data->assets.loadTexture( "PlayButtonOuter", MAIN_MENU_PLAY_BUTTON_OUTER );
        this->m_data->assets.loadTexture( "Title", MAIN_MENU_TITLE );

        this->m_background.setTexture( this->m_data->assets.getTexture( "Background" ) );
        this->m_playButton.setTexture( this->m_data->assets.getTexture( "PlayButton" ) );
        this->m_playButtonOuter.setTexture( this->m_data->assets.getTexture( "PlayButtonOuter" ) );
        this->m_title.setTexture( this->m_data->assets.getTexture( "Title" ) );

        this->m_playButton.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->m_playButton.getGlobalBounds().width / 2 ),
            ( SCREEN_HEIGHT / 2 ) - ( this->m_playButton.getGlobalBounds().height / 2 ));
        this->m_playButtonOuter.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->m_playButtonOuter.getGlobalBounds().width / 2 ) - 2,
            ( SCREEN_HEIGHT / 2 ) - ( this->m_playButtonOuter.getGlobalBounds().height / 2 + 8 ));

        this->m_title.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->m_title.getGlobalBounds().width / 2 ),
            this->m_title.getGlobalBounds().height * 0.1 );
    }

    void MainMenuState::handleInput()
    {
        sf::Event event;

        while( this->m_data->window.pollEvent( event ) )
        {
            if( sf::Event::Closed == event.type )
            {
                this->m_data->window.close();
            }

            if( this->m_data->input.isSpriteClicked( this->m_playButton, sf::Mouse::Left, this->m_data->window )
             || sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )
            {
                this->m_data->machine.addState( StateRef( new GameState( m_data ) ), true );
            }
        }
    }

    void MainMenuState::update( float dt )
    {

    }

    void MainMenuState::draw( float dt )
    {
        this->m_data->window.clear();
        this->m_data->window.draw( this->m_background );
        this->m_data->window.draw( this->m_title );
        this->m_data->window.draw( this->m_playButtonOuter );
        this->m_data->window.draw( this->m_playButton );

        this->m_data->window.display();
    }
}

