// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"

namespace CoreGame
{
    class Food
    {
    public:
        Food() = default;

        void setPosition(const Position& position) { m_position = position; }

        Position getPosition() const { return m_position; }

    private:
        Position m_position;
    };

}  // namespace CoreGame
