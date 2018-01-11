//déplacement, détection touches

void Move()
{
	a +=  speed1*cos(M_PI/180*angle1);
	b +=  speed1*sin(M_PI/180*angle1);
	if(animate && ckey==122 && (int) a - a > -0.1 && angle1 != 270)      //z
	{
		if (Open(a,b-1))
		{
			animate = true;
			angle1 = 270;
		}
	}

	else if(animate && ckey==115 && (int) a - a > -0.1 && angle1 != 90)// s
	{
		if (Open(a,b+1))
		{
			animate = true;
			angle1= 90;
		}
	}

	else if(animate && ckey==113 && (int) b - b > -0.1 && angle1 != 180)//q
	{
		if (Open(a-1,b))
		{
			animate = true;
			angle1 = 180;
		}
	}

	else if(animate && ckey==100 && (int) b - b > -0.1 && angle1 != 0)//d
	{
		if (Open(a+1,b))
		{
			animate = true;
			angle1 = 0;
		}
	}
}


//touches spéciales

void mykey(unsigned char key,int x,int y)
{

	if (start_timer > 0)
	{
		start_timer--;
	}
	if(key==27) //echap
		exit(0);
	if(key==112) //'p' pour pause
		paused=!paused;
	if(key==114){ //'r' pour restart
		P_Reinit();
		G_Reinit();
		tp_restore();
		points=0;
		lives=3;
		paused=false;
		gameover=false;
	}
	if(key==99) //'c' pour camera
		camera=!camera;
	if(!paused){
		if (start_timer > 0)
			start_timer--;
		ckey=key;
		if(key==122 && (int) a - a > -0.1 && angle1 != 270) //z 
		{
			if (Open(a, b - 1))
			{
				animate = true;
				angle1 = 270;
			}
		}

		else if(key==115 && (int) a - a > -0.1 && angle1 != 90)// s
		{
			if (Open(a,b + 1))
			{
				animate = true;
				angle1= 90;
			}
		}

		else if(key==113 && (int) b - b > -0.1 && angle1 != 180)//q
		{
			if (Open(a-1,b))
			{
				animate = true;
				angle1 = 180;

			}
		}

		else if(key==100 && (int) b - b > -0.1 && angle1 != 0)//d
		{
			if (Open(a+1, b))
			{
				animate = true;
				angle1 = 0;
			}
		}
	}

}