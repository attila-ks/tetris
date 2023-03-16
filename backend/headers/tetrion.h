#ifndef TETRION_H
#define TETRION_H

#include "KeyboardEventHandler.h"
#include "Settings.h"
#include "tetrisboard.h"
#include "tetromino.h"
#include <QObject>
#include <QTimer>

class Tetrion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const TetrisBoard *tetrisBoard READ getTetrisBoard CONSTANT)

  public:
    explicit Tetrion(QObject *parent = nullptr);

    const TetrisBoard *getTetrisBoard() const;

    Q_INVOKABLE void startGame();

    void processInput(const Key key, const KeyEvent::Type type);

  private slots:
    void spawnTetromino();
    void dropTetromino();

  private:
    std::shared_ptr<Tetromino> selectTetromino();
    void fillBag();

  private:
    TetrisBoard m_tetrisBoard;
    std::vector<std::shared_ptr<Tetromino>> m_bag;
    std::shared_ptr<Tetromino> m_currentTetromino;
    QTimer m_tetrominoDropTimer;
    Settings m_settings;
    KeyboardEventHandler m_keyboardEventHandler;
};

#endif
