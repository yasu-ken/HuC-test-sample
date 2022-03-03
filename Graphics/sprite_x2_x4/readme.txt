
Sprite 2x magnification 4x magnification test.

The image is expanded by programming.

If you use it during the game, it is a heavy process and 
cannot be used during the game loop.
Processes during screen darkening before the start of the stage.

*********************************************************************************
structure

Function: Sprite double enlargement process

set_2x2(srcadr,vadr)
  srcadr   graphic data adress (source adress)
  vadr     vram adress $0000-$ffff (destination adress)


"srcadr" is cannot be apply "far adress".
Therefore, cannot be used directly by address name 
specified by #incbin or #incspr.
Transfer to the near area once. Specify that address
in the function.
The transfer amount of one sprite is 64 words ($ 40 words).


#incspr(spr_01,"sprite.pcx",0, 0, 2,4)

	for( i=0 ; i<64 ; i++ )      /* one sprite is 64words. */
		buf16x16[i] = spr_01[i];

	set_2x2(buf16x16,0x5100);    /* 2x2Sprite   set to VideoRam */

*********************************************************************************
x4 times

Set the forwarding destination of set_2x2(srcadr, vadr)
to ram instead of vram.
And by multiplying it by x2, it will be quadrupled.

The sprite multiplied by x4 is There are two 2x4 extended sprites.

*********************************************************************************
value
  1 sprite is $40 words.
  The word unit is the same value in vram's address calculation.

  Sprite 1x1 $40
         2x2 $100
         2x4 $200
             (word)
