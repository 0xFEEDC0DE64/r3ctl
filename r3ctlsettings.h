#pragma once

// Qt includes
#include <QSettings>

class R3CtlSettings : public QSettings
{
    Q_OBJECT
    Q_PROPERTY(QString theme READ theme WRITE setTheme NOTIFY themeChanged)

public:
    using QSettings::QSettings;

    QString theme() const;
    bool setTheme(const QString &theme);

Q_SIGNALS:
    void saveErrorOccured();

    void themeChanged(const QString &theme);

private:
    static const QString m_theme;
};
