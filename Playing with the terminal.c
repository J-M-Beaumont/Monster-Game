#include <stdio.h>
#include <ctype.h>
#include "gameheader.h"
#include <termios.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
char world[10][20];
static int count = 0;
int walls = 5;
mob player;
mob enemy;
mob enemy1;
MISSILE bomb;
MISSILE bomb1;
MISSILE bomb2;
MISSILE bomb3;
MISSILE bomb4;
FILE * levelplayback;
FILE * fp;
void main (void)
{		
	player.y = 8;
	player.x = 16;
	enemy.y = 1;
	enemy.x = 3;
	enemy1.x = 1;
	enemy1.y = 1;
	bomb.x = 1;
	bomb.y = 1;
	printf("controls are:\n");
	printf("w to move up,\n");
	printf("s to move down,\n");
	printf("d to move right\n");
	printf("a to move left,\n");
	printf("q quits,\n");
	printf("c skips your move\n");
	printf ("which level would you like to load\n");
	scanf ("%1d",&count);
	if (count != 0 && count <= 8) {
		count -= 1;
		printf("loading level");
		sleep(1);
		//count -= 1;
		levelchange ();
	} else {
		count = 0;
		system("clear");
		printf ("Invalid input \n loading level 1 \n");
		sleep(1);
		levelchange();
	} printworld ();
	player.player = &(world[player.y][player.x]);
	enemy.player = &(world[enemy.y][enemy.x]);
	**player.player = playerr;
	**enemy.player = enemysub;
	changeterminal();
	mainbody();
	return 0;
}
void mainbody(void)
{
    int ch,c;
    printworld ();
	while (ch != 'q') {
			player.player = &(world[player.y][player.x]);
			enemy.player = &(world[enemy.y][enemy.x]);
			**player.player = playerr;
			**enemy.player = enemysub;			
			if (world[player.y + 1][player.x] == finish || world[player.y - 1][player.x] == finish || world[player.y][player.x + 1] == finish || world[player.y][player.x - 1] == finish){
				levelchange ();
			} if (count == 6 || count == 9){
				enemy1.player = &(world[enemy1.y][enemy1.x]);
				enemyalgorithm (&enemy1);
			} if (count == 9){
				//missilealgorithm (&bomb,4,1);
				missilealgorithm (&bomb1,7,3);
				missilealgorithm (&bomb2,6,3);
				missilealgorithm (&bomb3,18,16);
				missilealgorithm (&bomb4,18,16);
			} if (bomb.x == player.x && bomb.y == player.y && count == 9){
				*bomb.pt = BOMB;
				printworld (); 
				printf ("GAME OVER");
				exit (EXIT_SUCCESS);
			} if (ch = getchar ()){
				switch (ch)
				{
					case 'w':
						NORTHmove ();					
						enemyalgorithm (&enemy);
						continue;
					case 's':
						SOUTHmove ();
						enemyalgorithm (&enemy);
						continue;
					case 'd':
						EASTmove ();
						enemyalgorithm (&enemy);
						continue;
					case 'a':
						WESTmove ();
						enemyalgorithm (&enemy);
						continue;
					case 'i':
						buildwall ("BUILDNORTH");
						//enemyalgorithm (&enemy);
						continue;
					case 'k':
						buildwall ("BUILDSOUTH");
						//enemyalgorithm (&enemy);
						continue;
					case 'j':
						buildwall ("BUILDWEST");
						//enemyalgorithm (&enemy);
						continue;
					case 'l':
						buildwall ("BUILDEAST");
						//enemyalgorithm (&enemy);
						continue;
					case 'c':
						enemyalgorithm (&enemy);
						continue;
				
				}
			}
		} changeterminalback ();
		exit(EXIT_SUCCESS);
}
void printworld (void)
{
	system ("clear");
	printf (ANSI_COLOR_CYAN"LEVEL %d \n",count);
	int pwcountY, pwcountX,pwcountY1,pwcountX1;		
	for (pwcountY = 0; pwcountY < 10; pwcountY++) {
		for (pwcountX = 0; pwcountX < 20;pwcountX++) {
			if(world[pwcountY][pwcountX] == wall){
				printf (ANSI_COLOR_RED "=" ANSI_COLOR_GREEN);} 
			else if (world[pwcountY][pwcountX] == playerr){
				printf (ANSI_COLOR_YELLOW "@" ANSI_COLOR_GREEN);}
			else if(world[pwcountY][pwcountX] == UP){
				printf (ANSI_COLOR_CYAN "^" ANSI_COLOR_GREEN);}
			else if(world[pwcountY][pwcountX] == DOWN){
				printf (ANSI_COLOR_CYAN "V" ANSI_COLOR_GREEN);}
			else if(world[pwcountY][pwcountX] == RIGHT){
				printf (ANSI_COLOR_CYAN ">" ANSI_COLOR_GREEN);}
			else if(world[pwcountY][pwcountX] == LEFT){
				printf (ANSI_COLOR_CYAN "<" ANSI_COLOR_GREEN);}
			else if(world[pwcountY][pwcountX] == finish){
				printf (ANSI_COLOR_BLUE "#" ANSI_COLOR_GREEN);}
			/*else if (world[pwcountY][pwcountX] == INTERIOR){
				printf(ANSI_COLOR_RESET "-" ANSI_COLOR_GREEN);}	*/
			else
				printf ("%c",world[pwcountY][pwcountX]);
		} printf ("\n");
	}
}

