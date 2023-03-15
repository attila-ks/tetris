#include "../headers/KeyboardEventHandler.h"
#include <qguiapplication.h>

using namespace std;

KeyboardEventHandler::KeyboardEventHandler(QObject* parent) :
  QObject {parent},
  m_filteredKeys {},
  m_callbacks {}
{
  QGuiApplication::instance()->installEventFilter(this);
}


void KeyboardEventHandler::addKey(const Key key, const KeyEvent::Type type)
{
  m_filteredKeys[key] = type;
}


void KeyboardEventHandler::addCallback(
    function<void(const Key key, const KeyEvent::Type type)> callback)
{
  m_callbacks.push_back(callback);
}


bool KeyboardEventHandler::eventFilter(QObject* obj, QEvent* event)
{
  if (const QEvent::Type eventType = event->type();
      eventType == QEvent::KeyPress)
  {
    const QKeyEvent* const keyEvent = static_cast<QKeyEvent*>(event);
    // Is it okay to use `std::static_cast` here?
    const Key key = static_cast<Key>(keyEvent->key());
    map<Key, KeyEvent::Type>::const_iterator itr = m_filteredKeys.find(key);

    // FIXME: Check the `KeyEvent::Type` too!
    if (itr != m_filteredKeys.cend())
    {
      for (auto& callback : m_callbacks)
      {
        callback(itr->first, itr->second);
      }
    }
    else
    {
      return QObject::eventFilter(obj, event);
    }

    return true;
  }
  else
  {
    return QObject::eventFilter(obj, event);
  }

  return false;
}
