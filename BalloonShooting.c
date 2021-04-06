
//HEADER FILE

# include "graphics.h"
# include "conio.h"
# include "stdio.h"
# include "string.h"
# include "stdlib.h"
# include "dos.h"
#define ARROW_SIZE 8
#define BALLOON_SIZE 5

//GLOBAL VARAIABLE

int flag_arrow=0,flag_balloon=1,count_arrow=7,count_balloon=12;
char name[10],audio;

//FUNCTION DECLARATION

void *balloon,*bow,*arrow,*burst;
void *clear_balloon,*clear_burst;
void draw_balloon(int ,int );
void draw_burst ( int x, int y );
void draw_bow(int x,int y);
void draw_arrow(int x, int y);
void shoot(int *x, int *y);
int testkeys();
void fly(int *x, int *y);
void start();

void main()
{
int maxx,maxy;
int i,len,rate;
int gdriver=DETECT,gmode,area;
int p=400,q=300,m=100,n=100,x=m,y=n,key,score=0,finish=0,level=1,l_flag=1;
char score1[5],ch,cnt_ball[5],char_level[2];

//INITIALIZE GRAPHIC MODE

initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
setbkcolor(3);
	
//READ INPUT FROM USER
	
printf("\n\n\n\n\n\n\n\n\t\t\t  ENTER YOUR NAME : ");
gets(name);
len=strlen(name);

//CONVERTING NAME TO UPPER CASE

for(i=0;i<len;i++)
{
if(name[i]>='a' && name[i]<='z')
name[i]=name[i]^32;
else
name[i]=name[i];
}
	
//READ INPUT FROM USER

printf("\n\n\n\t\t\tDO YOU WANT AUDIO? (Y/N) :  ");
scanf("%c",&audio);
printf("\n\n\n\t     IF YOU WANT TO QUIT THE GAME IN BETWEEN, PRESS 'ESC'");
printf("\n\n\n\n\t\t\tPRESS ANY KEY TO CONTINUE....");
getch();
clrscr();
cleardevice();

//CALLING USERDEFINED FUNCTION
	
start(); 
maxx = getmaxx() ;
maxy = getmaxy() ;

    rectangle ( 0, 0, maxx-1, maxy-1 ) ;

    draw_burst(200,300);
    area=imagesize(0,0,32,24);
    burst=malloc(area);
    getimage(200-16,300-12,200+16,300+12,burst);
    putimage(200-16,300-12,burst,XOR_PUT);

    draw_balloon(p,q);

area=imagesize(p-4*BALLOON_SIZE,q-5*BALLOON_SIZE,p+4*BALLOON_SIZE,q+7*BALLOON_SIZE);
balloon=malloc(area);

getimage(p-4*BALLOON_SIZE,q-5*BALLOON_SIZE,p+4*BALLOON_SIZE,q+7*BALLOON_SIZE,balloon);
    putimage(p-4*BALLOON_SIZE, q-5*BALLOON_SIZE, balloon, COPY_PUT);

    draw_arrow(x ,y  );
    area = imagesize(x, y-ARROW_SIZE, x+(6*ARROW_SIZE), y+ARROW_SIZE);
    arrow=malloc(area);
    getimage(x, y-ARROW_SIZE, x+(6*ARROW_SIZE), y+ARROW_SIZE,arrow);
    putimage(x, y-ARROW_SIZE,arrow,XOR_PUT);

    draw_bow(x,y);
    area=imagesize(x+25,y-65,x+66,y+65);
    bow=malloc(area);
    getimage(x+25,y-65,x+66,y+65,bow);

    if ( balloon == NULL || burst == NULL || bow == NULL )
    {
	printf( "Insufficient memory... Press any key " ) ;
	getch() ;

	//EXITING GRAPHIC MODE

	closegraph() ;
	restorecrtmode() ;
	exit( 0 ) ;
    }

    while (!finish)
    {
	settextstyle(8,0,1);
	setusercharsize(4,4,3,3);
	outtextxy(getmaxx()/2-100,5,"LEVEL : ");
	itoa(level,char_level,10);
	setfillstyle(0,0);
	bar(getmaxx()/2+40,15,getmaxx()/2+70,45);
	outtextxy(getmaxx()/2+50,5,char_level);

	rectangle(5,360,250,460);
	    
	    //LOGIC
	    
	if( flag_balloon && count_balloon>0 )
	fly( &p, &q );
	else
    {
	q = 400;
	flag_balloon = 1;
    }
	
	    //THE PROGRAM WAITS TILL THE USER DOESNOT PRESS ANY KEY
	    
	if( kbhit() )
	{
	key = testkeys();
		
	if(key==77)
	flag_arrow = 1;
	}

	    //IF ESCAPE KEY IS PRESSED THE GAME EXITS
	    
	if( key == 27 )
	break;
	if (key == 80 &&!flag_arrow)
	{
	x=125;
	putimage(x,y-65,bow,XOR_PUT);
	if(y<300)
	y+=25;
	putimage(x,y-65,bow,XOR_PUT);
	draw_bow(x-25,y);
	key=0;
	}
	if (key == 72 &&!flag_arrow)
	{
	x=125;
	putimage(x,y-65,bow,XOR_PUT);
	if(y>70)
	y-=25;
	putimage(x,y-65,bow,XOR_PUT);
	draw_bow(x-25,y);
	key=0;
	}
	if(count_arrow > 0 && count_balloon > 0)

//LEVEL2

	{
    if(score==100 && l_flag==1)
    {
	  level=2;
	  setbkcolor(YELLOW);
	  count_balloon=9;
	  count_arrow=7;
	  l_flag=2;
    }

//LEVEL3

    if(score==200 && l_flag==2)
    {
	 level=3;
	 setbkcolor(GREEN);
	 count_balloon=7;
	 count_arrow=7;
	 l_flag=0;
    }
		
	//IF THE RIGHT ARROW KEY IS PRESSED AN ARROW IS SHOT
		
    if( key == 77 || flag_arrow)
	  {
	shoot(&x,&y);
	draw_bow(m,y);
	if(x>(p-12) && x<(p+12) && y>(q-15) && y<(q+25))
	{
	putimage(p-16,q-12,burst,COPY_PUT);
	sound(1500);
	delay(800);
	nosound();
	putimage(p-16,q-12,burst,XOR_PUT);
	count_balloon--;
	settextstyle(10,0,1);
	setusercharsize(30,70,20,70);
	outtextxy(20,380,"BALLOONS LEFT:");
	setfillstyle(0,0);
	bar(200,370,230,400);
	itoa(count_balloon,cnt_ball,10);
	outtextxy(200,380,cnt_ball);
	flag_balloon=0;
	score+=20;
	itoa(score,score1,10);
	setfillstyle(0,0);
	bar(190,getmaxy()-50,230,getmaxy()-30);
	setcolor(RED);
	outtextxy(20,getmaxy()-50,"SCORE          : ");
	outtextxy(190,getmaxy()-50,score1);
	}

	key=0;
	 }
	}
	else
	{
    clearviewport();
		
	//THE RESULT PAGE OF THE GAME WHERE THE COMPILER DISPLAYS THE FINAL SCORE & ETC
		
    setbkcolor(9);
    setcolor(10);
    settextstyle(4,0,7);
    setusercharsize(120,50,120,40);
		
    outtextxy(getmaxx()/2-235,getmaxy()/2-180,"GAME OVER");

    settextstyle(8,0,1);
    setusercharsize(50,60,40,50);
    if(count_arrow<=0)
    outtextxy(getmaxx()/2-115,getmaxy()/2-60,"NO MORE ARROWS");

    if(count_balloon<=0)
    outtextxy(getmaxx()/2-120,getmaxy()/2-60,"NO MORE BALLOONS");

    outtextxy(getmaxx()/2-225,getmaxy()/2-20,name);
    outtextxy(getmaxx()/2-100,getmaxy()/2-20," YOUR SCORE IS : ");
    itoa(score,score1,10);
    outtextxy(getmaxx()/2+190,getmaxy()/2-20,score1);

    if(level==1)
    {
    outtextxy(getmaxx()/2-185,getmaxy()/2+20,"YOU REACHED TILL LEVEL 1");
    outtextxy(getmaxx()/2-230,getmaxy()/2+60,"YOU REQUIRE TO PRACTICE MORE");
    }
    if(level==2)
    {
    outtextxy(getmaxx()/2-185,getmaxy()/2+20,"YOU REACHED TILL LEVEL 2");
    outtextxy(getmaxx()/2-70,getmaxy()/2+60,"WELL PLAYED");
    }
    if(level==3)
    {
    outtextxy(getmaxx()/2-185,getmaxy()/2+20,"YOU REACHED TILL LEVEL 3");
    outtextxy(getmaxx()/2-230,getmaxy()/2+60,"YOU ARE AN EFFICIENT SHOOTER");
    }

    outtextxy(getmaxx()/2-30,getmaxy()/2+100,"(Q)UIT");

    settextstyle(1,0,1);
    setusercharsize(30,65,30,60);
		
		//THE USER CAN EXIT THE GAME BY PRESSING 'Q'
		
    while( getch() != 'q');
		
		//READ INPUT FROM USER
		
    cleardevice();
    setbkcolor(3);
    printf("\n\n\n\n\n\n\n\n\t\t\tRATE YOUR EXPERIENCE (1-10) : ");
    scanf("%d",&rate);
    if(rate<1 || rate>10)
    {
    printf("\n\n\n\t\t\t   RATE AGAIN (1-10) : ");
    scanf("%d",&rate);
    }
    if(rate<=5 && rate>=1)
    printf("\n\n\n\tTHANKYOU FOR YOUR RESPONSE, WILL SURELY TRY TO MAKE IT BETTER.");
    else if(rate<=8 && rate>5)
    printf("\n\n\n\t     THANKYOU, WILL SURELY UPGRADE IT WITH NEW FEATURES");
    else if(rate<=10 && rate>8)
    printf("\n\n\n\t     THANKS A LOT, WE ARE GLAD THAT YOU LIKED THE GAME");
    printf("\n\n\n\t\t\t   PRESS ANY KEY TO EXIT!!");
    getch();
    finish=1;
    break;
    }
    }
   free(bow);
   free(arrow);
   free(balloon);
   closegraph();
}

