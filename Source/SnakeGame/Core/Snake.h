// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "Core/Types.h"

namespace CoreGame
{
    class Snake
    {
    public:
        Snake(const uint32 length, const Position startPosition);

        /**
         * Returns snake links nodes
         * @return const PositionList& snake links nodes
         */
        const PositionList& links() { return m_links; }

        /**
         * Returns snake head node
         * @return PositionListNode* snake head node
         */
        PositionListNode* head() const { return m_links.GetHead(); }

        /**
         * Returns snake tail node
         * @return PositionListNode* snake tail node
         */
        PositionListNode* tail() const { return m_links.GetTail(); }

        /**
         * Moves snake links with a given input
         * @param input user input
         */
        void move(const Input& input);

        /**
         * Increases snake length
         */
        void feed();

    private:
        PositionList m_links;
        Input m_currentInput = Input::Default;
    };

}  // namespace CoreGame
