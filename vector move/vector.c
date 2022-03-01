
/* 0.5 dot vector table x, y */
const int vector_table[32]={
			255/4,    0/4,   /* dir 0-16(xvector ,yvector) */
			254/4,   25/4,
			251/4,   50/4,
			244/4,   74/4,
			236/4,   98/4,
			225/4,  120/4,
			212/4,  142/4,
			198/4,  162/4,
			181/4,  181/4,
			162/4,  198/4,
			142/4,  212/4,
			120/4,  225/4,
			 98/4,  236/4,
			 74/4,  244/4,
			 50/4,  251/4,
			 25/4,  254/4
	};



vector_move(spd,dir,xx,yy)
char spd;
char dir;
int  *xx;
int  *yy;
{
	char dtloc;
	int spdvec1,spdvec0;
	int spdxwok,spdywok;

	dir &= 0x3f;
	dtloc = (dir & 0x0f)<<1;

	spdvec0 = vector_table[dtloc];
	spdvec1 = vector_table[dtloc+1];

	if( dir >= 48){
		spdywok = -spdvec1;
		spdxwok = -spdvec0;
	}
	else if( dir >= 32){
		spdywok =  spdvec0;
		spdxwok = -spdvec1;
	}
	else if( dir >= 16){
		spdywok =  spdvec1;
		spdxwok =  spdvec0;
	}
	else{
		spdywok = -spdvec0;
		spdxwok =  spdvec1;
	}

	*xx = spdxwok;
	*yy = spdywok;
}

