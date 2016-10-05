/*!
  * My script to displa and refresh images from http://http://wetterstationen.meteomedia.de
  *
  * Juan de Hoyos <juanmahv@gmail.com>
  * 02.May.2014
  */
import QtQuick 2.1
import QtQuick.Layouts 1.0

import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents

import pl.rlalik.cachedimg 1.0

Item {
    id:root

    function callback() {
       cimg.refresh()
    }

    Timer {
        running: true
        repeat: true
        triggeredOnStart: true
        interval: plasmoid.configuration.updateInterval * 100
        onTriggered: callback()
    }

    Plasmoid.fullRepresentation: Item {
        id: fullRoot
        Layout.minimumWidth: img.width
        Layout.minimumHeight: img.height
        Layout.preferredWidth: Layout.minimumWidth * 1.5
        Layout.preferredHeight: Layout.minimumHeight * 1.5

        Image {
            id: img
            source: cimg.local
        }
    }

    CachedImg {
        id: cimg
        source: plasmoid.configuration.remoteImage
    }
}
