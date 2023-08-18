// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "Core/Types.h"

namespace CoreGame
{
    class Snake
    {
    public:
        Snake(const uint32 length, const Position startPosition);

        const PositionList& links() { return m_links; }

        PositionListNode* head() const { return m_links.GetHead(); }

        void move(const Input& input);

        void feed();

    private:
        PositionList m_links;
        Input m_currentInput = Input::Default;
    };

}  // namespace CoreGame
