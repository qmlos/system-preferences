/****************************************************************************
 * This file is part of Settings.
 *
 * Copyright (C) 2011-2016 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL3+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "plugin.h"
#include "preflet.h"

using namespace Liri::Settings;

MousePlugin::MousePlugin(QObject *parent)
    : PreferencesModulePlugin(parent)
{
}

QStringList MousePlugin::keys() const
{
    return QStringList() << "mouse";
}

PreferencesModule *MousePlugin::create(const QString &key) const
{
    if (key.toLower() == "mouse")
        return new Preflet();
    return 0;
}

#include "moc_plugin.cpp"
