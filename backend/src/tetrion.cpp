#include "../headers/tetrion.h"

using namespace std;

// Helper functions:
void initRandomTetrominoGenerator();
// TODO: Consider to turn the next functions into methods of a class!
bool doSavedSettingsExist(const Settings &settings);
void useFallbackSettings(Settings &settings);
void setUpKeyboardEventHandler(KeyboardEventHandler &keyboardEventHandler,
                               const Settings &settings, Tetrion &tetrion);

Tetrion::Tetrion(QObject *parent) :
  QObject {parent},
  m_tetrisBoard {22, 10, QColor {0x0e001f}},
  m_bag {},
  m_currentTetromino {nullptr},
  m_tetrominoDropTimer {},
  m_settings {"./settings"},
  m_keyboardEventHandler {}
{
  initRandomTetrominoGenerator();

  if (!doSavedSettingsExist(m_settings)) {
    useFallbackSettings(m_settings);
  }

  setUpKeyboardEventHandler(m_keyboardEventHandler, m_settings, *this);

  m_tetrominoDropTimer.setInterval(1000);
  connect(&m_tetrominoDropTimer, &QTimer::timeout, this,
          &Tetrion::dropTetromino);
}


const TetrisBoard *Tetrion::getTetrisBoard() const
{
  return &m_tetrisBoard;
}


void Tetrion::startGame()
{
  spawnTetromino();
  m_tetrominoDropTimer.start();
}


void Tetrion::processInput(const Key key, const KeyEvent::Type type)
{
  // TODO: Turn these string literals into class constants!
  // TODO: Consider to call `Settings::getvalue` method only when the settings
  // have changed!
  optional<Key> opt;
  if (opt = m_settings.getValue<Key>("keyboard/move-down");
      opt.has_value() && opt.value() == key) {
    m_currentTetromino->moveDown(m_tetrisBoard);
  } else if (opt = m_settings.getValue<Key>("keyboard/move-left");
             opt.has_value() && opt.value() == key) {
    m_currentTetromino->moveLeft(m_tetrisBoard);
  } else if (opt = m_settings.getValue<Key>("keyboard/move-right");
             opt.has_value() && opt.value() == key) {
    m_currentTetromino->moveRight(m_tetrisBoard);
  } else if (opt = m_settings.getValue<Key>("keyboard/rotate-left");
             opt.has_value() && opt.value() == key) {
    m_currentTetromino->rotateLeft(m_tetrisBoard);
  } else if (opt = m_settings.getValue<Key>("keyboard/rotate-right");
             opt.has_value() && opt.value() == key) {
    m_currentTetromino->rotateRight(m_tetrisBoard);
  } else if (opt = m_settings.getValue<Key>("keyboard/hard-drop");
             opt.has_value() && opt.value() == key) {
    m_currentTetromino->hardDrop(m_tetrisBoard);
  }
}


void Tetrion::spawnTetromino()
{
  m_currentTetromino = selectTetromino();

  connect(m_currentTetromino.get(), &Tetromino::landed, this,
          &Tetrion::checkGameOver);
  connect(m_currentTetromino.get(), &Tetromino::landed, this,
          &Tetrion::spawnTetromino);

  m_currentTetromino->drawOn(m_tetrisBoard);
}


void Tetrion::dropTetromino()
{
  m_currentTetromino->moveDown(m_tetrisBoard);
}


void Tetrion::checkGameOver()
{
  const int tetrisBoardColumnCount = m_tetrisBoard.columnCount();
  for (int i = 0; i < tetrisBoardColumnCount; ++i) {
    if (m_tetrisBoard.hasBlockAt({1, i})) {
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
  m_bag = {
    make_shared<Tetromino>(Tetromino::Type::I, QColor {0x00b8d4}, Index {1, 3}),
    make_shared<Tetromino>(Tetromino::Type::J, QColor {0x304ffe}, Index {0, 3}),
    make_shared<Tetromino>(Tetromino::Type::L, QColor {0xff6d00}, Index {0, 3}),
    make_shared<Tetromino>(Tetromino::Type::O, QColor {0xffd600}, Index {0, 4}),
    make_shared<Tetromino>(Tetromino::Type::S, QColor {0x00c853}, Index {0, 3}),
    make_shared<Tetromino>(Tetromino::Type::T, QColor {0xaa00ff}, Index {0, 3}),
    make_shared<Tetromino>(Tetromino::Type::Z, QColor {0xd50000}, Index {0, 3})};
}


void initRandomTetrominoGenerator()
{
  srand(time(nullptr));
}


bool doSavedSettingsExist(const Settings &settings)
{
  constexpr array<string_view, 6> keys {"keyboard/move-down",
                                        "keyboard/move-left",
                                        "keyboard/move-right",
                                        "keyboard/rotate-left",
                                        "keyboard/rotate-right",
                                        "keyboard/hard-drop"};

  for (string_view key : keys) {
    // TODO: Check if the `key` has `enum Key` value!
    if (!settings.contains(key)) {
      return false;
    }
  }

  return true;
}


void useFallbackSettings(Settings &settings)
{
  settings.beginGroup("keyboard");
  settings.setValue("move-down", Key_S);
  settings.setValue("move-left", Key_A);
  settings.setValue("move-right", Key_D);
  settings.setValue("rotate-left", Key_Q);
  settings.setValue("rotate-right", Key_E);
  settings.setValue("hard-drop", Key_Space);
  settings.endGroup();
}


void setUpKeyboardEventHandler(KeyboardEventHandler &keyboardEventHandler,
                               const Settings &settings, Tetrion &tetrion)
{
  constexpr array<string_view, 6> keys {"keyboard/move-down",
                                        "keyboard/move-left",
                                        "keyboard/move-right",
                                        "keyboard/rotate-left",
                                        "keyboard/rotate-right",
                                        "keyboard/hard-drop"};

  for (string_view key : keys) {
    const optional<Key> opt = settings.getValue<Key>(key);
    keyboardEventHandler.addKey(opt.value(), KeyEvent::Type::KeyPress);
  }

  keyboardEventHandler.addCallback(
      [&tetrion](const Key key, const KeyEvent::Type type) -> void {
        return tetrion.processInput(key, type);
      });
}
