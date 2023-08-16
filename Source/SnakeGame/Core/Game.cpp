// SnakeGame. Copyright slrdv. All right Reserved.

#include "Core/Game.h"

DEFINE_LOG_CATEGORY_STATIC(SGLogCoreGame, All, All);

using namespace CoreGame;

Game::Game(const Settings& settings) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridSize);
    m_snake = MakeShared<Snake>(settings.snakeLength, settings.snakePosition);

    m_grid.Get()->updateSnake(m_snake.Get()->head());
    m_grid.Get()->printDebug();
}

bool Game::updateTime(float delta)
{
    m_timeAcc += delta;
    if (m_timeAcc < c_settings.tickInterval) return false;
    m_timeAcc = 0.0f;
    return true;
}

void Game::hitTest()
{
    const CellType hitCell = m_grid->getCell(m_snake->head()->GetValue());
    if (hitCell == CellType::Snake || hitCell == CellType::Wall)
    {
        m_gameOver = true;
        UE_LOG(SGLogCoreGame, Display, TEXT("GameOver!"));
    }
}

void Game::update(float delta, const Input& input)
{
    if (m_gameOver || !updateTime(delta)) return;
    m_snake->move(input);
    hitTest();
    if (m_gameOver) return;

    m_grid->updateSnake(m_snake.Get()->head());
    m_grid->printDebug();
}
