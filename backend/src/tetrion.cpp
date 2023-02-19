#include "../headers/tetrion.h"

using namespace std;

// Helper functions:
void initRandomTetrominoGenerator();


Tetrion::Tetrion(QObject* parent) :
  QObject {parent},
  m_tetrisBoard {22, 10, QColor {0x0e001f}},
  m_bag {},
  m_currentTetromino {nullptr},
  m_tetrominoDropTimer {}
{
  initRandomTetrominoGenerator();

  m_tetrominoDropTimer.setInterval(1000);
  connect(&m_tetrominoDropTimer, &QTimer::timeout, this,
          &Tetrion::dropTetromino);
}


const TetrisBoard* Tetrion::getTetrisBoard() const
{
  return &m_tetrisBoard;
}


void Tetrion::startGame()
{
  spawnTetromino();
  m_tetrominoDropTimer.start();
}


void Tetrion::spawnTetromino()
{
  m_currentTetromino = selectTetromino();

  connect(m_currentTetromino.get(), &Tetromino::landed, this,
          &Tetrion::spawnTetromino);

  m_currentTetromino->drawOn(m_tetrisBoard);
}


void Tetrion::dropTetromino()
{
  m_currentTetromino->moveDown(m_tetrisBoard);
}


shared_ptr<Tetromino> Tetrion::selectTetromino()
{
  if (m_bag.empty())
  {
    fillBag();
  }

  const unsigned long index {rand() % m_bag.size()};
  shared_ptr<Tetromino> tetromino = m_bag[index];
  m_bag.erase(m_bag.begin() + index);
  return tetromino;
}


void Tetrion::fillBag()
{
  m_bag = {
      make_shared<Tetromino>(Tetromino::Type::I, QColor {0x00b8d4},
                             Index {0, 3}),
      make_shared<Tetromino>(Tetromino::Type::J, QColor {0x304ffe},
                             Index {0, 3}),
      make_shared<Tetromino>(Tetromino::Type::L, QColor {0xff6d00},
                             Index {0, 3}),
      make_shared<Tetromino>(Tetromino::Type::O, QColor {0xffd600},
                             Index {0, 4}),
      make_shared<Tetromino>(Tetromino::Type::S, QColor {0x00c853},
                             Index {0, 3}),
      make_shared<Tetromino>(Tetromino::Type::T, QColor {0xaa00ff},
                             Index {0, 3}),
      make_shared<Tetromino>(Tetromino::Type::Z, QColor {0xd50000},
                             Index {0, 3})
  };
}


void initRandomTetrominoGenerator()
{
  srand(time(nullptr));
}
