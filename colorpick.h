#ifndef COLORPICK_H
#define COLORPICK_H
#include<QPainter>
#include<QToolBar>
#include<QColorDialog>
#include<QMouseEvent>

class ColorPick:public QToolBar{
public:
    ColorPick(QWidget* parent,QPainter* ptr):color(0,0,0),painter(ptr){

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
        if(px>0&&px<40&&py>0&&py<40){
            color=QColorDialog::getColor();
            setPen(color);
            update();
            return;
        }
        if(px<0||px>30||py<50||py>290)
            return;
        py-=50;
        py/=30;

        color.setRgb(255*(py&1),255*(py&2)>>1,255*(py&4)>>2);
        setPen(color);
        update();

    }
    void setColor(QColor col){
        color=col;
        update();
        setPen(color);
    }
    void setPainter(QPainter* p){
        painter=p;
    }
    QColor getColor(){ return color; }
    QColor getColor2(){return color2; }
    QColor color;
    QColor color2;
    QPainter* painter;
    void setPen(QColor color){
        QPen tmp=painter->pen();
        tmp.setColor(color);
        painter->setPen(tmp);

    }
};

#endif // COLORPICK_H
