QT += xml
CONFIG += qtestlib
HEADERS += test_data.h \
    ../graph/nodesfactory.h \
    ../graph/rootnode.h \
    ../graph/nodefsm.h \
    ../graph/nodedev.h \
    ../graph/nodeactivity.h \
    ../graph/node.h \
    ../graph/inode.h \
    ../graph/iedge.h \
    ../graph/graphbody.h \
    ../graph/edgeparams.h \
    ../graph/edge.h \
    ../generator/generator.h \
    ../log/errors.h \
    ../project/project.h \
    ../wiremodel.h \
    ../mainwindow.h \
    ../constants.h \
    ../help/textedit.h \
    ../help/tdialogadditem.h \
    ../widgets/identificatoredit.h
SOURCES += test_data.cpp \
    ../graph/nodesfactory.cpp \
    ../graph/rootnode.cpp \
    ../graph/nodefsm.cpp \
    ../graph/nodedev.cpp \
    ../graph/nodeactivity.cpp \
    ../graph/node.cpp \
    ../graph/graphbody.cpp \
    ../graph/edgeparams.cpp \
    ../graph/edge.cpp \
    ../generator/generator.cpp \
    ../log/errors.cpp \
    ../project/project.cpp \
    ../wiremodel.cpp \
    ../mainwindow.cpp \
    ../help/textedit.cpp \
    ../help/tdialogadditem.cpp \
    ../widgets/identificatoredit.cpp
TARGET = test
INCLUDEPATH += .. \
    ../generate \
	../graph \
	../help \
	../forms \
	../generator \
	../project \
	../widgets \
    ../log

FORMS += \
    ../forms/edgeparams.ui \
    ../forms/graphbody.ui \
    ../forms/generator.ui \
    ../forms/tdialogadditem.ui \
    ../forms/mainwindow.ui
