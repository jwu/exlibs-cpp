#  ======================================================================================
#  File         : exlibs.mk
#  Author       : Wu Jie 
#  Last Change  : 10/27/2008 | 23:39:39 PM | Monday,October
#  Description  : 
#  ======================================================================================

# /////////////////////////////////////////////////////////////////////////////
#  Global Configuration
# /////////////////////////////////////////////////////////////////////////////

#  ------------------------------------------------------------------ 
#  Desc: include general config
#  ------------------------------------------------------------------ 

include ../gcc_config.mk

# /////////////////////////////////////////////////////////////////////////////
#  User Define
# /////////////////////////////////////////////////////////////////////////////

#  ------------------------------------------------------------------ 
#  Desc: Parent Working Directory
#  ------------------------------------------------------------------ 

CWD := ..

#  ------------------------------------------------------------------ 
#  Desc: Project Name
#  ------------------------------------------------------------------ 

Project := exlibs
ProjectType := lib

#  ------------------------------------------------------------------ 
#  Desc: Include Path
#  ------------------------------------------------------------------ 

IncDirs += .
IncDirs += ../../ext

#  ------------------------------------------------------------------ 
#  Desc: Precompiled Headers Dependence Headers
#  ------------------------------------------------------------------ 

FullPath_GchSrcs += ./exlibs.h

#  ------------------------------------------------------------------ 
#  Desc: Source Path
#  ------------------------------------------------------------------ 

SrcDirs += ./AutoGen
SrcDirs += ./Container
SrcDirs += ./CppUnitLite
SrcDirs += ./Core
SrcDirs += ./Debug
SrcDirs += ./File
SrcDirs += ./GF
SrcDirs += ./Global
SrcDirs += ./Helpers
SrcDirs += ./Input
SrcDirs += ./Intersection
SrcDirs += ./Macro
SrcDirs += ./Math
SrcDirs += ./Memory
SrcDirs += ./Meta
SrcDirs += ./Parser
SrcDirs += ./Pattern
SrcDirs += ./Property
SrcDirs += ./QuadTree
SrcDirs += ./Resource
SrcDirs += ./Serialization
SrcDirs += ./String
SrcDirs += ./Thread
SrcDirs += ./Time
SrcDirs += ./Xml
# DISABLE SrcDirs += ./Yaml

ifeq ($(Platform),Win32) # win32
SrcDirs += ./File/platform/win32
SrcDirs += ./Thread/win32
endif

#  ------------------------------------------------------------------ 
#  Desc: Dependent Libaray File Paths
#  ------------------------------------------------------------------ 

LibDirs += ../../ext/expat/lib
LibDirs += ../../ext/SDL/lib
# DISABLE LibDirs += ../../ext/libyaml/lib

#  ------------------------------------------------------------------ 
#  Desc: Dependent Library File Names
#  ------------------------------------------------------------------ 

PrjLibs += # TODO: lib-file-name (sample: libSDK.a-->SDK) This is libs for project compile depence
ExtLibs += expat
ExtLibs += SDL
ExtLibs += SDLmain
# DISABLE ExtLibs += yaml

#  ------------------------------------------------------------------ 
#  Desc: Special Flags
# 	Some space-depent directory flag can't generate automatically, use this instead
#  ------------------------------------------------------------------ 

CFlag_Spec += -Wall
CFlag_Spec += # TODO: (sample: -I"C:/Program Files/Microsoft DirectX SDK/Include")
LFlag_Spec += -Wall
LFlag_Spec += # TODO: (sample: -L"C:/Program Files/Microsoft DirectX SDK/Lib/x86")

# /////////////////////////////////////////////////////////////////////////////
#  Advanced User Define
#  NOTE: in this section, you can define advanced macros by uncomment them
# /////////////////////////////////////////////////////////////////////////////

#  ------------------------------------------------------------------ 
#  Desc: output directory 
#  ------------------------------------------------------------------ 

OutDir := $(EX_SDK)/_build/gcc/$(Platform)/$(Configuration)
ErrDir := $(CWD)/_logs/errors

#  ------------------------------------------------------------------ 
#  Desc: Pre defines
#  ------------------------------------------------------------------ 

PreDefs += __EX_LIBS

# /////////////////////////////////////////////////////////////////////////////
#  Post Build Even
#   programme after target been built, this is the project specific one (sample: make_fself $(@) $(basename $(@)).self)
# /////////////////////////////////////////////////////////////////////////////

define POST_BUILD
$(ECHO) Post Build $(Project)...
endef

# /////////////////////////////////////////////////////////////////////////////
#  Rules
# /////////////////////////////////////////////////////////////////////////////

ifeq ($(Platform),Win32) # win32
include $(EX_DEV)/exVim/toolkit/makefile/gcc/gcc_rule_s.mk
else
ifeq ($(Platform),Linux) # unix/linux
include ~/.toolkit/makefile/gcc/gcc_rule_s.mk
else # other system
include ~/.toolkit/makefile/gcc/gcc_rule_s.mk
endif
endif
