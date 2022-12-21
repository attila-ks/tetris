#ifndef TETRION_H
#define TETRION_H

#include "playfield.h"
#include <QObject>

class Tetrion : public QObject
{
    Q_OBJECT
    // Can the compiler use RVO for `getPlayfield`?
    Q_PROPERTY(const Playfield* playfield READ getPlayfield CONSTANT)

  public:
    Tetrion();

    const Playfield* getPlayfield() const;

  private:
    Playfield m_playfield;
};

#endif
