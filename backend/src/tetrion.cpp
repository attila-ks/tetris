#include "../headers/tetrion.h"

using namespace std;

Tetrion::Tetrion() :
  m_playfield {22, 10, QColor {0x0e001f}}
{
}


const Playfield* Tetrion::getPlayfield() const
{
  return &m_playfield;
}
