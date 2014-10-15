#include <windows.h>
#include <stdio.h>
#include <time.h>
#include "resource.h"
#include "param.h"
#include "math.h"

int WINAPI
WinMain (HINSTANCE hThisInstance,
         HINSTANCE hPrevInstance,
         LPSTR lpszArgument,
         int nFunsterStil)

{
	fp = fopen(".LOG.txt","w+") ;
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    

	hInst = hThisInstance;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;   
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION) ;
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION) ;
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE (IDC_133);
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	RegisterClassEx(&wincl) ;	//    if (!RegisterClassEx (&wincl)) return 0;
	
	Initializeall() ;

    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           TEXT("À×µçX V1.00"), 		/* Title Text */
           WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU, /* default window */
           WINDOWSHOWX,       /* Windows decides the position */
           WINDOWSHOWY,       			/* where the window ends up on the screen */
           WindowWidth,       /* The programs width */
           WindowHeight,                 	/* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );
           
    fakeload = CreateWindowEx(
               WS_EX_TOPMOST,
	           TEXT("STATIC"),
    	       TEXT(""),
        	   WS_POPUP,
	           WINDOWSHOWX+WindowWidth/2-FakeWindowWidth/2,
    	       WINDOWSHOWY+WindowHeight/2-FakeWindowHeight/2,
        	   FakeWindowWidth,
	           FakeWindowHeight,
    	       HWND_DESKTOP,
        	   NULL,
	           hThisInstance,
    	       NULL
           );
    
    running = 2 ;
	Fakeloading(fakeload,nFunsterStil) ;
	ShowWindow(hwnd,nFunsterStil) ;
	Drawessential(hwnd) ;


    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    fclose(fp) ;
    return messages.wParam;
}

LRESULT CALLBACK
WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	
    switch (message)
    {
   		case WM_KEYUP:
	   		switch(wParam)
   			{
			case VK_X:
				KillTimer(hwnd,WM_mebulletTIMER);
				break;
			case VK_UP:
				KillTimer(hwnd,WM_memoveupTIMER) ;
				break ;
			case VK_DOWN:
				KillTimer(hwnd,WM_memovedownTIMER) ;
				break ;
			case VK_LEFT:
				KillTimer(hwnd,WM_memoveleftTIMER) ;
				break ;
			case VK_RIGHT:
				KillTimer(hwnd,WM_memoverightTIMER) ;
				break ;
			default:
				return DefWindowProc(hwnd, message, wParam, lParam);			
			}
    	case WM_KEYDOWN:
    		switch (wParam)
    		{
   			case VK_R:
   				if(running!=-1)break;
   				score = 0 ;
   				lastscore = 0 ;
			   	melifenum = DEFAULTMELIFE ;
   				Cleanwindow() ;
   				mebullethead = mebullettail = 0 ;
   				enemyhead[BONUSFIRE] = enemytail[BONUSFIRE] = 0 ;
   				enemyhead[BONUSBLOOD] = enemytail[BONUSBLOOD] = 0 ;
   				enemyhead[BONUSBOMB] = enemytail[BONUSBOMB] = 0 ;
   				bombhead=bombtail = 0 ;
   				Refreshme(hwnd) ;
   				running = 1 ;
				sprintf(buf,"play %s from %ld repeat",MWHEREBGM,0);
				mciSendString(buf,NULL,0,NULL);
			case VK_S:
				if (running==-1) break ;
				running = 1 ;
//				Refreshme(hwnd) ;
	    		SetTimer(hwnd,WM_mainrefreshTIMER,MAINREFRESHGAP,MainrefreshTimerproc) ;
		 		break ;
   			case VK_P :
   				if (running!=1) break ;
   				running = 0 ;
   				KillTimer(hwnd,WM_mainrefreshTIMER) ;
   				break ;
			case VK_E :
				if (running!=2) break ;
				enemypossibility[0]=9700 ;
				enemypossibility[1]=9750 ;
				enemypossibility[2]=9800 ;
				enemypossibility[3]=9995 ;
				enemypossibility[4]=8000 ;
				enemypossibility[5]=8600 ;
				enemypossibility[6]=9300 ;
				bulletpossibility[0]=9940 ;
				bulletpossibility[1]=9955 ;
				bulletpossibility[2]=9970 ;
				bulletpossibility[3]=9980 ;
				running = 1 ;
	    		SetTimer(hwnd,WM_mainrefreshTIMER,MAINREFRESHGAP,MainrefreshTimerproc) ;
//				Start(hwnd,fakeload,tnFunsterStil) ;
				break ;
			case VK_N :
				if (running!=2) break ;
				enemypossibility[0]=9700 ;
				enemypossibility[1]=9750 ;
				enemypossibility[2]=9800 ;
				enemypossibility[3]=9990 ;
				enemypossibility[4]=8300 ;
				enemypossibility[5]=8900 ;
				enemypossibility[6]=9300 ;
				bulletpossibility[0]=9935;
				bulletpossibility[1]=9945 ;
				bulletpossibility[2]=9960 ;
				bulletpossibility[3]=9970 ;
				running = 1 ;
	    		SetTimer(hwnd,WM_mainrefreshTIMER,MAINREFRESHGAP,MainrefreshTimerproc) ;
//				Start(hwnd,fakeload,tnFunsterStil) ;
				break ;
			case VK_H :
				if (running!=2) break ;
				enemypossibility[0]=9600 ;
				enemypossibility[1]=9750 ;
				enemypossibility[2]=9800 ;
				enemypossibility[3]=9990 ;
				enemypossibility[4]=8800 ;
				enemypossibility[5]=9200 ;
				enemypossibility[6]=9500 ;
				bulletpossibility[0]=9830 ;
				bulletpossibility[1]=9835 ;
				bulletpossibility[2]=9855 ;
				bulletpossibility[3]=9975 ;
				running = 1 ;
	    		SetTimer(hwnd,WM_mainrefreshTIMER,MAINREFRESHGAP,MainrefreshTimerproc) ;
//				Start(hwnd,fakeload,tnFunsterStil) ;
				break ;
   			case VK_Z :
				if (running==1)
		    	if (!(1<<30&lParam)) if (bombnum>0) Launchbomb() ;
   				break ;
			case VK_X:
				if (running==1)
				if (!(1<<30&lParam)) SetTimer(hwnd,WM_mebulletTIMER,MEFIREGAP,MefireTimerproc);
				break;
	    	case VK_UP:
				if (running==1)
	    		if (!(1<<30&lParam)) SetTimer(hwnd,WM_memoveupTIMER,MEMOVEGAP,MemoveupTimerproc) ;
    			break ;
   			case VK_DOWN:
				if (running==1)
   				if (!(1<<30&lParam)) SetTimer(hwnd,WM_memovedownTIMER,MEMOVEGAP,MemovedownTimerproc) ;
   				break ;
			case VK_LEFT:
				if (running==1)
				if (!(1<<30&lParam)) SetTimer(hwnd,WM_memoveleftTIMER,MEMOVEGAP,MemoveleftTimerproc) ;
				break ;
			case VK_RIGHT:
				if (running==1)
				if (!(1<<30&lParam)) SetTimer(hwnd,WM_memoverightTIMER,MEMOVEGAP,MemoverightTimerproc) ;
				break ;
			default:
				return DefWindowProc(hwnd, message, wParam, lParam);
		    }
		case WM_COMMAND:
    		switch (LOWORD(wParam))
    		{
		    case IDM_ABOUT:
				MessageBox (hwnd, TEXT ("Z:bomb\nX:fire\nS:start&continue\nR:restart\nP:pause\n\nÀ×µçX V1.00\nCopyright Pengjie Yunfeng Hetong\nAll rights reserved."),
                        TEXT ("Control Instruction"), MB_OK | MB_ICONINFORMATION);
				break;
			case IDM_EXIT:
				DestroyWindow(hwnd);
				break;
			default:
				return DefWindowProc(hwnd, message, wParam, lParam);
		    }
    		break;
    	case WM_PAINT:
			BeginPaint(hwnd, &ps);
			EndPaint(hwnd, &ps);
			break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

VOID CALLBACK Initializeall() 
{	
	//set random
	srand((unsigned)time(NULL)) ;
	//load background
	background[0].hbitmap = (HBITMAP)LoadImage(hInst,WHEREBACKGROUND,IMAGE_BITMAP,
					0,0,LR_DEFAULTCOLOR | LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREBACKGROUND,&background[0].width,&background[0].height) ;
	background[0].x = 0 ;
	background[0].y = 0 ;
	background[0].dx = 0 ;
	background[0].dy = 1 ;
	background[0].speed = BACKGROUNDMOVESPEED ;
	background[1] = background[0] ;
	background[1].hbitmap = (HBITMAP)LoadImage(hInst,WHEREBACKGROUND,IMAGE_BITMAP,
					0,0,LR_DEFAULTCOLOR | LR_LOADFROMFILE) ;	
	background[1].y=-background[1].height ;
	WindowWidth = background[0].width ;
	WindowHeight = background[0].height ;
	if (WindowWidth>MAXWINDOWWIDTH) WindowWidth = MAXWINDOWWIDTH ;
	if (WindowHeight>MAXWINDOWHEIGHT) WindowHeight = MAXWINDOWHEIGHT ;
	//set window ;
	window.x = 0 ;
	window.y = 0 ;
	window.width = WindowWidth-WINDOWWREMAIN ;
	window.height = WindowHeight-WINDOWREMAIN ;
	//load me
	me.hbitmap = (HBITMAP)LoadImage(hInst,WHEREME,IMAGE_BITMAP,
					0,0,LR_DEFAULTCOLOR | LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREME,&me.width,&me.height) ;
    mebirthx = window.width/2-me.width/2 ;
    mebirthy = window.height/5*4;	
	me.x=mebirthx ;
	me.y=mebirthy ;
	me.radius=MERADIUS ;
	me.blood=MEBLOODDEFAULT ;
	me.speed=MESPEED ;
	meharm = MEHARMDEFAULT ;
	//load enemytype1 and 2 and 3 and boss
	LONG i ;
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[ENEMYTYPE1][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREENEMYTYPE1,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREENEMYTYPE1,&enemy[ENEMYTYPE1][i].width,&enemy[ENEMYTYPE1][i].height) ;
		enemy[ENEMYTYPE1][i].radius = ENEMYRADIUS1 ;
	}
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[ENEMYTYPE2][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREENEMYTYPE2,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREENEMYTYPE2,&enemy[ENEMYTYPE2][i].width,&enemy[ENEMYTYPE2][i].height) ;
		enemy[ENEMYTYPE2][i].radius = ENEMYRADIUS2 ;
	}
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[ENEMYTYPE3][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREENEMYTYPE3,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREENEMYTYPE3,&enemy[ENEMYTYPE3][i].width,&enemy[ENEMYTYPE3][i].height) ;
		enemy[ENEMYTYPE3][i].radius = ENEMYRADIUS3 ;
	}
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[BOSS][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREBOSS,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREBOSS,&enemy[BOSS][i].width,&enemy[BOSS][i].height) ;
		enemy[BOSS][i].radius = BOSSRADIUS ;
	}
	//load bonusbomb
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[BONUSBOMB][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREBONUSBOMB,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREBONUSBOMB,&enemy[BONUSBOMB][i].width,&enemy[BONUSBOMB][i].height) ;
		enemy[BONUSBOMB][i].radius = BONUSBOMBRADIUS ;
	}
	//load bonusfire
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[BONUSFIRE][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREBONUSFIRE,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREBONUSFIRE,&enemy[BONUSFIRE][i].width,&enemy[BONUSFIRE][i].height) ;
		enemy[BONUSFIRE][i].radius = BONUSFIRERADIUS ;
	}
	//load bonusblood
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[BONUSBLOOD][i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREBONUSBLOOD,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREBONUSBLOOD,&enemy[BONUSBLOOD][i].width,&enemy[BONUSBLOOD][i].height) ;
		enemy[BONUSBLOOD][i].radius = BONUSBLOODRADIUS ;
	}
	//load laser queue
	for (i=0;i<MAXLASERNUM;i++) {
		laserqueue[i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHERELASER,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHERELASER,&laserqueue[i].width,&laserqueue[i].height) ;
		laserqueue[i].blood = bulletharm[LASER] ;
	}
	//load bullettype
	//type1
	bullettype[ENEMYTYPE1].hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREENEMYBULLET1,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREENEMYBULLET1,&bullettype[ENEMYTYPE1].width,&bullettype[ENEMYTYPE1].height) ;
	bullettype[ENEMYTYPE1].radius = ENEMYBULLETRADIUS1 ;
	bullettype[ENEMYTYPE1].blood = bulletharm[ENEMYTYPE1] ;
	
	//type2
	bullettype[ENEMYTYPE2].hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREENEMYBULLET2,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREENEMYBULLET2,&bullettype[ENEMYTYPE2].width,&bullettype[ENEMYTYPE2].height) ;
	bullettype[ENEMYTYPE2].radius = ENEMYBULLETRADIUS2 ;
	bullettype[ENEMYTYPE2].blood = bulletharm[ENEMYTYPE2] ;
	
	//type3
	bullettype[ENEMYTYPE3].hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREENEMYBULLET3,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREENEMYBULLET3,&bullettype[ENEMYTYPE3].width,&bullettype[ENEMYTYPE3].height) ;
	bullettype[ENEMYTYPE3].radius = ENEMYBULLETRADIUS3 ;
	bullettype[ENEMYTYPE3].blood = bulletharm[ENEMYTYPE3] ;
	
	//load my bullet
	for (i=0;i<MAXMEBULLETNUM;i++) {
		mebullet[i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREMEBULLET,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREMEBULLET,&mebullet[i].width,&mebullet[i].height) ;
		mebullet[i].radius=MEBULLETRADIUS ;
		mebullet[i].blood= meharm ;
		mebullet[i].dx=0 ;
		mebullet[i].dy=-1 ;
		mebullet[i].speed = MEBULLETSPEED ;
	}
	//load gameover
	gameover.hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREGAMEOVER,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREGAMEOVER,&gameover.width,&gameover.height) ;
	gameover.x = 0 ;
	gameover.y = 0 ;
	//load melife
	melife.hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREMELIFE,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREMELIFE,&melife.width,&melife.height) ;
	//load meblood
	meblood.hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREMEBLOOD,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREMEBLOOD,&meblood.width,&meblood.height) ;
	//load mebomb
	mebomb.hbitmap=(HBITMAP)
	LoadImage(hInst,WHEREMEBOMB,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREMEBOMB,&mebomb.width,&mebomb.height) ;
	//load bomb queue
	for (i=0;i<MAXBOMBNUM;i++){
		bomb[i].hbitmap=(HBITMAP)
		LoadImage(hInst,WHEREBOMB,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
		GetBitmapWidthAndHeight(WHEREBOMB,&bomb[i].width,&bomb[i].height) ;
	}
	//load fakeload
	fakeloadbg = (HBITMAP)
	LoadImage(hInst,WHEREFAKELOAD,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREFAKELOAD,&FakeWindowWidth,&FakeWindowHeight) ;
	loading = (HBITMAP)
	LoadImage(hInst,WHERELOADING,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHERELOADING,&loadingwidth,&loadingheight) ;
	instruction = (HBITMAP)
	LoadImage(hInst,WHEREINSTRUCTION,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(WHEREINSTRUCTION,&instructionwidth,&instructionheight) ;
	//tony initialize all sound effects
	sprintf(bufm1,"open %s",MWHEREMYDEATH);
	sprintf(buf0,"open %s",MWHEREHITE1);
	sprintf(buf1,"open %s",MWHEREHITE2);
	sprintf(buf2,"open %s",MWHEREHITE3);
	sprintf(buf3,"open %s",MWHEREHITE4);
	sprintf(bufbullet,"open %s",MWHEREMEBUL);
	sprintf(bufbomb,"open %s",MWHEREBOMB);
	sprintf(buflazer,"open %s",MWHERELAZER);
	sprintf(bufbonus,"open %s",MWHEREBONUS);
	sprintf(buflife,"open %s",MWHERELIFE);
	sprintf(bufm0,"open %s",MWHEREMEBEHIT);
	mciSendString(bufm0,NULL,0,NULL);
	mciSendString(bufm1,NULL,0,NULL);
	mciSendString(buf0,NULL,0,NULL);
	mciSendString(buf1,NULL,0,NULL);
	mciSendString(buf2,NULL,0,NULL);
	mciSendString(buf3,NULL,0,NULL);
	mciSendString(bufbullet,NULL,0,NULL);
	mciSendString(bufbomb,NULL,0,NULL);
	mciSendString(buflazer,NULL,0,NULL);
	mciSendString(bufbonus,NULL,0,NULL);
	mciSendString(buflife,NULL,0,NULL);
	//background sound
	sprintf(buf,"open %s",MWHEREBGM);
	mciSendString(buf,NULL,0,NULL);
	sprintf(buf,"play %s repeat",MWHEREBGM);
	mciSendString(buf,NULL,0,NULL);
	//gaveover music
	sprintf(bufover,"open %s",MWHEREOVER);
	mciSendString(bufover,NULL,0,NULL);
}

VOID CALLBACK Fakeloading(HWND fakeload,LONG nFunsterStil)
{
	ShowWindow(fakeload,nFunsterStil) ;
	HDC hdc ;
	hdc = GetDC(fakeload) ;
	DrawState(hdc,NULL,NULL,(LPARAM)fakeloadbg,0,0,0,0,0,DST_BITMAP) ;
	fakedc = CreateCompatibleDC(hdc) ;
	SelectObject(fakedc,loading) ;
	LONG i=LOADINGSPEED ;
	while (i<loadingwidth) {
		TransparentBltU(hdc,FakeWindowWidth/2-loadingwidth/2,FakeWindowHeight/2-loadingheight/2,i,loadingheight,fakedc,0,0,i,loadingheight,RGB(255,255,255)) ;
		i+=LOADINGSPEED ;
		Sleep(LOADINGTIMEGAP) ;
	}
	TransparentBltU(hdc,FakeWindowWidth/2-loadingwidth/2,FakeWindowHeight/2-loadingheight/2,loadingwidth,loadingheight,fakedc,0,0,loadingwidth,loadingheight,RGB(255,255,255)) ;
//	Sleep(LOADINGTIMEGAP) ;
//	DrawState(hdc,NULL,NULL,(LPARAM)instruction,0,0,0,0,0,DST_BITMAP) ;
//	Sleep(READINSTRUCTION) ;
	DeleteDC(fakedc) ;
	DestroyWindow(fakeload) ;
}

VOID CALLBACK Start(HWND hwnd,HWND fakeload,int nFunsterStil)
{	
}

VOID CALLBACK Drawessential(HWND hwnd) 
{
	displaydc = GetDC(hwnd) ;
	//set backgroundDC 
	background[0].dc = CreateCompatibleDC(displaydc) ;
	SelectObject(background[0].dc,background[0].hbitmap) ;
	background[1].dc = CreateCompatibleDC(displaydc) ;
	SelectObject(background[1].dc,background[1].hbitmap) ;	
	//set meDC
	me.dc= CreateCompatibleDC(displaydc) ;
	SelectObject(me.dc,me.hbitmap) ;
	//set enemytype1 2 3 boss bonusbomb bonusfire bonusblood DC
	LONG i,j ;
	for (j=0;j<ENEMYDIVERSITY;j++)
	for (i=0;i<MAXENEMYFLYOBJECT;i++) {
		enemy[j][i].dc = CreateCompatibleDC(displaydc) ;
		SelectObject(enemy[j][i].dc,enemy[j][i].hbitmap) ;
	}
	//load mebullet DC
	for (i=0;i<MAXMEBULLETNUM;i++) {
		mebullet[i].dc= CreateCompatibleDC(displaydc) ;
		SelectObject(mebullet[i].dc,mebullet[i].hbitmap) ;
	}
	//load gameover DC
	gameover.dc= CreateCompatibleDC(displaydc) ;
	SelectObject(gameover.dc,gameover.hbitmap) ;
	//load meblood mebomb melife DC
	meblood.dc= CreateCompatibleDC(displaydc) ;
	SelectObject(meblood.dc,meblood.hbitmap) ;
	mebomb.dc= CreateCompatibleDC(displaydc) ;
	SelectObject(mebomb.dc,mebomb.hbitmap) ;
	melife.dc= CreateCompatibleDC(displaydc) ;
	SelectObject(melife.dc,melife.hbitmap) ;
	//load bomb queue DC
	for (i=0;i<MAXBOMBNUM;i++) {
		bomb[i].dc=CreateCompatibleDC(displaydc) ;
		SelectObject(bomb[i].dc,bomb[i].hbitmap) ;
	}
	//load laserqueue DC
	for (i=0;i<MAXLASERNUM;i++) {
		laserqueue[i].dc=CreateCompatibleDC(displaydc) ;
		SelectObject(laserqueue[i].dc,laserqueue[i].hbitmap) ;
	}
	//load instruction DC
	instructiondc = CreateCompatibleDC(displaydc) ;
	SelectObject(instructiondc,instruction) ;
	//load scoretype
	Loadscoretype(WHERE0,0) ;
	Loadscoretype(WHERE1,1) ;
	Loadscoretype(WHERE2,2) ;
	Loadscoretype(WHERE3,3) ;
	Loadscoretype(WHERE4,4) ;
	Loadscoretype(WHERE5,5) ;
	Loadscoretype(WHERE6,6) ;
	Loadscoretype(WHERE7,7) ;
	Loadscoretype(WHERE8,8) ;
	Loadscoretype(WHERE9,9) ;
	
	memdc = CreateCompatibleDC(displaydc) ;
	memhbitmap = CreateCompatibleBitmap(displaydc,window.width,window.height) ;
	SelectObject(memdc,memhbitmap) ;
	//show background
	BitBlt(memdc,0,0,window.width,window.height,instructiondc,0,0,SRCCOPY) ;
//	BitBlt(memdc,0,0,window.width,window.height,background[0].dc,0,0,SRCCOPY) ;		
	//show me
	TransparentBltU(memdc,me.x,me.y,me.width,me.height,me.dc,0,0,me.width,me.height,RGB(255,255,255)) ;
	BitBlt(displaydc,0,0,window.width,window.height,memdc,0,0,SRCCOPY) ;
}

VOID CALLBACK MainrefreshTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
	//calculating part
	//variables
	static LONG times=0 ;//record time
	LONG i,j,k ;
	times++ ;	
	//createenemy
	if (times>DEFAULTTIME1&&enemytail[ENEMYTYPE1]-enemyhead[ENEMYTYPE1]<MAXENEMYFLYOBJECT) Createenemy(&enemytail[ENEMYTYPE1],ENEMYTYPE1,times) ;
	if (times>DEFAULTTIME2&&enemytail[ENEMYTYPE2]-enemyhead[ENEMYTYPE2]<MAXENEMYFLYOBJECT) Createenemy(&enemytail[ENEMYTYPE2],ENEMYTYPE2,times) ;
	if (times>DEFAULTTIME3&&enemytail[ENEMYTYPE3]-enemyhead[ENEMYTYPE3]<MAXENEMYFLYOBJECT) Createenemy(&enemytail[ENEMYTYPE3],ENEMYTYPE3,times) ;
	if (times>DEFAULTTIME4&&enemytail[BOSS]-enemyhead[BOSS]<1)  Createenemy(&enemytail[BOSS],BOSS,times) ;
	//createenemybullet
	for (j=0;j<ENEMYDIVERSITY-BONUSDIVERSITY;j++) //enemytype
	for (k=0;k<=j;k++) //bullettype
	for (i=enemyhead[j];i<enemytail[j];i++) {
		if (enemybullettail-enemybullethead>=MAXENEMYBULLETNUM) break ;
		poss = rand()%10000 ;
		if (poss>=bulletpossibility[k]&&k<LASER) Createenemybullet(j,k,i%MAXENEMYFLYOBJECT) ;
		else if (k==BOSS&&poss>=bulletpossibility[LASER]&&lasertail-laserhead<MAXLASERNUM-1&&enemy[BOSS][i%MAXENEMYFLYOBJECT].y>-enemy[BOSS][i%MAXENEMYFLYOBJECT].height/2) 
		Launchlaser(hwnd,enemy[BOSS][i%MAXENEMYFLYOBJECT]) ;
	}
	//move the background
	Moveflyobject(&background[0]) ;
	if (background[0].y>=background[0].height) 
		background[0].y = background[1].y-background[0].height ;
	Moveflyobject(&background[1]) ;
	if (background[1].y>=background[1].height) 
		background[1].y = background[0].y-background[1].height ;
	//move enemyflyobject
	for (j=0;j<ENEMYDIVERSITY;j++)
	for (i=enemyhead[j];i<enemytail[j];i++) {
		Moveflyobject(&enemy[j][i%MAXENEMYFLYOBJECT]) ;
		if (!(Isin(window,enemy[j][i%MAXENEMYFLYOBJECT]))) {
			Removeflyobject(enemy[j],&enemyhead[j],i,MAXENEMYFLYOBJECT) ;//out of window			
		}
	}
	//move enemybullet
	for (i=enemybullethead;i<enemybullettail;i++) {
		Moveflyobject(&enemybullet[i%MAXENEMYBULLETNUM]) ;
		if (!(Isin(window,enemybullet[i%MAXENEMYBULLETNUM]))) {
			DeleteDC(enemybullet[i%MAXENEMYBULLETNUM].dc) ;
			Removeflyobject(enemybullet,&enemybullethead,i,MAXENEMYBULLETNUM) ;
		}
	}
	//move laser
	for (i=laserhead;i<lasertail;i++) {
		Moveflyobject(&laserqueue[i%MAXLASERNUM]) ;
		if (!(Isin(window,laserqueue[i%MAXLASERNUM]))) {
			Removelaser(hwnd) ;
		}
	}
	//move mebullet
	for (i=mebullethead;i<mebullettail;i++) {
		Moveflyobject(&mebullet[i%MAXMEBULLETNUM]) ;
		if (!(Isin(window,mebullet[i%MAXMEBULLETNUM]))) {
			Removeflyobject(mebullet,&mebullethead,i,MAXMEBULLETNUM) ;
		}
	}
	if (mebullethead==mebullettail) {
		mebullethead=mebullettail=0 ;
	}
	//move bomb
	for (i=bombhead;i<bombtail;i++) {
		Moveflyobject(&bomb[i%MAXBOMBNUM]) ;
		if (!(Isin(window,bomb[i%MAXBOMBNUM]))) {
			Removeflyobject(bomb,&bombhead,i,MAXBOMBNUM) ;
			Cleanwindow() ;
		}
	}
	//whether be hit
	for (i=enemybullethead;i<enemybullettail;i++){
		if (Collision(enemybullet[i%MAXENEMYBULLETNUM],me)) {
			me.blood -= enemybullet[i%MAXENEMYBULLETNUM].blood ;
			DeleteDC(enemybullet[i%MAXENEMYBULLETNUM].dc) ;
			Removeflyobject(enemybullet,&enemybullethead,i,MAXENEMYBULLETNUM) ;
			sprintf(bufm0,"play %s from %ld",MWHEREMEBEHIT,start);
			mciSendString(bufm0,NULL,0,NULL);
			if (me.blood<=0){
				/**************************to be done*/  //blinking,sound effect
				//tony
				sprintf(bufm1,"play %s from %ld",MWHEREMYDEATH,start);
				mciSendString(bufm1,NULL,0,NULL);
				
				melifenum-- ;
				if (melifenum<=0) {
					Gameover(hwnd);
					return ;
				}
   				Refreshme(hwnd) ;
			}
		}
	}
	//whether meet laser
	for (i=laserhead;i<lasertail;i++){
		if (Isin(laserqueue[i%MAXLASERNUM],me)){
			/**************************to be done*/  //blinking,sound effect
			me.blood-=laserqueue[i%MAXLASERNUM].blood ;
			if (me.blood<=0){
				melifenum-- ;
				if (melifenum<=0) {
					Gameover(hwnd);
					return ;
				}
				sprintf(bufm1,"play %s from %ld",MWHEREMYDEATH,start);
				mciSendString(bufm1,NULL,0,NULL);
				Refreshme(hwnd) ;
			}
		}
	}
	//whether get bonusfire
	for (i=enemyhead[BONUSFIRE];i<enemytail[BONUSFIRE];i++)
		if (Collision(enemy[BONUSFIRE][i%MAXENEMYFLYOBJECT],me)) {
			meharm+=MEHARMDEFAULT/2 ;
			if (meharm>MAXMEHARM) meharm = MAXMEHARM ;
			Removeflyobject(enemy[BONUSFIRE],&enemyhead[BONUSFIRE],i,MAXENEMYFLYOBJECT) ;
			score+=scoreadd[BONUSBLOOD] ;
			sprintf(bufbonus,"play %s from %ld",MWHEREBONUS,200);
			mciSendString(bufbonus,NULL,0,NULL);
		}
	//whether get bonusbomb
	for (i=enemyhead[BONUSBOMB];i<enemytail[BONUSBOMB];i++) 
		if (Collision(enemy[BONUSBOMB][i%MAXENEMYFLYOBJECT],me)) {
			if (bombnum<MAXBOMBNUM)bombnum++ ;
			Removeflyobject(enemy[BONUSBOMB],&enemyhead[BONUSBOMB],i,MAXENEMYFLYOBJECT) ;
			score+=scoreadd[BONUSBLOOD] ;
			sprintf(bufbonus,"play %s from %ld",MWHEREBONUS,200);
			mciSendString(bufbonus,NULL,0,NULL);			
		}
	//whether get bonusblood
	for (i=enemyhead[BONUSBLOOD];i<enemytail[BONUSBLOOD];i++)
		if (Collision(enemy[BONUSBLOOD][i%MAXENEMYFLYOBJECT],me)) {
			Removeflyobject(enemy[BONUSBLOOD],&enemyhead[BONUSBLOOD],i,MAXENEMYFLYOBJECT) ;
			score+=scoreadd[BONUSBLOOD] ;
			sprintf(bufbonus,"play %s from %ld",MWHEREBONUS,200);
			mciSendString(bufbonus,NULL,0,NULL);
			if (me.blood<MEBLOODDEFAULT) {
				me.blood+=BLOODADD ;
				if (me.blood>MEBLOODDEFAULT) me.blood=MEBLOODDEFAULT ;
			}
		}
	//whether hit enemy
	for (k=0;k<ENEMYDIVERSITY-BONUSDIVERSITY;k++)
	for (i=mebullethead;i<mebullettail;i++)
	for (j=enemyhead[k];j<enemytail[k];j++)
		if (Collision(enemy[k][j%MAXENEMYFLYOBJECT],mebullet[i%MAXMEBULLETNUM])) {
			enemy[k][j%MAXENEMYFLYOBJECT].blood -= meharm ;
			Removeflyobject(mebullet,&mebullethead,i,MAXMEBULLETNUM) ;
			score+=scoreadd[BOSS+1] ;
			if (enemy[k][j%MAXENEMYFLYOBJECT].blood<=0) {
				/**************************to be done*/  //blinking,sound effect
				poss = rand()%10000 ;
				//create bonus
				if (poss>=enemypossibility[BONUSBLOOD]){
					if (enemytail[BONUSBLOOD]-enemyhead[BONUSBLOOD]<MAXENEMYFLYOBJECT)
						Createbonus(&enemytail[BONUSBLOOD],BONUSBLOOD,enemy[k][j%MAXENEMYFLYOBJECT]) ;
				}
				else if (poss>=enemypossibility[BONUSFIRE]){
					if (enemytail[BONUSFIRE]-enemyhead[BONUSFIRE]<MAXENEMYFLYOBJECT)
						Createbonus(&enemytail[BONUSFIRE],BONUSFIRE,enemy[k][j%MAXENEMYFLYOBJECT]) ;
				}
				else if(poss>=enemypossibility[BONUSBOMB]){
					if (enemytail[BONUSBOMB]-enemyhead[BONUSBOMB]<MAXENEMYFLYOBJECT)
						Createbonus(&enemytail[BONUSBOMB],BONUSBOMB,enemy[k][j%MAXENEMYFLYOBJECT]) ;
				}
				Removeflyobject(enemy[k],&enemyhead[k],j,MAXENEMYFLYOBJECT) ;
				if (k==BOSS) while (laserhead<lasertail) Removelaser(hwnd) ;
				score+=scoreadd[k] ;
			//tony
				switch(k){
					case 0:sprintf(buf0, "play %s from %ld",MWHEREHITE1,start);
							mciSendString(buf0, NULL, 0, NULL);break;//0,enemy type1
					case 1:sprintf(buf1, "play %s from %ld",MWHEREHITE2,start);
							mciSendString(buf1, NULL, 0, NULL);break;//1,enemy type2
					case 2:sprintf(buf2, "play %s from %ld",MWHEREHITE3,start);
							mciSendString(buf2, NULL, 0, NULL);break;//2,enemy type3
					case 3:sprintf(buf3, "play %s from %ld",MWHEREHITE4,start);
							mciSendString(buf3, NULL, 0, NULL);break;//3,boss
					default:break;
				}
			}
			break ;
		}
	//whether enemy be bombed
	for (i=bombhead;i<bombtail;i++) {
		//clear enemy
		for (k=0;k<ENEMYDIVERSITY-BONUSDIVERSITY;k++)
		for (j=enemyhead[k];j<enemytail[k];j++)	
			if (enemy[k][j%MAXENEMYFLYOBJECT].y+enemy[k][j%MAXENEMYFLYOBJECT].height>=bomb[i%MAXBOMBNUM].y) {
				Removeflyobject(enemy[k],&enemyhead[k],j,MAXENEMYFLYOBJECT) ;
		}
		//clear enemy bullet
		for (k=enemybullethead;k<enemybullettail;k++)
			if (enemybullet[k%MAXENEMYBULLETNUM].y+enemybullet[k%MAXENEMYBULLETNUM].height>=bomb[i%MAXBOMBNUM].y) {
				Removeflyobject(enemybullet,&enemybullethead,k,MAXENEMYBULLETNUM) ;
			}
		//clear laser
		while (lasertail>laserhead)Removelaser(hwnd) ;
	}
	//whether get a new life
	if (score-lastscore>=ADDALIFESCORE) {
		//sound effect
		if (melifenum<MAXMELIFE) {
			sprintf(buflife,"play %s from %ld",MWHERELIFE,0);
			mciSendString(buflife,NULL,0,NULL);
			melifenum++ ;
		}
		lastscore +=ADDALIFESCORE ;
	}
	//showing part
	//show background
	BitBlt(memdc,background[0].x,background[0].y,background[0].width,background[0].height,background[0].dc,0,0,SRCCOPY) ;
	BitBlt(memdc,background[1].x,background[1].y,background[1].width,background[1].height,background[1].dc,0,0,SRCCOPY) ;

	//show enemyflyobject
	for (j=ENEMYDIVERSITY-BONUSDIVERSITY-1;j>=0;j--)
	for (i=enemyhead[j];i<enemytail[j];i++)
		TransparentBltU(memdc,enemy[j][i%MAXENEMYFLYOBJECT].x,enemy[j][i%MAXENEMYFLYOBJECT].y,enemy[j][i%MAXENEMYFLYOBJECT].width,enemy[j][i%MAXENEMYFLYOBJECT].height,enemy[j][i%MAXENEMYFLYOBJECT].dc,0,0,enemy[j][i%MAXENEMYFLYOBJECT].width,enemy[j][i%MAXENEMYFLYOBJECT].height,RGB(255,255,255)) ;
	for (j=ENEMYDIVERSITY-1;j>=ENEMYDIVERSITY-BONUSDIVERSITY;j--)
	for (i=enemyhead[j];i<enemytail[j];i++)
		TransparentBltU(memdc,enemy[j][i%MAXENEMYFLYOBJECT].x,enemy[j][i%MAXENEMYFLYOBJECT].y,enemy[j][i%MAXENEMYFLYOBJECT].width,enemy[j][i%MAXENEMYFLYOBJECT].height,enemy[j][i%MAXENEMYFLYOBJECT].dc,0,0,enemy[j][i%MAXENEMYFLYOBJECT].width,enemy[j][i%MAXENEMYFLYOBJECT].height,RGB(255,255,255)) ;
	//show enemybullet
	for (i=enemybullethead;i<enemybullettail;i++)
		TransparentBltU(memdc,enemybullet[i%MAXENEMYBULLETNUM].x,enemybullet[i%MAXENEMYBULLETNUM].y,enemybullet[i%MAXENEMYBULLETNUM].width,enemybullet[i%MAXENEMYBULLETNUM].height,enemybullet[i%MAXENEMYBULLETNUM].dc,0,0,enemybullet[i%MAXENEMYBULLETNUM].width,enemybullet[i%MAXENEMYBULLETNUM].height,RGB(255,255,255)) ;
	//show laser
	for (i=laserhead;i<lasertail;i++)
		TransparentBltU(memdc,laserqueue[i%MAXLASERNUM].x,laserqueue[i%MAXLASERNUM].y,laserqueue[i%MAXLASERNUM].width,laserqueue[i%MAXLASERNUM].height,laserqueue[i%MAXLASERNUM].dc,0,0,laserqueue[i%MAXLASERNUM].width,laserqueue[i%MAXLASERNUM].height,RGB(255,255,255)) ;
	//show mebullet
	for (i=mebullethead;i<mebullettail;i++)
		TransparentBltU(memdc,mebullet[i%MAXMEBULLETNUM].x,mebullet[i%MAXMEBULLETNUM].y,mebullet[i%MAXMEBULLETNUM].width,mebullet[i%MAXMEBULLETNUM].height,mebullet[i%MAXMEBULLETNUM].dc,0,0,mebullet[i%MAXMEBULLETNUM].width,mebullet[i%MAXMEBULLETNUM].height,RGB(255,255,255)) ;
	//show me
		TransparentBltU(memdc,me.x,me.y,me.width,me.height,me.dc,0,0,me.width,me.height,RGB(255,255,255)) ;
	//show bomb
	for (i=bombhead;i<bombtail;i++) {
		TransparentBltU(memdc,bomb[i%MAXBOMBNUM].x,bomb[i%MAXBOMBNUM].y,bomb[i%MAXBOMBNUM].width,bomb[i%MAXBOMBNUM].height,bomb[i%MAXBOMBNUM].dc,0,0,bomb[i%MAXBOMBNUM].width,bomb[i%MAXBOMBNUM].height,RGB(255,255,255));
	}
	//show information
	//show melife
	for (i=0;i<melifenum-1;i++) {
		TransparentBltU(memdc,ICONGAP+i*(melife.width+ICONGAP),0,melife.width,melife.height,melife.dc,0,0,melife.width,melife.height,RGB(255,255,255)) ;
	}
	//show meblood
	TransparentBltU(memdc,ICONGAP,window.height-meblood.height-ICONGAP,(LONG)(meblood.width*((DOUBLE)me.blood/(DOUBLE)MEBLOODDEFAULT)),meblood.height,meblood.dc,0,0,(LONG)(meblood.width*((DOUBLE)me.blood/(DOUBLE)MEBLOODDEFAULT)),meblood.height,RGB(255,255,255)) ;
	//show bombnum
	for (i=1;i<bombnum+1;i++) {
		TransparentBltU(memdc,window.width-i*(mebomb.width+ICONGAP),0,mebomb.width,mebomb.height,mebomb.dc,0,0,mebomb.width,mebomb.height,RGB(255,255,255)) ;
	}
	
	//show score
	i=score ;
	j=1 ;
	do {
		FLYOBJECT temp ;
		temp=scoretype[i%10] ;
		TransparentBltU(memdc,window.width-j*(temp.width+ICONGAP),window.height-temp.height-ICONGAP,temp.width,temp.height,temp.dc,0,0,temp.width,temp.height,RGB(255,255,255)) ;
		j++ ;
		i/=10 ;
	}
	while (i>0) ;
	
	//show to the screen
	BitBlt(displaydc,0,0,window.width,window.height,memdc,0,0,SRCCOPY) ;
