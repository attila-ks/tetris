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
    Tetrion();
    ~Tetrion();

    const Playfield *getPlayfield() const;
    Q_INVOKABLE int getLevel() const;
    Q_INVOKABLE float getLevelProgress() const;
    Q_INVOKABLE int getScore() const;
    Q_INVOKABLE int getHighScore() const;

    Q_INVOKABLE void startGame(const bool load);

    void processInput(const Key key, const KeyEvent keyEvent);

  signals:
    void gameOver();
    void levelIncreased(int level);
    void levelProgressed(float levelProgress);
    void nextTetrominoChanged(QUrl nextTetrominoImageUrl);
    void scoreChanged(int score);
    void highScoreChanged(int highScore);

  private slots:
    void handleTetrominoLanding();

  private:
    void spawnTetromino();
    void dropTetromino();

    void checkGameOver();

    Tetromino selectTetromino();
    void fillBag();

    void setLevel(const int level);
    void setLevelProgress(const float levelProgress);
    void calculateSpeed();

    void setScore(const int score);
    void setHighScore(const int highScore);

    QUrl getNextTetrominoImageUrl() const;

    void save();
    template <typename T>
    static void save(std::string_view fileName, const T &t);

    void load();
    template <typename T>
    static void load(std::string_view fileName, T &t);

    void clear();

    Playfield m_playfield {QColor {0x0e001f}};
    std::vector<Tetromino> m_bag;
    Tetromino m_currentTetromino;
    Tetromino m_nextTetromino;
    std::optional<GhostTetromino> m_ghostTetromino {std::nullopt};
    QTimer m_tetrominoDropTimer;
    KeyboardEventHandler m_keyboardEventHandler;
    int m_level {1};
    float m_levelProgress {0.0f};
    int m_score {0};
    int m_highScore {0};
    bool m_isGameOver {false};
};

#endif
