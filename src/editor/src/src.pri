DEPENDPATH += ./src
INCLUDEPATH += ./src

HEADERS +=
SOURCES += main.cpp

include (src/widgets/widgets.pri)
include (src/misc/misc.pri)
include (src/props/props.pri)
include (src/resource/resource.pri)
include (src/luabind/luabind.pri)
include (../../ext/qtpropertybrowser-2.5_1-opensource/src/qtpropertybrowser.pri)
