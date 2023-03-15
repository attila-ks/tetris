#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings
{
  public:
    /// @param @p fileName is the name of the settings file.
    Settings(std::string_view fileName);

    void beginGroup(std::string_view prefix);
    void endGroup();

    template <typename T>
    void setValue(std::string_view key, const T& value);

    template <typename T>
    std::optional<T> getValue(std::string_view key) const;

    [[nodiscard]] bool contains(std::string_view key) const;

    void clear();

  private:
    QSettings m_qsettings;
};


inline Settings::Settings(std::string_view fileName) :
  m_qsettings {QString {fileName.data()}, QSettings::NativeFormat}
{
}


inline void Settings::beginGroup(std::string_view prefix)
{
  m_qsettings.beginGroup(prefix);
}


inline void Settings::endGroup()
{
  m_qsettings.endGroup();
}


template <typename T>
void Settings::setValue(std::string_view key, const T& value)
{
  m_qsettings.setValue(key, QVariant::fromValue(value));
}


template <typename T>
std::optional<T> Settings::getValue(std::string_view key) const
{
  QVariant variant = m_qsettings.value(key);
  if (variant.isNull())
  {
    return std::nullopt;
  }

  std::optional<T> opt = variant.value<T>();
  return opt;
}


inline bool Settings::contains(std::string_view key) const
{
  return m_qsettings.contains(key);
}


inline void Settings::clear()
{
  m_qsettings.clear();
}

#endif
