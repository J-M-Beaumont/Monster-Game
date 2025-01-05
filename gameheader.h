#include <stdio.h>
#include <stdlib.h>
#define playerr '@'
#define space '.'
#define wall '='
#define enemysub '*'
#define finish '#'
#define UP '^'
#define DOWN 'v'
#define LEFT '<'
#define RIGHT '>'
#define INTERIOR '-'
#define BEARTRAP '~'
#define TRAP '%'
#define BOMB '%'
void printworld(void);
void NORTHmove(void);
void SOUTHmove(void);
void EASTmove(void);
void WESTmove(void);
void loadworld(void);
void levelchange(void);
void buildwall(char mode[10]);
void playback(void);
void exiting(void);
void loadworld(void);
void changeterminal(void);
void changeterminalback(void);
struct mob
{
	char (*player)[20]; //defines pointer to an array
	int y,x;
	_Bool isnulled;
	_Bool halted;
	int startposy,startposx;
};
struct missile{
	char * pt;
	int y,x;
	int startposy,startposx;
};
typedef struct missile MISSILE;

typedef struct mob mob;
