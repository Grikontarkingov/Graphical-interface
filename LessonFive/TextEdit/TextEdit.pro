QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    helpwindow.cpp \
    hotkeyswindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    helpwindow.h \
    hotkeyswindow.h \
    mainwindow.h

FORMS += \
    helpwindow.ui \
    hotkeyswindow.ui \
    mainwindow.ui

TRANSLATIONS += TextEdit_ru.ts TextEdit_en.ts
CODECFORSRC = UTF-8


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Files.qrc