//	if (times%5000==0) Refreshdc(hwnd) ;
	//debugging part
	fprintf(fp,"times:%6ld,enemyheadtail:",times) ;
	for (i=0;i<7;i++) fprintf(fp,"%6ld %6ld ",enemyhead[i],enemytail[i]) ;
	fprintf(fp,"enemybulletheadtail:%6ld %6ld ",enemybullethead,enemybullettail) ;
	fprintf(fp,"mebulletheadtail:%6ld %6ld ",mebullethead,mebullettail) ;
	fprintf(fp,"window:%6ld %6ld %6ld %6ld ",window.x,window.y,window.width,window.height) ;
	fprintf(fp,"\n") ;
	if (times%DIFFICULTYGAP==0&&times<=MAXDIFFICULTY) {
		for (i=0;i<ENEMYDIVERSITY;i++) enemypossibility[i]-=DIFFICULTYINCREASE ;
	}
	if (times%DIFFICULTYGAP==0&&times<=MAXDIFFICULTY) {
		for (i=0;i<BULLETDIVERSITY;i++)  bulletpossibility[i]-=DIFFICULTYINCREASE ;
	}
	if (times%DIFFICULTYGAP==0&&times<=MAXDIFFICULTY) {
		for (i=0;i<ENEMYDIVERSITY;i++) scoreadd[i]+=DIFFICULTYINCREASE ;
	}
