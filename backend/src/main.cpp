#include "../headers/tetrion.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  qRegisterMetaType<Key>("Key");
  Tetrion tetrion;

  QQmlApplicationEngine engine;
  engine.rootContext()->setContextProperty("tetrion", &tetrion);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
      []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
  engine.loadFromModule("tetris", "Main");

  return app.exec();
}
