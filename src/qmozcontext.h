/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-*/
/* vim: set ts=2 sw=2 et tw=79: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef qmozcontext_h
#define qmozcontext_h

#include <QObject>
#include <QThread>
#include <QVariant>

class QMozContextPrivate;

namespace mozilla {
namespace embedlite {
class EmbedLiteApp;
}}

class QEventLoop;
class QMozContext;
class GeckoThread : public QThread
{
    Q_OBJECT
public:
    GeckoThread(QMozContext* aContext) : mContext(aContext), mEventLoop(NULL) {}
    void run();

public Q_SLOTS:
    void Quit();

public:
    QMozContext* mContext;
    QEventLoop* mEventLoop;
};

class QMozContext : public QObject
{
    Q_OBJECT
public:
    virtual ~QMozContext();

    bool initialized();
    mozilla::embedlite::EmbedLiteApp* GetApp();

    static QMozContext* GetInstance();

Q_SIGNALS:
    void onInitialized();
    unsigned newWindowRequested(const QString& url, const unsigned& parentId);
    void recvObserve(const QString message, const QVariant data);

public Q_SLOTS:
    void setIsAccelerated(bool aIsAccelerated);
    void addComponentManifest(const QString& manifestPath);
    void addObserver(const QString& aTopic);
    quint32 newWindow(const QString& url, const quint32& parentId);
    void sendObserve(const QString& aTopic, const QVariant& variant);

private Q_SLOTS:
    void runEmbedding();
    void onLastWindowClosed();

private:
    QMozContext(QObject* parent = 0);

    QMozContextPrivate* d;
    friend class QMozContextPrivate;
};

class QmlMozContext : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* child READ getChild)

public:
    QmlMozContext(QObject* parent = 0);
    virtual ~QmlMozContext() {}

private:
    QObject* getChild() const;

public Q_SLOTS:
    void setPref(const QString& aName, const QVariant& aPref);
    void newWindow(const QString& url = "about:mozilla");
};

#endif /* qmozcontext_h */
