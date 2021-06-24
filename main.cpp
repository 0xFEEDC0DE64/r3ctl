#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfo>
#include <QMessageBox>

#include "mainwindow.h"
#include "r3ctlsettings.h"

namespace {
bool loadTheme(R3CtlSettings &settings);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qSetMessagePattern(QStringLiteral("%{time dd.MM.yyyy HH:mm:ss.zzz} "
                                      "["
                                      "%{if-debug}D%{endif}"
                                      "%{if-info}I%{endif}"
                                      "%{if-warning}W%{endif}"
                                      "%{if-critical}C%{endif}"
                                      "%{if-fatal}F%{endif}"
                                      "] "
                                      "%{function}(): "
                                      "%{message}"));

    QCoreApplication::setOrganizationDomain(QStringLiteral("brunner.ninja"));
    QCoreApplication::setOrganizationName(QStringLiteral("db-software"));
    QCoreApplication::setApplicationName(QStringLiteral("r3ctl"));
    QCoreApplication::setApplicationVersion(QStringLiteral("1.0"));

    R3CtlSettings settings{&app};

    loadTheme(settings);

    MainWindow mainWindow{settings};
    mainWindow.show();

    return app.exec();
}

namespace {
bool loadTheme(R3CtlSettings &settings)
{
    qDebug() << "Loading theme...";

    if(settings.theme().isEmpty())
        return true;

    auto themePath = QDir{QDir{QCoreApplication::applicationDirPath()}.absoluteFilePath(QStringLiteral("themes"))}.absoluteFilePath(settings.theme());

    QFile file{themePath + ".qss"};

    if(!file.exists())
    {
        QMessageBox::warning(nullptr, QCoreApplication::translate("main", "Could not load theme!"),
                             QCoreApplication::translate("main", "Could not load theme!") + "\n\n" +
                             QCoreApplication::translate("main", "Theme file does not exist!"));
        return false;
    }

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(nullptr, QCoreApplication::translate("main", "Could not load theme!"),
                             QCoreApplication::translate("main", "Could not load theme!") + "\n\n" +
                             file.errorString());
        return false;
    }

    QTextStream textStream(&file);
    qApp->setStyleSheet(textStream.readAll().replace(QStringLiteral("@THEME_RESOURCES@"), themePath));

    return true;
}
}
