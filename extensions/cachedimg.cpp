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

#include "cachedimg.h"

#include <QCryptographicHash>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <iostream>

CachedImg::CachedImg(QObject *parent)
    : QObject(parent), manager(nullptr)
{
}

CachedImg::~CachedImg()
{
}

QUrl CachedImg::source() const
{
    return m_source;
}

QString CachedImg::getLocal() const
{
    std::cout << "get_local = " << (QDir::tempPath() + "/" + m_local).toStdString() << std::endl;
    return QDir::tempPath() + "/" + m_local;
}

void CachedImg::setSource(const QUrl & source)
{
    if (m_source == source)
        return;

    m_source = source;

    QByteArray ba(m_source.toString().toStdString().c_str());
    m_local = QString(QCryptographicHash::hash(ba, QCryptographicHash::Md5).toHex());

    std::cout << "remote = " << m_source.toString().toStdString() << std::endl;
    std::cout << "local = " << m_local.toStdString() << std::endl;
    emit sourceChanged(source);
    emit localChanged(m_local);
}

bool CachedImg::refresh()
{
    if (m_source.isEmpty())
        return false;

    if (!manager)
    {
        manager = new QNetworkAccessManager(this);

        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));
    }

    m_updating = true;
    manager->get(QNetworkRequest(m_source));

    return true;
}


void CachedImg::replyFinished(QNetworkReply* reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();;
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

        QString tmp_file = QDir::tempPath() + "/" + m_local;

        qDebug() << "TmpFile = " << tmp_file << "\n";

        QFile *file = new QFile(tmp_file);

        if(file->open(QFile::WriteOnly | QFile::Truncate))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();

            emit localRefreshed();
        }
        delete file;
    }

    m_updating = false;
    reply->deleteLater();
}


QDateTime CachedImg::last_refresh() const
{
    QFileInfo fileinfo(m_local);
    return fileinfo.lastModified();
}

QString CachedImg::buildSource(const QString& id) const
{
    QString str = "http://wetterstationen.meteomedia.de/messnetz/vorhersagegrafik/%s.png";
    str.replace("%s", id);
    return str;
}
