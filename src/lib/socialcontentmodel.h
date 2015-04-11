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

#ifndef SOCIALCONTENTMODEL_H
#define SOCIALCONTENTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtQml/QQmlParserStatus>
#include "isocialcontent.h"

class SocialNetwork;
class SocialObject;
class SocialRequest;
class SocialContentModelBuilder;
class SocialContentModelPrivate;
class SocialContentModel : public QAbstractListModel, public ISocialContent, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool haveNext READ haveNext NOTIFY haveNextChanged)
    Q_PROPERTY(bool havePrevious READ havePrevious NOTIFY havePreviousChanged)
    Q_PROPERTY(SocialNetwork * socialNetwork READ socialNetwork WRITE setSocialNetwork
               NOTIFY socialNetworkChanged)
    Q_PROPERTY(SocialRequest * request READ request WRITE setRequest NOTIFY requestChanged)
    Q_PROPERTY(SocialContentModelBuilder * builder READ builder WRITE setBuilder NOTIFY builderChanged)
    Q_PROPERTY(SocialNetworkStatus::type status READ status NOTIFY statusChanged)
    Q_PROPERTY(SocialNetworkError::type error READ error NOTIFY errorChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY errorStringChanged)
public:
    enum Roles {
        ObjectRole = Qt::UserRole + 1,
    };
    explicit SocialContentModel(QObject *parent = 0);
    virtual ~SocialContentModel();
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void classBegin() override;
    void componentComplete() override;
    int count() const;
    bool haveNext() const;
    bool havePrevious() const;
    SocialNetwork * socialNetwork() const;
    void setSocialNetwork(SocialNetwork *socialNetwork);
    SocialRequest * request() const;
    void setRequest(SocialRequest *request);
    SocialContentModelBuilder * builder() const;
    void setBuilder(SocialContentModelBuilder * builder);
    SocialNetworkStatus::type status() const override;
    SocialNetworkError::type error() const override;
    QString errorString() const override;
public Q_SLOTS:
    bool load();
    bool loadNext();
    bool loadPrevious();
Q_SIGNALS:
    void countChanged();
    void haveNextChanged();
    void havePreviousChanged();
    void socialNetworkChanged();
    void requestChanged();
    void builderChanged();
    void statusChanged() override;
    void errorChanged() override;
    void errorStringChanged() override;
    void finished(bool ok) override;
protected:
    QScopedPointer<SocialContentModelPrivate> d_ptr;
private:
    Q_DECLARE_PRIVATE(SocialContentModel)
};

#endif // SOCIALCONTENTMODEL_H
