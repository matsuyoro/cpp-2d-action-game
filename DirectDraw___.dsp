# Microsoft Developer Studio Project File - Name="DirectDrawスケルトンプログラム" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DirectDrawスケルトンプログラム - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "DirectDrawスケルトンプログラム.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "DirectDrawスケルトンプログラム.mak"\
 CFG="DirectDrawスケルトンプログラム - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "DirectDrawスケルトンプログラム - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "DirectDrawスケルトンプログラム - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DirectDrawスケルトンプログラム - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "DirectDrawスケルトンプログラム - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o NUL /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib ddraw.lib dxguid.lib dsound.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DirectDrawスケルトンプログラム - Win32 Release"
# Name "DirectDrawスケルトンプログラム - Win32 Debug"
# Begin Group "外部変数宣言"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Extern.h
# End Source File
# Begin Source File

SOURCE=.\Global.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Group "ゲーム関数のヘッダ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameMain.h
# End Source File
# Begin Source File

SOURCE=.\GameOver.h
# End Source File
# Begin Source File

SOURCE=.\GameStop.h
# End Source File
# Begin Source File

SOURCE=.\GameTitle.h
# End Source File
# Begin Source File

SOURCE=.\Main.h
# End Source File
# Begin Source File

SOURCE=.\StageSelect.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\GameMain.cpp
# End Source File
# Begin Source File

SOURCE=.\GameOver.cpp
# End Source File
# Begin Source File

SOURCE=.\GameStop.cpp
# End Source File
# Begin Source File

SOURCE=.\GameTitle.cpp
# End Source File
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\StageSelect.cpp
# End Source File
# End Group
# Begin Group "マクロ定義"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Define.h
# End Source File
# End Group
# Begin Group "DirectDrawスケルトン（WinMain"

# PROP Default_Filter ""
# Begin Group "DirectSound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DirectSound.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectSound.h
# End Source File
# End Group
# Begin Group "DirectMusic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DirectMusic.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectMusic.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DDrawProc.cpp
# End Source File
# End Group
# Begin Group "Game準備、解放"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameInit.cpp
# End Source File
# Begin Source File

SOURCE=.\GameInit.h
# End Source File
# End Group
# Begin Group "WinProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WinProc.cpp
# End Source File
# Begin Source File

SOURCE=.\WinProc.h
# End Source File
# End Group
# Begin Group "描画関数"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BltProc.cpp
# End Source File
# Begin Source File

SOURCE=.\BltProc.h
# End Source File
# End Group
# Begin Group "セーブ、ロード関数"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SaveLoadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\SaveLoadProc.h
# End Source File
# End Group
# Begin Group "GameProc"

# PROP Default_Filter ""
# Begin Group "表示処理関数"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BackProc.cpp
# End Source File
# Begin Source File

SOURCE=.\GameBltProc.cpp
# End Source File
# End Group
# Begin Group "ゲーム処理、判定関数"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameCheckProc.cpp
# End Source File
# Begin Source File

SOURCE=.\MapProc.cpp
# End Source File
# Begin Source File

SOURCE=.\StageEvent.cpp
# End Source File
# End Group
# Begin Group "キャラアクション関数"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\EnemyAct.cpp
# End Source File
# Begin Source File

SOURCE=.\GameChrAct.cpp
# End Source File
# End Group
# Begin Group "GameProcのヘッダ"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BackProc.h
# End Source File
# Begin Source File

SOURCE=.\EnemyAct.h
# End Source File
# Begin Source File

SOURCE=.\GameBltProc.h
# End Source File
# Begin Source File

SOURCE=.\GameCheckProc.h
# End Source File
# Begin Source File

SOURCE=.\GameChrActProc.h
# End Source File
# Begin Source File

SOURCE=.\MapProc.h
# End Source File
# Begin Source File

SOURCE=.\StageEventProc.h
# End Source File
# End Group
# End Group
# Begin Group "構造体の型の定義"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\GameStruct.h
# End Source File
# End Group
# Begin Group "DebugProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DebugProc.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugProc.h
# End Source File
# End Group
# End Target
# End Project
