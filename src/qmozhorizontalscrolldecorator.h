/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef QMOZHORIZONTALSCROLLDECORATOR_H
#define QMOZHORIZONTALSCROLLDECORATOR_H

#include <QObject>

class QMozHorizontalScrollDecorator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x NOTIFY xChanged FINAL)
    Q_PROPERTY(qreal width READ width NOTIFY widthChanged FINAL)

public:
    QMozHorizontalScrollDecorator(QObject *parent = 0);
    virtual ~QMozHorizontalScrollDecorator();

    qreal x() const;
    void setX(qreal x);

    qreal width() const;
    void setWidth(qreal width);

Q_SIGNALS:
    void xChanged();
    void widthChanged();

private:
    qreal mX;
    qreal mWidth;
};

#endif
