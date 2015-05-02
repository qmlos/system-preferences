/****************************************************************************
 * This file is part of Hawaii.
 *
 * Copyright (C) 2013-2015 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
 *
 * Author(s):
 *    Pier Luigi Fiorini
 *
 * $BEGIN_LICENSE:LGPL2.1+$
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * $END_LICENSE$
 ***************************************************************************/

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.0
import org.hawaii.settings 0.2

ColumnLayout {
    Settings {
        id: keyboardSettings
        schema.id: "org.hawaii.desktop.peripherals.keyboard"
        schema.path: "/org/hawaii/desktop/peripherals/keyboard/"
    }

    Settings {
        id: uiSettings
        schema.id: "org.hawaii.desktop.interface"
        schema.path: "/org/hawaii/desktop/interface/"
    }

    GroupBox {
        id: repeatKeysGroup
        title: qsTr("Repeat Keys")
        checkable: true
        onCheckedChanged: keyboardSettings.repeat = checked

        GridLayout {
            rows: 2
            columns: 4

            /*
             * Delay
             */

            Label {
                text: qsTr("Delay:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Short")
                scale: 0.82999999999999996
            }

            Slider {
                id: inputIntervalSlider
                minimumValue: 0
                maximumValue: 1000
                onValueChanged: keyboardSettings.repeatInterval = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Long")
                scale: 0.82999999999999996
            }

            /*
             * Speed
             */

            Label {
                text: qsTr("Speed:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Slow")
                scale: 0.82999999999999996
            }

            Slider {
                id: autoRepeatRateSlider
                minimumValue: 0
                maximumValue: 1000
                onValueChanged: keyboardSettings.delay = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }
        }
    }

    GroupBox {
        id: cursorBlinkingGroup
        title: qsTr("Cursor Blinking")
        checkable: true
        onCheckedChanged: uiSettings.cursorBlink = checked

        GridLayout {
            rows: 2
            columns: 4

            /*
             * Blink Time
             */

            Label {
                text: qsTr("Speed:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Slow")
                scale: 0.82999999999999996
            }

            Slider {
                id: cursorFlashTimeSlider
                minimumValue: 100
                maximumValue: 2500
                onValueChanged: uiSettings.cursorBlinkTime = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }

            /*
             * Blink Timeout
             */

            Label {
                text: qsTr("Speed:")

                Layout.alignment: Qt.AlignRight
            }

            Label {
                text: qsTr("Slow")
                scale: 0.82999999999999996
            }

            Slider {
                id: cursorFlashTimeoutSlider
                minimumValue: 1
                maximumValue: 2147483647
                onValueChanged: uiSettings.cursorBlinkTimeout = maximumValue - value

                Layout.fillWidth: true
            }

            Label {
                text: qsTr("Fast")
                scale: 0.82999999999999996
            }
        }
    }

    Item {
        Layout.fillHeight: true
    }
}