void NORTHmove (void)	
{
	**player.player = space;
	if (world[player.y - 1][player.x] != wall && world[player.y - 1][player.x] != INTERIOR && player.halted != 1) {	
		player.y -= 1;		
		player.player = &(world[player.y][player.x]);
		if (**player.player == UP){
			**player.player = playerr;	
			NORTHmove ();}
		if (**player.player == DOWN){
			**player.player = playerr;	
			SOUTHmove ();
			SOUTHmove ();}
		if (**player.player == RIGHT){
			**player.player = playerr;	
			EASTmove ();}
		if (**player.player == LEFT){
			**player.player = playerr;	
			WESTmove ();}
		if(**player.player == BEARTRAP){
			player.halted = 1;
			system ("clear");
			printf ("\"oh man i hit a bear trap\"\n");
		}
		if (**player.player == TRAP){
			printworld();
			**player.player = TRAP;
			printworld();
			printf("GAME OVER\n");
			exiting();
		}
	
	}
	if(**player.player != BEARTRAP && player.halted == 1)
	{
		player.halted = 0;
	}
	
	**player.player = playerr;	
}

void SOUTHmove(void)
{

		**player.player = space;	
	if (world[player.y + 1][player.x] != wall && world[player.y + 1][player.x] != INTERIOR && player.halted != 1){	
		player.y += 1;		
		player.player = &(world[player.y][player.x]);
		if (**player.player == UP){
			**player.player = playerr;	
			NORTHmove();}
		if (**player.player == DOWN){
			**player.player = playerr;	
			SOUTHmove();
			SOUTHmove();}
		if (**player.player == RIGHT){
			**player.player = playerr;	
			EASTmove();}
		if (**player.player == LEFT){
			**player.player = playerr;	
			WESTmove();}
		if(**player.player == BEARTRAP){
			player.halted = 1;
			system("clear");
			printf("\"oh man i hit a bear trap\"\n");
		}
		if (**player.player == TRAP){
			printworld();
			**player.player = TRAP;
			printworld();
			printf("GAME OVER\n");
			exiting();
		}
	}
	if(**player.player != BEARTRAP && player.halted == 1)
	{
		player.halted = 0;
	}
	**player.player = playerr;	
}

void EASTmove(void)
{
		**player.player = space;	
	if (world[player.y][player.x + 1] != wall && world[player.y][player.x + 1] != INTERIOR && player.halted != 1){	
		player.x += 1;		
		player.player = &(world[player.y][player.x]);
		if (**player.player == UP){
			**player.player = playerr;	
			NORTHmove();}
		if (**player.player == DOWN){
			**player.player = playerr;	
			SOUTHmove();
			SOUTHmove();}
		if (**player.player == RIGHT){
			**player.player = playerr;	
			EASTmove();}
		if (**player.player == LEFT){
			**player.player = playerr;	
			WESTmove();}
		if(**player.player == BEARTRAP){
			player.halted = 1;
			system("clear");
			printf("\"i hit a bear trap\"\n");
		}
		if (**player.player == TRAP){
			printworld();
			**player.player = TRAP;
			printworld();
			printf("GAME OVER\n");
			exiting();
		}
	}
	if(**player.player != BEARTRAP && player.halted == 1)
	{
		player.halted = 0;
	}
	**player.player = playerr;	
}

