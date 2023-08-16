// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Grid.h"
#include "Snake.h"

namespace CoreGame
{
    class Game
    {
    public:
        Game(const Settings& settings);

        /**
         * Return pointer to the core grid object
         * @return TSharedPtr<Grid> return pointer to the core grid object
         */
        TSharedPtr<Grid> getGrid() const { return m_grid; }
        TSharedPtr<Snake> getSnake() const { return m_snake; }

        void update(float delta, const Input& input);

    private:
        const Settings c_settings;
        TSharedPtr<Grid> m_grid;
        TSharedPtr<Snake> m_snake;
        float m_timeAcc{0.0f};
        bool m_gameOver{false};

        bool updateTime(float delta);
        void hitTest();
    };

}  // namespace CoreGame
