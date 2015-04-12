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

#include "infohelper.h"
#include <QtCore/QMetaProperty>
#include <QtCore/QUrl>

InfoHelper::InfoHelper(QObject *parent)
    : QObject(parent)
{
}

InfoHelper::~InfoHelper()
{
}

QObject * InfoHelper::object() const
{
    return m_object;
}

void InfoHelper::setObject(QObject *object)
{
    if (m_object != object) {
        m_object = object;
        emit objectChanged();
        generateText();
    }
}

QString InfoHelper::text() const
{
    return m_text;
}

QStringList InfoHelper::urls() const
{
    return m_urls;
}

void InfoHelper::generateText()
{
    if (!m_object) {
        return;
    }
    const QMetaObject *meta = m_object->metaObject();
    int offset = meta->propertyOffset();
    int count = meta->propertyCount();

    QString text;
    QStringList urls;
    for (int i = offset; i < count; ++i) {
        const QMetaProperty &metaProperty = meta->property(i);
        QString value = metaProperty.read(m_object).toString();
        text.append(QString("<p><b>%1</b>: %2</p>").arg(metaProperty.name(), value));
        QUrl url (value, QUrl::StrictMode);
        if (url.isValid() && url.scheme().startsWith("http")) {
            urls.append(value);
        }
    }

    if (m_text != text) {
        m_text = text;
        emit textChanged();
    }

    if (m_urls != urls) {
        m_urls = urls;
        emit urlsChanged();
    }
}