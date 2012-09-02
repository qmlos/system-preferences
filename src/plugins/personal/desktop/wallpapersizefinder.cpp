/****************************************************************************
 * This file is part of System Preferences.
 *
 * Copyright (c) 2011-2012 Pier Luigi Fiorini
 *
 * Author(s):
 *    Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * $BEGIN_LICENSE:GPL$
 *
 * System Preferences is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * System Preferences is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with System Preferences.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

#include <QSet>
#include <QImage>

#include "wallpapersizefinder.h"

static bool sizeGreaterThan(const QSize &s1, const QSize &s2)
{
    return (s1.width() > s2.width()) || (s1.height() > s2.height());
}

WallpaperSizeFinder::WallpaperSizeFinder(const QSize &resolution,
                                         const QDir &imagesDir, QObject *parent)
    : QThread(parent)
    , m_resolution(resolution)
    , m_imagesDir(imagesDir)
{
}

WallpaperSizeFinder::~WallpaperSizeFinder()
{
    wait();
}

void WallpaperSizeFinder::run()
{
    // Check for available resolutions
    QList<QSize> resolutions;
    QSet<QString> suffixes;
    suffixes << "png" << "jpg" << "jpeg" << "svg" << "svgz";
    QFileInfoList fileInfoList = m_imagesDir.entryInfoList(QDir::Files | QDir::Readable);
    foreach(QFileInfo fileInfo, fileInfoList) {
        if (suffixes.contains(fileInfo.suffix().toLower())) {
            // Save resolutions
            QImage image(fileInfo.absoluteFilePath());
            resolutions.append(image.size());
        }
    }

    // Sort resolutions list
    qSort(resolutions.begin(), resolutions.end(), sizeGreaterThan);

    // Find the resolution closest to the screen size
    QSize closestSize;
    for (int i = 0; i < resolutions.size(); i++) {
        QSize currentSize = resolutions.at(i);
        QSize size1(qAbs(currentSize.width() - m_resolution.width()),
                    qAbs(currentSize.height() - m_resolution.height()));
        QSize size2(qAbs(closestSize.width() - m_resolution.width()),
                    qAbs(closestSize.height() - m_resolution.height()));
        if ((size1.width() < size2.width()) && (size1.height() < size2.height()))
            closestSize = currentSize;
    }

    if (closestSize.isValid())
        emit sizeFound(closestSize);
}

#include "moc_wallpapersizefinder.cpp"
