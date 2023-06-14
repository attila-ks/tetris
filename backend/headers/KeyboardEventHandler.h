#ifndef KEYBOARD_EVENT_HANDLER_H
#define KEYBOARD_EVENT_HANDLER_H

#include "Key.h"
#include "KeyEvent.h"

class KeyboardEventHandler : public QObject
{
    Q_OBJECT

  public:
    KeyboardEventHandler();

    void addKey(const Key key, const KeyEvent keyEvent);

    void addCallback(
        std::function<void(const Key key, const KeyEvent keyEvent)> callback);

    void pause(const bool value);

  protected:
    bool eventFilter(QObject *obj, QEvent *event);

  private:
    // FIXME: Cannot store the same `Key` with different `KeyEvent::Type`!
    std::map<Key const, KeyEvent> m_filteredKeys;
    std::vector<std::function<void(Key, KeyEvent)>> m_callbacks;
    bool m_pauseEventHandle;
};

#endif
