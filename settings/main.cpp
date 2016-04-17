/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2011-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL2+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QtCore/QFileInfo>
#include <QtCore/QLoggingCategory>
#include <QtCore/QStandardPaths>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>

#include "config.h"
#include "cmakedirs.h"
#include "pluginmanager.h"
#include "prefletsproxymodel.h"

Q_DECLARE_LOGGING_CATEGORY(PREFERENCES)
Q_LOGGING_CATEGORY(PREFERENCES, "hawaii.systempreferences")

static void loadQtTranslations()
{
#ifndef QT_NO_TRANSLATION
    QString locale = QLocale::system().name();

    // Load Qt translations
    QTranslator *qtTranslator = new QTranslator(qApp);
    if (qtTranslator->load(QStringLiteral("qt_%1").arg(locale), QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        qApp->installTranslator(qtTranslator);
    } else {
        delete qtTranslator;
    }
#endif
}

int main(int argc, char *argv[])
{
    // Setup application
    QGuiApplication app(argc, argv);
    app.setApplicationName(QLatin1String("System Preferences"));
    app.setApplicationVersion(QLatin1String(SYSTEMPREFERENCES_VERSION_STRING));
    app.setOrganizationDomain(QLatin1String("hawaii.org"));
    app.setOrganizationName(QLatin1String("Hawaii"));

    // Register types
    qmlRegisterType<Plugin>();
    qmlRegisterType<PluginManager>("org.hawaiios.systempreferences", 0, 1, "PluginManager");
    //qmlRegisterType<PrefletsProxyModel>("org.hawaiios.systempreferences", 0, 1, "PrefletsProxyModel");

    // Find plugin
    const QString plugin = QLatin1String("org.hawaiios.systempreferences");
    QString fileName = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                              QStringLiteral("hawaii-system-preferences/shells/%1/main.qml").arg(plugin));
    if (fileName.isEmpty()) {
        qCWarning(PREFERENCES) << "Failed to find" << plugin << "plugin, aborting...";
        return 1;
    }

    // Load translations
    loadQtTranslations();

    // Setup QML engine and show the main window
    qCDebug(PREFERENCES) << "Loading:" << fileName;
    QQmlApplicationEngine engine(QUrl::fromLocalFile(fileName));
    QQuickWindow *window = qobject_cast<QQuickWindow *>(engine.rootObjects().at(0));
    window->show();

    return app.exec();
}
