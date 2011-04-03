@echo off

rem  ======================================================================================
rem  File         : gen_qmakefiles.bat
rem  Author       : Wu Jie 
rem  Last Change  : 07/26/2009 | 10:42:10 AM | Sunday,July
rem  Description  : 
rem  ======================================================================================

rem  echo process exEditorCore.pro...
rem  cd exEditorCore
rem  qmake -tp vc exEditorCore.pro
rem  cd ..
rem  echo done!

echo process editor.pro...
qmake -tp vc editor.pro
echo done!

echo Finish
echo on
