#include "../headers/KeyboardEventHandler.h"
#include <qguiapplication.h>

using namespace std;

KeyboardEventHandler::KeyboardEventHandler() :
  QObject {nullptr},
  m_filteredKeys {},
  m_callbacks {},
  m_pauseEventHandle {false}
{
  QGuiApplication::instance()->installEventFilter(this);
}


void KeyboardEventHandler::addKey(const Key key, const KeyEvent keyEvent)
{
  m_filteredKeys[key] = keyEvent;
}


void KeyboardEventHandler::addCallback(
    function<void(const Key key, const KeyEvent keyEvent)> callback)
{
  m_callbacks.push_back(callback);
}


void KeyboardEventHandler::pause(const bool value)
{
  m_pauseEventHandle = value;
}


bool KeyboardEventHandler::eventFilter(QObject *obj, QEvent *event)
{
  if (m_pauseEventHandle) {
    return QObject::eventFilter(obj, event);
  }
  if (const QEvent::Type eventType = event->type();
      eventType == QEvent::KeyPress) {
    const QKeyEvent *const keyEvent = static_cast<QKeyEvent *>(event);
    // Is it okay to use `static_cast` here?
    const Key key = static_cast<Key>(keyEvent->key());
    unordered_map<Key, KeyEvent>::const_iterator itr = m_filteredKeys.find(key);

    // FIXME: `KeyEvent` is not checked!
    if (itr != m_filteredKeys.cend()) {
      for (auto &callback : m_callbacks) {
        callback(itr->first, itr->second);
      }
    } else {
      return QObject::eventFilter(obj, event);
    }

    return true;
  } else {
    return QObject::eventFilter(obj, event);
  }

  return false;
}
