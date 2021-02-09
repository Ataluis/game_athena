#include "GameState.hpp"

namespace engine
{
    template <typename T> int sgn(T val) {
        return (T(0) < val) - (val < T(0));
    }

    std::vector<float> enemy_path( int enemy_width, float max_vel = MAX_SPEED_LASER_BALL )
    {
        std::vector<float> pos_and_vel(4,0);
        bool coin1 = rand() % 2;
        bool coin2 = rand() % 2;
        double scaling = 0.7f * ( rand() / (double)RAND_MAX ) + 0.3f;
        if( coin1 )
        {
            if( coin2 )
            {
                pos_and_vel[0] = 0.0f - enemy_width / 2.0f;
                pos_and_vel[1] = rand() % SCREEN_HEIGHT;
                pos_and_vel[2] = ( max_vel / 2.0f ) + ( ( rand() / (double)RAND_MAX ) * ( max_vel / 2.0f ) );
                pos_and_vel[3] = std::sqrt( max_vel*max_vel - pos_and_vel[2]*pos_and_vel[2] ) * scaling * ( rand() % 2 );
                pos_and_vel[2] *= scaling;
            }
            else
            {
                pos_and_vel[0] = SCREEN_WIDTH + enemy_width / 2.0f;
                pos_and_vel[1] = rand() % SCREEN_HEIGHT;
                pos_and_vel[2] = - ( ( max_vel / 2.0f ) + ( ( rand() / (double)RAND_MAX ) * ( max_vel / 2.0f ) ) );
                pos_and_vel[3] = std::sqrt( max_vel*max_vel - pos_and_vel[2]*pos_and_vel[2] ) * scaling * ( rand() % 2 );
                pos_and_vel[2] *= scaling;
            }
        }
        else
        {
            if( coin2 )
            {
                pos_and_vel[0] = rand() % SCREEN_WIDTH;
                pos_and_vel[1] = 0.0 - enemy_width / 2.0f;
                pos_and_vel[3] = ( max_vel / 2.0f ) + ( ( rand() / (double)RAND_MAX ) * ( max_vel / 2.0f ) );
                pos_and_vel[2] = std::sqrt( max_vel*max_vel - pos_and_vel[3]*pos_and_vel[3] ) * scaling * ( rand() % 2 );
                pos_and_vel[3] *= scaling;
            }
            else
            {
                pos_and_vel[0] = rand() % SCREEN_WIDTH;
                pos_and_vel[1] = SCREEN_HEIGHT + enemy_width / 2.0f;
                pos_and_vel[3] = - ( ( max_vel / 2.0f ) + ( ( rand() / (double)RAND_MAX ) * ( max_vel / 2.0f ) ) );
                pos_and_vel[2] = std::sqrt( max_vel*max_vel - pos_and_vel[3]*pos_and_vel[3] ) * scaling * ( rand() % 2 );
                pos_and_vel[3] *= scaling;
            }
        }
        return pos_and_vel;
    }

    GameState::GameState( GameDataRef data ) : m_data( data )
    {
        srand( time(NULL) );
        this->m_spawning_time.emplace_back( rand() % SPAWNING_TIME_MAX_START );
        this->m_spaceship = Character( MAX_SPEED_SPACESHIP, ACCELARATION_SPACESHIP );
        this->m_spaceship.vx = 0.0f;
        this->m_spaceship.vy = 0.0f;
        for( int i = 0; i < MAX_ENEMIES; i++ )
        {
            this->m_enemy.emplace_back( new Character( MAX_SPEED_LASER_BALL, 0.0f ) );
            this->m_spawning_counter.emplace_back(0);
            this->m_active.emplace_back(false);
            if( i > 0 )
                this->m_spawning_time.emplace_back( rand() % SPAWNING_TIME_MAX_START + this->m_spawning_time[i-1] );
        }
        srand( time(NULL) );
    }

