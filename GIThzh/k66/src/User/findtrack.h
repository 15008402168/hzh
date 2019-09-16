#ifndef __FINDTRACK_H__
#define __FINDTRACK_H__

/*** 宏定义 ****/ 

//配置摄像头的特性
#define CAMERA_USE_HREF     0               //是否使用 行中断 (0 为 不使用，1为使用)
#define CAMERA_COLOR        0               //摄像头输出颜色 ， 0 为 黑白二值化图像 ，1 为 灰度 图像 ，2 为 RGB565 图像
#define CAMERA_POWER        0               //摄像头 电源选择， 0 为 3.3V ,1 为 5V

//配置 摄像头 参数
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH         //定义摄像头的DMA采集通道
//#define CAMERA_W            OV7725_EAGLE_W              //定义摄像头图像宽度
//#define CAMERA_H            OV7725_EAGLE_H              //定义摄像头图像高度

#define CAMERA_SIZE         OV7725_EAGLE_SIZE           //图像占用空间大小
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM        //DMA采集次数


//配置摄像头 属性
#define OV7725_EAGLE_DMA_CH       DMA_CH0                               //定义摄像头的DMA采集通道
#define OV7725_EAGLE_W            80                                    //定义摄像头图像宽度
#define OV7725_EAGLE_H            60                                    //定义摄像头图像高度
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //图像占用空间大小
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE )                  //DMA采集次数




#define Black_Point 0
#define White_Point 1
#define RowMax	    120	  //行数
#define ColumnMax	160	  //列数


/*** 外部函数变量申明 ****/  


extern uint8  Image_Data[120][120];//定义存储接收图像的数组,CAMERA_H(59-0),CAMERA_W(0-79)
extern u8 Image_Data_Second[120][120];
extern u8 Pixle[LCDH][LCDW];
extern uint8 imgbuff[CAMERA_SIZE];
extern int   AllLose;
extern unsigned char StartingLineFlag;
extern int BlackEndL;//20
extern int BlackEndM;//40
extern int BlackEndR;//60
extern int BlackEndMR;//50
extern int BlackEndML;//30
extern int midline_x[120];
extern int midline_y[120];
extern int m;
extern int LastLine;
extern double slangle;
extern double angle;
extern double fx,fy;
extern int nextposition_y;
extern int nextposition_x;
extern int Endpoint;
//extern int roundpointr;
//extern int roundpointl;
extern int roundflagl;
extern int roundflagr;
extern int BrokenFlag;
extern int broken_p;
extern int broken_m;
extern int DropRow;
extern int point;
extern int game;

/*** 函数声明 ****/    

extern void GetBlackEndParam();
extern void rengongshichang(void);
extern void yuanhuanshibie(void);
extern void gamestart_over(void);
#endif