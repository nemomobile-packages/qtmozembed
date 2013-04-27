TEMPLATE = app
TARGET = qmlmoztestrunner
CONFIG += warn_on link_pkgconfig
SOURCES += main.cpp

INCLUDEPATH+=../../src
isEmpty(OBJ_BUILD_PATH) {
LIBS+= -L../../ -lqtembedwidget
} else {
LIBS+= -L../../$$OBJ_BUILD_PATH -lqtembedwidget
}

LIBS += -lQtQuickTest
PKGCONFIG += QJson
contains(QT_CONFIG, opengl)|contains(QT_CONFIG, opengles1)|contains(QT_CONFIG, opengles2) {
    QT += opengl
}

target.path = $$[QT_INSTALL_BINS]
INSTALLS += target
