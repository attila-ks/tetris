#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include <QKeyEvent>

// Is it okay to use namespace instead of class?
namespace KeyEvent
{
  enum Type { KeyPress = QEvent::Type::KeyPress };
};

#endif