//	if (times>=10000&&enemybullettail==enemybullethead+1) exit(1) ;
}

VOID CALLBACK Launchlaser(HWND hwnd,FLYOBJECT position)
{
	laserqueue[lasertail%MAXLASERNUM].x = position.x+position.width/2-laserqueue[lasertail%MAXLASERNUM].width/2-36 ;
	laserqueue[lasertail%MAXLASERNUM].y = position.y+position.height/2+67 ;
	laserqueue[lasertail%MAXLASERNUM].dx= position.dx ;
	laserqueue[lasertail%MAXLASERNUM].dy= position.dy ;
	laserqueue[lasertail%MAXLASERNUM].speed=position.speed ;
	lasertail++ ;
	laserqueue[lasertail%MAXLASERNUM].x = position.x+position.width/2-laserqueue[lasertail%MAXLASERNUM].width/2+35 ;
	laserqueue[lasertail%MAXLASERNUM].y = position.y+position.height/2+67 ;
	laserqueue[lasertail%MAXLASERNUM].dx= position.dx ;
	laserqueue[lasertail%MAXLASERNUM].dy= position.dy ;
	laserqueue[lasertail%MAXLASERNUM].speed=position.speed ;
	lasertail++ ;
	SetTimer(hwnd,WM_launchlaserTIMER,REMOVELASERGAP,RemovelaserTimerproc) ;
	sprintf(buflazer, "play %s from %ld",MWHERELAZER,start);
	mciSendString(buflazer,NULL,0,NULL);
}

