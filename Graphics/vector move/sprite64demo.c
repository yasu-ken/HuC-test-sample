#include "huc.h"

#define TASK_MAX 64

#include "vector.c"
#include "task.c"


#incbin(spriteGraphic,"spr64.bin")

#incbin(palette_cursol,  "spr64.pal")

int taskX;
int taskY;

main()
{
	int xx,yy;
	char dir;
	char i;
	dir =0;

	/* screen center */
	taskX=120<<6;
	taskY=120<<6;

	disp_off();
	vsync();
	set_screen_size(0x00);    /* Screen size 32x32 */
	cls();

	/* move sprites out of screen. */
	for(i=0;i<64;i++)
	{
		spr_set(i);
		spr_x(500);
		spr_y(500);
	}

	load_sprites(0x4000,  spriteGraphic, 8);  /* 8chank */
	load_palette(17, palette_cursol,1);    /* 16= spritepal no. 0 */

	tasks_inz();

	vsync();
	disp_on();

	dir=64;
	for(;;){

		if(joy(0)&JOY_UP){
			dir=0;
		}
		if(joy(0)&JOY_RGHT){
			dir=16;
		}
		if(joy(0)&JOY_DOWN){
			dir=32;
		}
		if(joy(0)&JOY_LEFT){
			dir=48;
		}

		if( dir != 64 )
			vector_move(2,dir,&xx, &yy);

		taskX+=xx;
		taskY+=yy;

		spr_set(62);
		spr_pal(17);
		spr_pattern(0x4000);
		spr_ctrl( SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP );
		spr_x((taskX>>6)-8);
		spr_y((taskY>>6)-8);

		tasks_Move();
		tasks_Render();

		vsync();
		satb_update();          /* satbupdate-> vsynk() no jun de su */

	}
}
