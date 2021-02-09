#include "StateMachine.hpp"


namespace engine
{
    void StateMachine::addState( StateRef newState, bool isReplacing )
    {
        this->m_isAdding = true;
        this->m_isReplacing = isReplacing;
        this->m_newState = std::move( newState );
    }

    void StateMachine::removeState()
    {
        this->m_isRemoving = true;
    }

    void StateMachine::processStateChanges()
    {
        if( this->m_isRemoving && !this->m_states.empty() )
        {
            this->m_states.pop();

            if( !this->m_states.empty() )
            {
                this->m_states.top()->resume();
            }
            this->m_isRemoving = false;
        }

        if( this->m_isAdding )
        {
            if( !this->m_states.empty() )
            {
                if( this->m_isReplacing )
                {
                    this->m_states.pop();
                }
                else
                {
                    this->m_states.top()->pause();
                }
            }

            this->m_states.push( std::move( this->m_newState )  );
            this->m_states.top()->init();
            this->m_isAdding = false;
        }
    }

    StateRef& StateMachine::getActiveState()
    {
        return this->m_states.top();
    }
}
