#ifndef CHARACTER_HPP_INCLUDED
#define CHARACTER_HPP_INCLUDED

#include <SFML/Graphics.hpp>

namespace engine
{
    class Character
    {
    public:
        Character(){};
        Character(float t_v_max, float t_a)
            : vx(0.0f), vy(0.0f), v_max(t_v_max), ax_temp(0.0f), ay_temp(0.0f), a(t_a) {};
        Character( Character* c )
            : vx(0.0), vy(0.0), v_max(c->v_max), ax_temp(0.0f), ay_temp(0.0f), a(c->a) {};
        sf::Sprite m_sprite;
        float vx,
              vy,
              v_max,
              ax_temp,
              ay_temp,
              a;
    };
}

#endif // CHARACTER_HPP_INCLUDED