VOID CALLBACK Createenemybullet(LONG enemytype,LONG bullet,LONG position) 
{
	char *address ;
	switch(bullet) {
		case ENEMYTYPE1:
			address = WHEREENEMYBULLET1 ;
			break ;
		case ENEMYTYPE2:
			address = WHEREENEMYBULLET2 ;
			break ;
		case ENEMYTYPE3:
			address = WHEREENEMYBULLET3 ;
			break ;
		}
	enemybullet[enemybullettail%MAXENEMYBULLETNUM] = bullettype[bullet] ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].hbitmap = (HBITMAP)
	LoadImage(hInst,address,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].x = enemy[enemytype][position].x+enemy[enemytype][position].width/2-bullettype[bullet].width/2 ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].y = enemy[enemytype][position].y+enemy[enemytype][position].height/2-bullettype[bullet].height/2 ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].blood = bulletharm[bullet] ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].dx = (me.x-enemy[enemytype][position].x)/TRACEDIVISOR ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy = (me.y-enemy[enemytype][position].y)/TRACEDIVISOR ;
	if (enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy<=3&&enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy>=0) enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy=4 ;
	if (enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy<0&&enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy>=-3) enemybullet[enemybullettail%MAXENEMYBULLETNUM].dy=-4 ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].speed = rand()%bulletspeed[bullet]+MINSMALLMOVESPEED ;
	enemybullet[enemybullettail%MAXENEMYBULLETNUM].dc = CreateCompatibleDC(displaydc) ;
	SelectObject(enemybullet[enemybullettail%MAXENEMYBULLETNUM].dc,enemybullet[enemybullettail%MAXENEMYBULLETNUM].hbitmap) ;
	enemybullettail++ ;
}

