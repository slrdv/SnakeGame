// SnakeGame. Copyright slrdv. All right Reserved.

#include "Core/Game.h"

DEFINE_LOG_CATEGORY_STATIC(SGLogCoreGame, All, All);

using namespace CoreGame;

Game::Game(const Settings& settings) : c_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridSize);
    m_snake = MakeShared<Snake>(settings.snakeLength, settings.snakePosition);
    checkf(m_grid->isEmpty(m_snake->head()->GetValue()), TEXT("Error: Invalid snake positon"));
    checkf(m_grid->isEmpty(m_snake->tail()->GetValue()), TEXT("Error: Snake length too large"));

    m_food = MakeShared<Food>();

    m_grid->updateSnake(m_snake->head());
    updateFoodPosition();

    m_grid->printDebug();
}

bool Game::updateTime(float delta)
{
    m_timeAcc += delta;
    if (m_timeAcc < c_settings.tickInterval) return false;
    m_timeAcc = 0.0f;
    return true;
}

void Game::checkHit()
{
    const CellType hitCell = m_grid->getCell(m_snake->head()->GetValue());

    if (hitCell == CellType::Snake || hitCell == CellType::Wall)
    {
        m_gameOver = true;
        broadcastGameEvent(GameEvent::GameOver);
    }
    else if (hitCell == CellType::Food)
    {
        m_snake->feed();
        ++m_score;
        broadcastGameEvent(GameEvent::FoodTaken);
        updateFoodPosition();
    }
}

void Game::updateFoodPosition()
{
    Position foodPosition;
    if (m_grid->getRandomEmptyPosition(foodPosition))
    {
        m_food->setPosition(foodPosition);
        m_grid->updateFood(foodPosition);
    }
    else
    {
        m_gameOver = true;
        broadcastGameEvent(GameEvent::GameCompleted);
    }
}

void Game::broadcastGameEvent(GameEvent gameEvent)
{
    for (const auto& callback : m_gameEventCallbacks)
    {
        if (callback)
        {
            callback(gameEvent);
        }
    }
}

void Game::update(float delta, const Input& input)
{
    if (m_gameOver || !updateTime(delta)) return;
    m_snake->move(input);
    checkHit();
    if (m_gameOver) return;

    m_grid->updateSnake(m_snake->head());
    // m_grid->printDebug();
}

void Game::subscribeGameEvent(const GameEventCallback& callback)
{
    m_gameEventCallbacks.Add(callback);
}
