#include "../headers/tetrion.h"

using namespace std;

// Helper functions:
void initRandomTetrominoGenerator();
void setUpKeyboardEventHandler(KeyboardEventHandler &keyboardEventHandler,
                               Tetrion &tetrion);

Tetrion::Tetrion(QObject *parent) :
  QObject {parent},
  m_playfield {QColor {0x0e001f}},
  m_bag {},
  m_currentTetromino {nullptr},
  m_nextTetromino {selectTetromino()},
  m_ghostTetromino {nullopt},
  m_tetrominoDropTimer {},
  m_keyboardEventHandler {},
  m_level {1},
  m_levelProgress {0.0f},
  m_score {0}
{
  initRandomTetrominoGenerator();

  setUpKeyboardEventHandler(m_keyboardEventHandler, *this);

  setSpeed();
  connect(&m_tetrominoDropTimer, &QTimer::timeout, this,
          &Tetrion::dropTetromino);
}


const Playfield *Tetrion::getPlayfield() const
{
  return &m_playfield;
}


int Tetrion::getLevel() const
{
  return m_level;
}


float Tetrion::getLevelProgress() const
{
  return m_levelProgress;
}


void Tetrion::startGame()
{
  spawnTetromino();
  m_tetrominoDropTimer.start();
}


void Tetrion::processInput(const Key key, const KeyEvent::Type type)
{
  // FIXME: Movement keys are duplicated: here and in the
  // setUpKeyboardEventHandler method!
  bool isTetrominoRotatedOrMovedHorizontally = false;

  if (key == Key_S) {
    m_currentTetromino->moveDown(m_playfield);
  } else if (key == Key_A) {
    m_currentTetromino->moveLeft(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_D) {
    m_currentTetromino->moveRight(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_Q) {
    m_currentTetromino->rotateLeft(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_E) {
    m_currentTetromino->rotateRight(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_Space) {
    m_currentTetromino->hardDrop(m_playfield);
  }

  // FIXME: This is true even if the `m_currentTetromino` could not move, in
  // which case the `m_ghostTetromino` `move` method is called unnecessarily.
  if (isTetrominoRotatedOrMovedHorizontally && m_ghostTetromino.has_value()) {
    m_ghostTetromino->move(m_playfield);
  }
}


void Tetrion::handleTetrominoLanding()
{
  const int clearedRows = m_playfield.clearFilledRows();

  checkGameOver();

  m_levelProgress += clearedRows * 0.1f;
  updateScore(clearedRows);

  if (m_levelProgress >= 1.0f) {
    increaseLevel();
    setSpeed();
    m_levelProgress = m_levelProgress - 1.0f;
    emit levelProgressed();
  } else if (clearedRows > 0) {
    emit levelProgressed();
  }

  spawnTetromino();
}


void Tetrion::spawnTetromino()
{
  m_currentTetromino = m_nextTetromino;
  m_nextTetromino = selectTetromino();
  emit nextTetrominoChanged(getNextTetrominoImageUrl());

  connect(m_currentTetromino.get(), &Tetromino::landed, this,
          &Tetrion::handleTetrominoLanding);

  m_currentTetromino->drawOn(m_playfield);

  m_ghostTetromino.emplace(*(m_currentTetromino.get()), QColor {0x0e001f});
  m_ghostTetromino->drawOn(m_playfield);
}


void Tetrion::dropTetromino()
{
  m_currentTetromino->moveDown(m_playfield);
}


void Tetrion::checkGameOver()
{
  const int playfieldColumnCount = m_playfield.columnCount();
  for (int i = 0; i < playfieldColumnCount; ++i) {
    const Index index {1, i};
    if (m_playfield.hasBlockAt(index) &&
        m_playfield.getBlock(index).getType() == Block::Type::Landed) {
      m_keyboardEventHandler.pause(true);
      m_tetrominoDropTimer.stop();
      emit gameOver();
      break;
    }
  }
}


shared_ptr<Tetromino> Tetrion::selectTetromino()
{
  if (m_bag.empty()) {
    fillBag();
  }

  const unsigned long index {rand() % m_bag.size()};
  shared_ptr<Tetromino> tetromino = m_bag[index];
  m_bag.erase(m_bag.begin() + index);
  return tetromino;
}


void Tetrion::fillBag()
{
  m_bag = {make_shared<Tetromino>(Tetromino::Type::I, QColor {0x00b8d4},
                                  QColor {0x00b8d4}, Index {1, 3}),
           make_shared<Tetromino>(Tetromino::Type::J, QColor {0x304ffe},
                                  QColor {0x304ffe}, Index {0, 3}),
           make_shared<Tetromino>(Tetromino::Type::L, QColor {0xff6d00},
                                  QColor {0xff6d00}, Index {0, 3}),
           make_shared<Tetromino>(Tetromino::Type::O, QColor {0xffd600},
                                  QColor {0xffd600}, Index {0, 4}),
           make_shared<Tetromino>(Tetromino::Type::S, QColor {0x00c853},
                                  QColor {0x00c853}, Index {0, 3}),
           make_shared<Tetromino>(Tetromino::Type::T, QColor {0xaa00ff},
                                  QColor {0xaa00ff}, Index {0, 3}),
           make_shared<Tetromino>(Tetromino::Type::Z, QColor {0xd50000},
                                  QColor {0xd50000}, Index {0, 3})};
}


void Tetrion::increaseLevel()
{
  ++m_level;
  emit levelIncreased();
}


void Tetrion::setSpeed()
{
  int frames;

  switch (m_level) {
    case 1:
      frames = 48;
      break;
    case 2:
      frames = 43;
      break;
    case 3:
      frames = 38;
      break;
    case 4:
      frames = 33;
      break;
    case 5:
      frames = 28;
      break;
    case 6:
      frames = 23;
      break;
    case 7:
      frames = 18;
      break;
    case 8:
      frames = 13;
      break;
    case 9:
      frames = 8;
      break;
    default:
      frames = 6;
  }

  const int millisecond = 1000;
  const double speed = frames / 60.0 * millisecond;
  m_tetrominoDropTimer.setInterval(speed);
}


inline void Tetrion::updateScore(const int clearedRows)
{
  m_score += clearedRows * 10;
  emit scoreChanged(m_score);
}


QUrl Tetrion::getNextTetrominoImageUrl() const
{
  switch (m_nextTetromino->getType()) {
    case Tetromino::Type::I:
      return QUrl {"../resources/images/tetrominoes/Tetromino-I.svg"};
    case Tetromino::Type::J:
      return QUrl {"../resources/images/tetrominoes/Tetromino-J.svg"};
    case Tetromino::Type::L:
      return QUrl {"../resources/images/tetrominoes/Tetromino-L.svg"};
    case Tetromino::Type::O:
      return QUrl {"../resources/images/tetrominoes/Tetromino-O.svg"};
    case Tetromino::Type::S:
      return QUrl {"../resources/images/tetrominoes/Tetromino-S.svg"};
    case Tetromino::Type::T:
      return QUrl {"../resources/images/tetrominoes/Tetromino-T.svg"};
    case Tetromino::Type::Z:
      return QUrl {"../resources/images/tetrominoes/Tetromino-Z.svg"};
  }
}


void initRandomTetrominoGenerator()
{
  srand(time(nullptr));
}


void setUpKeyboardEventHandler(KeyboardEventHandler &keyboardEventHandler,
                               Tetrion &tetrion)
{
  constexpr array<Key, 6> tetrominoMovementKeys = {Key_S, Key_A, Key_D,
                                                   Key_Q, Key_E, Key_Space};
  for (const Key &key : tetrominoMovementKeys) {
    keyboardEventHandler.addKey(key, KeyEvent::Type::KeyPress);
  }

  keyboardEventHandler.addCallback(
      [&tetrion](const Key key, const KeyEvent::Type type) -> void {
        return tetrion.processInput(key, type);
      });
}