    void GameState::init()
    {

        this->m_data->assets.loadTexture( "Background", MAIN_MENU_BACKGROUND_FILEPATH );
        this->m_data->assets.loadTexture( "SpaceShip", SPACEHIP_BITMAP );
        this->m_data->assets.loadTexture( "Enemy", ENEMY_BITMAP );
        this->m_data->assets.loadTexture( "LaserBall", LASER_BALL );
        this->m_data->assets.loadTexture( "LaserRed", LASER_RED );
        this->m_data->assets.loadTexture( "LaserGreen", LASER_GREEN );

        this->m_data->assets.loadFont( "Anklepants", ANKLEPANTS_FONT );

        this->m_background.setTexture( this->m_data->assets.getTexture( "Background" ) );
        this->m_spaceship.m_sprite.setTexture( this->m_data->assets.getTexture( "SpaceShip" ) );

        this->m_score.setFont( this->m_data->assets.getFont( "Anklepants" ) );

        this->m_health = sf::RectangleShape( sf::Vector2f( 500, 24 ) );
        this->m_health.setFillColor( sf::Color( 100, 250, 50 ) );
        this->m_health.setOrigin( (double)this->m_health.getGlobalBounds().width, 0.0f );
        this->m_health.setPosition( SCREEN_WIDTH - 10, 10 );

        for( int i = 0; i < MAX_ENEMIES; i++ )
        {
            this->m_enemy[i].m_sprite.setTexture( this->m_data->assets.getTexture( "LaserBall" ) );
            this->m_enemy[i].m_sprite.setPosition( 0.0f, 0.0f );
            this->m_enemy[i].m_sprite.setOrigin( this->m_enemy[i].m_sprite.getGlobalBounds().width, this->m_enemy[i].m_sprite.getGlobalBounds().height );
        }

        this->m_clock = *(new sf::Clock);

        this->m_score.setPosition( 10, 10 );
        this->m_score_string = "SCORE: " + std::to_string( this->m_clock.getElapsedTime().asMilliseconds() / 100 );
        this->m_score.setString( this->m_score_string );
        this->m_score.setCharacterSize(24);
        this->m_score.setFillColor(sf::Color::White);
        this->m_score.setStyle(sf::Text::Bold );

        this->m_spaceship.m_sprite.setOrigin( this->m_spaceship.m_sprite.getGlobalBounds().width / 2, this->m_spaceship.m_sprite.getGlobalBounds().height / 2 );
        this->m_spaceship.m_sprite.setPosition( ( SCREEN_WIDTH / 2 ) - ( this->m_spaceship.m_sprite.getGlobalBounds().width / 2 ),
            ( SCREEN_HEIGHT / 2 ) - ( this->m_spaceship.m_sprite.getGlobalBounds().height / 2 - 200 ));

    }

