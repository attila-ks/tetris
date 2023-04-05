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
    Q_INVOKABLE int getLevel() const;
    Q_INVOKABLE float getLevelProgress() const;

    Q_INVOKABLE void startGame();

    void processInput(const Key key, const KeyEvent::Type type);

  signals:
    void gameOver();
    void levelIncreased();
    void levelProgressed();

  private slots:
    void handleTetrominoLanding();

  private:
    void spawnTetromino();
    void dropTetromino();

    void checkGameOver();

    std::shared_ptr<Tetromino> selectTetromino();
    void fillBag();

    void increaseLevel();
    void setSpeed();

    TetrisBoard m_tetrisBoard;
    std::vector<std::shared_ptr<Tetromino>> m_bag;
    std::shared_ptr<Tetromino> m_currentTetromino;
    QTimer m_tetrominoDropTimer;
    Settings m_settings;
    KeyboardEventHandler m_keyboardEventHandler;
    int m_level;
    float m_levelProgress;
};

#endif
