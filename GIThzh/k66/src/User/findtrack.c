
#include  "common.h"
#include "include.h"
#include "findtrack.h"
#include "math.h"
#include "magnet.h"
#include "steer.h"



/*********SearchCenterBlackline相关定义**********/

int   MiddleLine[RowMax+1];
int   RightEdge[RowMax+1];
int   LeftEdge[RowMax+1];
int   Width[RowMax+1];//={2,3,3,3,4,4,5,5,6,6,
//8,8,10,10,12,13,14,14,16,17,
//18,18,20,20,22,22,24,24,26,26,
//28,30,31,32,32,34,36,36,38,39,
//41,41,43,43,45,45,47,47,49,50,
//50,51,52,54,55,56,57,58,59,60,61};  // Width[i]  = 20+i*3/4;     //动态路宽

int   MidPri         = 80;

int game=0;
int overover=200;
/*********GetBlackEndParam相关定义**********/
int LastLine;

int BlackEndMR      = 0;
int BlackEndML      = 0;
int BlackEndL       = 0;
int BlackEndM       = 0;
int BlackEndR       = 0;
int BrokenU         = 0;
int BrokenUZ         = 0;
int BrokenUY         = 0;
int BrokenM         = 0;
int BrokenD         = 0;
int Brokenend       = 0;

int lengthm=0;
int lengthml=0;
int lengthmr=0;
int lengthl=0;
int lengthr=0;

int BrokenFlag      = 0;
int broken_p=0;
int broken_m=0;
int broken_d=0;

float pi =3.1415926;
int attractivepower_l = 30000;
int attractivepower_r = 30000;
int repulsivepawer  = 30000;
int r=4;
int R=4;
//int maxTurn=10*pi/180;
int currentPosition_y=119;
int currentPosition_x;
int nextposition_y=119;
int nextposition_x;
int lastposition_y=119;
int lastposition_x;
int Endpoint =0;
int roundflagl =0;
//int roundpointl=0;
int roundflagr =0;
//int roundpointr=0;
extern int rr=10,ll=10;


double angle = 0;
double slangle;
float lastangle =0;
int midline_x[120];
int midline_y[120];
int m;
double fx,fy;
// double B;
int LL;
int RR;
int oll;
int orr;
int point =0;

void findend(void);
void shiliangle(void);
void yuanhuanshibie(void);
void gamestart_over(void);

