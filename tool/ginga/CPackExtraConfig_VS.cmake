SET(CPACK_NSIS_PACKAGE_NAME "ginga.ar 2.0.0")
SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
	StrCpy $FONT_DIR $FONTS
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\TIRESIAS.TTF\\\"
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\TIRESIAS-ITALIC.TTF\\\"
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\TIRESIAS-BOLD.TTF\\\"
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\DEJAVUSANS.TTF\\\"
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\DEJAVUSANS-BOLD.TTF\\\"
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\DEJAVUSANS-ITALIC.TTF\\\"
	!insertmacro InstallTTF \\\"\\\${INST_DIR}\\\\share\\\\ginga\\\\font\\\\DEJAVUSANS-BOLDITALIC.TTF\\\"
	!insertmacro APP_ASSOCIATE \\\"ncl\\\" \\\"ginga.ncl\\\" \\\"\\\$INSTDIR\\\\bin\\\\ginga.exe,0\\\" \\\"NCL app\\\" \\\"\\\$INSTDIR\\\\bin\\\\ginga.exe --ncl \\\$\\\\\\\"%1\\\$\\\\\\\"\\\" \\\"\\\$INSTDIR\\\\bin\\\\ginga.exe --ncl \\\$\\\\\\\"%1\\\$\\\\\\\"\\\"
	!define env_hklm 'HKLM \\\"SYSTEM\\\\CurrentControlSet\\\\Control\\\\Session Manager\\\\Environment\\\"'
	WriteRegExpandStr \\\${env_hklm} \\\"GINGA_PROCESS\\\" \\\"\\\$INSTDIR\\\\bin\\\\ginga.exe\\\"
")