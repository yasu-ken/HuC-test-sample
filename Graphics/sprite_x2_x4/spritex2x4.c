/*

	SPRITE X2 X4 SAMPLE

    x1    x2       x4

    1 --> 1 2 --> 1 2 9 A
          3 4     3 4 B C
                  5 6 D E
                  7 8 F 10
*/

#include "huc.h"


#incspr(spr_01,  "sprite.pcx",0, 0, 2,4)  /*(0,0)  2x4sprite 1chank */
#incpal(spritepalett,  "sprite.pcx", 0)   /* palette */


/* 128byte = 64word. 64x4=256 */
int buf16x16[64];    /* 1sprite = 64 words */
int buf2x2spr[256];  /* 2x2sprite = 64x4 words */


const int ofset_tbl[32]={
	0x0000,0x0000,0x0001,0x0001,0x0002,0x0003,0x0004,0x0006,
	0x0009,0x000b,0x000d,0x000e,0x000f,0x000f,0x0010,0x0010,
	0x0010,0x0010,0x000f,0x000f,0x000e,0x000d,0x000b,0x0009,
	0x0006,0x0004,0x0003,0x0002,0x0001,0x0001,0x0000,0x0000
	};


/***********************************************/
/* Sprite 1x1 ---> 2x2                         */
/***********************************************/

set_2x2(srcadr,vadr)
int srcadr[];
int vadr;
{
	int offs;
	int i,wok,wok2,wok3;

	for( i=0 ; i<64 ; i++ )
	{
		buf16x16[i] = srcadr[i];
	}

	for( i=0; i<64;i++){ /* 16x4plane */
		wok2=0;
		wok3=0;
		wok = buf16x16[i];
		wok >>= 8;
		if( wok & 0x80 ) wok2 |= 0xc000;
		if( wok & 0x40 ) wok2 |= 0x3000;
		if( wok & 0x20 ) wok2 |= 0x0c00;
		if( wok & 0x10 ) wok2 |= 0x0300;
		if( wok & 0x8 )  wok2 |= 0x00c0;
		if( wok & 0x4 )  wok2 |= 0x0030;
		if( wok & 0x2 )  wok2 |= 0x000c;
		if( wok & 0x1 )  wok2 |= 0x0003;

		wok = buf16x16[i];
		wok &= 0xff;
		if( wok & 0x80 ) wok3 |= 0xc000;
		if( wok & 0x40 ) wok3 |= 0x3000;
		if( wok & 0x20 ) wok3 |= 0x0c00;
		if( wok & 0x10 ) wok3 |= 0x0300;
		if( wok & 0x8 )  wok3 |= 0x00c0;
		if( wok & 0x4 )  wok3 |= 0x0030;
		if( wok & 0x2 )  wok3 |= 0x000c;
		if( wok & 0x1 )  wok3 |= 0x0003;

		if( i <8){       /* 0...7*/
			wok = i;
			offs = 0;
		}
		else if( i <16){       /* 0...7*/
			wok = i-8;
			offs = 128;
		}
		else if( i <24){
			wok = i-16;
			offs = 16;
		}
		else if( i <32){
			wok = i-24;
			offs = 128+16;
		}
		else if( i <40){
			wok = i-32;
			offs = 32;
		}
		else if( i <48){
			wok = i-40;
			offs = 128+32;
		}
		else if( i <56){
			wok = i-48;
			offs = 48;
		}
		else{
			wok = i-56;
			offs = 128+48;
		}

		if(vadr==buf2x2spr)
		{
			wok <<= 1;
			buf2x2spr[offs+wok]=wok2;
			buf2x2spr[offs+1+wok]=wok2;
			buf2x2spr[offs+64+wok]=wok3;
			buf2x2spr[offs+65+wok]=wok3;
		}
		else
		{
			wok <<= 1;
			put_raw(wok2,vadr+(offs+wok));
			put_raw(wok2,vadr+(offs+wok+1));
			put_raw(wok3,vadr+(offs+wok+64));
			put_raw(wok3,vadr+(offs+wok+65));
		}
	}
}



/***********************************************/
/* main                                        */
/***********************************************/

