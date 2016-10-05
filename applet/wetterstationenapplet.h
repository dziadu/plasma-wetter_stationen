/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  Rafal Lalik rafallalik@gmail.com
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
 */

#ifndef WETTER_STATIONEN_APPLET_H
#define WETTER_STATIONEN_APPLET_H

#include <Plasma/Applet>
#include <QString>

#include "plasma_applet_wetter_stationen_export.h"

/**
 * @class WetterStationenApplet
 *
 * @short Base class for Weather Applets
 */
class WetterStationenApplet : public Plasma::Applet
{
Q_OBJECT

public:
    WetterStationenApplet(QObject *parent, const QVariantList &args);
    ~WetterStationenApplet() override;

public: // Plasma::Applet API
    /**
        * Called once the applet is loaded and added to a Corona.
        */
    void init() override;

    /**
        * Called when config is chnaged
        */
    void configChanged() override;

    QString source() const;

public: // API to be implemented by subclasses
    /**
        * Used by QML config code, so check used keys carefully
        * @return currently used config values
        */
    Q_INVOKABLE virtual QVariantMap configValues() const;

public Q_SLOTS: // API to be implemented by subclasses
    /**
        * Called when config is accepted
        * @param changedConfigValues config values which got changed
        */
    virtual void saveConfig(const QVariantMap& changedConfigValues);

private:
    int m_updateInterval;
    QString m_source;
};

#endif
