!include "MUI2.nsh"

Name "Todo List"
Outfile "$%NSIS_OUTPUT_DIR%\install.exe"
Unicode True

InstallDir "$APPDATA\Todo List"

!define MUI_ABORTWARNING
!define MUI_FINISHPAGE_RUN "$INSTDIR\TodoList.exe"
!define MUI_FINISHPAGE_RUN_TEXT "Run TodoList"

!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_LANGUAGE English

Section
    SetOutPath "$INSTDIR"
    File /r "$%NSIS_INPUT_DIR%\*"
    File "icon.ico"
    CreateShortcut "$DESKTOP\TodoList.lnk" "$INSTDIR\TodoList.exe" "" "$INSTDIR\icon.ico" 0
    WriteUninstaller "$INSTDIR\uninstall.exe"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TodoList" "DisplayName" "Todo List"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TodoList" "DisplayIcon" "$INSTDIR\icon.ico"
    WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TodoList" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
    ExecWait "$INSTDIR\vc_redist.x64.exe"
    installed:
SectionEnd

Section "Uninstall"
    Delete "$INSTDIR\uninstall.exe"
    Delete "$DESKTOP\TodoList.lnk"
    RMDir /r "$INSTDIR"
    DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\TodoList"
SectionEnd