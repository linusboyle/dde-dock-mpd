#include "marqueewidget.h"
#include <QPainter>
#include <QTimer>

MarqueeWidget::MarqueeWidget(QWidget *parent) :
    QWidget(parent),
    scrollPos(0),
    m_timer(new QTimer(this))
{
    setFixedWidth(120);

    connect(m_timer, &QTimer::timeout, this, &MarqueeWidget::ontimerTimeout);
    m_timer->setInterval(1000);
}

void MarqueeWidget::setText(QString text)
{
    m_timer->stop();
    m_text = text;

    scrollEnabled = (fontMetrics().width(m_text) > width());

    if(scrollEnabled){
        m_text = m_text.leftJustified(m_text.length()+5,' ');
        scrollPos = 0;
        m_timer->start();
    }
    update();
}

void MarqueeWidget::paintEvent(QPaintEvent* event)
{
    QWidget::paintEvent(event);

    QPainter p(this);
    p.setPen(Qt::white);
    //FIXME
    //4 is magic and inaccurate...
    int baseline = (height()+fontMetrics().height())/2 - 3;
    if(scrollEnabled)
    {
        //it's not smooth but it works fine
        QString leftstring = m_text.mid(scrollPos);
        p.drawText(0,baseline,leftstring);
        if(fontMetrics().width(leftstring)<width()){
            //if trailing white space appear,
            //start from the beginning
            scrollPos = -1;
        }
    } else {
        p.drawText((width()-fontMetrics().width(m_text))/2,baseline,m_text);
    }
}

void MarqueeWidget::ontimerTimeout()
{
    scrollPos++;
    if(scrollPos > m_text.length()){
        scrollPos = 0;
    }
    update();
}
