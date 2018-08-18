#include "clickablelabel.h"
#include <QMouseEvent>

ClickableLabel::ClickableLabel(QWidget *parent):QLabel(parent)
{
    setFixedHeight(fontMetrics().height());
}

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton ){
        emit clicked();
    }
    else{
        QLabel::mousePressEvent(event);
    }
}
