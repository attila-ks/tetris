#ifndef KEYBOARD_EVENT_HANDLER_H
#define KEYBOARD_EVENT_HANDLER_H

#include "Key.h"
#include "KeyEvent.h"

class KeyboardEventHandler : public QObject
{
    Q_OBJECT

  public:
    explicit KeyboardEventHandler(QObject* parent = nullptr);

    void addKey(const Key key, const KeyEvent::Type type);

    // Should the method accept a reference to `std::function`?
    void addCallback(
        std::function<void(const Key key, const KeyEvent::Type type)> callback);

  protected:
    bool eventFilter(QObject* obj, QEvent* event);

  private:
    // FIXME: Cannot store the same `Key` with different `KeyEvent::Type`!
    std::map<Key const, KeyEvent::Type> m_filteredKeys;
    std::vector<std::function<void(Key, KeyEvent::Type)>> m_callbacks;
};

#endif
