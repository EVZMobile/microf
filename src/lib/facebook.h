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

#ifndef MICROF_FACEBOOK_H
#define MICROF_FACEBOOK_H

#include <QObject>

namespace microf {

class Facebook : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString locale READ locale CONSTANT)
    Q_PROPERTY(QString countryCode READ countryCode CONSTANT)
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(QString sessionKey READ sessionKey WRITE setSessionKey NOTIFY sessionKeyChanged)
    Q_PROPERTY(QString secret READ secret WRITE setSecret NOTIFY secretChanged)
    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)
public:
    explicit Facebook(QObject *parent = nullptr);
    QString apiKey() const;
    QString locale() const;
    QString countryCode() const;
    QString userId() const;
    void setUserId(const QString &userId);
    QString sessionKey() const;
    void setSessionKey(const QString &sessionKey);
    QString secret() const;
    void setSecret(const QString &secret);
    QString accessToken() const;
    void setAccessToken(const QString &accessToken);
    QByteArray userAgent() const;
Q_SIGNALS:
    void userIdChanged();
    void sessionKeyChanged();
    void secretChanged();
    void accessTokenChanged();
private:
    QString m_locale {};
    QString m_countryCode {};
    QString m_userId {};
    QString m_sessionKey {};
    QString m_secret {};
    QString m_accessToken {};
};

}

#endif // MICROF_FACEBOOK_H