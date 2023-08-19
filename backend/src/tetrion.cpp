#include "../headers/tetrion.h"
#include "../headers/FileError.h"
#include <fstream>
#include <iostream>

using namespace std;

// Helper functions:
void initRandomTetrominoGenerator();
void setUpKeyboardEventHandler(KeyboardEventHandler &keyboardEventHandler,
                               Tetrion &tetrion);

Tetrion::Tetrion() :
  QObject {nullptr}
{
  initRandomTetrominoGenerator();

  setUpKeyboardEventHandler(m_keyboardEventHandler, *this);

  calculateSpeed();
  connect(&m_tetrominoDropTimer, &QTimer::timeout, this,
          &Tetrion::dropTetromino);

  loadHighScore();
}


Tetrion::~Tetrion()
{
  save();
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


int Tetrion::getScore() const
{
  return m_score;
}


int Tetrion::getHighScore() const
{
  return m_highScore;
}


void Tetrion::startGame()
{
  // FIXME: State is unnecessarily cleared for the first game!
  clear();

  m_nextTetromino = selectTetromino();

  spawnTetromino();
  m_keyboardEventHandler.pause(false);
  m_tetrominoDropTimer.start();
}


void Tetrion::loadGame()
{
  // FIXME: State is unnecessarily cleared for the first game!
  clear();

  load();
  spawnTetromino();
  m_keyboardEventHandler.pause(false);
  m_tetrominoDropTimer.start();
}


void Tetrion::resumeGame()
{
  m_keyboardEventHandler.pause(false);
  m_tetrominoDropTimer.start();
}


void Tetrion::processInput(const Key key, const KeyEvent keyEvent)
{
  // FIXME: Movement keys are duplicated: here and in the
  // setUpKeyboardEventHandler method!
  bool isTetrominoRotatedOrMovedHorizontally = false;

  if (key == Key_S || key == Key_Down) {
    m_currentTetromino.moveDown(m_playfield);
    if (m_currentTetromino.isLanded()) {
      handleTetrominoLanding();
      // There is no reason to go further in this method.
      return;
    }
  } else if (key == Key_A || key == Key_Left) {
    m_currentTetromino.moveLeft(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_D || key == Key_Right) {
    m_currentTetromino.moveRight(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_Q) {
    m_currentTetromino.rotateLeft(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_E) {
    m_currentTetromino.rotateRight(m_playfield);
    isTetrominoRotatedOrMovedHorizontally = true;
  } else if (key == Key_Space) {
    m_currentTetromino.hardDrop(m_playfield);
  } else if (key == Key_Escape) {
    pauseGame();
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

  if (clearedRows > 0) {
    const float levelProgress = m_levelProgress + clearedRows * 0.1f;
    if (levelProgress >= 1.0f) {
      setLevel(m_level + 1);
      setLevelProgress(levelProgress - 1.0f);
      calculateSpeed();
    } else {
      setLevelProgress(levelProgress);
    }
    setScore(m_score + clearedRows * 10);
    if (m_score > m_highScore) {
      setHighScore(m_score);
    }
  }

  spawnTetromino();
}


void Tetrion::spawnTetromino()
{
  m_currentTetromino = std::move(m_nextTetromino);
  m_nextTetromino = selectTetromino();
  emit nextTetrominoChanged(getNextTetrominoImageUrl());

  m_currentTetromino.drawOn(m_playfield);

  m_ghostTetromino.emplace(m_currentTetromino, QColor {0x0e001f});
  m_ghostTetromino->drawOn(m_playfield);
}


inline void Tetrion::dropTetromino()
{
  m_currentTetromino.moveDown(m_playfield);
  if (m_currentTetromino.isLanded()) {
    handleTetrominoLanding();
  }
}


void Tetrion::checkGameOver()
{
  const int playfieldColumnCount = m_playfield.columnCount();
  for (int i = 0; i < playfieldColumnCount; ++i) {
    if (m_playfield.hasLandedBlockAt(1, i)) {
      m_keyboardEventHandler.pause(true);
      m_tetrominoDropTimer.stop();
      m_isGameOver = true;
      emit gameOver();
      break;
    }
  }
}


void Tetrion::pauseGame()
{
  m_keyboardEventHandler.pause(true);
  m_tetrominoDropTimer.stop();
  emit gamePaused();
}


Tetromino Tetrion::selectTetromino()
{
  if (m_bag.empty()) {
    fillBag();
  }

  const unsigned long index {rand() % m_bag.size()};
  Tetromino tetromino {std::move(m_bag[index])};
  m_bag.erase(m_bag.begin() + index);
  return tetromino;
}


void Tetrion::fillBag()
{
  m_bag = {
      Tetromino(Tetromino::Type::I, QColor {0x00b8d4}, QColor {0x00b8d4}, 1, 3),
      Tetromino(Tetromino::Type::J, QColor {0x304ffe}, QColor {0x304ffe}, 0, 3),
      Tetromino(Tetromino::Type::L, QColor {0xff6d00}, QColor {0xff6d00}, 0, 3),
      Tetromino(Tetromino::Type::O, QColor {0xffd600}, QColor {0xffd600}, 0, 4),
      Tetromino(Tetromino::Type::S, QColor {0x00c853}, QColor {0x00c853}, 0, 3),
      Tetromino(Tetromino::Type::T, QColor {0xaa00ff}, QColor {0xaa00ff}, 0, 3),
      Tetromino(Tetromino::Type::Z, QColor {0xd50000}, QColor {0xd50000}, 0,
                3)};
}


inline void Tetrion::setLevel(const int level)
{
  m_level = level;
  emit levelIncreased(m_level);
}


inline void Tetrion::setLevelProgress(const float levelProgress)
{
  m_levelProgress = levelProgress;
  emit levelProgressed(m_levelProgress);
}


void Tetrion::calculateSpeed()
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

  constexpr int millisecond = 1000;
  const double speed = frames / 60.0 * millisecond;
  m_tetrominoDropTimer.setInterval(speed);
}


inline void Tetrion::setScore(const int score)
{
  m_score = score;
  emit scoreChanged(m_score);
}


inline void Tetrion::setHighScore(const int highScore)
{
  m_highScore = highScore;
  emit highScoreChanged(m_highScore);
}


QUrl Tetrion::getNextTetrominoImageUrl() const
{
  switch (m_nextTetromino.getType()) {
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


void Tetrion::save()
{
  try {
    // `m_highScore` is saved separately because we want to load it in a new
    // game too.
    save("highScore.txt", m_highScore);

    if (m_isGameOver) {
      return;
    }

    m_tetrominoDropTimer.stop();

    save("playfield.txt", m_playfield);
    save("currentTetromino.txt", m_currentTetromino);
    // `m_nextTetromino` is intentionally not saved, a new one will be randomly
    // selected the next time the application runs.

    ofstream ofstream {"tetrionMisc.txt"};
    if (ofstream) {
      ofstream << m_level << ' ' << m_levelProgress << ' ' << m_score;
    }

    if (!ofstream) {
      throw FileError {
          "An error occurred while saving to file: 'tetrionMisc.txt'"};
    }
  } catch (const FileError &e) {
    cerr << "ERROR: " << e.what();
  }
}


template <typename T>
void Tetrion::save(string_view fileName, const T &t)
{
  ofstream ofstream {fileName.data()};
  if (!ofstream) {
    throw FileError {string {"Cannot open file: '"} + fileName.data() + "'"};
  }

  ofstream << t;

  if (!ofstream) {
    throw FileError {string {"An error occured while saving to file: '"} +
                     fileName.data() + "'"};
  }
}


void Tetrion::load()
{
  try {
    load("playfield.txt", m_playfield);

    // The previously saved `m_currentTetromino` is loaded as `m_nextTetromino`,
    // so the `::startGame` method can be called without code modification.
    load("currentTetromino.txt", m_nextTetromino);

    ifstream ifstream {"tetrionMisc.txt"};
    if (ifstream) {
      int level;
      float levelProgress;
      int score;
      ifstream >> level >> levelProgress >> score;
      setLevel(level);
      setLevelProgress(levelProgress);
      setScore(score);
    }

    if (!ifstream) {
      throw FileError {
          "An error occurred while reading file: 'tetrionMisc.txt'"};
    }

  } catch (const FileError &e) {
    cerr << "ERROR: " << e.what();
    clear();
    m_nextTetromino = selectTetromino();
  }
}


void Tetrion::loadHighScore()
{
  try {
    int highScore = 0;
    this->load("highScore.txt", highScore);
    setHighScore(highScore);
  } catch (const FileError &e) {
    cerr << "ERROR: " << e.what();
  }
}


template <typename T>
void Tetrion::load(string_view fileName, T &t)
{
  ifstream ifstream {fileName.data()};
  if (!ifstream) {
    throw FileError {string {"Cannot open file: '"} + fileName.data() + "'"};
  }

  ifstream >> t;
  if (!ifstream.eof()) {
    throw FileError {string {"An error occurred while reading file: '"} +
                     fileName.data() + "'"};
  }
}


inline void Tetrion::clear()
{
  m_playfield.clear();
  m_nextTetromino.clear();
  setLevel(1);
  setLevelProgress(0.0f);
  setScore(0);
  m_isGameOver = false;
}


inline void initRandomTetrominoGenerator()
{
  srand(time(nullptr));
}


void setUpKeyboardEventHandler(KeyboardEventHandler &keyboardEventHandler,
                               Tetrion &tetrion)
{
  constexpr array<Key, 9> tetrominoMovementKeys = {
      Key_S,     Key_Down, Key_A, Key_Left, Key_D,
      Key_Right, Key_Q,    Key_E, Key_Space};
  for (const Key &key : tetrominoMovementKeys) {
    keyboardEventHandler.addKey(key, KeyEvent::KeyPress);
  }

  keyboardEventHandler.addKey(Key_Escape, KeyEvent::KeyPress);

  keyboardEventHandler.addCallback(
      [&tetrion](const Key key, const KeyEvent keyEvent) {
        tetrion.processInput(key, keyEvent);
      });
}
