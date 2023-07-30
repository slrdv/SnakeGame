// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"
#include "Grid.h"

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

    private:
        const Settings c_settings;
        TSharedPtr<Grid> m_grid;
    };

}  // namespace CoreGame
