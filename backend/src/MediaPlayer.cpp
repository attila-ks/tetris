#include "../headers/MediaPlayer.h"

using namespace std;

MediaPlayer::MediaPlayer(string_view media) :
  m_qMediaPlayer {},
  m_qAudioOutput {}
{
  m_qMediaPlayer.setAudioOutput(&m_qAudioOutput);
  m_qMediaPlayer.setSource(QUrl::fromLocalFile(media.data()));
}


void MediaPlayer::setVolume(const float volume)
{
  m_qAudioOutput.setVolume(volume);
}


void MediaPlayer::play()
{
  m_qMediaPlayer.play();
}


void MediaPlayer::setLoops(const int loops)
{
  m_qMediaPlayer.setLoops(loops);
}


void MediaPlayer::pause()
{
  m_qMediaPlayer.pause();
}


void MediaPlayer::stop()
{
  m_qMediaPlayer.stop();
}
