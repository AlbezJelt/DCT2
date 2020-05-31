#include "include/my_qlabel.h"
#include <iostream>

my_qlabel::my_qlabel(QWidget *parent) : QLabel(parent)
{

}

void my_qlabel::mouseMoveEvent(QMouseEvent *ev)
{
    this->x = ev->x();
    this->y = ev->y();

    emit Mouse_Pos();
}

void my_qlabel::mousePressEvent(QMouseEvent *ev)
{
    emit Mouse_Pressed();
}

void my_qlabel::mouseReleaseEvent(QMouseEvent *ev)
{
    emit Mouse_Left();
}