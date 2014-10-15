#include "TransparentBltU.c"
#include "GetBitmapWidthAndHeight.c"

#define VK_Z				90
#define VK_X				88
#define VK_S				83
#define VK_P				80
#define VK_R				82
#define VK_E				69
#define VK_N				78
#define VK_H				72

#define	WM_memoveupTIMER	WM_USER+2
#define WM_memovedownTIMER	WM_USER+3
#define WM_memoveleftTIMER	WM_USER+4
#define WM_memoverightTIMER	WM_USER+5
#define WM_mebombTIMER		WM_USER+6
#define WM_mainrefreshTIMER WM_USER+7
#define WM_mebulletTIMER	WM_USER+8
#define WM_launchlaserTIMER WM_USER+1
#define WM_regainbloodTIMER WM_USER+9

#define MAINREFRESHGAP		20
#define MEMOVEGAP			3
#define MEFIREGAP			20
#define LAUNCHBOMBGAP		160
#define REMOVELASERGAP		1000
#define REGAINBLOODLATENCY	3000

#define DEFAULTTIME1		0
#define DEFAULTTIME2		500
#define DEFAULTTIME3		1000
#define DEFAULTTIME4		1500

#define BACKGROUNDMOVESPEED 1

#define MAXMEBULLETNUM		35
#define MAXENEMYFLYOBJECT	3
#define MAXENEMYBULLETNUM	300
#define MAXLASERNUM			10
#define MAXBOMBNUM			6
#define MAXMEHARM			300

#define MEBLOODDEFAULT		600
#define MESPEED				4
#define MERADIUS			12
#define MEHARMDEFAULT		100
#define MEBULLETRADIUS		8
#define MEBULLETSPEED		300
#define DEFAULTBOMBNUM		3
#define DEFAULTMELIFE		4
#define BLOODADD			100

#define MAXMELIFE			7
#define ADDALIFESCORE		50000

#define BOMBSPEED			300

#define ICONGAP				5

#define	MOVEDIVISOR			10

#define ENEMYTYPE1			0
#define ENEMYTYPE2			1
#define ENEMYTYPE3			2
#define BOSS				3
#define LASER				3
#define BONUSBOMB			4
#define BONUSFIRE			5
#define BONUSBLOOD			6
#define ENEMYDIVERSITY		7
#define BONUSDIVERSITY		3
#define BULLETDIVERSITY		4

#define ENEMYRADIUS1		17
#define ENEMYRADIUS2		24
#define ENEMYRADIUS3		30
#define BOSSRADIUS			70
#define ENEMYBULLETRADIUS1	5
#define ENEMYBULLETRADIUS2	8
#define ENEMYBULLETRADIUS3	12
#define BONUSBOMBRADIUS		20
#define BONUSFIRERADIUS		20
#define BONUSBLOODRADIUS	10

#define TRACEDIVISOR		50

#define MAXDX				15
#define MAXDY				20
#define MAXBULLETDX			13
#define MAXBULLETDY			13

#define MINSMALLMOVESPEED	5
//#define MAXSMALLMOVESPEED	5

#define DEFAULTOFF			2

#define WINDOWREMAIN		48
#define WINDOWWREMAIN		5

#define MAXWINDOWHEIGHT		700
#define MAXWINDOWWIDTH		500

#define WINDOWSHOWX			200
#define WINDOWSHOWY			10

#define LOADINGSPEED		1
#define LOADINGTIMEGAP		10
#define READINSTRUCTION		2000

#define DIFFICULTYINCREASE	3
#define DIFFICULTYGAP		1500
#define MAXDIFFICULTY		30000

