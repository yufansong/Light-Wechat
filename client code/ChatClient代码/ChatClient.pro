FORMS += \
    filedisplay.ui \
    mylogin.ui \
    newpassword.ui

HEADERS += \
    chatdialog.h \
    filedisplay.h \
    mylogin.h \
    message.h \
    newpassword.h \
    mylabel.h

SOURCES += \
    main.cpp \
    chatdialog.cpp \
    filedisplay.cpp \
    mylogin.cpp \
    message.cpp \
    newpassword.cpp \
    mylabel.cpp

RESOURCES += \
    myimage.qrc

greaterThan(QT_MAJOR_VERSION,4):QT += widgets
QT += gui core
QT += network

RC_ICONS = /images/chat.ico