void WESTmove(void)
{

		**player.player = space;	
	if (world[player.y][player.x - 1] != wall && world[player.y][player.x - 1] != INTERIOR && player.halted != 1){	
		player.x -= 1;		
		player.player = &(world[player.y][player.x]);
		if (**player.player == UP){
			**player.player = playerr;	
			NORTHmove();}
		if (**player.player == DOWN){
			**player.player = playerr;	
			SOUTHmove();
			SOUTHmove();}
		if (**player.player == RIGHT){
			**player.player = playerr;	
			EASTmove();}
		if (**player.player == LEFT){
			**player.player = playerr;	
			WESTmove();}
		if(**player.player == BEARTRAP){
			player.halted = 1;
			system("clear");
			printf("\"oh man i hit a bear trap\"\n");
		}
		if (**player.player == TRAP){
			printworld();
			**player.player = space;
			printworld();
			printf("GAME OVER\n");
			**player.player = TRAP;
			printworld();
			exiting();
		}	
	}
	if(**player.player != BEARTRAP && player.halted == 1)
	{
		player.halted = 0;
	}
	**player.player = playerr;	
}
void NORTHemove(struct mob * man)
{	
	if(world[man->y - 1][man->x] != wall && world[man->y - 1][man->x] != INTERIOR && world[man->y - 1][man->x] != '/'){ 	
		**man->player = space;
		man->y -= 1;		
		man->player = &(world[man->y][man->x]);
		
		if (**man->player == UP){
			**man->player = enemysub;	
			NORTHemove(man);}
		if (**man->player == DOWN){
			**man->player = enemysub;	
			SOUTHemove(man);
			SOUTHemove(man);}
		if (**man->player == RIGHT){
			**man->player = enemysub;	
			EASTemove(man);}
		if (**man->player == LEFT){
			**man->player = enemysub;	
			WESTemove(man);}
		
		//**man->player = enemysub;
		if(**man->player == BEARTRAP){
			system("clear");
			printf("monster:\"bear traps only effect puny humans and bears\"\n");
		}
		if(**man->player == TRAP){
			man->isnulled = 1;
			system("clear");
			printf("monster:\"AHHHHH\"\n");
		}
	}	
	else if(world[man->y - 1][man->x] == '/'){
		world[man->y - 1][man->x] = space; }
	else if(world[man->y - 1][man->x] == '-'){
		world[man->y - 1][man->x] = '/'; }		
}

void SOUTHemove(struct mob * man)
{	
	if (world[man->y + 1][man->x] != wall && world[man->y + 1][man->x] != INTERIOR && world[man->y + 1][man->x] != '/'){	
		**man->player = space;
		man->y += 1;		
		man->player = &(world[man->y][man->x]);
		if (**man->player == UP){
			**man->player = enemysub;
			NORTHemove(man);}
		if (**man->player == DOWN){
			**man->player = enemysub;	
			SOUTHemove(man);
			SOUTHemove(man);}
		if (**man->player == RIGHT){
			**man->player = enemysub;	
			EASTemove(man);}
		if (**man->player == LEFT){
			**man->player = enemysub;	
			WESTemove(man);}	
		//**man->player = enemysub;
		if(**man->player == BEARTRAP){
			system("clear");
			printf("monster:\"bear traps only effect puny humans and bears\"\n");
		}
		if(**man->player == TRAP){
			man->isnulled = 1;
			system("clear");
			printf("monster:\"AHHHHH\"\n");
		}	
	}
	else if(world[man->y + 1][man->x] == '/'){
		world[man->y + 1][man->x] = space;}
	else if(world[man->y + 1][man->x] == '-'){
		world[man->y + 1][man->x] = '/';}
	
}

