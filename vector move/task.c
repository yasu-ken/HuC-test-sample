
/* FLAG, direction, x,y */

char task_Flag[TASK_MAX];
char task_Dir[TASK_MAX];
int task_Xloc[TASK_MAX];
int task_Yloc[TASK_MAX];

tasks_inz()
{
	char i;
	for( i=0; i<TASK_MAX; i++ )
	{
		task_Flag[i] = 1;
		task_Dir[i]     = i;     /* 0-63 */
		task_Xloc[i]  =(256/2)<<6;
		task_Yloc[i]  =(224/2)<<6;
	}
}

tasks_Move()
{
	char i;
	int xx,yy;

	for( i=0 ; i<TASK_MAX ; i++ )
	{
		if( task_Flag[i] != 0 )
		{

			vector_move(1,task_Dir[i],&xx, &yy);

			task_Xloc[i]+= xx;
			task_Yloc[i]+= yy;

			/* Fixed decimal point. (The upper 10 bits are integers.) */ 
			xx = task_Xloc[i]>>6;
			yy = task_Yloc[i]>>6;

			if( xx > (256-8) )task_Dir[i] = (task_Dir[i]+0x20) & 0x3f;
			if( xx < 8 ) task_Dir[i] = (task_Dir[i]+0x20) & 0x3f;
			if( yy > (224-8) )task_Dir[i] = (task_Dir[i]+0x20) & 0x3f;
			if( yy < 8 ) task_Dir[i] = (task_Dir[i]+0x20) & 0x3f;
		}
	}
}


tasks_Render()
{
	char i;

	for( i=0 ; i<TASK_MAX ; i++ )
	{
		if( task_Flag[i] != 0 )
		{
			spr_set(i);
			spr_pal(17);
			spr_pattern(0x4000+(i*0x40)); /* 1sprite $40word (<<7) */
			spr_ctrl( SIZE_MAS|FLIP_MAS, SZ_16x16|NO_FLIP );    /* 16x16dot sprite */
			spr_x((task_Xloc[i]>>6)-8);
			spr_y((task_Yloc[i]>>6)-8);
		}
	}
}
