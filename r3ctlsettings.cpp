#include "r3ctlsettings.h"

const QString R3CtlSettings::m_theme("theme");

QString R3CtlSettings::theme() const
{
    return value(m_theme).toString();
}

bool R3CtlSettings::setTheme(const QString &theme)
{
    if(this->theme() == theme)
        return true;

    if(theme.isEmpty())
        remove(m_theme);
    else
        setValue(m_theme, theme);

    sync();

    const auto success = status() == QSettings::NoError;
    if(success)
        Q_EMIT themeChanged(theme);
    else
        Q_EMIT saveErrorOccured();

    return success;
}