void EASTemove(struct mob * man)
{	
	if (world[man->y][man->x + 1] != wall && world[man->y][man->x + 1] != INTERIOR && world[man->y][man->x + 1] != '/'){
		**man->player = space;
		man->x += 1;		
		man->player = &(world[man->y][man->x]);
		//**man->player = enemysub;	
		if (**man->player == UP){
			**man->player = enemysub;	
			NORTHemove(man);}
		if (**man->player == DOWN){
			**man->player = enemysub;	
			SOUTHemove(man);
			SOUTHemove(man);}
		if (**man->player == RIGHT){
			**man->player = enemysub;	
			EASTemove(man);}
		if (**man->player == LEFT){
			**man->player = enemysub;	
			WESTemove(man);}
		//**man->player = enemysub;
		if(**man->player == BEARTRAP){
			system("clear");
			printf("monster:\"bear traps only effect puny humans and bears\"\n");
		}
		if(**man->player == TRAP){
			man->isnulled = 1;
			system("clear");
			printf("monster:\"AHHHHH\"\n");
		}	
	}
	else if(world[man->y][man->x + 1] == '/')
			world[man->y][man->x + 1] = space;
		
	else if(world[man->y][man->x + 1] == '-')
			world[man->y][man->x + 1] ='/';
}

void WESTemove(struct mob * man)
{	
	if (world[man->y][man->x - 1] != wall && world[man->y][man->x - 1] != INTERIOR && world[man->y][man->x - 1] != '/'){	
		**man->player = space;
		man->x -= 1;		
		man->player = &(world[man->y][man->x]);	
		if (**man->player == UP){
			**man->player = enemysub;	
			NORTHemove(man);}
		if (**man->player == DOWN){
			**man->player = enemysub;	
			SOUTHemove(man);
			SOUTHemove(man);}
		if (**man->player == RIGHT){
			**man->player = enemysub;	
			EASTemove(man);}
		if (**man->player == LEFT){
			**man->player = enemysub;	
			WESTemove(man);}
		//**man->player = enemysub;
		if(**man->player == BEARTRAP){
			system("clear");
			printf("monster:\"bear traps only effect puny humans and bears\"\n");
		}
		if(**man->player == TRAP){
			man->isnulled = 1;
			system("clear");
			printf("monster:\"AHHHHH\"\n");
		}
	}
	else if(world[man->y][man->x - 1] == '/')
		world[man->y][man->x - 1] = space;
	else if(world[man->y][man->x - 1] == '-')
		world[man->y][man->x - 1] = '/';
		
}

void enemyalgorithm(struct mob * man)
{
	
	if(man->y < player.y && man->isnulled != 1){	
		SOUTHemove(man);
		**man->player = enemysub;
	}
	if(man->y > player.y && man->isnulled != 1){
		NORTHemove(man);
		**man->player = enemysub;
	} 
	if(man->x < player.x && man->isnulled != 1 ){
		EASTemove(man);
		**man->player = enemysub;
	}
	if(man->x > player.x && man->isnulled != 1){
		WESTemove(man);
		**man->player = enemysub;
	}	
	if(man->y == player.y && man->x == player.x  && man->isnulled != 1){
		**man->player = enemysub;
		printworld();
		printf("GAME OVER\n");
		exiting();}
	if(man->isnulled == 1)
		**man->player = TRAP;
	if(**man->player != BEARTRAP && man->halted == 1)
	{
		man->halted = 0;
	}
	printworld();
}

