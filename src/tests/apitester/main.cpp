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

#include <QtWidgets/QApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/qqml.h>
#include <socialcontentitem.h>
#include <socialcontentmodel.h>
#include <socialobject.h>
#include <facebook/facebook.h>
#include <facebook/facebookloginrequest.h>
#include <facebook/facebooklogincontentbuilder.h>
#include <facebook/facebooklogoutrequest.h>
#include <facebook/facebookconfirmationcontentbuilder.h>
#include <facebook/facebookfriendlistrequest.h>
#include <facebook/facebookmodelbuilder.h>
#include "authhelper.h"
#include "infohelper.h"
#include "requesthelpermodel.h"
#include "requestpropertyhelpermodel.h"

static void registerTypes()
{
    qmlRegisterUncreatableType<SocialNetwork>("org.sfietkonstantin.microf", 1, 0, "SocialNetwork", "Abstract type");
    qmlRegisterUncreatableType<SocialNetworkStatus>("org.sfietkonstantin.microf", 1, 0, "SocialNetworkStatus", "Abstract type");
    qmlRegisterUncreatableType<SocialNetworkError>("org.sfietkonstantin.microf", 1, 0, "SocialNetworkError", "Abstract type");
    qmlRegisterUncreatableType<SocialObject>("org.sfietkonstantin.microf", 1, 0, "SocialObject", "Abstract type");
    qmlRegisterUncreatableType<SocialRequest>("org.sfietkonstantin.microf", 1, 0, "SocialRequest", "Abstract type");
    qmlRegisterUncreatableType<SocialContentItemBuilder>("org.sfietkonstantin.microf", 1, 0, "SocialContentItemBuilder", "Abstract type");
    qmlRegisterUncreatableType<SocialContentModelBuilder>("org.sfietkonstantin.microf", 1, 0, "SocialContentModelBuilder", "Abstract type");
    qmlRegisterType<SocialContentItem>("org.sfietkonstantin.microf", 1, 0, "SocialContentItem");
    qmlRegisterType<SocialContentModel>("org.sfietkonstantin.microf", 1, 0, "SocialContentModel");
    qmlRegisterType<Facebook>("org.sfietkonstantin.microf", 1, 0, "Facebook");
    qmlRegisterType<FacebookLoginRequest>("org.sfietkonstantin.microf", 1, 0, "FacebookLoginRequest");
    qmlRegisterType<FacebookLoginContentBuilder>("org.sfietkonstantin.microf", 1, 0, "FacebookLoginContentBuilder");
    qmlRegisterType<FacebookLogoutRequest>("org.sfietkonstantin.microf", 1, 0, "FacebookLogoutRequest");
    qmlRegisterType<FacebookConfirmationContentBuilder>("org.sfietkonstantin.microf", 1, 0, "FacebookConfirmationContentBuilder");
    qmlRegisterType<FacebookFriendListRequest>("org.sfietkonstantin.microf", 1, 0, "FacebookFriendListRequest");
    qmlRegisterType<FacebookModelBuilder>("org.sfietkonstantin.microf", 1, 0, "FacebookModelBuilder");
    qmlRegisterType<AuthHelper>("org.sfietkonstantin.microf", 1, 0, "AuthHelper");
    qmlRegisterType<InfoHelper>("org.sfietkonstantin.microf", 1, 0, "InfoHelper");
    qmlRegisterType<RequestHelperModel>("org.sfietkonstantin.microf", 1, 0, "RequestHelperModel");
    qmlRegisterType<RequestPropertyHelperModel>("org.sfietkonstantin.microf", 1, 0, "RequestPropertyHelperModel");
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    registerTypes();
    app.setOrganizationName("microf");
    app.setApplicationName("apitester");
    QQmlApplicationEngine engine (QUrl("qrc:/main.qml"));
    Q_UNUSED(engine);
    return app.exec();
}