VOID CALLBACK Refreshdc(HWND hwnd)
{
	DeleteDC(displaydc) ;
	DeleteDC(memdc) ;
	displaydc = GetDC(hwnd) ;
	memdc = CreateCompatibleDC(displaydc) ;
	memhbitmap = CreateCompatibleBitmap(displaydc,window.width,window.height) ;
	SelectObject(memdc,memhbitmap) ;
}

VOID CALLBACK Createenemy(LONG *tail,LONG type,LONG which) 
{
	poss = rand()%10000 ;
	if (poss>=enemypossibility[type]) {
		enemy[type][*tail%MAXENEMYFLYOBJECT].x = window.width/8+rand()%(window.width*3/4-enemy[type][*tail%MAXENEMYFLYOBJECT].width) ;
		enemy[type][*tail%MAXENEMYFLYOBJECT].y = -enemy[type][*tail%MAXENEMYFLYOBJECT].height+DEFAULTOFF ;
		enemy[type][*tail%MAXENEMYFLYOBJECT].blood = fullblood[type] ;
		enemy[type][*tail%MAXENEMYFLYOBJECT].dx = rand()%MAXDX-(MAXDX/2) ;
		enemy[type][*tail%MAXENEMYFLYOBJECT].dy = rand()%MAXDY+1 ;
		enemy[type][*tail%MAXENEMYFLYOBJECT].speed = rand()%enemyspeed[type]+1 ;
		*tail = *tail+1 ;
	}
}

