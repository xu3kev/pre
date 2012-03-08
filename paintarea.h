#ifndef PAINTAREA_H
#define PAINTAREA_H

#include<QWidget>
#include<QImage>
#include<QPainter>
#include<QPushButton>
#include<QColor>
#include<QToolBar>
#include<QColorDialog>
#include<QString>

#include<vector>

#include<iostream>

using namespace std;
void swap(int& x,int& y){
    int temp=x;
    x=y;
    y=temp;
}

//class ColorButton;


class PaintArea: public QWidget
{
public:
    PaintArea(QObject* parent=0):width(800),height(500),copy(0),check(0),copy2(0),snapI(false)
    {
        state=0;
        tmpPaint=0;
        image=new QImage(width,height,QImage::Format_RGB32);
        image->fill(-1);
        painter=new QPainter(image);
        resize(width,height);

    }
    void setState(int s){

        if(state==7&&copy){
            painter->drawImage(cpx,cpy,*copy);
            delete copy;
            copy=0;
            update();
        }
        state=s;
    }
    void setCheck(bool g){
        check=g;
    }
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void initial(QPen pen,QBrush brush){
        resize(width,height);
        painter = new QPainter(image);
        painter->setPen(pen);
        painter->setBrush(brush);
        colorPick->setPainter(painter);

    }

    void setImage(QString name){
        QPen pen=painter->pen();
        QBrush brush=painter->brush();
        delete painter;
        delete image;
        image = new QImage;
        image->load(name);
        width=image->width();
        height=image->height();
      //  painter=new QPainter(image);
      //  colorPick->setPainter(painter);
      //  resize(width,height);
        initial(pen,brush);
        snapI=0;
        snapV=0;
    }
    void saveImage(QString name){

        bool g=image->save(name);
        cerr<<g;
    }
    void resizeImage(int w,int h){
        QPen pen=painter->pen();
        QBrush brush=painter->brush();
        delete painter;
        QImage* tmp=image;
        image=new QImage(w,h,QImage::Format_RGB32);
        update();
        width=w;
        height=h;
        initial(pen,brush);
        image->fill(-1);

        //painter=new QPainter (image);
        painter->drawImage(0,0,*tmp);
        update();
        delete tmp;

        //resize(width,height);
    }
    void newImage(int w,int h){
        QBrush brush=painter->brush();
        QPen pen=painter->pen();
        delete painter;
        delete image;
        image = new QImage(w,h,QImage::Format_RGB32);
        //painter=new QPainter(image);
        width=w;
        height=h;
        initial(pen,brush);
        image->fill(-1);
        snapI=0;
        snapV=0;
    }

    void setColorPick(ColorPick* colPick){
        colorPick=colPick;
    }

