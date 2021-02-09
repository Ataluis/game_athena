#ifndef STATEMACHINE_HPP_INCLUDED
#define STATEMACHINE_HPP_INCLUDED

#include <memory>
#include <stack>

#include "State.hpp"

namespace engine
{
    typedef std::unique_ptr<State> StateRef;

    class StateMachine
    {
    public:
        StateMachine(){}
        ~StateMachine(){}

        void addState( StateRef newState, bool isReplacing = true );
        void removeState();

        void processStateChanges();

        StateRef& getActiveState();
    private:
        std::stack<StateRef> m_states;
        StateRef m_newState;
        bool m_isRemoving;
        bool m_isAdding;
        bool m_isReplacing;
    };
}

#endif // STATEMACHINE_HPP_INCLUDED
