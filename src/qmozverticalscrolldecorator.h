/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QMOZVERTICALSCROLLDECORATOR_H
#define QMOZVERTICALSCROLLDECORATOR_H

#include <QObject>

class QMozVerticalScrollDecorator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal y READ y NOTIFY yChanged FINAL)
    Q_PROPERTY(qreal height READ height NOTIFY heightChanged FINAL)

public:
    QMozVerticalScrollDecorator(QObject *parent = 0);
    virtual ~QMozVerticalScrollDecorator();

    qreal y() const;
    void setY(qreal y);

    qreal height() const;
    void setHeight(qreal height);

Q_SIGNALS:
    void yChanged();
    void heightChanged();

private:
    qreal mY;
    qreal mHeight;
};

#endif
