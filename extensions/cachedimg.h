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

#ifndef CACHEDIMG_H
#define CACHEDIMG_H

#include <QDateTime>
#include <QNetworkAccessManager>
#include <QObject>
#include <QString>
#include <QTemporaryFile>
#include <QUrl>

class CachedImg : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CachedImg)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString local READ getLocal NOTIFY localChanged)

public:
    CachedImg(QObject * parent = 0);
    ~CachedImg();

    QUrl source() const;
    Q_INVOKABLE QString getLocal() const;

    Q_INVOKABLE bool refresh();
    Q_INVOKABLE bool updating() const { return m_updating; };
    Q_INVOKABLE QDateTime last_refresh() const;

    Q_INVOKABLE QString buildSource(const QString & id) const;

public slots:
    void setSource(const QUrl & source);

private slots:
    void replyFinished (QNetworkReply *reply);

signals:
    void sourceChanged(QUrl arg);
    void localChanged(QString arg);
    void localRefreshed();

private:
    QUrl m_source;
    QString m_local;
    bool m_updating;

    QNetworkAccessManager *manager;
};

#endif // CACHEDIMG_H
