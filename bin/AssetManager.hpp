#ifndef ASSETMANAGER_HPP_INCLUDED
#define ASSETMANAGER_HPP_INCLUDED

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

namespace engine
{
    class AssetManager
    {
    public:
        AssetManager(){};
        ~AssetManager(){};

        void loadTexture( std::string name, std::string fileName );
        sf::Texture& getTexture( std::string name );

        void loadFont( std::string name, std::string fileName );
        sf::Font &getFont( std::string name );

    private:
        std::map<std::string, sf::Texture> m_textures;
        std::map<std::string, sf::Font> m_fonts;
    };
}

#endif // ASSETMANAGER_HPP_INCLUDED
