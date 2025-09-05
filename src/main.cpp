#include <QApplication>
#include <QStyleFactory>
#include <QIcon>
#include <QFile>
#include "Frontend/Windows/MainWindow.h"


int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);
    
    
    app.setApplicationName("Multimedia Library");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("MultimediaLibrary");
    
    app.setWindowIcon(QIcon(":/icons/appicon.svg"));
    
    
    app.setStyle(QStyleFactory::create("Fusion"));
    
    QFile styleFile(":/styles/dark.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        app.setStyleSheet(QString::fromUtf8(styleFile.readAll()));
        styleFile.close();
    }
    
    
    MainWindow mainWindow;
    mainWindow.show();
    
    
    return app.exec();
}
