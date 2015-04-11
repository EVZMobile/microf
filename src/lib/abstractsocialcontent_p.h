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

#ifndef ABSTRACTSOCIALCONTENT_P_H
#define ABSTRACTSOCIALCONTENT_P_H

#include <QtNetwork/QNetworkReply>
#include "socialnetworkstatus.h"
#include "socialnetworkerror.h"
#include "isocialcontent.h"

class AbstractSocialContentPrivate
{
public:
    virtual ~AbstractSocialContentPrivate();
    const QVariantMap & metadata() const;
    void setMetadata(const QVariantMap &metadata);
    static void handleNetworkReply(AbstractSocialContentPrivate &contentPrivate,
                                   QNetworkReply::NetworkError error, const QString &errorString,
                                   const QByteArray &data);
protected:
    explicit AbstractSocialContentPrivate(ISocialContent *q);
    void setStatus(SocialNetworkStatus::type status);
    void setError(SocialNetworkError::type error, const QString &errorString);
    virtual bool build(QNetworkReply::NetworkError error, const QString &errorString,
                       const QByteArray &data) = 0;
    ISocialContent * const q_ptr;
    SocialNetworkStatus::type status;
    SocialNetworkError::type error;
    QString errorString;
private:
    void handleNetworkReply(QNetworkReply::NetworkError error, const QString &errorString,
                            const QByteArray &data);
    QVariantMap m_metadata;
    Q_DECLARE_PUBLIC(ISocialContent)
};


#endif // ABSTRACTSOCIALCONTENT_P_H

