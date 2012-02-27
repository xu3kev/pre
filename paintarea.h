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

        image=new QImage(800,500,QImage::Format_RGB32);
        image->fill(-1);
        painter=new QPainter(image);

    }
    void setState(int s){
        state=s;
    }

    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        painter.drawImage(0,0,*image);
    }
    void mousePressEvent(QMouseEvent* event){
        if(state==0){
            px=event->x();
            py=event->y();
            draw(px,py);
            state=1;
        }


    }
    void mouseMoveEvent(QMouseEvent* event){
        if(state==1){
            draw(event->x(),event->y());
            px=event->x();
            py=event->y();
        }
    }
    void mouseReleaseEvent(QMouseEvent *){
        if(state==1)
            state=0;
    }

private:
    QImage* image;
    QPainter* painter;
    int state;
    int px;
    int py;

    void draw(int x,int y){
        painter->drawLine(x,y,px,py);
        update();
    }
    void paint(){

    }
    void rec(){

    }
    void ecl(){

    }

};


#endif // PAINTAREA_H
