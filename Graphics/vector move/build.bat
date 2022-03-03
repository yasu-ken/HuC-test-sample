SET PATH=c:\huc\bin;c:\huc\include\pce
SET PCE_INCLUDE=c:\huc\include\pce

bmp2PCE -LX128 -LY128 -PAL1 spr64.bmp

del *.pce
del sprite64demo.s

huc.exe -v sprite64demo.c > error.txt