main()
{
	int loopcnt;
	int val,i;

	disp_off();
	cls();
	vsync();

	/*load_sprites(0x4000,  spr_exp, 8);   8chank = 8x8 = 64sprite = 1bank */

	load_palette(16, spritepalett,1);    /* spritePalette No.0 = palette 16 */


	/*--------------------------------------------------*/
	/* 1x1Sprite Display                                */
	/*                                                  */
	/* 1x1 Sprite-> VramAdress 0x5000                   */
	/*--------------------------------------------------*/
	load_sprites(0x5000,  spr_01, 1);   /* 1chank = 2x4 = 8sprite */


	/*--------------------------------------------------*/
	/* 2x2Sprite Display                                */
	/*                                                  */
	/* 1x1 Sprite-> 2x2Sprite(VramAdress 0x5100)        */
	/*    []-->[][]                                     */
	/*         [][]                                     */
	/*--------------------------------------------------*/

	/* ! spr_01 is Far Adress Data.  */
	/* Far Data copy to local.       */
	for( i=0 ; i<64 ; i++ )
	{
		buf16x16[i] = spr_01[i];
	}

	set_2x2(buf16x16,0x5100);    /* 2x2Sprite   set to VideoRam */

	/*--------------------------------------------------*/
	/* 4x4Sprite Display                                */
	/*                                                  */
	/* 1x1 Sprite => 2x2Sprite(RamBuffer)               */
	/* RamBuffer  => 4x4(2x2 x4) Sprite                 */
	/*                 0x5400 Left Up 2x2               */
	/*                 0x5500 Right Up 2x2              */
	/*                 0x5600 Left Down 2x2             */
	/*                 0x5700 Right Down 2x2            */
	/*                                                  */
	/*    [ ]-->[0][1]-->[0][0][1][1]                   */
	/*          [2][3]   [0][0][1][1]                   */
	/*                   [2][2][3][3]                   */
	/*                   [2][2][3][3]                   */
	/*--------------------------------------------------*/

	/* ! spr_01 is Far Adress Data.  */
	/* Far Data copy to local.       */
	for( i=0 ; i<64 ; i++ )
	{
		buf16x16[i] = spr_01[i+64];
	}

	set_2x2(buf16x16,buf2x2spr );  /* 2x2Sprite set to Ram Buffer */

	/* 2x2 LeftUp LeftDown RightUp RIghtDown ---> 2x2 ----> 4x4Sprite*/

	set_2x2(&buf2x2spr[0],  0x5400 );  /* Left Up */
	set_2x2(&buf2x2spr[128],0x5500);  /* Right Up */
	set_2x2(&buf2x2spr[64], 0x5600); /* Left Down */
	set_2x2(&buf2x2spr[192],0x5700); /* Right Down */

	vsync();

	spr_set(0);
	spr_x(100);
	spr_y(20);
	spr_pattern(0x5000);
	spr_pal(16);
	spr_ctrl( SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP ); /* 1x1sprite 16x16dot */
	spr_pri(1);

	spr_set(1);
	spr_x(100);
	spr_y(60);
	spr_pattern(0x5100);
	spr_pal(16);
	spr_ctrl( SIZE_MAS|FLIP_MAS, SZ_32x32|NO_FLIP );  /* 2x2sprite 32x32dot */
	spr_pri(1);


	/* 2x2Sprite x4  == 2x4spr(1chank) x2 */
	spr_set(2);
	spr_y(100);
	spr_pattern(0x5400);
	spr_pal(16);
	spr_ctrl( SIZE_MAS|FLIP_MAS, SZ_32x64|NO_FLIP );  /* 2x4sprite */
	spr_pri(1);
	spr_set(3);
	spr_y(100);
	spr_pattern(0x5600);
	spr_pal(16);
	spr_ctrl( SIZE_MAS|FLIP_MAS, SZ_32x64|NO_FLIP );  /* 2x4sprite */
	spr_pri(1);

	disp_on();

	put_string("abcdefg",10,10);

	for(;;)
	{
		/* 1x1 sprite */
		spr_set(0);
		spr_y(20+ofset_tbl[(loopcnt+20)&0x1f]);
		spr_x(loopcnt-128);

		/* 2x2 */
		spr_set(1);
		spr_y(60+ofset_tbl[loopcnt&0x1f]);
		spr_x(loopcnt-96);


		/* 2x4 sprite x2 (4x4) */
		spr_set(2);
		spr_y(100+ofset_tbl[(loopcnt+10)&0x1f]);
		spr_x(loopcnt-64);
		spr_set(3);
		spr_y(100+ofset_tbl[(loopcnt+10)&0x1f]);
		spr_x(loopcnt-64+32);

		loopcnt++;
		if(loopcnt>(384))loopcnt=0;

		vsync();
		satb_update();
	}
}

