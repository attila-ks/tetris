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
  const QUrl url(u"qrc:/tetris/frontend/main.qml"_qs);

  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);

  engine.load(url);

  return app.exec();
}
