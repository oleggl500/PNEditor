@REM Makes documents

SET GRAPHVIZPATH=c:\otherProgs\GraphWiz\bin
SET PATH=%GRAPHVIZPATH%;%PATH%
SET DOXYRUN="c:\Program Files\doxygen\bin\doxygen.exe"

start %DOXYRUN% Doxyfile