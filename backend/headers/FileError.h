#ifndef FILE_ERROR_H
#define FILE_ERROR_H

#include <exception>
#include <string>

class FileError : public std::exception
{
  public:
    FileError(std::string_view message);

    const char *what() const noexcept override;

  private:
    std::string m_message;
};

#endif
