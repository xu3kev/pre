#ifndef PAINTAREA_H
#define PAINTAREA_H

#include<QWidget>
#include<QImage>
#include<QPainter>
#include<QPushButton>
#include<QColor>
#include<QToolBar>

#include<vector>
#include<iostream>

using namespace std;
class PaintArea: public QWidget
{
public:
    PaintArea(QObject* parent=0):width(800),height(500)
    {
        state=0;
        tmpPaint=0;
        image=new QImage(width,height,QImage::Format_RGB32);
        image->fill(-1);
        painter=new QPainter(image);

    }
    void setState(int s){
        state=s;
    }

    void paintEvent(QPaintEvent*){
        QPainter painter2(this);
        painter2.setPen(painter->pen());
        painter2.drawImage(0,0,*image);

        if(state==4){
            painter2.drawRect(px,py,px2-px,py2-py);
        }
        else if(state==6){
            painter2.drawEllipse(px,py,px2-px,py2-py);
        }

    }
    void mousePressEvent(QMouseEvent* event){
        px=event->x();
        py=event->y();
        px2=px;
        py2=py;

        if(state==0){
            draw(px,py);
            state=1;
        }
        else if(state==2){
            paint(px,py);
            update();
        }
        else if(state==3||state==5){
            ++state;
        }

    }
    void mouseMoveEvent(QMouseEvent* event){
        px2=event->x();
        py2=event->y();
        if(state==1){
            draw(event->x(),event->y());
            px=event->x();
            py=event->y();
        }
        if(state==4||state==6){
            update();
        }
    }
    void mouseReleaseEvent(QMouseEvent* event){
        if(state==1){
            state=0;
        }
        else if(state==4){
            rec(px,py,event->x(),event->y());
            --state;
        }
        else if(state==6){
            ecl(px,py,event->x(),event->y());
            --state;
        }
    }
    QPainter* getPainter(){return painter;}
private:
    QImage* image;
    QPainter* painter;
    int state;
    int px;
    int py;
    int tmpPaint;
    int px2;
    int py2;
    int width;
    int height;


    void draw(int x,int y){
        painter->drawLine(x,y,px,py);
        update();
    }

    void rec(int x,int y,int xx,int yy){
        painter->drawRect(x,y,xx-x,yy-y);
        update();
    }
    void ecl(int x,int y,int xx,int yy){
        painter->drawEllipse(x,y,xx-x,yy-y);
        update();
    }
    void paint(int x,int y){
        if(x<0||x>=width||y<0||y>=height)
            return ;

        unsigned pcol=image->pixel(x,y);
        if(painter->pen().color().rgb()==pcol)
            return;
        vector<int> xs;
        vector<int> ys;
        int i=0;
        int s=1;
        xs.push_back(x);
        ys.push_back(y);
        painter->drawPoint(x,y);
        while(i<xs.size()){
            if(xs[i]>0 && image->pixel(xs[i]-1,ys[i])==pcol ){
                xs.push_back(xs[i]-1);
                ys.push_back(ys[i]);
                painter->drawPoint(xs.back(),ys.back());
            }
            if(xs[i]<width-1 && image->pixel(xs[i]+1,ys[i])==pcol ){
                xs.push_back(xs[i]+1);
                ys.push_back(ys[i]);
                painter->drawPoint(xs.back(),ys.back());
            }
            if(ys[i]>0 && image->pixel(xs[i],ys[i]-1)==pcol ){
                xs.push_back(xs[i]);
                ys.push_back(ys[i]-1);
                painter->drawPoint(xs.back(),ys.back());
            }
            if(ys[i]<height-1 && image->pixel(xs[i],ys[i]+1)==pcol ){
                xs.push_back(xs[i]);
                ys.push_back(ys[i]+1);
                painter->drawPoint(xs.back(),ys.back());
            }
            ++i;

        }

        cout<<xs.size()<<" "<<ys.size()<<endl;

    }
};
class ColorPick:public QToolBar{
public:
    ColorPick(QPainter* ptr):color(0,0,0),painter(ptr){

    }

    void paintEvent(QPaintEvent *event){

        QPainter painter(this);

        painter.fillRect(0,0,40,40,color);

        for(int i=0;i<8;++i){
            painter.fillRect(0,50+i*30,30,30,QColor(255*(i&1),255*(i&2)>>1,255*(i&4)>>2))  ;
        }
    }
    void mousePressEvent(QMouseEvent* event){
        int px=event->x();
        int py=event->y();
        //cerr<<px;
        if(px<0||px>30||py<50||py>290)
            return;
        py-=50;
        py/=30;

        color.setRgb(255*(py&1),255*(py&2)>>1,255*(py&4)>>2);
        painter->setPen(color);
        update();

    }
    QColor color;
    QPainter* painter;
};

/*
class ColorAction:public QAction{
    ColorAction(QColor qcolor):QAction(),color(qcolor){

    }

    QColor color;
};
*/



#endif // PAINTAREA_H
