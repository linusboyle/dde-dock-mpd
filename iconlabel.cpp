#include "iconlabel.h"
#include <QMouseEvent>

IconLabel::IconLabel(QWidget *parent):QLabel(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
}

void IconLabel::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::RightButton ){
        return;
    }

    emit clicked();
}
