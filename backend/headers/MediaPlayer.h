#ifndef MEDIA_PLAYER_H
#define MEDIA_PLAYER_H

#include <QAudioOutput>
#include <QMediaPlayer>

class MediaPlayer
{
  public:
    enum Loops { Infinite = QMediaPlayer::Infinite };

    MediaPlayer(std::string_view media);
    virtual ~MediaPlayer() = default;

    void setVolume(const float volume);

    void setLoops(const int loops);

    void play();
    void pause();
    void stop();

  private:
    QMediaPlayer m_qMediaPlayer;
    QAudioOutput m_qAudioOutput;
};

#endif
