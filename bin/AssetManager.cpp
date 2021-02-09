#include "AssetManager.hpp"

namespace engine
{
    void AssetManager::loadTexture( std::string name, std::string fileName )
    {
        sf::Texture texture;

        if( texture.loadFromFile( fileName ) )
        {
            this->m_textures[name] = texture;
        }
    }

    sf::Texture& AssetManager::getTexture( std::string name )
    {
        return this->m_textures.at( name );
    }

    void AssetManager::loadFont( std::string name, std::string fileName )
    {
        sf::Font font;

        if( font.loadFromFile( fileName ) )
        {
            this->m_fonts[name] = font;
        }
    }

    sf::Font& AssetManager::getFont( std::string name )
    {
        return this->m_fonts.at( name );
    }

}