//FUNCTION USED TO DRAW BALLOON

void draw_balloon(int x,int y)
{
     setcolor(RED);
     setfillstyle(1,RED);
     fillellipse(x,y,3*BALLOON_SIZE,4*BALLOON_SIZE);
     line(x,y+4*BALLOON_SIZE,x,y+6*BALLOON_SIZE);
}

//FUNCTION USED TO DRAW BALLOON BURST

void draw_burst ( int x, int y )
{
    setlinestyle(0,0,1);
    line ( x - 16, y - 12, x - 10, y - 2 ) ;
    line ( x - 10, y - 2, x - 16, y ) ;
    line ( x - 16, y, x - 10, y + 2 ) ;
    line ( x - 10, y + 2, x - 16, y + 12 ) ;

    line ( x - 16, y + 12, x - 6, y + 2 ) ;
    line ( x - 6, y + 2, x, y + 12 ) ;
    line ( x, y + 12, x + 6, y + 2 ) ;
    line ( x + 6, y + 2, x + 16, y + 12 ) ;

    line ( x - 16, y - 12, x - 6, y - 2 ) ;
    line ( x - 6, y - 2, x, y - 12 ) ;
    line ( x, y - 12, x + 6, y - 2 ) ;
    line ( x + 6, y - 2, x + 16, y - 12 ) ;

    line ( x + 16, y - 12, x + 10, y - 2 ) ;
    line ( x + 10, y - 2, x + 16, y ) ;
    line ( x + 16, y, x + 10, y + 2 ) ;
    line ( x + 10, y + 2, x + 16, y + 12 ) ;

}

