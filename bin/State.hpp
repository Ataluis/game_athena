#ifndef GAMESTATES_HPP_INCLUDED
#define GAMESTATES_HPP_INCLUDED

namespace engine
{
    class State
    {
    public:
        virtual void init() = 0;

        virtual void handleInput() = 0;
        virtual void update( float dt ) = 0;
        virtual void draw( float dt ) = 0;

        virtual void pause() {}
        virtual void resume() {}
    };
}

#endif // GAMESTATES_HPP_INCLUDED
