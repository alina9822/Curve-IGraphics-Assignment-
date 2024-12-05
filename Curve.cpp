#include "iGraphics.h"

int screenWidth=1366;
int screenHeight=768;
int midHeight=screenHeight/2;

int r=255;
int g=255;
int b=255;

int red[] = {255,0,255,0,255,153,102,255};
int green[] = {255,0,0,255,51,0,255,153};
int blue[] = {0,255,0,0,153,153,255,51};
int colors=8;

double frequency[]= {1,0.5,1.5,0.7,3,2,1.8,2.4};
double amplitude[]= {100,50,150,80,200,250,300,180};
double curveType[]= {1,0,1,0,1,0,1,0};
int totalCurve=3;

double amp=1;
double frq=1;

int x=0;
int y=midHeight;
double startX=0;

double ballX=0;
int d=8;
int dir=1;
int l=1;

int showCurve=1;
int showBall=1;
int ballShow[10]= {1,1,1,1,1,1,1,1,1,1};
int ballNum[10]= {0};
int numBall=1;
int resultCurveShow=1;
int highlight=1;
int start=0;
int co_ordinateShow=1;
int Xshow=1;
int Yshow=1;

int dx;
double s=3.1416/20;
double phase=0;

char str[10];

void ballMove();
void drawCurves();
void drawBall();