void levelchange(void)
{
	
	
	count++;
	player.isnulled = 0;
	enemy.isnulled = 0;
	enemy1.isnulled = 0;
	if(count == 1)
	{
		fp = fopen("levels/Level 1/level.dat","a+b");
		levelplayback = fopen("levels/Level 1/playback1.dat","a+b");
		player.startposy = 8;
		player.startposx = 16;
		enemy.startposx = 1;
		enemy.startposy = 3;		
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
	}
	else if (count == 2)
	{
		fp = fopen("levels/Level 2/level2.dat","a+b");
		levelplayback = fopen("levels/Level 2/playback2.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 16;
		enemy.startposx = 10;
		enemy.startposy = 3;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
	}
	else if(count == 3)
	{
		fp = fopen("levels/Level 3/level3.dat","a+b");
		levelplayback = fopen("levels/Level 3/playback3.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 16;
		enemy.startposx = 16;
		enemy.startposy = 3;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
	}
	else if(count == 4){
		fp = fopen("levels/Level 4/level4.dat","a+b");
		levelplayback = fopen("levels/Level 4/playback4.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 2;
		enemy.startposx = 18;
		enemy.startposy = 8;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
	}
		else if(count == 5){
		fp = fopen("levels/Level 5/level5.dat","a+b");
		levelplayback = fopen("levels/Level 5/playback5.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 18;
		enemy.startposx = 5;
		enemy.startposy = 1;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
	}
	
	else if(count == 6){
		fp = fopen("levels/Level 6/level6.dat","a+b");
		levelplayback = fopen("levels/Level 6/playback6.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 18;
		enemy.startposx = 5;
		enemy.startposy = 1;
		enemy1.startposx = 1;
		enemy1.startposy = 1;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
		enemy1.x = enemy.startposx;
		enemy1.y = enemy.startposy;
	}
		
	else if(count == 7){
		fp = fopen("levels/Level 7/level7.dat","a+b");
		levelplayback = fopen("levels/Level 7/playback7.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 18;
		enemy.startposx = 5;
		enemy.startposy = 1;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
		system("clear");
		printf ("New controls are: \n j to place wall west,\n l to place wall east,\n i to place wall north, \n k to place wall south \n");
		sleep(2);
		printworld();
	} else if (count == 8) {
		fp = fopen("levels/Level 8/level8.dat","a+b");
		levelplayback = fopen("levels/Level 8/playback8.dat","a+b");
		player.startposy = 8; //sets value of 8 to player.y
		player.startposx = 18;
		enemy.startposx = 5;
		enemy.startposy = 1;
		player.y = player.startposy;
		player.x = player.startposx;
		enemy.x = enemy.startposx;
		enemy.y = enemy.startposy;
		printworld();
	}
	/*else if(count == 9){
		fp = fopen("levels/Level 9/level9.dat","a+b");
		player.y = 8; //sets value of 8 to player.y
		player.x = 18;
		enemy.x = 16;
		enemy.y = 1;
		enemy1.x = 17;
		enemy1.y = 1;
		bomb.y = 1;
		bomb.x = 1;
		bomb1.x = 3;
		bomb1.y = 2;
		bomb2.x = 4;
		bomb2.y = 3;
		bomb3.x = 16;
		bomb3.y = 4;
		bomb4.x = 16;
		bomb4.y = 5;
		loadworld();
		printworld();
	}*/
	else{
		printworld();
		//system("clear");
		printf("\n*** WINNER *** \n");
		changeterminalback();
		exit(EXIT_SUCCESS);
	}
	loadworld();

}

void buildwall(char mode[10])
{
	if(world[player.y - 1][player.x] != wall && world[player.y - 1][player.x] != enemysub && mode == "BUILDNORTH" && count > 5)
		world[player.y - 1][player.x] = INTERIOR;
	else if(world[player.y + 1][player.x] != wall && world[player.y + 1][player.x] != enemysub && mode == "BUILDSOUTH" && count > 5)
		world[player.y + 1][player.x] = INTERIOR; 
	else if(world[player.y][player.x + 1] != wall && world[player.y][player.x + 1] != enemysub && mode == "BUILDEAST" && count > 5)
		world[player.y][player.x + 1] = INTERIOR;
	else if(world[player.y][player.x - 1] != wall && world[player.y][player.x - 1] != enemysub && mode == "BUILDWEST" && count > 5)
		world[player.y][player.x - 1] = INTERIOR;
	printworld();
}

void EASTmissile(MISSILE * pnt)
{
	//pnt->pt = &(world[pnt->y][pnt->x]);
	*pnt->pt = space;
	if(world[pnt->y][pnt->x + 1] != wall){
		pnt->x += 1;
	}
	pnt->pt = &(world[pnt->y][pnt->x]);
	*pnt->pt = BOMB;
}

void WESTmissile(MISSILE * pnt)
{
	//pnt->pt = &(world[pnt->y][pnt->x]);
	*pnt->pt = space;
	if(world[pnt->y][pnt->x - 1] != wall){
		pnt->x -= 1;
	}
	pnt->pt = &(world[pnt->y][pnt->x]);
	*pnt->pt = BOMB;
}
void missilealgorithm(MISSILE * pnt,int east,int west)
{
	pnt->pt = &(world[pnt->y][pnt->x]);
	static _Bool direction = 1;
	if(pnt->x != east && direction == 1){
		EASTmissile(pnt);
	}
	if(pnt->x == east){
		direction = 0;}
	if(pnt->x == west){
		direction = 1;}
	else if(pnt->x != west && direction == 0){
		WESTmissile(pnt);}
	if(pnt->x == player.x && pnt->y == player.y){
		printf("GAME OVER");
		exiting();
	}
}

void playback(void)
{
	int ch;
	//printf("which level would you like to load\n");
	//scanf("%1d",&count);
	//if(count != 0 && count <= 9){
		//count -= 1;
		//levelchange();}
	//e//lse{
		//count = 1;
		//printf("Invalid input \n loading level 1 \n");
	//}
	
	//loadworld();
	printworld();
	while (ch != 'q'){
			sleep(1);
			if(world[player.y + 1][player.x] == finish || world[player.y - 1][player.x] == finish || world[player.y][player.x + 1] == finish || world[player.y][player.x - 1] == finish){
				levelchange();
			}
			if(count == 6 || count == 9){
				enemy1.player = &(world[enemy1.y][enemy1.x]);
				enemyalgorithm(&enemy1);}
			if(count == 9){
				//missilealgorithm(&bomb,4,1);
				missilealgorithm(&bomb1,7,3);
				missilealgorithm(&bomb2,6,3);
				missilealgorithm(&bomb3,18,16);
				missilealgorithm(&bomb4,18,16);
			}
			printworld();
			if (ch = getc(levelplayback)){
				switch(ch)
				{
					case 'n':
						NORTHmove();					
						enemyalgorithm(&enemy);
						continue;
					case 's':
						SOUTHmove();
						enemyalgorithm(&enemy);
						continue;
					case 'e':
						EASTmove();
						enemyalgorithm(&enemy);
						continue;
					case 'w':
						WESTmove();
						enemyalgorithm(&enemy);
						continue;
					case 'x':
						buildwall("BUILDNORTH");
						//enemyalgorithm(&enemy);
						continue;
					case 'y':
						buildwall("BUILDSOUTH");
						//enemyalgorithm(&enemy);
						continue;
					case 'z':
						buildwall("BUILDWEST");
						//enemyalgorithm(&enemy);
						continue;
					case 'a':
						buildwall("BUILDEAST");
						//enemyalgorithm(&enemy);
						continue;
				
				}
			}
		}
}
void exiting(void)
{
//changeterminalback();
//exit(EXIT_SUCCESS);
	int ch;
	//system("clear");
	printf("q to quit,p to playback game from current level,r to replay level,b to play game from beginning,s to playback game from start\n");
	while((ch = getchar()) != 'q')
	{
		
		if(ch == 'p'){				
			count -= 1;
			levelchange();
			playback();}
		else if(ch == 'r'){
			count -= 1;
			levelchange();
			mainbody();
		} else if(ch == 'b'){
			count = 0;
			levelchange();
			mainbody();
		} else if(ch == 's') {
			count = 0;
			levelchange();
			playback ();
		} else{
			system("clear");
		} printf("q to quit,p to playback game from current level,r to replay level,b to play game from beginning,s to playback game from start\n");
	
	}
	changeterminalback();
	exit(EXIT_SUCCESS);
}
void loadworld(void)
{
	char temp[10][20];	
	fread(temp,sizeof(char),10*20,fp);
	int load,load1;
	for(load = 0; load < 10; load++)
	{
		for (load1 = 0; load1 < 20;load1++)
		{
			if(temp[load][load1] == 'w'){
				world[load][load1] = wall;}
			else if(temp[load][load1] == 's'){
				world[load][load1] = space;}
			else if(temp[load][load1] == 'f'){
				world[load][load1] = finish;}
			else if(temp[load][load1] == 'u'){
				world[load][load1] = UP;}
			else if(temp[load][load1] == 'd'){
				world[load][load1] = DOWN;}		
			else if(temp[load][load1] == 'r'){
				world[load][load1] = RIGHT;}
			else if(temp[load][load1] == 'l'){
				world[load][load1] = LEFT;}						
			else if(temp[load][load1] == 'i'){
				world[load][load1] = INTERIOR;}
			else if(temp[load][load1] == 't'){
				world[load][load1] = TRAP;
			}
			else if(temp[load][load1] == 'b'){
				world[load][load1] = BEARTRAP;
			}
		}
	}
	player.player = &(world[player.y][player.x]);
	enemy.player = &(world[enemy.y][enemy.x]);
	**player.player = playerr;
	**enemy.player = enemysub;
}

void changeterminal(void){
	struct termios change;
	tcgetattr(0,&change);
	change.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(0,TCSANOW,&change);
}
void changeterminalback(void)
{
	printf(ANSI_COLOR_RESET "\n");
	struct termios change;
	tcgetattr(0,&change);
	change.c_lflag |= ECHO;
	tcsetattr(0,TCSANOW,&change);
}
