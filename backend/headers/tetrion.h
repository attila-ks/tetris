#ifndef TETRION_H
#define TETRION_H

#include "GhostTetromino.h"
#include "KeyboardEventHandler.h"
#include "Playfield.h"
#include <QObject>
#include <QTimer>

class Tetrion : public QObject
{
    Q_OBJECT
    Q_PROPERTY(const Playfield *playfield READ getPlayfield CONSTANT)

  public:
    explicit Tetrion(QObject *parent = nullptr);

    const Playfield *getPlayfield() const;
    Q_INVOKABLE int getLevel() const;
    Q_INVOKABLE float getLevelProgress() const;

    Q_INVOKABLE void startGame();

    void processInput(const Key key, const KeyEvent::Type type);

  signals:
    void gameOver();
    void levelIncreased();
    void levelProgressed();
    void nextTetrominoChanged(QUrl nextTetrominoImageUrl);
    void scoreChanged(int score);

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

    void updateScore(const int clearedRows);

    QUrl getNextTetrominoImageUrl() const;

    Playfield m_playfield;
    std::vector<std::shared_ptr<Tetromino>> m_bag;
    std::shared_ptr<Tetromino> m_currentTetromino;
    std::shared_ptr<Tetromino> m_nextTetromino;
    std::optional<GhostTetromino> m_ghostTetromino;
    QTimer m_tetrominoDropTimer;
    KeyboardEventHandler m_keyboardEventHandler;
    int m_level;
    float m_levelProgress;
    int m_score;
};

#endif
