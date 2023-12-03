#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>
#include<QDebug>
#include<myshape.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget* window = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;

    CollectionShapes* win = new CollectionShapes;

    QGraphicsView view(&win->scene);



    layout->addWidget(win);
    layout->addWidget(&view);
    window->setLayout(layout);

    window->show();

    return app.exec();
}