VOID CALLBACK Createbonus(LONG *tail,LONG type,FLYOBJECT which)
{
	enemy[type][*tail%MAXENEMYFLYOBJECT].x = which.x+which.width/2-enemy[type][*tail%MAXENEMYFLYOBJECT].width/2 ;
	enemy[type][*tail%MAXENEMYFLYOBJECT].y = which.y+which.height/2-enemy[type][*tail%MAXENEMYFLYOBJECT].height/2 ;
	enemy[type][*tail%MAXENEMYFLYOBJECT].dx = rand()%MAXDX-(MAXDX/2) ;
	enemy[type][*tail%MAXENEMYFLYOBJECT].dy = rand()%MAXDY+1 ;
	enemy[type][*tail%MAXENEMYFLYOBJECT].speed = rand()%enemyspeed[type]+1 ;
	*tail = *tail+1 ;
}

VOID CALLBACK Removeflyobject(FLYOBJECT *flyer,LONG *head,LONG now,LONG max) 
{
	FLYOBJECT temp ;
	FLYOBJECT *flyhead,*flynow ;
	flyhead = flyer+(*head%max) ;
	flynow = flyer+(now%max) ;
	temp = *flyhead ;
	*flyhead = *flynow ;
	*flynow = temp ;
	*head = *head+1 ;
}