//FUNCTION USED TO DRAW A BOW

void draw_bow(int x,int y)
{
    setcolor(RED);
    setlinestyle(0,0,1);
    line(x+32,y-49,x+32,y+49);
    setlinestyle(0,0,3);
    arc(x,y,300,60,60);
    arc(x+34,y-56,100,220,6);
    arc(x+34,y+56,140,260,6);
}

void shoot(int *x, int *y)
{
    char cnt_arrow[5];
    putimage(*x, *y-ARROW_SIZE, arrow, COPY_PUT);
    delay(1);
    putimage(*x, *y-ARROW_SIZE, arrow, XOR_PUT);
    *x+=ARROW_SIZE;

    if (*x>590)
    {
	*x=155;
	flag_arrow=0;
	count_arrow--;
	settextstyle(10,0,1);
	setusercharsize(30,70,20,70);
	outtextxy(20,400,"ARROWS LEFT :");
	setfillstyle(0,WHITE);
	bar(200,400,220,425);
	itoa(count_arrow,cnt_arrow,10);
	outtextxy(200,400,cnt_arrow);
    }

}

//FUNCTION USED TO DRAW AN ARROW

void draw_arrow(int x, int y)
{
    setlinestyle(0,0,2);
    moveto(x, y);
    linerel(6*ARROW_SIZE, 0);
    linerel(-2*ARROW_SIZE, -1*ARROW_SIZE+1);
    linerel(0, 2*ARROW_SIZE-1);
    linerel(2*ARROW_SIZE, -1*ARROW_SIZE);
}

