#ifndef PAINTAREA_H
#define PAINTAREA_H

#include<QWidget>
#include<QImage>
#include<QPainter>
#include<QPushButton>
class PaintArea: public QWidget
{
public:
    PaintArea(QObject* parent=0){
        state=0;
        tmpPaint=0;
        image=new QImage(800,500,QImage::Format_RGB32);
        image->fill(-1);
        painter=new QPainter(image);

    }
    void setState(int s){
        state=s;
    }

    void paintEvent(QPaintEvent*){
        QPainter painter(this);
        painter.drawImage(0,0,*image);

        if(state==4){
            painter.drawRect(px,py,px2-px,py2-py);
        }
        else if(state==6){
            painter.drawEllipse(px,py,px2-px,py2-py);
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

private:
    QImage* image;
    QPainter* painter;
    int state;
    int px;
    int py;
    int tmpPaint;
    int px2;
    int py2;

    void draw(int x,int y){
        painter->drawLine(x,y,px,py);
        update();
    }

    void rec(int x,int y,int xx,int yy){
        //QPainter painter(this);
        painter->drawRect(x,y,xx-x,yy-y);
        update();
    }
    void ecl(int x,int y,int xx,int yy){
        //QPainter painter(this);
        painter->drawEllipse(x,y,xx-x,yy-y);
        update();
    }
    void paint(){

    }
};


#endif // PAINTAREA_H
