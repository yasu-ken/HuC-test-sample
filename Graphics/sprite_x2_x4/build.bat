SET PATH=c:\huc\bin;c:\huc\include\pce
SET PCE_INCLUDE=c:\huc\include\pce

del *.pce
del *.s
del *.lst
huc.exe -v spritex2x4.c > errors.txt