#define WHEREME				"image\\me.bmp"
#define WHEREBACKGROUND		"image\\background.bmp"
#define WHEREENEMYTYPE1		"image\\enemytype1.bmp"
#define WHEREENEMYTYPE2		"image\\enemytype2.bmp"
#define WHEREENEMYTYPE3		"image\\enemytype3.bmp"
#define WHEREBOSS			"image\\boss.bmp"
#define WHEREBONUSBOMB		"image\\bonusbomb.bmp"
#define WHEREBONUSFIRE		"image\\bonusfire.bmp"
#define WHEREMEBULLET		"image\\mebullet.bmp"
#define WHEREENEMYBULLET1	"image\\enemybullet1.bmp"
#define WHEREENEMYBULLET2	"image\\enemybullet2.bmp"
#define WHEREENEMYBULLET3	"image\\enemybullet3.bmp"
#define WHERELASER			"image\\laser.bmp"
#define WHEREFAKELOAD		"image\\fakeload.bmp"
#define WHERELOADING		"image\\loading.bmp"
#define WHEREINSTRUCTION	"image\\instruction.bmp"
#define WHEREGAMEOVER		"image\\gameover.bmp"
#define WHEREMEBLOOD		"image\\meblood.bmp"
#define WHEREMEBOMB			"image\\mebomb.bmp"
#define WHEREMELIFE			"image\\melife.bmp"
#define WHEREBOMB			"image\\bomb.bmp"
#define WHEREBONUSBLOOD		"image\\bonusblood.bmp"
#define WHERE0				"image\\numbers\\0.bmp"
#define WHERE1				"image\\numbers\\1.bmp"
#define WHERE2				"image\\numbers\\2.bmp"
#define WHERE3				"image\\numbers\\3.bmp"
#define WHERE4				"image\\numbers\\4.bmp"
#define WHERE5				"image\\numbers\\5.bmp"
#define WHERE6				"image\\numbers\\6.bmp"
#define WHERE7				"image\\numbers\\7.bmp"
#define WHERE8				"image\\numbers\\8.bmp"
#define WHERE9				"image\\numbers\\9.bmp"

//tony whole music definition block
#define MWHEREBGM			"sound\\bgm.mp3"  //The music need playing while loading
#define MWHEREMEBEHIT		"sound\\mebehit.wav"
#define MWHEREMYDEATH		"sound\\mydeath.wav"
#define MWHEREHITE1			"sound\\fire1.wav"
#define MWHEREHITE2			"sound\\fire2.wav"
#define MWHEREHITE3			"sound\\fire3.wav"
#define MWHEREHITE4			"sound\\fire4.wav"
#define MWHEREBONUS			"sound\\bonus.wav"
#define MWHEREMEBUL			"sound\\mebullet.wav"
#define MWHERELAZER			"sound\\lazer.wav"
#define MWHEREBOMB			"sound\\bomb.wav"
#define MWHEREOVER			"sound\\gameover.mp3"
#define MWHERELIFE			"sound\\newlife.wav"
CHAR buf[200];//background

CHAR bufm0[200];
CHAR bufm1[200];
CHAR buf0[200];
CHAR buf1[200];
CHAR buf2[200];
CHAR buf3[200];

CHAR bufbullet[200];
CHAR bufbomb[200];
CHAR buflazer[200];
CHAR bufbonus[200];
CHAR bufover[200];
CHAR buflife[200];

DWORD start = (DWORD)(0);

typedef struct flyobject {
	HBITMAP hbitmap ;
	LONG x ;				//decided when emerged
	LONG y ;				//decided when emerged
	LONG width ;
	LONG height ;
	LONG radius ;
	LONG blood ;			//decided when emerged
	LONG dx ;				//decided when emerged
	LONG dy ;				//decided when emerged
	LONG speed ;			//decided when emerged
	HDC dc ;
} FLYOBJECT ;

VOID CALLBACK Initializeall() ;
VOID CALLBACK Drawessential(HWND) ;
VOID CALLBACK MainrefreshTimerproc(HWND,UINT,UINT,DWORD);
VOID CALLBACK MemoveupTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK MemovedownTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK MemoveleftTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK MemoverightTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK MefireTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK Moveflyobject(FLYOBJECT *) ;
VOID CALLBACK Removeflyobject(FLYOBJECT *,LONG *,LONG,LONG) ;
VOID CALLBACK Createenemy(LONG *,LONG,LONG) ;
VOID CALLBACK Createenemybullet(LONG,LONG,LONG) ;
BOOL CALLBACK Isin(FLYOBJECT,FLYOBJECT) ;
BOOL CALLBACK Collision(FLYOBJECT,FLYOBJECT) ;
VOID CALLBACK Launchlaser(HWND,FLYOBJECT) ;
VOID CALLBACK RemovelaserTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK Launchbomb() ;
VOID CALLBACK Refreshme(HWND) ;
DOUBLE CALLBACK Distance(LONG,LONG,LONG,LONG) ;
VOID CALLBACK Refreshdc(HWND) ;
VOID CALLBACK Cleanwindow() ;
VOID CALLBACK Createbonus(LONG *,LONG,FLYOBJECT) ;
VOID CALLBACK Fakeloading(HWND,LONG) ;
VOID CALLBACK Gameover(HWND) ;
VOID CALLBACK Removelaser(HWND) ;
VOID CALLBACK Loadscoretype(CHAR *,LONG) ;
VOID CALLBACK RegainbloodTimerproc(HWND,UINT,UINT,DWORD) ;
VOID CALLBACK Start(HWND,HWND,int) ;

