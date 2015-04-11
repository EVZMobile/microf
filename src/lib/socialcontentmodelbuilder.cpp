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

#include "socialcontentmodelbuilder.h"
#include "socialcontentmodelbuilder_p.h"
#include "socialcontentmodel_p.h"

SocialContentModelBuilderPrivate::SocialContentModelBuilderPrivate(SocialContentModelBuilder *q)
    : q_ptr(q)
{
}

void SocialContentModelBuilderPrivate::build(SocialContentModelBuilder &builder,
                                             SocialContentModel &contentModel,
                                             QNetworkReply::NetworkError error,
                                             const QString &errorString, const QByteArray &data)
{
    builder.build(contentModel, error, errorString, data);
}

SocialContentModelBuilder::SocialContentModelBuilder(QObject *parent)
    : QObject(parent), d_ptr(new SocialContentModelBuilderPrivate(this))
{
}

SocialContentModelBuilder::~SocialContentModelBuilder()
{
}

void SocialContentModelBuilder::classBegin()
{
}

void SocialContentModelBuilder::componentComplete()
{
}

void SocialContentModelBuilder::setData(SocialContentModel &contentModel,
                                        const QList<QVariantMap> &data,
                                        bool haveNext, bool havePrevious,
                                        const QVariantMap &metadata)
{
    SocialContentModelPrivate::setContentModelData(contentModel, data, haveNext, havePrevious,
                                                   metadata);

}

void SocialContentModelBuilder::setError(SocialContentModel &contentModel,
                                         SocialNetworkError::type error, const QString &errorString)
{
    SocialContentModelPrivate::setContentModelError(contentModel, error, errorString);

}

