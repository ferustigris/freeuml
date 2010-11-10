QT += xml
HEADERS += sources/wiremodel.h \
    sources/mainwindow.h \
    sources/inodesfactory.h \
    sources/editclass.h \
    sources/generator/generator.h \
    sources/graph/usecasebody.h \
    sources/graph/topologybody.h \
    sources/graph/statebody.h \
    sources/graph/sequencebody.h \
    sources/graph/rootnode.h \
    sources/graph/nodeusecase.h \
    sources/graph/nodesync.h \
    sources/graph/nodesfactory.h \
    sources/graph/nodesequence.h \
    sources/graph/nodeif.h \
    sources/graph/nodehost.h \
    sources/graph/nodeclass.h \
    sources/graph/nodeauthor.h \
    sources/graph/nodeactivity.h \
    sources/graph/node.h \
    sources/graph/inode.h \
    sources/graph/iedge.h \
    sources/graph/graphbody.h \
    sources/graph/edgesequence.h \
    sources/graph/edgeparams.h \
    sources/graph/edgeline.h \
    sources/graph/edgedirectlist.h \
    sources/graph/edgeassotiation.h \
    sources/graph/edgeaggregation.h \
    sources/graph/edge.h \
    sources/graph/collaborationbody.h \
    sources/graph/classbody.h \
    sources/graph/activitybody.h \
    sources/help/textedit.h \
    sources/help/tdialogadditem.h \
    sources/log/errors.h \
    sources/project/project.h \
    sources/widgets/identificatoredit.h
SOURCES += sources/wiremodel.cpp \
    sources/mainwindow.cpp \
    sources/editclass.cpp \
    sources/generator/generator.cpp \
    sources/graph/usecasebody.cpp \
    sources/graph/topologybody.cpp \
    sources/graph/statebody.cpp \
    sources/graph/sequencebody.cpp \
    sources/graph/rootnode.cpp \
    sources/graph/nodeusecase.cpp \
    sources/graph/nodesync.cpp \
    sources/graph/nodesfactory.cpp \
    sources/graph/nodesequence.cpp \
    sources/graph/nodeif.cpp \
    sources/graph/nodehost.cpp \
    sources/graph/nodeclass.cpp \
    sources/graph/nodeauthor.cpp \
    sources/graph/nodeactivity.cpp \
    sources/graph/node.cpp \
    sources/graph/graphbody.cpp \
    sources/graph/edgesequence.cpp \
    sources/graph/edgeparams.cpp \
    sources/graph/edgeline.cpp \
    sources/graph/edgedirectlist.cpp \
    sources/graph/edgeassotiation.cpp \
    sources/graph/edgeaggregation.cpp \
    sources/graph/edge.cpp \
    sources/graph/collaborationbody.cpp \
    sources/graph/classbody.cpp \
    sources/graph/activitybody.cpp \
    sources/help/textedit.cpp \
    sources/help/tdialogadditem.cpp \
    sources/log/errors.cpp \
    sources/project/project.cpp \
    sources/widgets/identificatoredit.cpp \
    main.cpp
RESOURCES += share/mainResources.qrc
FORMS += sources/forms/tdialogadditem.ui \
    sources/forms/mainwindow.ui \
    sources/forms/graphbody.ui \
    sources/forms/generator.ui \
    sources/forms/editclass.ui \
    sources/forms/edgeparams.ui
INCLUDEPATH += sources \
    sources/forms \
    sources/log \
    sources/help \
    sources/graph \
    sources/generator \
    sources/project \
    sources/widgets
