/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QOPENGLWEBPAGE_H
#define QOPENGLWEBPAGE_H

#include <qqml.h>
#include <QSizeF>

// Needed events, all of these renders to qevent.h includes.
#include <QMouseEvent>
#include <QInputMethodEvent>
#include <QKeyEvent>
#include <QFocusEvent>
#include <QTouchEvent>
#include <QMutex>

#include "qmozview_defined_wrapper.h"

class QGraphicsMozViewPrivate;
class QMozGrabResult;

class QOpenGLWebPage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int parentId READ parentId WRITE setParentID NOTIFY parentIdChanged FINAL)
    Q_PROPERTY(bool privateMode READ privateMode WRITE setPrivateMode NOTIFY privateModeChanged FINAL)

    Q_PROPERTY(bool completed READ completed NOTIFY completedChanged FINAL)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged FINAL)
    Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged FINAL)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(QSizeF size READ size WRITE setSize NOTIFY sizeChanged FINAL)
    Q_PROPERTY(bool loaded READ loaded NOTIFY loadedChanged FINAL)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged FINAL)
    Q_PROPERTY(bool throttlePainting READ throttlePainting WRITE setThrottlePainting NOTIFY throttlePaintingChanged FINAL)
    Q_PROPERTY(bool readyToPaint READ readyToPaint WRITE setReadyToPaint NOTIFY readyToPaintChanged FINAL)

    Q_MOZ_VIEW_PRORERTIES

public:
    QOpenGLWebPage(QObject *parent = 0);
    ~QOpenGLWebPage();

    Q_MOZ_VIEW_PUBLIC_METHODS
    int parentId() const;

    bool privateMode() const;
    void setPrivateMode(bool privateMode);

    bool completed() const;

    bool enabled() const;
    void setEnabled(bool enabled);

    bool active() const;
    void setActive(bool active);

    qreal width() const;
    void setWidth(qreal width);

    qreal height() const;
    void setHeight(qreal height);

    QSizeF size() const;
    void setSize(const QSizeF &size);

    bool loaded() const;

    QWindow *window() const;
    void setWindow(QWindow *window);

    bool throttlePainting() const;
    void setThrottlePainting(bool);

    bool readyToPaint() const;
    void setReadyToPaint(bool);

    void initialize();

    virtual bool event(QEvent *event);
    virtual void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery property) const;
    virtual void inputMethodEvent(QInputMethodEvent* event);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);
    virtual void focusInEvent(QFocusEvent*);
    virtual void focusOutEvent(QFocusEvent*);
    virtual void touchEvent(QTouchEvent*);
    virtual void timerEvent(QTimerEvent*);

    QSharedPointer<QMozGrabResult> grabToImage(const QSize &targetSize = QSize());

public Q_SLOTS:
    Q_MOZ_VIEW_PUBLIC_SLOTS
    void update();
    void forceActiveFocus();
    void setInputMethodHints(Qt::InputMethodHints hints);

    void updateContentOrientation(Qt::ScreenOrientation orientation);

Q_SIGNALS:
    void parentIdChanged();
    void privateModeChanged();
    void completedChanged();
    void enabledChanged();
    void activeChanged();
    void widthChanged();
    void heightChanged();
    void sizeChanged();
    void loadedChanged();
    void windowChanged();
    void requestGLContext();
    void afterRendering(const QRect &rect);
    void throttlePaintingChanged();
    void readyToPaintChanged();

    Q_MOZ_VIEW_SIGNALS

private Q_SLOTS:
    void processViewInitialization();
    void updateLoaded();
    void createView();
    void updateSize();

private:
    void scheduleSizeUpdate();

    QGraphicsMozViewPrivate* d;
    friend class QGraphicsMozViewPrivate;

    unsigned mParentID;
    bool mPrivateMode;
    bool mActive;
    bool mLoaded;
    bool mCompleted;
    QWindow *mWindow;
    QList<QWeakPointer<QMozGrabResult> > mGrabResultList;
    QMutex mGrabResultListLock;
    bool mSizeUpdateScheduled;
    bool mThrottlePainting;
    mutable QMutex mReadyToPaintMutex;
    bool mReadyToPaint;

    Q_DISABLE_COPY(QOpenGLWebPage)
};

QML_DECLARE_TYPE(QOpenGLWebPage)

#endif // QOPENGLWEBPAGE_H
