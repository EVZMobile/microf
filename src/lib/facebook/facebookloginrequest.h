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

#ifndef FACEBOOKLOGINREQUEST_H
#define FACEBOOKLOGINREQUEST_H

#include "socialrequest.h"

class FacebookLoginRequestPrivate;
class FacebookLoginRequest : public SocialRequest
{
    Q_OBJECT
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId NOTIFY deviceIdChanged)
    Q_PROPERTY(QString machineId READ machineId WRITE setMachineId NOTIFY machineIdChanged)
public:
    explicit FacebookLoginRequest(QObject *parent = 0);
    Type type() const;
    QString email() const;
    void setEmail(const QString &email);
    QString password() const;
    void setPassword(const QString &password);
    QString deviceId() const;
    void setDeviceId(const QString &deviceId);
    QString machineId() const;
    void setMachineId(const QString &machineId);
Q_SIGNALS:
    void emailChanged();
    void passwordChanged();
    void deviceIdChanged();
    void machineIdChanged();
protected:
    QNetworkRequest createRequest(const SocialNetwork &socialNetwork,
                                  const QByteArray &postData, Mode mode,
                                  const QVariantMap &metadata) const Q_DECL_OVERRIDE;
    QByteArray createPostData(const SocialNetwork &socialNetwork, Mode mode,
                              const QVariantMap &metadata) const Q_DECL_OVERRIDE;
private:
    Q_DECLARE_PRIVATE(FacebookLoginRequest)
};

#endif // FACEBOOKLOGINREQUEST_H