    void GameState::handleInput()
    {
        sf::Event event;

        while( this->m_data->window.pollEvent( event ) )
        {
            if( sf::Event::Closed == event.type )
            {
                this->m_data->window.close();
            }

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) )
            {
                this->m_spaceship.ay_temp = - this->m_spaceship.a;
            }
            else if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) )
            {
                this->m_spaceship.ay_temp = this->m_spaceship.a;
            }
            else
            {
                this->m_spaceship.ay_temp = 0.0f;
            }
            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
            {
                this->m_spaceship.ax_temp = - this->m_spaceship.a;
            }
            else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
            {
                this->m_spaceship.ax_temp = this->m_spaceship.a;
            }
            else
            {
                this->m_spaceship.ax_temp = 0.0f;
            }
        }
    }

    void GameState::update( float dt )
    {
        this->m_spaceship.vx = DECLINE_FACTOR * this->m_spaceship.vx + this->m_spaceship.ax_temp;
        this->m_spaceship.vy = DECLINE_FACTOR * this->m_spaceship.vy + this->m_spaceship.ay_temp;
        float v_spaceship_square = this->m_spaceship.vx * this->m_spaceship.vx + this->m_spaceship.vy * this->m_spaceship.vy;
        if( v_spaceship_square > this->m_spaceship.v_max * this->m_spaceship.v_max )
        {
            this->m_spaceship.vx = sgn( this->m_spaceship.vx ) *
            std::sqrt( this->m_spaceship.vx * this->m_spaceship.vx * this->m_spaceship.v_max * this->m_spaceship.v_max / v_spaceship_square );
            this->m_spaceship.vy = sgn( this->m_spaceship.vy ) *
            std::sqrt( this->m_spaceship.vy * this->m_spaceship.vy * this->m_spaceship.v_max * this->m_spaceship.v_max / v_spaceship_square );
        }

        if( this->m_spaceship.m_sprite.getPosition().x <= 0 )
        {
            this->m_spaceship.vy = 0.f;
            this->m_spaceship.m_sprite.setPosition( m_spaceship.m_sprite.getPosition().x + 1, m_spaceship.m_sprite.getPosition().y );
        }
        else if( this->m_spaceship.m_sprite.getPosition().x >= SCREEN_WIDTH )
        {
            this->m_spaceship.vy = 0.f;
            this->m_spaceship.m_sprite.setPosition( m_spaceship.m_sprite.getPosition().x - 1, m_spaceship.m_sprite.getPosition().y );
        }
        if( this->m_spaceship.m_sprite.getPosition().y <= 0 )
        {
            this->m_spaceship.vx = 0.f;
            this->m_spaceship.m_sprite.setPosition( m_spaceship.m_sprite.getPosition().x, m_spaceship.m_sprite.getPosition().y + 1 );
        }
        else if( this->m_spaceship.m_sprite.getPosition().y >= SCREEN_HEIGHT )
        {
            this->m_spaceship.vx = 0.f;
            this->m_spaceship.m_sprite.setPosition( m_spaceship.m_sprite.getPosition().x, m_spaceship.m_sprite.getPosition().y - 1 );
        }

        float angle = 0.f;
        if( this->m_spaceship.vy != 0.0f )
        {
            if( this->m_spaceship.vx < 0.0f )
            {
                angle = std::atan(-this->m_spaceship.vy / this->m_spaceship.vx) * 180.f / M_PI;
            }
            else if( this->m_spaceship.vx > 0.0f )
            {
                angle = std::atan(-this->m_spaceship.vy / this->m_spaceship.vx) * 180.f / M_PI + 180.f;
            }
            else
            {
                angle = 90.f * sgn( this->m_spaceship.vy );
            }
        }
        else
        {
            if( this->m_spaceship.vx != 0.0f )
            {
                angle = 90.f + 90.f * sgn( this->m_spaceship.vx );
            }

        }
        if( this->m_spaceship.vx != 0.0f || this->m_spaceship.vy != 0.0f )
            this->m_spaceship.m_sprite.setRotation(angle);
        this->m_spaceship.m_sprite.move(this->m_spaceship.vy,this->m_spaceship.vx);

        for( int i = 0; i < MAX_ENEMIES; i++ )
        {
            if( ( this->m_spawning_time[i] < this->m_clock.getElapsedTime().asMilliseconds() ) && !this->m_active[i] )
            {
                std::vector<float> temp = enemy_path( this->m_enemy[i].m_sprite.getGlobalBounds().width );
                this->m_active[i] = true;
                this->m_enemy[i].m_sprite.setPosition(temp[0],temp[1]);
                this->m_enemy[i].vx = temp[2];
                this->m_enemy[i].vy = temp[3];
            }
            if( this->m_active[i] )
            {
                this->m_enemy[i].m_sprite.move( this->m_enemy[i].vx, this->m_enemy[i].vy );
                sf::Vector2f position = this->m_enemy[i].m_sprite.getPosition();
                if( position.x < 0.0f - this->m_enemy[i].m_sprite.getGlobalBounds().width / 2.0f - 100.0f
                ||  position.x > SCREEN_WIDTH + this->m_enemy[i].m_sprite.getGlobalBounds().width / 2.0f + 100.0f
                ||  position.y < 0.0f - this->m_enemy[i].m_sprite.getGlobalBounds().height / 2.0f - 100.0f
                ||  position.y > SCREEN_HEIGHT + this->m_enemy[i].m_sprite.getGlobalBounds().width / 2.0f + 100.0f )
                {
                    position.x = -300.0f;
                    position.y = -300.0f;
                    this->m_enemy[i].m_sprite.setPosition( position );
                    this->m_spawning_counter[i]++;
                    this->m_spawning_time[i] = this->m_clock.getElapsedTime().asMilliseconds()
                    + std::min( SPAWNING_TIME_MAX_FINAL, (int)( SPAWNING_TIME_MAX_START - ( this->m_spawning_counter[i] * SPAWNING_TIME_MAX_DECREASE )
                              + std::round( this->m_spawning_counter[i] * rand() / (double)RAND_MAX ) ) );
                    this->m_active[i] = false;
                }


                if ( Collision::PixelPerfectTest( this->m_spaceship.m_sprite, this->m_enemy[i].m_sprite, sf::Uint8(0) ) )
                {
                    if( this->m_health.getGlobalBounds().width <= 1 )
                    {
                        std::ofstream score;
                        score.open( ".tempscore.dat" );
                        if ( !score )
                        {
                                std::cout << "An error occurred opening the file" << std::endl;
                        }
                        score << (int)(this->m_clock.getElapsedTime().asMilliseconds() / 100 ) << std::endl;
                        score.close();
                        this->m_data->machine.addState( StateRef( new GameOverState( m_data ) ), true );
                    }
                    this->m_health = sf::RectangleShape( sf::Vector2f( this->m_health.getGlobalBounds().width - DAMAGE_LASER_BALL, 24 ) );
                    this->m_health.setFillColor( sf::Color( 100, 250, 50 ) );
                    this->m_health.setOrigin( (double)this->m_health.getGlobalBounds().width, 0.0f );
                    this->m_health.setPosition( SCREEN_WIDTH - 10, 10 );
                }

            }
        }
    }

    void GameState::draw( float dt )
    {
        this->m_data->window.clear();
        this->m_data->window.draw( this->m_background );
        this->m_data->window.draw( this->m_spaceship.m_sprite );
        for( int i = 0; i < MAX_ENEMIES; i++ )
        {
            if( this->m_active[i] ) this->m_data->window.draw( this->m_enemy[i].m_sprite );
        }
        this->m_score.setString( "SCORE: " + std::to_string( this->m_clock.getElapsedTime().asMilliseconds() / 100 ) );
        this->m_data->window.draw( this->m_score );
        this->m_data->window.draw( this->m_health );
        this->m_data->window.display();
    }
}