DOUBLE CALLBACK Distance(LONG x1,LONG y1,LONG x2,LONG y2) 
{
	return(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))) ;
}

BOOL CALLBACK Collision(FLYOBJECT a,FLYOBJECT b) 
{
	LONG x1,x2,y1,y2 ;
	x1=a.x+a.width/2 ;
	x2=b.x+b.width/2 ;
	y1=a.y+a.height/2 ;
	y2=b.y+b.height/2 ;
	if (Distance(x1,y1,x2,y2)<=a.radius+b.radius) return 1 ;
	return 0 ;
}

VOID CALLBACK Refreshme(HWND hwnd) 
{
	me.x=mebirthx ;
	me.y=mebirthy ;
	me.blood=1<<31 ;
	meharm = MEHARMDEFAULT ;
	bombnum = DEFAULTBOMBNUM ;
	SetTimer(hwnd,WM_regainbloodTIMER,REGAINBLOODLATENCY,RegainbloodTimerproc) ;
}

VOID CALLBACK RegainbloodTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime)
{
	me.blood=MEBLOODDEFAULT ;
	KillTimer(hwnd,WM_regainbloodTIMER) ;
}

BOOL CALLBACK Isin(FLYOBJECT a,FLYOBJECT b) 
{
	if (a.x<=b.x&&a.x+a.width>=b.x) {
		if (a.y<=b.y+b.height&&a.y+a.height>=b.y) return 1 ;
	}
	if (b.x<=a.x&&b.x+b.width>=a.x) {
		if (b.y<=a.y+a.height&&b.y+b.height>=a.y) return 1 ;
	}
	return 0 ;
}

