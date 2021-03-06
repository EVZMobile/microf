/*
 * Copyright (C) 2014 Lucien XU <sfietkonstantin@free.fr>
 *
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *   * The names of its contributors may not be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 */

#include "authhelper.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QSettings>
#include <QtCore/QUuid>
#include <QtCore/QUrlQuery>
#include <QtCore/QDateTime>
#include <QtCore/QLocale>
#include <QtCore/QDebug>

AuthHelper::AuthHelper(QObject *parent)
    : QObject(parent)
{
    QSettings settings;
    m_email = settings.value("General/email").toString();
    m_deviceId = settings.value("General/deviceId").toString();
    m_machineId = settings.value("General/machineId").toString();
    m_userId = settings.value("General/userId").toString();
    m_sessionKey = settings.value("General/sessionKey").toString();
    m_secret = settings.value("General/secret").toString();
    m_accessToken = settings.value("General/accessToken").toString();
}


AuthHelper::~AuthHelper()
{
}

QString AuthHelper::generateDeviceId()
{
    return QUuid::createUuid().toString().remove("{").remove("}");
}

QString AuthHelper::parseUrlQuery(const QString &queryString)
{
    QString result;
    QUrlQuery query(queryString);
    for (QPair<QString, QString> queryEntry : query.queryItems(QUrl::FullyEncoded)) {
        result.append("<p><b>");
        result.append(queryEntry.first);
        result.append("</b>");
        result.append(" = ");
        result.append(QUrl::fromPercentEncoding(queryEntry.second.toLocal8Bit()));
        result.append("</p>");
    }
    return result;
}

QString AuthHelper::formatJson(const QString &json)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(json.toLocal8Bit(), &error);
    if (error.error != QJsonParseError::NoError) {
        return error.errorString();
    }
    return document.toJson(QJsonDocument::Indented);
}

QString AuthHelper::fromBase64(const QString &base64)
{
    return QByteArray::fromBase64(base64.toLocal8Bit());
}

QString AuthHelper::formatDate(const QString &date)
{
    QString realDate = date;
    realDate.remove("CEST ");
    QLocale locale = QLocale(QLocale::English);
    QDateTime dateTime = locale.toDateTime(realDate, "ddd MMM dd hh:mm:ss yyyy");
    return dateTime.time().toString(Qt::SystemLocaleShortDate);
}

QString AuthHelper::formatBurpRequestInfo(const QString &base64Encoded)
{
    QString data = fromBase64(base64Encoded);
    QStringList dataSplitted = data.split("\r\n\r\n");
    if (dataSplitted.count() != 2) {
        return QString();
    }

    QStringList dataList = dataSplitted.first().split("\r\n");
    if (dataList.isEmpty()) {
        return QString();
    }
    dataList.removeFirst();

    QString result;
    for (const QString &entry : dataList) {
        QStringList entrySplitted = entry.split(": ");
        int count = entrySplitted.count();
        if (count == 1 || count == 2) {
            result.append("<p><b>");
            result.append(entrySplitted.at(0));
            result.append("</b>");
            if (count == 2) {
                result.append(" = ");
                result.append(QUrl::fromPercentEncoding(entrySplitted.at(1).toLocal8Bit()));
            }
            result.append("</p>");
        }
    }
    return result;
}

QString AuthHelper::formatBurpRequestQuery(const QString &url)
{
    return parseUrlQuery(QUrl(url).query());
}

QString AuthHelper::formatBurpRequestPostData(const QString &base64Encoded)
{
    QString data = fromBase64(base64Encoded);
    QStringList dataSplitted = data.split("\r\n\r\n");
    if (dataSplitted.count() != 2) {
        return QString();
    }

    return parseUrlQuery(dataSplitted.at(1));
}

QString AuthHelper::formatBurpReply(const QString &base64Encoded)
{
    QString data = fromBase64(base64Encoded);
    QStringList dataSplitted = data.split("\r\n\r\n");
    if (dataSplitted.count() != 2) {
        return QString();
    }

    QStringList dataList = dataSplitted.first().split("\r\n");
    if (dataList.isEmpty()) {
        return QString();
    }
    QString result;
    result.append("<b>");
    result.append(dataList.takeFirst());
    result.append("</b>");

    for (const QString &entry : dataList) {
        QStringList entrySplitted = entry.split(": ");
        int count = entrySplitted.count();
        if (count == 1 || count == 2) {
            result.append("<p><b>");
            result.append(entrySplitted.at(0));
            result.append("</b>");
            if (count == 2) {
                result.append(" = ");
                result.append(QUrl::fromPercentEncoding(entrySplitted.at(1).toLocal8Bit()));
            }
            result.append("</p>");
        }
    }
    return result;
}

QString AuthHelper::formatBurpReplyData(const QString &base64Encoded)
{
    QString data = fromBase64(base64Encoded);
    QStringList dataSplitted = data.split("\r\n\r\n");
    if (dataSplitted.count() != 2) {
        return QString();
    }

    const QString &returned = dataSplitted.at(1);
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(returned.toLocal8Bit(), &error);
    if (error.error != QJsonParseError::NoError) {
        return returned;
    }
    return document.toJson(QJsonDocument::Indented);
}

QString AuthHelper::email() const
{
    return m_email;
}

void AuthHelper::setEmail(const QString &email)
{
    if (m_email != email) {
        m_email = email;
        emit emailChanged();
    }
}

QString AuthHelper::deviceId() const
{
    return m_deviceId;
}

void AuthHelper::setDeviceId(const QString &deviceId)
{
    if (m_deviceId != deviceId) {
        m_deviceId = deviceId;
        emit deviceIdChanged();
    }
}

QString AuthHelper::machineId() const
{
    return m_machineId;
}

void AuthHelper::setMachineId(const QString &machineId)
{
    if (m_machineId != machineId) {
        m_machineId = machineId;
        emit machineIdChanged();
    }
}

QString AuthHelper::userId() const
{
    return m_userId;
}

void AuthHelper::setUserId(const QString &userId)
{
    if (m_userId != userId) {
        m_userId = userId;
        emit userIdChanged();
    }
}

QString AuthHelper::sessionKey() const
{
    return m_sessionKey;
}

void AuthHelper::setSessionKey(const QString &sessionKey)
{
    if (m_sessionKey != sessionKey) {
        m_sessionKey = sessionKey;
        emit sessionKeyChanged();
    }
}

QString AuthHelper::secret() const
{
    return m_secret;
}

void AuthHelper::setSecret(const QString &secret)
{
    if (m_secret != secret) {
        m_secret = secret;
        emit secretChanged();
    }
}

QString AuthHelper::accessToken() const
{
    return m_accessToken;
}

void AuthHelper::setAccessToken(const QString &accessToken)
{
    if (m_accessToken != accessToken) {
        m_accessToken = accessToken;
        emit accessTokenChanged();
    }
}

void AuthHelper::save()
{
    QSettings settings;
    settings.setValue("General/email", m_email);
    settings.setValue("General/deviceId", m_deviceId);
    settings.setValue("General/machineId", m_machineId);
    settings.setValue("General/userId", m_userId);
    settings.setValue("General/sessionKey", m_sessionKey);
    settings.setValue("General/secret", m_secret);
    settings.setValue("General/accessToken", m_accessToken);
}

void AuthHelper::logout()
{
    setUserId(QString());
    setSessionKey(QString());
    setSecret(QString());
    setAccessToken(QString());
    save();
}