void iKeyboard(unsigned char key)
{
    if(key=='a')
        amp*=1.05;
    if(key=='A')
        amp/=1.05;
    if(key=='f')
        frq*=1.05;
    if(key=='F')
        frq/=1.05;

    /* if(key=='a')
         amp+=.05;
     if(key=='A')
         amp-=.05;
     if(key=='f')
         frq+=.05;
     if(key=='F')
         frq-=.05;*/

    if(key=='s' || key=='S')
        showCurve=1-showCurve;
    if(key=='b' || key=='B')
        showBall=1-showBall;
    if(key=='p' || key=='P')
        iPauseTimer(0);
    if(key=='r' || key=='R')
        iResumeTimer(0);
    if(key=='h' || key=='H')
    {
        if(showCurve)
            resultCurveShow=1-resultCurveShow;
    }
    if(key=='n')
    {
        if(totalCurve<8)
        {
            totalCurve++;
            ballShow[totalCurve]=ballShow[totalCurve-1];
            ballNum[totalCurve]=ballNum[totalCurve-1];
        }
    }
    if(key=='N')
        totalCurve--;
    if(key=='+')
        d++;
    if(key=='-')
    {
        d--;
        if(d<=0)
        {
            //d=0;
            l=1-l;
            d=l;
        }
    }
    if(key=='M')
        phase+=s;
    if(key=='m')
        phase-=s;
    if(key=='c' || key=='C')
        co_ordinateShow=1-co_ordinateShow;
    if(key=='l' || key=='L')
        highlight=1-highlight;
    if(key=='x' || key=='X')
        if(co_ordinateShow)
            Xshow=1-Xshow;
    if(key=='y' || key=='Y')
        if(co_ordinateShow)
            Yshow=1-Yshow;
    if(key>='1' && key<='9')
    {
        int idx=key-'0'-1;
        if(idx<=totalCurve && showBall && ballNum[idx]==0)
            ballShow[idx]=1-ballShow[idx];
    }
    if(key=='t' || key=='T')
    {
        if(showBall==1)
        {
            for(int i=0; i<=totalCurve; i++)
            {
                ballShow[i]=1-ballShow[i];
                ballNum[i]=1-ballNum[i];
            }
        }
    }
}
void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_F1)
        start=1-start;
    if(key==GLUT_KEY_LEFT)
    {
        // x-=d;
        startX+=(d-3);
        // screenWidth+=d;
    }
    if(key==GLUT_KEY_RIGHT)
    {
        //x+=d;
        startX-=(d-3);
        //screenWidth-=d;
    }
    if(key==GLUT_KEY_END)
    {
        printf("THANK YOU!");
        exit(0);
    }

}
void iMouseMove(int mx, int my)
{
     /* startX=mx;
       midHeight=my;*/
}
void iMouse(int button,int state,int mx, int my)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
    }
    if(button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
    }
}
void iDraw()
{
    if(start==0)
    {
        iClear();
        iShowBMP(171,44,"help.bmp");

        iSetColor(100,100,100);
        iText(342,690,"Toggle Help/Main page  : F1",GLUT_BITMAP_9_BY_15);
        iText(342,660,"Toggle curve show/hide : s/S",GLUT_BITMAP_9_BY_15);
        iText(342,630,"Toggle ball show/hide  : b/B",GLUT_BITMAP_9_BY_15);
        iText(342,600,"Toggle tracer show/hide: <curve_No>",GLUT_BITMAP_9_BY_15);
        iText(342,570,"Pause animation  : p/P",GLUT_BITMAP_9_BY_15);
        iText(342,540,"Resume animation : r/R",GLUT_BITMAP_9_BY_15);
        iText(342,510,"Increase amplitude: a",GLUT_BITMAP_9_BY_15);
        iText(342,480,"Decrease amplitude: A",GLUT_BITMAP_9_BY_15);
        iText(342,450,"Increase frequency: f",GLUT_BITMAP_9_BY_15);
        iText(342,420,"Decrease frequency: F",GLUT_BITMAP_9_BY_15);
        iText(342,390,"Increase speed    : +",GLUT_BITMAP_9_BY_15);
        iText(342,360,"Decrease speed    : -",GLUT_BITMAP_9_BY_15);
        iText(342,330,"Increase curve no : n",GLUT_BITMAP_9_BY_15);
        iText(342,300,"Decrease curve no : N",GLUT_BITMAP_9_BY_15);
        iText(342,270,"Curve no show/hide: t/T",GLUT_BITMAP_9_BY_15);
        iText(342,240,"Only result curve show: h/H",GLUT_BITMAP_9_BY_15);
        iText(342,210,"Co-ordinate shift leftward  : left arrow",GLUT_BITMAP_9_BY_15);
        iText(342,180,"Co-ordinate shift rightward : right arrow",GLUT_BITMAP_9_BY_15);
        iText(342,150,"Phase shift rightward : m",GLUT_BITMAP_9_BY_15);
        iText(342,120,"Phase shift leftward  : M",GLUT_BITMAP_9_BY_15);
        iText(342,90,"Exit                   : END",GLUT_BITMAP_9_BY_15);
    }
    else
    {
        iClear();
        iSetColor(255,255,255);//iSetColor(r,g,b);

        if(showCurve && co_ordinateShow)
        {
            if(Xshow)
                iLine(0,midHeight,screenWidth,midHeight);
            if(Yshow)
                iLine(-startX,0,-startX,1366);
        }

        drawCurves();
        if(showBall)
            drawBall();
    }
}
void drawCurves()
{
    double dy,dx1,dy1,theta,theta1,resultY=0,resultY1=0;
    int i;
    for(dx=0; dx<=1366; dx++)
    {
        resultY=resultY1=0;


        for(i=0; i<totalCurve; i++)
        {
            theta = ((dx+startX)*3.1416/180);//+(phase*(1/frequency[i]));
            theta1=((dx+1+startX)*3.1416/180);//+(phase*(1/frequency[i]));
            if(curveType[i])
            {
                dy=amp*amplitude[i]*sin(frq*(frequency[i]*theta+phase));
                dy1=amp*amplitude[i]*sin(frq*(frequency[i]*theta1+phase));
            }
            else
            {
                dy=amp*amplitude[i]*cos(frq*(frequency[i]*theta+phase));
                dy1=amp*amplitude[i]*cos(frq*(frequency[i]*theta1+phase));
            }
            resultY+=dy;
            resultY1+=dy1;

            iSetColor(red[i],green[i],blue[i]);//iSetColor(255,255,255);//iSetColor(r,g,b);
            if(showCurve && resultCurveShow)
                iLine(x+dx,y+dy,x+dx+1,y+dy1);
        }

        iSetColor(r,g,b);//iSetColor(red[i%colors],green[i%colors],blue[i%colors]);//iSetColor(255,255,255);//

        if(showCurve)
            iLine(x+dx,y+resultY,x+dx+1,y+resultY1);

        //iPoint(x+dx,y+resultY,2);
    }
}
void drawBall()
{
    double ballY,theta,resultBallY=0;
    int color[10];

    int i;
    for(i=0; i<totalCurve; i++)
    {
        theta=((ballX+startX)*3.1416/180);//+(phase*(1/frequency[i]));

        iSetColor(red[i],green[i],blue[i]);
        if(curveType[i])
            ballY=amp*amplitude[i]*sin(frq*(frequency[i]*theta+phase));
        else
            ballY=amp*amplitude[i]*cos(frq*(frequency[i]*theta+phase));

        resultBallY+=ballY;
        str[0]=i+1+48;
        if(ballShow[i] && showBall)
            iFilledCircle(x+ballX,y+ballY,3+i);
        else if(ballNum[i])
            iText(x+ballX,y+ballY,str,GLUT_BITMAP_HELVETICA_18);
    }

    str[0]=i+1+48;
    iSetColor(r,g,b);
    if(ballShow[i] && showBall)
        iFilledCircle(x+ballX,y+resultBallY,5+i);
    else if(ballNum[i])
        iText(x+ballX,y+resultBallY,str,GLUT_BITMAP_TIMES_ROMAN_24);

}
void ballMove()
{
    if(highlight)
    {
        r=rand()%100;
        g=rand()%100;
        b=rand()%100;
    }
    else
        r=g=b=255;

    ballX+=(d*dir);
    if(ballX>screenWidth || ballX<x)
        dir*=-1;

}
int main()
{
    iSetTimer(25,ballMove);
    iInitialize(screenWidth,screenHeight,"1905099");

    return 0;
}

