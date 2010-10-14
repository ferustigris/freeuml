# -------------------------------------------------
# Project created by QtCreator 2010-02-10T14:25:49
# -------------------------------------------------
QT = core gui webkit \
    xml
TARGET = freeuml
TEMPLATE = app
INCLUDEPATH += sources/graph \
    sources/forms \
    sources/generator \
    sources/help \
    sources/project \
    sources/widgets \
    sources \
    sources/log
SOURCES += main.cpp \
    sources/mainwindow.cpp \
    sources/log/errors.cpp \
    sources/graph/graphbody.cpp \
    sources/graph/node.cpp \
    sources/graph/edge.cpp \
    sources/generator/generator.cpp \
    sources/help/textedit.cpp \
    sources/help/tdialogadditem.cpp \
    sources/project/project.cpp \
    sources/wiremodel.cpp \
    sources/graph/nodesfactory.cpp \
    sources/graph/rootnode.cpp \
    sources/widgets/identificatoredit.cpp \
    sources/graph/nodeactivity.cpp \
    sources/graph/nodeusecase.cpp \
    sources/graph/nodeif.cpp \
    sources/graph/nodesync.cpp \
    sources/graph/activitybody.cpp \
    sources/graph/usecasebody.cpp \
    sources/graph/nodeauthor.cpp \
    sources/graph/statebody.cpp \
    sources/graph/topologybody.cpp \
    sources/graph/nodehost.cpp \
    sources/graph/collaborationbody.cpp \
	sources/graph/edgedirectlist.cpp \
    sources/graph/edgeparams.cpp \
    sources/graph/sequencebody.cpp \
    sources/graph/nodesequence.cpp \
    sources/graph/edgesequence.cpp \
    sources/graph/nodeclass.cpp \
    sources/graph/classbody.cpp \
    sources/editclass.cpp
HEADERS += sources/mainwindow.h \
    sources/log/errors.h \
    sources/graph/graphbody.h \
    sources/graph/node.h \
    sources/graph/edge.h \
    sources/graph/inode.h \
    sources/generator/generator.h \
    sources/graph/iedge.h \
    sources/help/textedit.h \
    sources/help/tdialogadditem.h \
    sources/project/project.h \
    sources/wiremodel.h \
    sources/graph/nodesfactory.h \
    sources/graph/rootnode.h \
    sources/widgets/identificatoredit.h \
    sources/graph/nodeactivity.h \
    sources/graph/nodeusecase.h \
    sources/graph/nodeif.h \
    sources/graph/nodesync.h \
    sources/graph/activitybody.h \
    sources/graph/usecasebody.h \
    sources/graph/nodeauthor.h \
    sources/graph/statebody.h \
    sources/graph/topologybody.h \
    sources/graph/nodehost.h \
    sources/graph/collaborationbody.h \
	sources/graph/edgedirectlist.h \
    sources/graph/edgeparams.h \
    sources/graph/sequencebody.h \
    sources/graph/nodesequence.h \
    sources/graph/edgesequence.h \
    sources/graph/nodeclass.h \
    sources/graph/classbody.h \
    sources/editclass.h
FORMS += sources/forms/mainwindow.ui \
    sources/forms/graphbody.ui \
    sources/forms/generator.ui \
    sources/forms/edgeparams.ui \
    sources/forms/tdialogadditem.ui \
    sources/forms/editclass.ui
RESOURCES += share/mainResources.qrc
TRANSLATIONS = share/lang/tr_ru.ts
