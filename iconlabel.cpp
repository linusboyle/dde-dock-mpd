#include "iconlabel.h"

IconLabel::IconLabel(QWidget *parent):QLabel(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed));
}

void IconLabel::mousePressEvent(QMouseEvent *event) {
    emit clicked();

    QLabel::mousePressEvent(event);
}
