void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x,y);

	for (c=string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}


void Write(char *string)
{
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}

void print(char *string)
{
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}


void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if(camera){
		glRotatef(angle, 1.0f, 0.0f, 0.0f);
		camera=!camera;
		if(angle==-60)
			angle=-300;
		else
			angle=-60;
	}

	if ((int)a == 27 && (int) b == 14 && angle1 == 0)
	{
		a = 0;
		animate = true;
	}

	else
	if ((int)(a + 0.9) == 0 && (int) b == 14 && angle1 == 180)
	{
		a = 27;
		animate = true;
	}

	if(animate && !paused)
		Move();

	if(!(Open((int)(a + cos(M_PI/180*angle1)),
			  (int)(b + sin(M_PI/180*angle1)))) &&
	   a - (int)a < 0.1 && b - (int)b < 0.1)

		animate = false;

	//bille normale

	if (tp_array[(int)(b+0.5)][(int)(a+0.5)]== 1)
	{
		tp_array[(int)(b+0.5)][(int)(a+0.5)]= 0;
		pebbles_left--;
		points+=10;
	}


	//bille spéciale

	else if(tp_array[(int)(b+0.5)][(int)(a+0.5)] == 3)
	{
		tp_array[(int)(b+0.5)][(int)(a+0.5)]= 0;
		pebbles_left--;

		for (int i = 0; i < 4; i++)
		{
			if (!ghost[i]->eaten)
				ghost[i]->Vulnerable(); //rend le fantôme vulnérable
		}
	}

	//toutes les billes mangées
	if (pebbles_left == 0)
	{
		glDisable(GL_LIGHTING);
		glColor3f(0,1,0);
		char S[]="VICTOIRE";
		renderBitmapString(-4, 0.5,GLUT_BITMAP_HELVETICA_18 ,S);
		gameover=true;
		glEnable(GL_LIGHTING);
	}

	Draw();


	for (int d = 0; d < num_ghosts; d++)
	{

		if (!gameover && start_timer == 0 && !paused)
			ghost[d]->Update();

		if (!ghost[d]->in_jail &&
			ghost[d]->x - (int)ghost[d]->x < 0.1 && ghost[d]->y - (int)ghost[d]->y < 0.1)
		{

			bool open_move[4];

			for (int ang = 0; ang < 4; ang++)
			{
				open_move[ang] = Open((int)(ghost[d]->x + cos(M_PI/180*ang*90)),
									  (int)(ghost[d]->y + sin(M_PI/180*ang*90)));

			}

			if (!ghost[d]->eaten)
			{
				if(ghost[d]->x - (int)ghost[d]->x < 0.1 && ghost[d]->y - (int)ghost[d]->y < 0.1)
					ghost[d]->Chase(a, b, open_move);
			}

			else
			{
				if(ghost[d]->x - (int)ghost[d]->x < 0.1 && ghost[d]->y - (int)ghost[d]->y < 0.1)
					ghost[d]->Chase(13, 11, open_move);
			}
		}


		if (ghost[d]->in_jail && !(Open((int)(ghost[d]->x + cos(M_PI/180*ghost[d]->angle)),
										(int)(ghost[d]->y + sin(M_PI/180*ghost[d]->angle)))) && ghost[d]->jail_timer > 0   &&ghost[d]->x - (int)ghost[d]->x < 0.1 && ghost[d]->y - (int)ghost[d]->y < 0.1)
		{
			ghost[d]->angle = (double)(((int)ghost[d]->angle + 180)%360);
		}


		if (!gameover && start_timer == 0 && !paused)
			ghost[d]->Move();
		ghost[d]->Draw();

		if(!(ghost[d]->eaten))
		{
			bool collide = ghost[d]->Catch(a,b);

			//fantôme qui mange Pacman

			if(lives>0)
			{
				if (collide && !(ghost[d]->edible))
				{
					lives--;

					if (lives == 0)
					{
						gameover = true;
						lives=0;
						ghost[d]->game_over();
						paused=true;
					}
					G_Reinit(); //on remet les fantômes à leur place initiale
					P_Reinit(); //on remet Pacman à sa place
					d = 4;
				}

				//si Pacman mange un fantôme

				else if (collide && ghost[d]->edible)
				{
					points += 200;
					ghost[d]->edible = false;
					ghost[d]->eaten = true;
					ghost[d]->speed = 1;
				}
			}

		}
	}

    glDisable(GL_LIGHTING);

	if(gameover==true && pebbles_left!=0) {
        glColor3f(1, 0, 0);
        char S[] = "GAME OVER";
        renderBitmapString(-4.3, 0.5, GLUT_BITMAP_HELVETICA_18, S);
    }

    //affichage du menu
    
    glColor3f(0, 1, 0);
	glRasterPos2f(10, 20.5);
	sprintf(tmp_str, "Points: %d", points);
	Write(tmp_str);

	glColor3f(1, 1, 1);
	glRasterPos2f(-16, 17.5);
	sprintf(tmp_str, "zqsd : move / c : cam");
	Write(tmp_str); 

	glColor3f(1, 1, 1);
	glRasterPos2f(-3, 17.5);
	sprintf(tmp_str, "p : pause / r : restart / esc : quit");
	Write(tmp_str);

	glColor3f(1, 1, 1);
	glRasterPos2f(-6, 20.5);
	sprintf(tmp_str, "IMACMAN 3D");
	print(tmp_str);

	glColor3f(1, 1, 1);
	glRasterPos2f(-16, 20.5);
	sprintf(tmp_str, "Vies: %d", lives);
	Write(tmp_str);

	if(paused){
		glColor3f(1, 0, 0);
		glRasterPos2f(10,-3);
		sprintf(tmp_str, "Pause");
		Write(tmp_str);
	}

	glutPostRedisplay();
	glutSwapBuffers();

	glEnable(GL_LIGHTING);
}

void init()
{
	float color[4];
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	//lumière ambiante et diffuse
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f; color[3] = 0.0f;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

	color[0] = 1.0f; color[1] = 0.0f; color[2] = 1.0f; color[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, color);

	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60,1.33,0.005,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1.5, 0, 40, -1.5, 0, 0, 0.0f,1.0f,0.0f);
}