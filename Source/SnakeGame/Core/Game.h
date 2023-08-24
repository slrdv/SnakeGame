// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Grid.h"
#include "Snake.h"
#include "Food.h"

namespace CoreGame
{
    class Game
    {
    public:
        Game(const Settings& settings);

        /**
         * Returns pointer to the core grid object
         * @return TSharedPtr<Grid> pointer to the core grid object
         */
        TSharedPtr<Grid> getGrid() const { return m_grid; }

        /**
         * Returns pointer to the core snake object
         * @return TSharedPtr<Snake> pointer to the core snake object
         */
        TSharedPtr<Snake> getSnake() const { return m_snake; }

        /**
         * Returns pointer to the core food object
         * @return TSharedPtr<Food> pointer to the core food object
         */
        TSharedPtr<Food> getFood() const { return m_food; }

        /**
         * Updates game
         * @param delta delta time
         * @param input user input
         */
        void update(float delta, const Input& input);

        void subscribeGameEvent(const GameEventCallback& callback);

        uint32 getScore() const { return m_score; }

    private:
        const Settings c_settings;
        TSharedPtr<Grid> m_grid;
        TSharedPtr<Snake> m_snake;
        TSharedPtr<Food> m_food;

        float m_timeAcc{0.0f};
        bool m_gameOver{false};
        uint32 m_score{0};

        TArray<GameEventCallback> m_gameEventCallbacks;

        bool updateTime(float delta);
        void checkHit();
        void updateFoodPosition();
        void broadcastGameEvent(GameEvent gameEvent);
    };

}  // namespace CoreGame
