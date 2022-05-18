set PATH=C:\Qt5\5.3\msvc2013_64_opengl\bin;%PATH%\
@echo %time%
C:\repository\PythonQtOnSourceForge\sf\pythonqt\trunk\generator\release\pythonqt_generator.exe --output-directory=C:\repository\dev\MeVisLab\Standard\Sources\Bindings --include-paths=C:\repository\dev\MeVis\ThirdParty\Sources\Inventor\include global.h typesystem_Inventor_all.xml 
@echo %time%
