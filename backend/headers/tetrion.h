#ifndef TETRION_H
#define TETRION_H

#include "tetrisboard.h"
#include "tetromino.h"
#include <QObject>
#include <QTimer>
#include <vector>

class Tetrion : public QObject
{
    Q_OBJECT
    // Can the compiler use RVO for `getTetrisBoard`?
    Q_PROPERTY(const TetrisBoard* tetrisBoard READ getTetrisBoard CONSTANT)

  public:
    Tetrion(QObject* parent = nullptr);
    ~Tetrion();

    const TetrisBoard* getTetrisBoard() const;

    Q_INVOKABLE void startGame();

  private slots:
    void spawnTetromino();
    void dropTetromino();

  private:
    Tetromino* selectTetromino();
    void fillBag();

  private:
    TetrisBoard m_tetrisBoard;
    std::vector<Tetromino*> m_bag;
    Tetromino* m_currentTetromino;
    QTimer m_tetrominoDropTimer;
};

#endif
