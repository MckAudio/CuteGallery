#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QQmlContext>

#include "imagegallerycontroller.h"
#include "imagegallerymodel.h"
#include "fileimageprovider.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Init Model, Controller and Image Provider
    ImageGalleryController *controller = new ImageGalleryController(&engine);
    ImageGalleryModel *model = controller->model();
    // Publish to QML
    QQmlContext *context = engine.rootContext();
    context->setContextProperty("controller", controller);
    context->setContextProperty("model", model);
    engine.addImageProvider(QLatin1String("file"),
                            new FileImageProvider(QQuickImageProvider::Pixmap));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
