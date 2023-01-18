#ifndef TETRION_H
#define TETRION_H

#include "playfield.h"
#include "tetromino.h"
#include <QObject>
#include <QTimer>
#include <vector>

class Tetrion : public QObject
{
    Q_OBJECT
    // Can the compiler use RVO for `getPlayfield`?
    Q_PROPERTY(const Playfield* playfield READ getPlayfield CONSTANT)

  public:
    Tetrion(QObject* parent = nullptr);

    const Playfield* getPlayfield() const;

    Q_INVOKABLE void startGame();

  private:
    void spawnTetromino();
    Tetromino selectTetromino();
    void fillBag();

  private slots:
    void dropTetromino();

  private:
    Playfield m_playfield;
    std::vector<Tetromino> m_bag;
    Tetromino m_currentTetromino;
    QTimer m_tetrominoDropTimer;
};

#endif
