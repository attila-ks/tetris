#include "../headers/FileError.h"

using namespace std;

FileError::FileError(string_view message) :
  m_message {message}
{
}


const char *FileError::what() const noexcept
{
  return m_message.data();
}
