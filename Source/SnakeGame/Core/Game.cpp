// SnakeGame. Copyright slrdv. All right Reserved.

#include "Core/Game.h"

DEFINE_LOG_CATEGORY_STATIC(SGLogCoreGame, All, All);

using namespace CoreGame;

Game::Game(const Settings& settings) : c_settings(settings), m_grid(MakeShared<Grid>(settings.gridSize)) {}
