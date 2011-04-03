#  ======================================================================================
#  File         : testbed.mk
#  Author       : Wu Jie 
#  Last Change  : 10/19/2008 | 17:30:30 PM | Sunday,October
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

Project := testbed
ProjectType := exe

#  ------------------------------------------------------------------ 
#  Desc: Include Path
#  ------------------------------------------------------------------ 

IncDirs += .
IncDirs += ..
IncDirs += ../../ext

#  ------------------------------------------------------------------ 
#  Desc: Precompiled Headers Dependence Headers
#  ------------------------------------------------------------------ 

FullPath_GchSrcs += ./testbed.h

#  ------------------------------------------------------------------ 
#  Desc: Source Path
#  ------------------------------------------------------------------ 

SrcDirs += .
SrcDirs += ./helpers
SrcDirs += ./tests
SrcDirs += ./debugs

#  ------------------------------------------------------------------ 
#  Desc: Dependent Libaray File Paths
#  ------------------------------------------------------------------ 

LibDirs += ../../ext/expat/lib
LibDirs += ../../ext/SDL/lib/mingw
# DISABLE LibDirs += ../../ext/libyaml/lib

#  ------------------------------------------------------------------ 
#  Desc: Dependent Library File Names
#  ------------------------------------------------------------------ 

PrjLibs += exlibs
ExtLibs += expat
ExtLibs += SDL
ExtLibs += SDLmain
ExtLibs += SDL_gfx
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

PreDefs += __EX_TEST_LIBS

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
