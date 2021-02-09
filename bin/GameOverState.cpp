#include "GameOverState.hpp"

namespace engine
{
    GameOverState::GameOverState( GameDataRef data ) : m_data(data)
    {
        std::ifstream score;
        score.open( ".tempscore.dat" );
        if ( !score )
        {
            std::cout << "An error occurred opening the file" << std::endl;
        }
        score >> this->m_score;
        score.close();
    }

    void GameOverState::init()
    {
        this->m_background.setTexture( this->m_data->assets.getTexture( "Background" ) );
        this->m_final.setFont( this->m_data->assets.getFont( "Anklepants" ) );
        this->m_finalscore.setFont( this->m_data->assets.getFont( "Anklepants" ) );
        this->m_retry.setFont( this->m_data->assets.getFont( "Anklepants" ) );

        this->m_score = "SCORE: " + this->m_score;

        this->m_final.setString( "GAME OVER" );
        this->m_final.setCharacterSize(140);
        this->m_final.setFillColor(sf::Color::White);
        this->m_final.setStyle(sf::Text::Bold );
        this->m_final.setOrigin( this->m_final.getGlobalBounds().width / 2, this->m_final.getGlobalBounds().height / 2 );
        this->m_final.setPosition( SCREEN_WIDTH / 2, SCREEN_HEIGHT - ( 5 * SCREEN_HEIGHT / 7 ) );

        this->m_finalscore.setString( this->m_score );
        this->m_finalscore.setCharacterSize(75);
        this->m_finalscore.setFillColor(sf::Color::White);
        this->m_finalscore.setStyle(sf::Text::Bold );
        this->m_finalscore.setOrigin( this->m_finalscore.getGlobalBounds().width / 2, this->m_finalscore.getGlobalBounds().height / 2 );
        this->m_finalscore.setPosition( SCREEN_WIDTH / 2, SCREEN_HEIGHT - ( 2 * SCREEN_HEIGHT / 5 ) );

        this->m_retry.setString( "RETRY?" );
        this->m_retry.setCharacterSize(45);
        this->m_retry.setFillColor(sf::Color::White);
        this->m_retry.setStyle(sf::Text::Bold );
        this->m_retry.setOrigin( this->m_retry.getGlobalBounds().width / 2, this->m_retry.getGlobalBounds().height / 2 );
        this->m_retry.setPosition( SCREEN_WIDTH / 2, SCREEN_HEIGHT - ( SCREEN_HEIGHT / 5 ) );

    }

    void GameOverState::handleInput()
    {
        sf::Event event;

        while( this->m_data->window.pollEvent( event ) )
        {
            if( sf::Event::Closed == event.type )
            {
                this->m_data->window.close();
            }

            if( this->m_data->input.isTextClicked( this->m_retry, sf::Mouse::Left, this->m_data->window )
             || sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) )
            {
                this->m_data->machine.addState( StateRef( new MainMenuState( m_data ) ), true );
            }
        }
    }

    void GameOverState::update( float dt )
    {

    }

    void GameOverState::draw( float dt )
    {
        this->m_data->window.clear( sf::Color::Black );

        this->m_data->window.draw( this->m_background );
        this->m_data->window.draw( this->m_final );
        this->m_data->window.draw( this->m_finalscore );
        this->m_data->window.draw( this->m_retry );

        this->m_data->window.display();
    }
}
