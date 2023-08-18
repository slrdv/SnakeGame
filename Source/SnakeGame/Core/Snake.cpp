// SnakeGame. Copyright slrdv. All right Reserved.

#include "Core/Snake.h"

using namespace CoreGame;

Snake::Snake(const uint32 length, const Position startPosition)
{
    check(length >= 3);

    // Init snake links, from right to left
    for (uint32 i = 0; i < length; ++i)
    {
        m_links.AddTail(Position{startPosition.x - i, startPosition.y});
    }
}

void Snake::move(const Input& input)
{
    if (!m_currentInput.isOpposite(input))
    {
        m_currentInput = input;
    }

    m_links.RemoveNode(m_links.GetTail());
    const Position& headPosition = head()->GetValue();
    m_links.AddHead(Position{headPosition.x + m_currentInput.x, headPosition.y + m_currentInput.y});
}

void Snake::feed()
{
    m_links.AddTail(m_links.GetTail()->GetValue());
}
