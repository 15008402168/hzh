#ifndef __FINDTRACK_H__
#define __FINDTRACK_H__

/*** �궨�� ****/ 

//��������ͷ������
#define CAMERA_USE_HREF     0               //�Ƿ�ʹ�� ���ж� (0 Ϊ ��ʹ�ã�1Ϊʹ��)
#define CAMERA_COLOR        0               //����ͷ�����ɫ �� 0 Ϊ �ڰ׶�ֵ��ͼ�� ��1 Ϊ �Ҷ� ͼ�� ��2 Ϊ RGB565 ͼ��
#define CAMERA_POWER        0               //����ͷ ��Դѡ�� 0 Ϊ 3.3V ,1 Ϊ 5V

//���� ����ͷ ����
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH         //��������ͷ��DMA�ɼ�ͨ��
//#define CAMERA_W            OV7725_EAGLE_W              //��������ͷͼ����
//#define CAMERA_H            OV7725_EAGLE_H              //��������ͷͼ��߶�

#define CAMERA_SIZE         OV7725_EAGLE_SIZE           //ͼ��ռ�ÿռ��С
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM        //DMA�ɼ�����


//��������ͷ ����
#define OV7725_EAGLE_DMA_CH       DMA_CH0                               //��������ͷ��DMA�ɼ�ͨ��
#define OV7725_EAGLE_W            80                                    //��������ͷͼ����
#define OV7725_EAGLE_H            60                                    //��������ͷͼ��߶�
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //ͼ��ռ�ÿռ��С
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE )                  //DMA�ɼ�����




#define Black_Point 0
#define White_Point 1
#define RowMax	    120	  //����
#define ColumnMax	160	  //����


/*** �ⲿ������������ ****/  


extern uint8  Image_Data[120][120];//����洢����ͼ�������,CAMERA_H(59-0),CAMERA_W(0-79)
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

/*** �������� ****/    

extern void GetBlackEndParam();
extern void rengongshichang(void);
extern void yuanhuanshibie(void);
extern void gamestart_over(void);
#endif