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
#include "wetterstationenapplet.h"

#include <QTimer>

WetterStationenApplet::WetterStationenApplet(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
{
}

WetterStationenApplet::~WetterStationenApplet()
{
}

void WetterStationenApplet::init()
{
    Plasma::Applet::init();

    configChanged();
}

void WetterStationenApplet::saveConfig(const QVariantMap& configChanges)
{
    KConfigGroup cfg = config();

    // data source
    if (configChanges.contains(QStringLiteral("updateInterval"))) {
        cfg.writeEntry("updateInterval", configChanges.value(QStringLiteral("updateInterval")).toInt());
    }
    if (configChanges.contains(QStringLiteral("source"))) {
        cfg.writeEntry("source", configChanges.value(QStringLiteral("source")).toString());
    }

    emit configNeedsSaving();
}

void WetterStationenApplet::configChanged()
{
    if (!m_source.isEmpty()) {
    }

    KConfigGroup cfg = config();

    m_updateInterval = cfg.readEntry("updateInterval", 30);
    m_source = cfg.readEntry("source", QString());
    setConfigurationRequired(m_source.isEmpty());
}

QString WetterStationenApplet::source() const
{
    return m_source;
}

QVariantMap WetterStationenApplet::configValues() const
{
    QVariantMap config;

    // data source
    config.insert(QStringLiteral("updateInterval"), m_updateInterval);
    config.insert(QStringLiteral("source"), m_source);

    return config;
}

// needed due to private slots
#include "moc_wetterstationenapplet.cpp"
