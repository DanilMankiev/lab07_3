#ifndef MYSHAPE_H
#define MYSHAPE_H
#include <QWidget>
#include<QPoint>
#include<QVector>
#include<QPushButton>
#include<QHBoxLayout>
#include<QGraphicsItem>
#include<QPainter>
#include <QGraphicsSceneMouseEvent>
#include<QGraphicsScene>

class Shape
{
public:
    Shape();
    virtual ~Shape();
};

class Circle : public QGraphicsItem, public Shape {
    QPoint center;
    double radius;
public:
    Circle(QPoint center, double radius);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class Rect :public QGraphicsItem, public Shape {
    int x;
    int y;
    int height;
    int width;
public:
    Rect(int x,int y, int height,int width);

    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class Triangle :public QGraphicsPolygonItem,public Shape{
    QPointF point1;
    QPointF point2;
    QPointF point3;
    bool  isBeingMoved;
    QPointF offset;
public:
    Triangle(QPolygonF &polygon,QGraphicsItem *parent = nullptr);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};


class CollectionShapes: public QWidget{
    Q_OBJECT
private:
    QPushButton* addNewRect;
    QPushButton* addNewCircle;
    QPushButton* addNewTriangel;           // Buttons - user interface
    QPushButton* deletOneRect;
    QPushButton* deleteOneCircle;
    QPushButton* deleteOneTriangel;
    QVector<Shape*> collection;
    QVector<Circle*> collectionC;
    QVector<Rect*> collectionR;
    QVector<Triangle*> collectionT;
public:
    QHBoxLayout* Collections_layout;
    void deleteShape();
    void deleteCircle();
    void deleteRect();
    void deleteTraingle();
    void createButtons();
    void connectingButtons();
private slots:
     void createNewRect();
     void createNewCircle();   // Slots for creating new shape and adding to collections
     void createNewTriangle();
public:
    CollectionShapes();
    virtual ~CollectionShapes();
    QHBoxLayout* collections_layout;
    QGraphicsScene scene;

};


#endif // MYSHAPE_H
