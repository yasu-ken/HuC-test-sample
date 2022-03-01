
HuC ( PC-Engine C language compiler ) test & sample code.

-----------------------------------------
Where is huc ?

github
https://github.com/dshadoff/huc
https://github.com/uli/huc

DevKit HomePage
http://www.magicengine.com/mkit/
(16bit)

Zophar's Domain(development->pce)
https://www.zophar.net/
(16bit)

Zeograd's lair(->HuC)
https://www.zeograd.com/index.php
(16bit)

-----------------------------------------
HuC installation( Windows )

c:\Huc\bin\        -----> huc.exe etc. (exec file)
      \include\pce ----> startup.asm huc.h. etc. (include file)


bmp2PCE.exe
https://github.com/yasu-ken/bmp2PCE
  --->  c:\Huc\bin\

-----------------------------------------
Compile example( Windows )

( build.bat )
SET PATH=c:\huc\bin;c:\huc\include\pce
SET PCE_INCLUDE=c:\huc\include\pce
huc.exe -v test.c > errors.txt

-----------------------------------------
Licence.

These samples All are free software.
Can be freely modified and reused.
Use is at your own risk.
