# ======================================================================================
# File         : editor.pro
# Author       : Wu Jie 
# Last Change  : 08/06/2010 | 08:54:57 AM | Friday,August
# Description  : 
# ======================================================================================

# ------------------------------------------------------------------ 
# Desc: general 
# ------------------------------------------------------------------ 

TEMPLATE = app
CONFIG += static

TARGET = editor

INCLUDEPATH += ./
INCLUDEPATH += ../
INCLUDEPATH += ../../ext
INCLUDEPATH += ./autogen/ui/inc

PRECOMPILED_HEADER = src/editor.h

# ------------------------------------------------------------------ 
# Desc: ui 
# ------------------------------------------------------------------ 

UI_DIR = autogen/ui
UI_HEADERS_DIR = autogen/ui/inc
UI_SOURCES_DIR = autogen/ui/src

# ------------------------------------------------------------------ 
# Desc: define
# ------------------------------------------------------------------ 

DLL_SUFFIX =
DEFINES += __DL_EDITOR
DEFINES += __EX_WIN32 # TODO: platform select
DEFINES += __EX_USE_LUA
CONFIG ( static ) {
    DLL_SUFFIX =
} else {
    DLL_SUFFIX = _dll
    DEFINES += __EX_DLL
}

# ------------------------------------------------------------------ 
# Desc: resources 
# ------------------------------------------------------------------ 

RESOURCES += editor.qrc

# ------------------------------------------------------------------ 
# Desc: config
# ------------------------------------------------------------------ 

CONFIG += debug_and_release
CONFIG ( debug, debug|release ) {
    DEFINES += __EX_DEBUG
    DEFINES += NIDEBUG
    LIBS += dxguid.lib
    LIBS += ../../ext/expat/lib/libexpatMT.lib
    LIBS += ../../ext/lua-5.1.4/src/lua51.lib
    win32:DESTDIR = ../_bin/Debug$$DLL_SUFFIX
    unix:DESTDIR = ../_bin/Debug$$DLL_SUFFIX
} else {
    DEFINES += __EX_RELEASE
    DEFINES += NIRELEASE
    LIBS += dxguid.lib
    LIBS += ../../ext/expat/lib/libexpatMT.lib
    LIBS += ../../ext/lua-5.1.4/src/lua51.lib
    win32:DESTDIR = ../_bin/Release$$DLL_SUFFIX
    unix:DESTDIR = ../_bin/Release$$DLL_SUFFIX
}

# ------------------------------------------------------------------ 
# Desc: source 
# ------------------------------------------------------------------ 

include (src/src.pri)

HEADERS +=
SOURCES += 
# QT += opengl
QT += xml