    void paintEvent(QPaintEvent*){
        QPainter painter2(this);
        painter2.setPen(painter->pen());
        painter2.drawImage(0,0,*image);
        painter2.setBrush(painter->brush());

        if(state==4){


            painter2.drawRect(px,py,px2-px,py2-py);

        }
        else if(state==6){
            painter2.drawEllipse(px,py,px2-px,py2-py);
        }
        else if(state==8){
            QPainter painter3(this);
            painter3.setPen(Qt::DashDotDotLine);
            painter3.drawRect(px,py,px2-px,py2-py);
        }
        else if(state==7&&copy){
            QPainter painter3(this);
            painter3.setPen(Qt::DashDotDotLine);
            painter3.drawImage(cpx,cpy,*copy);
            painter3.drawRect(cpx,cpy,copy->width(),copy->height());
        }
        else if(state==9){
            QPainter painter3(this);
            painter3.setPen(Qt::DashDotDotLine);
            painter3.drawImage(QPoint(cpx+px2-px,cpy+py2-py),*copy);
            painter3.drawRect(cpx+px2-px,cpy+py2-py,copy->width(),copy->height());
        }
        else if(state==11){
            painter2.drawLine(px,py,px2,py2);
        }

    }
    void mousePressEvent(QMouseEvent* event){
        px=event->x();
        py=event->y();
        px2=px;
        py2=py;
        if(snapI<10){
        snap[snapI]=image->copy();
        ++snapI;
        snapV=snapI;
        }
        else{
            for(int i=0;i<9;++i)
                snap[i]=snap[i+1];
            snap[snapI-1]=image->copy();
        }
        if(state==0){
            draw(px,py);
            state=1;
        }
        else if(state==2){
            paint(px,py);
            update();
        }
        else if(state==3||state==5||state==10){
            ++state;
        }
        else if(state==7){
            if(copy){
                if(copy->valid(px-cpx,py-cpy)){
                    state+=2;
                }
                else{
                    painter->drawImage(cpx,cpy,*copy);
                    cpx=px;
                    cpy=py;
                    ++state;
                    delete copy;
                    copy=0;
                    update();
                    checkClean=false;
                }
            }
            else{
                cpx=px;
                cpy=py;
                ++state;
                checkClean=false;
            }


        }
        else if(state==12){
            colorPick->setColor(QColor(image->pixel(px,py)));
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
        else if(state==4||state==6||state==8||state==9||state==11){
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
        else if(state==8){
            if(px>px2){
              cpx=px2;
              swap(px,px2);
            }
            if(py>py2){
              cpy=py2;
              swap(py,py2);
            }

            copy=new QImage(image->copy(px,py,px2-px+1,py2-py+1) );
            //cerr<<"??";
            painter->fillRect(px,py,px2-px,py2-py,QColor(255,255,255));
            checkClean=true;
            --state;
        }
        else if(state==9){
            cpx+=px2-px;
            cpy+=py2-py;
            state=7;
        }
        else if(state==11){
            painter->drawLine(px,py,px2,py2);
            --state;
        }


    }
    QPainter* getPainter(){return painter;}
    void copyImage(){
        if(state==7&&copy){
            delete copy2;
            copy2=new QImage (*copy);
        }
    }
    void cut(){
        if(state==7&&copy){
            delete copy2;
            copy2=new QImage(*copy);
            if(!checkClean)
                painter->fillRect(cpx,cpy,copy->width(),copy->height(),QColor(255,255,255));
            copy=0;
            update();
        }
    }
    bool paste(){
        if(!copy2)
            return false;
        if(state==7&&copy){
            painter->drawImage(cpx,cpy,*copy);
        }
        cpx=0;
        cpy=0;
        delete copy;
        copy=new QImage(*copy2);
        //copy=0;
        checkClean=true;
        state=7;
        //painter->drawImage(0,0,*copy2);
        update();
        return true;
    }
    int getState(){
        return state;
    }
    void undo(){
        cerr<<snapI;
        if(snapI){
            snap[snapI]=image->copy();
            --snapI;

            //image->fill(0);
            painter->drawImage(0,0,snap[snapI]);
            //*image=snap[snapI];
            //resize(snap[snapI].width(),snap[snapI].height());
            update();
        }
    }
    void redo(){
        if(snapI<snapV){
            ++snapI;
            painter->drawImage(0,0,snap[snapI]);
            //resize(snap[snapI].width(),snap[snapI].height());
            update();
        }
    }

private:
    QImage* image;
    QPainter* painter;
    QImage* copy;
    QImage* copy2;
    ColorPick* colorPick;
    bool checkClean;
    bool check;
    int state;
    int px;
    int py;
    int tmpPaint;
    int px2;
    int py2;
    int width;
    int height;
    int cpx;
    int cpy;
    int cpx2;
    int cpy2;
    QImage snap[15];
    int snapI;
    int snapV;
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

        QPen pen=painter->pen();
        pen.setWidth(1);
        painter->save();
        painter->setPen(pen);

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
        painter->restore();
    }

};

class ColorButton:public QPushButton{
    //Q_OBJECT
public:
    ColorButton(QPainter* p,QColor col):painter(p),color(col){

    }
    void mousePressEvent(QMouseEvent *e){
        QPen tmp = painter->pen();
        tmp.setColor(color);
        painter->setPen(tmp);
    }
    QPainter* painter;
    QColor color;
};

/*
class ColorAction:public QAction{
    ColorAction(QColor qcolor):QAction(),color(qcolor){

    }

    QColor color;
};
*/



#endif // PAINTAREA_H