int testkeys()
{
    union REGS ii, oo ;
    ii.h.ah = 0 ;
    int86 ( 22, &ii, &oo ) ;
    /* if ascii code is not 0 */
    if ( oo.h.al )
	return ( oo.h.al ) ;  /* return ascii code */
    else
	return ( oo.h.ah ) ;  /* return scan code */
}

//PARAMETERS LIKE SPEED,DELAY OF THE BALLOON FLIGHT ARE STORED HERE

void fly(int *x, int *y)
{
    int x1;
    char cnt_ball[5];
    putimage(*x-4*BALLOON_SIZE, *y-5*BALLOON_SIZE, balloon, COPY_PUT);
    delay(55);
    putimage(*x-4*BALLOON_SIZE, *y-5*BALLOON_SIZE, balloon, XOR_PUT);
    *y-=BALLOON_SIZE;

    if(*y<= 20)
    {
	*y=400;
	x1=450+rand()%150;
	*x=x1;
	count_balloon--;
	settextstyle(10,0,1);
	setusercharsize(30,70,20,70);
	outtextxy(20,380,"BALLOONS LEFT:");
	setfillstyle(0,0);
	bar(200,370,230,400);
	itoa(count_balloon,cnt_ball,10);
	outtextxy(200,380,cnt_ball);
    }
}

void start()
{
    float octave[7] = { 130.81, 146.83, 164.81, 174.61, 196, 220, 246.94};
    setbkcolor(3);
    settextstyle(8,0,0);
    setcolor(15);
    outtextxy(10,400,"  PRESS ANY KEY TO CONTINUE....");
    settextstyle(1,0,1);
    setcolor(4);
    setusercharsize(25,15,20,4);
    outtextxy(85,120,"BALLOON SHOOTING");

   //AUDIO SETTINGS
	
	if(audio=='Y' || audio=='y')
    {
    while( !kbhit() )
    {
	sound( octave[ random(7) ]*2 );
	delay(300);
    }
    }
    nosound();
    getch();
	
	//INSTRUCTION PAGE
	
    clearviewport();
    rectangle(1,1,638,478);
    settextstyle(3,0,1);
    setusercharsize(50,30,50,30);
    outtextxy(155,10,"INSTRUCTIONS");
    setbkcolor(3);
    settextstyle(6,0,1);
    setusercharsize(40,70,20,20);
    outtextxy(10,70,"1. The game has three levels.");
    outtextxy(10,110,"2. The bow can be moved UP and DOWN with the help of arrow keys.");
    outtextxy(10,150,"3. The arrow can be shot using the right arrow key.");
    outtextxy(10,190,"4. Every time you shoot the balloon, you score 20 points.");
    outtextxy(10,230,"5. First level has 7 arrows and 12 balloons.");
    outtextxy(10,270,"6. You require to score 100 points to enter the second level.");
    outtextxy(10,310,"7. Second level has 7 arrows and 9 balloons.");
    outtextxy(10,350,"8. You require to score 200 points to enter the third level.");
    outtextxy(10,390,"9. Third level has 7 arrows and 7 balloons.");
    settextstyle(8,0,3);
    setcolor(15);
    outtextxy(145,445,"PRESS ANY KEY TO CONTINUE");
    setcolor(4);
    getch();
    setusercharsize(1,1,1,1);
    settextstyle(0,0,0);
    setbkcolor(3);
clearviewport();
}
