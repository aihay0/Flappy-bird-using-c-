#include<graphics.h>
#include<conio.h>
#include<bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define f first
#define s second
char * increment(char score[]){
    if(score[1]<'9'){
        score[1]++;
    }
    else{
        score[1]='0';
        if(score[0]<'9')
            score[0]++;
        else
            score[0]='0';
    }
    return score;
}
int distsq(int x1,int y1,int x2,int y2){
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}
int main()
{
    initwindow(1000,500,"Ball game",0,0,1);
    clearviewport();
    int ballx=500,bally=250,radius=20;
    double sp=1;
    char score[]="00";
    settextstyle(10, HORIZ_DIR, 8);
    setbkcolor(LIGHTCYAN);
    srand(time(0)^clock());
    vector<pair<int,int> > v;
    int lst=0,scr=0,beg=0;
    bool reset=0;
    while(1){
        if(reset){
            v.clear();
            score[0]='0';
            score[1]='0';
            settextstyle(10, HORIZ_DIR, 8);
            setbkcolor(LIGHTCYAN);
            srand(time(0)^clock());
            vector<pair<int,int> > v;
            lst=0,scr=0;
            beg=clock();
            sp=1;
            ballx=500,bally=250,radius=20;
            reset=0;
        }
        if((clock()-beg)/2000>lst){
            cout<<1<<endl;
            v.push_back({1100,rand()%300+70});
            lst=(clock()-beg)/2000;
        }
        if(((clock()-beg)-3500)/2000>scr){
            scr++;
            increment(score);
        }
        int ch=-1;
        if(kbhit())
            ch=getch();
        if(ch==KEY_UP)
            sp=-3;
        clearviewport();
        setfillstyle(SOLID_FILL, GREEN);
        int ground[]={0,450,1000,450,1000,500,0,500,0,450};
        fillpoly(5,ground);
        outtextxy(455,50,score);
        setfillstyle(SOLID_FILL, YELLOW);
        fillellipse(ballx,bally,radius,radius);
        bally+=sp;
        if(bally<20)
            bally=20;
        if(bally>440)
            reset=1;
        sp+=0.1;
        setfillstyle(SOLID_FILL, GREEN);
        vector<pair<int,int> > v2;
        for(int i=0;i<v.size();i++){
            int topbar[]={v[i].f-30,0,v[i].f+30,0,v[i].f+30,v[i].s-60,v[i].f-30,v[i].s-60,v[i].f-30,0},botbar[]={v[i].f-30,500,v[i].f+30,500,v[i].f+30,v[i].s+60,v[i].f-30,v[i].s+60,v[i].f-30,500};
            fillpoly(5,topbar);
            fillpoly(5,botbar);
            int mn=100000;
            mn=min(mn,distsq(ballx,bally,v[i].f-30,0));
            mn=min(mn,distsq(ballx,bally,v[i].f+30,0));
            mn=min(mn,distsq(ballx,bally,v[i].f-30,v[i].s-60));
            mn=min(mn,distsq(ballx,bally,v[i].f+30,v[i].s-60));
            mn=min(mn,distsq(ballx,bally,v[i].f-30,500));
            mn=min(mn,distsq(ballx,bally,v[i].f+30,500));
            mn=min(mn,distsq(ballx,bally,v[i].f-30,v[i].s+60));
            mn=min(mn,distsq(ballx,bally,v[i].f+30,v[i].s+60));
            if(bally<v[i].s-60||bally>v[i].s+60)
                mn=min(mn,distsq(ballx,bally,v[i].f-30,bally));
            if(mn<radius*radius-10)
                reset=1;
            v[i].f-=3;
            if(v[i].f>-100)
                v2.push_back(v[i]);
        }
        v=v2;
        if(sp>4)
            sp=4;
        swapbuffers();
        delay(10);
    }
    a:;
    getch();
    closegraph();
    return 0;
}
