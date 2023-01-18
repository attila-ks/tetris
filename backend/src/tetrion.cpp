#include "../headers/tetrion.h"

using namespace std;

// Helper functions:
void initRandomTetrominoGenerator();


Tetrion::Tetrion(QObject* parent) :
  QObject {parent},
  m_playfield {22, 10, QColor {0x0e001f}},
  m_bag {},
  m_currentTetromino {},
  m_tetrominoDropTimer {}
{
  initRandomTetrominoGenerator();

  m_tetrominoDropTimer.setInterval(1000);
  connect(&m_tetrominoDropTimer, &QTimer::timeout, this,
          &Tetrion::dropTetromino);
}


const Playfield* Tetrion::getPlayfield() const
{
  return &m_playfield;
}


void Tetrion::startGame()
{
  spawnTetromino();
  m_tetrominoDropTimer.start();
}


void Tetrion::spawnTetromino()
{
  m_currentTetromino = selectTetromino();
  m_currentTetromino.drawOn(m_playfield);
}


Tetromino Tetrion::selectTetromino()
{
  if (m_bag.empty())
  {
    fillBag();
  }

  const unsigned long index {rand() % m_bag.size()};
  const Tetromino tetromino = m_bag[index];
  m_bag.erase(m_bag.begin() + index);
  return tetromino;
}


void Tetrion::fillBag()
{
  m_bag = {
      Tetromino {Tetromino::Type::I, QColor {0x00b8d4}, Position {0, 3}},
      Tetromino {Tetromino::Type::J, QColor {0x304ffe}, Position {0, 3}},
      Tetromino {Tetromino::Type::L, QColor {0xff6d00}, Position {0, 3}},
      Tetromino {Tetromino::Type::O, QColor {0xffd600}, Position {0, 4}},
      Tetromino {Tetromino::Type::S, QColor {0x00c853}, Position {0, 3}},
      Tetromino {Tetromino::Type::T, QColor {0xaa00ff}, Position {0, 3}},
      Tetromino {Tetromino::Type::Z, QColor {0xd50000}, Position {0, 3}},
  };
}


void Tetrion::dropTetromino()
{
  m_currentTetromino.moveDown(m_playfield);
}


void initRandomTetrominoGenerator()
{
  srand(time(nullptr));
}