//enemy&boss&bonus
LONG				enemyhead[ENEMYDIVERSITY]={0} ;
LONG				enemytail[ENEMYDIVERSITY]={0} ;
FLYOBJECT			enemy[ENEMYDIVERSITY][MAXENEMYFLYOBJECT] ;
					//0,enemy type1
					//1,enemy type2
					//2,enemy type3
					//3,boss
					//4,bonusbomb
					//5,bonusfire
					//6,bonusblood
FLYOBJECT			enemytype[ENEMYDIVERSITY] ;
					//0,enemy icon1
					//1,enemy icon2
					//2,enemy icon3
					//3,boss icon
					//4,bonusbomb icon
					//5,bonusfire icon
					//6,bonusblood icon
FLYOBJECT			bullettype[BULLETDIVERSITY] ;
					//0,bullet icon1
					//1,bullet icon2
					//2,bullet icon3
					//3,laser
//speed
LONG				enemyspeed[ENEMYDIVERSITY]={7,6,5,1,3,3,3} ;
LONG				bulletspeed[BULLETDIVERSITY]={19,15,11,7} ;

LONG				fullblood[ENEMYDIVERSITY-BONUSDIVERSITY]={600,1200,2000,13000} ;
LONG				bulletharm[BULLETDIVERSITY]={100,200,300,5000}  ;
//possibility
LONG				enemypossibility[ENEMYDIVERSITY]={9700,9750,9800,9995,8700,9000,9300} ;
LONG				bulletpossibility[BULLETDIVERSITY]={9930,9945,9960,9940} ;
//all the enemy bullet queue
LONG				enemybullethead=0 ;
LONG				enemybullettail=0 ;
FLYOBJECT			enemybullet[MAXENEMYBULLETNUM] ;
//laser queue
LONG				laserhead=0 ;
LONG				lasertail=0 ;
FLYOBJECT			laserqueue[MAXLASERNUM] ;
//my bullet queue
LONG				mebullethead=0 ;
LONG				mebullettail=0 ;
FLYOBJECT			mebullet[MAXMEBULLETNUM] ;
FLYOBJECT			me ;
LONG				meharm=MEHARMDEFAULT ;
LONG				bombnum=DEFAULTBOMBNUM ;
LONG				melifenum=DEFAULTMELIFE ;
//bomb queue
FLYOBJECT			bomb[MAXBOMBNUM] ;
LONG				bombhead=0,bombtail=0 ;
//information
FLYOBJECT			meblood ;
FLYOBJECT			mebomb ;
FLYOBJECT			melife ;

LONG				score=0,lastscore=0 ;
FLYOBJECT			scoretype[10] ;
LONG				scoreadd[ENEMYDIVERSITY]={100,200,500,2000,19,17,17} ;

FLYOBJECT			background[2] ;
FLYOBJECT			gameover ;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;
TCHAR szClassName[] = TEXT("WindowsApp");

LONG WindowWidth,WindowHeight ;
LONG mebirthx,mebirthy ;

FLYOBJECT window ;
HDC memdc,displaydc ;
HBITMAP memhbitmap ;
//fakeload
HWND fakeload ;
HDC fakedc ;
HBITMAP fakeloadbg,loading ;
LONG FakeWindowWidth,FakeWindowHeight ;
LONG loadingwidth,loadingheight ;
//instruction 
HBITMAP instruction ;
HDC instructiondc ;
LONG instructionwidth,instructionheight ;
//running status 
LONG running=0 ;
			//0,no refresh
			//1,refresh
			//-1,gameover
			//2,wait to choose difficulty

//random initializing
LONG poss ;

FILE *fp ;