void rengongshichang(void)
{
  Endpoint=0;
  int i,j;
  int le=0,re=119;
  int x1,y1;
  lengthm=0;
  lengthml=0;
  lengthmr=0;
  lengthl=0;
  lengthr=0;
  angle = 0;
  // int endm=0,endmr=0,endr=0,endml=0,endl=0;
  m=0;
  
  for(j=80;j>=0;j--)          //找首行中点
  {
    if(Pixle[119][j]==1&&Pixle[119][j-1]==0&&Pixle[119][j-2]==0)
      le=j;
    if(Pixle[119][160-j]==1&&Pixle[119][161-j]==0&&Pixle[119][162-j]==0)
      re=160-j;
  }
  
  currentPosition_x=(int)((le+re)/2);
  nextposition_x=(int)((le+re)/2);
  lastposition_x=(int)((le+re)/2);  //确定起点
  // currentPosition_x=80;
  // nextposition_x=80;
  nextposition_y=119;
  // lastposition_x=80;
 midline_x[0]=nextposition_x;

  midline_y[0]=119;
  
  while(!Endpoint)
  {
    int endm=0,endmr=0,endr=0,endml=0,endl=0; 
    
    currentPosition_x=nextposition_x;
    currentPosition_y=nextposition_y;
    i=nextposition_y;
    j=nextposition_x;
    
    y1=(int)(r*sin(0.5*pi-angle));
    x1=(int)(r*cos(0.5*pi-angle));
    while(!endm)                      //中间的线
    { 
      if((i-y1)<0||(i-y1)>119||(j+x1)<0||(j+x1)>159)
      {
        lengthm=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endm=1;
      }
      else if(Pixle[i-y1][j+x1]==1)
      {
        i=i-y1;
        j=j+x1;
        BlackEndM++;
      }
      
      else
      {
        lengthm=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        if(i<40&&BlackEndM<9)
          lengthm=2*lengthm;
        endm=1;         
      }
    }
    i=currentPosition_y;
    j=currentPosition_x;
    y1=(int)(r*sin(0.75*pi-angle));
    x1=(int)(r*cos(0.75*pi-angle));
    while(!endml)                      //左中的线
    {      
      if((i-y1)<0||(i-y1)>119||(j+x1)<0||(j+x1)>159)
      {
        lengthml=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endml=1;
      }
      else if(Pixle[i-y1][j+x1]==1)
      {
        i=i-y1;
        j=j+x1;
      }
      else
      {
        lengthml=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endml=1;         
      }
    }
    i=currentPosition_y;
    j=currentPosition_x;
    y1=(int)(r*sin(pi-angle));
    x1=(int)(r*cos(pi-angle));
    while(!endl)                      //左的线
    {       
      if((i-y1)<0||(i-y1)>119||(j+x1)<0||(j+x1)>159)
      {
        lengthl=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endl=1;
      }
      else if(Pixle[i-y1][j+x1]==1)
      {
        i=i-y1;
        j=j+x1;
      }
      else
      {
        lengthl=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endl=1;         
      }
    }
    i=currentPosition_y;
    j=currentPosition_x;
    y1=(int)(r*sin(0.25*pi-angle));
    x1=(int)(r*cos(0.25*pi-angle));    
    while(!endmr)                      //右中的线
    {
      if((i-y1)<0||(i-y1)>119||(j+x1)<0||(j+x1)>159)
      {
        lengthmr=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endmr=1;
      }
      else if(Pixle[i-y1][j+x1]==1)
      {
        i=i-y1;
        j=j+x1;
      }
      else
      {
        lengthmr=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endmr=1;         
      }
    }
    i=currentPosition_y;
    j=currentPosition_x;
    y1=(int)(r*sin(-angle));
    x1=(int)(r*cos(-angle));
    while(!endr)                      //右中的线
    {
      if((i-y1)<0||(i-y1)>119||(j+x1)<0||(j+x1)>159)
      {
        lengthr=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endr=1;
      }
      else if(Pixle[i-y1][j+x1]==1)
      {
        i=i-y1;
        j=j+x1;
      }
      else
      {
        lengthr=(int)(sqrt((j-currentPosition_x)*(j-currentPosition_x)+(i-currentPosition_y)*(i-currentPosition_y)));
        endr=1;         
      }
    }
    
    shiliangle();
    nextposition_x=(int)(currentPosition_x+R*cos(0.5*pi-angle-slangle));
    nextposition_y=(int)(currentPosition_y-R*sin(0.5*pi-angle-slangle));
    angle=angle+slangle;
    lastposition_y=currentPosition_y;
    lastposition_x=currentPosition_x;
    findend();   
  }   
}

void findend(void)
{
  if(nextposition_y<30||nextposition_x>139||nextposition_x<20)
    Endpoint=1;
  else if(nextposition_y>lastposition_y)
    Endpoint=1;
  else
  {
    m=m+1;
    midline_x[m]=nextposition_x;
    midline_y[m]=nextposition_y;
    Endpoint=0;
  }
}

void shiliangle(void)
{
  
  if(roundflagl==1)
  {
    repulsivepawer=3000;//3950                      3300
    attractivepower_l=3000;//6300，6000  5800  5000  4500  4000
    attractivepower_r=3000;//2000，2100  2600  3000  3000  3000
  }
  else if(roundflagr)
  {
    repulsivepawer=3000;
    attractivepower_r=3000;
    attractivepower_l=3000;
  }
  
  if(1)
  {
    repulsivepawer=3000;
    attractivepower_l=3000;
    attractivepower_r=3000;
  }
  
  fx=(attractivepower_r*(lengthr+lengthmr*0.7071067)-attractivepower_l*(lengthl+lengthml*0.7071067));
  fy=(repulsivepawer*(lengthm+lengthmr*0.7071067+lengthml*0.7071067));
  if(fx==0&&fy!=0)                    //计算与上一点的偏角
    slangle=0;
  else if(fy==0&&fx!=0)
  {if(fx>0)
    slangle=(pi/2);
  else
    slangle=-(pi/2);
  }
  else
  {
    double A;
    A=fx/fy;
    slangle=atan(A);
  }
}


