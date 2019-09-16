#ifndef MAGNET_H_INCLUDED
#define MAGNET_H_INCLUDED

extern int out;
extern int kongzhi;
extern int stopstop;
extern int magleft,magmiddle,magright,magrright,maglleft,magF1,magF2,magF3;
extern float mid;
extern int circle1,circle2,break1,break2,key1,key2,circleout1,circleout2;
void magnetcontrol(int input);
int magnetanalysis1(void);
void circlescanning(void);
extern void circuitright(void);
extern void circuitleft(void);
extern float error;
extern int yyy;
extern int STEER;
#endif // MAGNET_H_INCLUDED