VOID CALLBACK Cleanwindow()
{
	LONG i ;
	for (i=0;i<ENEMYDIVERSITY-BONUSDIVERSITY;i++) 
		enemyhead[i] = enemytail[i] = 0 ;
	for (i=enemybullethead;i<enemybullettail;i++)
		DeleteDC(enemybullet[i%MAXENEMYBULLETNUM].dc) ;
	enemybullethead = enemybullettail = 0 ;
}

VOID CALLBACK Moveflyobject(FLYOBJECT *flyer) 
{
	flyer->x += flyer->dx*flyer->speed/MOVEDIVISOR ;
	flyer->y += (flyer->dy*flyer->speed/MOVEDIVISOR==0)?1:flyer->dy*flyer->speed/MOVEDIVISOR ;

}

VOID CALLBACK MemoveupTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) 
{
	if (me.y-me.speed<0) {
		KillTimer(hwnd,WM_memoveupTIMER) ;
		return ;
	}
	me.y -= me.speed ;
}

VOID CALLBACK MemovedownTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) 
{
	if (me.y+me.height+me.speed>window.height) {
		KillTimer(hwnd,WM_memovedownTIMER) ;
		return ;
	}
	me.y += me.speed ;
}
VOID CALLBACK MemoveleftTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) 
{
	if (me.x-me.speed<0) {
		KillTimer(hwnd,WM_memoveleftTIMER) ;
		return ;
	}
	me.x -= me.speed ;
}
VOID CALLBACK MemoverightTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwTime) 
{
	if (me.x+me.width+me.speed>window.width) {
		KillTimer(hwnd,WM_memoverightTIMER) ;
		return ;
	}
	me.x += me.speed ;
}

VOID CALLBACK Launchbomb() 
{
	bomb[bombtail%MAXBOMBNUM].x=0 ;
	bomb[bombtail%MAXBOMBNUM].y=window.height-DEFAULTOFF ;
	bomb[bombtail%MAXBOMBNUM].dx=0 ;
	bomb[bombtail%MAXBOMBNUM].dy=-1 ;
	bomb[bombtail%MAXBOMBNUM].speed=BOMBSPEED ;
	bombnum-- ;
	bombtail++ ;
	sprintf(bufbomb, "play %s from %ld",MWHEREBOMB,500);
	mciSendString(bufbomb,NULL,0,NULL);
}

VOID CALLBACK MefireTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwtime)
{
	if(mebullettail-mebullethead<MAXMEBULLETNUM){
		mebullet[mebullettail%MAXMEBULLETNUM].x=me.x+me.width/2-mebullet[mebullettail%MAXMEBULLETNUM].width/2;
		mebullet[mebullettail%MAXMEBULLETNUM].y=me.y;
		++mebullettail;
				sprintf(bufbullet,"play %s from %ld",MWHEREMEBUL,40);
				mciSendString(bufbullet,NULL,0,NULL);	
	}
}

VOID CALLBACK RemovelaserTimerproc(HWND hwnd,UINT uMsg,UINT idEvent,DWORD dwtime)
{
	while (lasertail>laserhead)Removelaser(hwnd) ;
	KillTimer(hwnd,WM_launchlaserTIMER) ;
}

VOID CALLBACK Removelaser(HWND hwnd)
{
	Removeflyobject(laserqueue,&laserhead,laserhead,MAXLASERNUM) ;
	laserhead++ ;
}

VOID CALLBACK Gameover(HWND hwnd) 
{
	LONG j,i ;
	KillTimer(hwnd,WM_mainrefreshTIMER) ;
	StretchBlt(displaydc,0,0,window.width,window.height,gameover.dc,0,0,gameover.width,gameover.height,SRCCOPY) ;
	//show score
	i=score ;
	j=1 ;
	do {
		FLYOBJECT temp ;
		temp=scoretype[i%10] ;
		TransparentBltU(displaydc,window.width-j*(temp.width+ICONGAP),window.height-temp.height-ICONGAP,temp.width,temp.height,temp.dc,0,0,temp.width,temp.height,RGB(255,255,255)) ;
		j++ ;
		i/=10 ;
	}
	while (i>0) ;

	running = -1 ;
	sprintf(buf,"stop %s",MWHEREBGM,0);
	mciSendString(buf,NULL,0,NULL);
	sprintf(bufover,"play %s from %ld",MWHEREOVER,start);
	mciSendString(bufover,NULL,0,NULL);
}

VOID CALLBACK Loadscoretype(CHAR *from,LONG i)
{
	scoretype[i].hbitmap=(HBITMAP)
	LoadImage(hInst,from,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE) ;
	GetBitmapWidthAndHeight(from,&scoretype[i].width,&scoretype[i].height) ;
	scoretype[i].dc=CreateCompatibleDC(displaydc) ;
	SelectObject(scoretype[i].dc,scoretype[i].hbitmap) ;
}