void yuanhuanshibie(void)
{
  if((Pixle[50][79]==White_Point)&&(Pixle[60][20]==Black_Point)&&(Pixle[80][20]==White_Point))
  {
    if((magmiddle>2800)||(magleft>1300)||(magright>1300)||maglleft>750||magrright>750)
    {
      if(roundflagl==0)
      {
        ll=30;
        roundflagl=1;
      }
      
    }
  }
  else if((Pixle[50][79]==White_Point)&&(Pixle[60][139]==Black_Point)&&(Pixle[80][139]==White_Point))
  {
    if((magmiddle>2800)||(magleft>1300)||(magright>1300)||maglleft>750||magrright>750)
    {
      if(roundflagr==0)
      {
        rr=30;
        roundflagr=1;
      }
    }
  }
  if((roundflagl==1)&&(roundflagr==1))//清除错误
  {
    roundflagl=0;
    roundflagr=0;
  }
  if(roundflagl==1)
  {
    if(ll>0)
      ll--;
    else if(magmiddle>2700||magleft>1250||magright>1250||maglleft>750||magrright>750)//3900
    {
      roundflagl=2;
      oll=100;
    }
  }
  if(roundflagr==1)
  {
    if(rr>0)
      rr--;
    else if(magmiddle>2700||magleft>1250||magright>1250||maglleft>750||magrright>750)//3880
    {
      roundflagr=2;
      orr=100;
    }
  }
  if(roundflagl==2)//出环更新延时
  {
    if(oll>0)
      oll--;
    else
    {
      roundflagl=0;
    }
  }
  if(roundflagr==2)
  {
    if(orr>0)
      orr--;
    else
    {
      roundflagr=0;
    }
  }
}




//提取图像的特征
//选取几列，从图像底部往上扫描
//内部调用

void GetBlackEndParam()//获取黑线截止行
{
  BrokenD=0;
  BrokenM=0;
  BrokenU=0;
  BrokenUZ=0;
  BrokenUY=0;
  Brokenend=0;
  
  if(Pixle[10][80] == Black_Point)
    broken_p=1;
  else
    broken_p=0;
  
  if(Pixle[35][80] == Black_Point)
    broken_m=1;
  else
    broken_m=0;
  
  if(Pixle[110][80] == Black_Point&&Pixle[110][73] == Black_Point&&Pixle[110][87] == Black_Point)
    broken_d=1;
  else
    broken_d=0;
  
  int j;
  
  for(j=40;j<=120;j+=2)
  {
    if(Pixle[30][j] == Black_Point)
     BrokenM++;
    if(Pixle[70][j] == Black_Point)
      BrokenD++;
    if(Pixle[110][j] == Black_Point)
      Brokenend++;
  }
  for(j=20;j<=80;j+=2)
  {
    if(Pixle[j][79] == Black_Point)
     BrokenU++;
    if(Pixle[j][20] == Black_Point)
     BrokenUZ++;
   if(Pixle[j][140] == Black_Point)
     BrokenUY++;
  }
  
  
  
  if(BrokenM>30&&BrokenD<12&3&Brokenend<11&&BrokenUZ>28&&BrokenUY>28)     
     BrokenFlag=1;
 // else if(Brokenend<3&&BrokenM>30&&BrokenD<20&&BrokenUZ>40&&BrokenUY>60)     
  //   BrokenFlag=1;
  else if(BrokenU<5&&broken_d==0)
    BrokenFlag=0;
  /*
  if(m<=5)
  BrokenFlag=1;
  else
  BrokenFlag=0;
  */
  
}






