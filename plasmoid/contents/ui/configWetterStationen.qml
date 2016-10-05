/*
 * Copyright 2016  Friedrich W. H. Kossebau <kossebau@kde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0
import QtQuick.Controls 1.0 as QtControls
import QtQuick.Layouts 1.0

import org.kde.plasma.components 2.0 as PlasmaComponents

import pl.rlalik.cachedimg 1.0

ColumnLayout {
    id: generalConfigPage

    signal configurationChanged
    property alias cfg_updateInterval: updateIntervalSpin.value
    property alias cfg_remoteImage: locationDisplay.text

    function validateLocation() {
        var source_url = img.buildSource(searchStringEdit.text);
        locationDisplay.text = source_url;
//         img.setSource(source_url);
//         img.setSource(source_url);
//         img.refresh();
//         plasmoid.configuration.updateInterval = updateIntervalSpin.value;
//         plasmoid.configuration.remoteImage = searchStringEdit.text;
    }

//     Component.onCompleted: {
//         updateIntervalSpin.value = plasmoid.configuration.updateInterval;
//         locationDisplay.text = ""
//     }

    GridLayout {
        columns: 2

        QtControls.Label {
            Layout.row: 0
            Layout.column: 0
            Layout.alignment: Qt.AlignRight
            text: i18n("Station ID:")
        }

        QtControls.Label {
            id: locationDisplay
            Layout.row: 0
            Layout.column: 1
            Layout.fillWidth: true
            elide: Text.ElideRight

            function setLocation(location) {
                locationDisplay.text = location || "-";
            }
        }

        RowLayout {
            Layout.row: 1
            Layout.column: 1
            Layout.fillWidth: true

            QtControls.TextField {
                id: searchStringEdit
                Layout.fillWidth: true
                text: "098370"
            }

            Item {
                Layout.preferredHeight: Math.max(searchButton.height, searchStringEdit.height)
                Layout.preferredWidth: Layout.preferredHeight

                PlasmaComponents.BusyIndicator {
                    id: busy
                    anchors.fill: parent
                    visible: false
                }
            }

            QtControls.Button {
                id: searchButton
                text: i18n("Validate")
                enabled: !!searchStringEdit.text
                onClicked: validateLocation();
            }
        }

        QtControls.Label {
            Layout.row: 3
            Layout.column: 0
            Layout.alignment: Qt.AlignRight
            text: i18n("Update every:")
        }

        QtControls.SpinBox {
            id: updateIntervalSpin
            Layout.row: 3
            Layout.column: 1
            Layout.minimumWidth: units.gridUnit * 8
            suffix: i18n(" min")
            stepSize: 5
            minimumValue: 30
            maximumValue: 3600
            onValueChanged: generalConfigPage.configurationChanged();
        }
    }

    CachedImg {
        id: img
    }
}
