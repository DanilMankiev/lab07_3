#include"myshape.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include<QScrollBar>
#include<QDebug>
#include<QPainter>
int Circle::countC = 0;
int Rect::countR = 0;
int Triangle::countT = 0;

Shape::Shape(){}

Shape::~Shape(){}

Circle::Circle(QPoint center, double radius) : center(center), radius(radius) {
    setFlag(QGraphicsItem::ItemIsMovable);
    setZValue(0);
    countC++;
}

QRectF Circle::boundingRect() const {
    return QRectF(center.x() - radius, center.y() - radius, 2 * radius, 2 * radius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QBrush(Qt::green));
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->drawEllipse(center.x(),center.y(), radius, radius);
}

    void Circle::mousePressEvent(QGraphicsSceneMouseEvent *event){

        if (event->button() == Qt::LeftButton) {
            setZValue(countC+Rect::countR+Triangle::countT+1);
            countC++;
        }
        QGraphicsItem::mousePressEvent(event);

    }

    void Circle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
        setZValue(countC+Rect::countR+Triangle::countT+1);
        QGraphicsItem::mouseMoveEvent(event);
    }

    void Circle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {

        if (event->button() == Qt::LeftButton) {
            setZValue(countC+Rect::countR+Triangle::countT+1);
        }
        QGraphicsItem::mouseReleaseEvent(event);
    }

    Rect::Rect(int x,int y, int height,int width) : x(x),y(y), height(height),width(width) {
        setFlag(QGraphicsItem::ItemIsMovable);
        setZValue(0);
        countR++;
    }

    QRectF Rect::boundingRect() const {
        return QRectF(x, y, height,width);
    }

    void Rect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setBrush(QBrush(Qt::red));
        painter->setRenderHint(QPainter::Antialiasing, true);
        painter->drawRect(x,y, height, width);
    }
    void Rect::mousePressEvent(QGraphicsSceneMouseEvent *event){

        if (event->button() == Qt::LeftButton) {
            setZValue(Circle::countC+Rect::countR+Triangle::countT+1);
            countR++;
        }
        QGraphicsItem::mousePressEvent(event);
    }

    void Rect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
        setZValue(Circle::countC+Rect::countR+Triangle::countT+1);
        QGraphicsItem::mouseMoveEvent(event);

    }

    void Rect::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {
        if (event->button() == Qt::LeftButton) {
            setZValue(Circle::countC+Rect::countR+Triangle::countT+1);
        }
        QGraphicsItem::mouseReleaseEvent(event);
    }

    Triangle::Triangle(QPolygonF &polygon,QGraphicsItem *parent):isBeingMoved(false),QGraphicsPolygonItem(polygon, parent){
      setFlag(QGraphicsItem::ItemIsMovable);
      setZValue(0);
      setBrush(Qt::blue);
      countT++;

    }

    void Triangle::mousePressEvent(QGraphicsSceneMouseEvent *event)  {

            if (event->button() == Qt::LeftButton) {
                isBeingMoved = true;
                offset = event->pos();
                setZValue(Circle::countC+Rect::countR+Triangle::countT+1);
                countT++;
            }
            QGraphicsPolygonItem::mousePressEvent(event);
        }

        void Triangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)  {
            if (isBeingMoved) {
                QPointF newPos = event->scenePos() - offset;
                setPos(newPos);
                setZValue(Circle::countC+Rect::countR+Triangle::countT+1);
            }
            QGraphicsPolygonItem::mouseMoveEvent(event);
        }

        void Triangle::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  {
            if (event->button() == Qt::LeftButton) {
                isBeingMoved = false;
                setZValue(Circle::countC+Rect::countR+Triangle::countT+1);
            }
            QGraphicsPolygonItem::mouseReleaseEvent(event);
        }




void CollectionShapes::createNewRect(){

    Rect * tmp_rect = new Rect(50,50,100,100);
    collectionR.push_back(tmp_rect);
    scene.addItem(tmp_rect);

}
void CollectionShapes::createNewCircle(){

    Circle * tmp_circle = new Circle(QPoint(10,10),100);
    collectionC.push_back(tmp_circle);
    scene.addItem(tmp_circle);


}
void CollectionShapes::createNewTriangle(){

    QPolygonF trianglePolygon;
    trianglePolygon << QPointF(0, -50) << QPointF(50, 50) << QPointF(-50, 50);

    Triangle * tmp_triangel = new Triangle(trianglePolygon);
    collectionT.push_back(tmp_triangel);
    scene.addItem(tmp_triangel);


}
void CollectionShapes::deleteShape(){
    if(collection.isEmpty()){}
    else{
        delete collection.back();
        collection.pop_back();

    }
}
void CollectionShapes::deleteCircle(){

    if(collectionC.isEmpty()){}
    else{
        delete collectionC.back();
        collectionC.pop_back();
    }


}
void CollectionShapes::deleteRect(){

    if(collectionR.isEmpty()){}
    else{
        delete collectionR.back();
        collectionR.pop_back();
    }


}
void CollectionShapes::deleteTraingle(){

    if(collectionT.isEmpty()){}
    else{
        delete collectionT.back();
        collectionT.pop_back();
    }


}

void CollectionShapes::createButtons()
{
    collections_layout =new QHBoxLayout(this);
    addNewRect = new QPushButton("Create Rectangle");
    addNewCircle = new QPushButton("Create Clircle");
    addNewTriangel = new QPushButton("Create Triangel");
    deletOneRect = new QPushButton("Delete Rectangle");
    deleteOneCircle = new QPushButton("Delete Clircle");
    deleteOneTriangel = new QPushButton("Delete Triangel");
    collections_layout->addWidget(addNewRect,Qt::AlignTop);
    collections_layout->addWidget(addNewCircle,Qt::AlignTop);
    collections_layout->addWidget(addNewTriangel,Qt::AlignTop);
    collections_layout->addWidget(deletOneRect,Qt::AlignTop);
    collections_layout->addWidget(deleteOneCircle,Qt::AlignTop);
    collections_layout->addWidget(deleteOneTriangel,Qt::AlignTop);
}

void CollectionShapes::connectingButtons()
{
    QObject::connect(addNewRect,&QPushButton::clicked,this,&CollectionShapes::createNewRect);
    QObject::connect(addNewCircle,&QPushButton::clicked,this,&CollectionShapes::createNewCircle);
    QObject::connect(addNewTriangel,&QPushButton::clicked,this,&CollectionShapes::createNewTriangle);
    QObject::connect(deletOneRect,&QPushButton::clicked,this,&CollectionShapes::deleteRect);
    QObject::connect(deleteOneCircle,&QPushButton::clicked,this,&CollectionShapes::deleteCircle);
    QObject::connect(deleteOneTriangel,&QPushButton::clicked,this,&CollectionShapes::deleteTraingle);
}

CollectionShapes::CollectionShapes()
{

    createButtons();
    connectingButtons();  // Creating and connecting buttons using by 2 methods
}

CollectionShapes::~CollectionShapes()
{

}
