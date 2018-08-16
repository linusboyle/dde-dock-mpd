#include "tipswidget.h"
#include "mpdinterface.h"
#include <QPainter>
#include <QTimer>

TipsWidget::TipsWidget(QWidget *parent)
    : QFrame(parent),
      m_timer(new QTimer(this))
{
    setFixedHeight(fontMetrics().height());

    m_interface = MPDInterface::instance();

    m_timer->setInterval(1000);

    connect(m_interface,&MPDInterface::songChanged,this,&TipsWidget::onSongChanged);

    connect(m_timer,&QTimer::timeout,[this](){
        this->elapsedTime++;
        //NOTE
        //just not sure about repeat mode behaviour
        this->elapsedTime = this->elapsedTime % this->totalTime;
        update();
    });

    connect(m_interface,&MPDInterface::stateChanged,[this](MPDState state){
        switch (state) {
            case MPDState::PAUSE:
                m_timer->stop();
                break;
            case MPDState::STOP:
                m_timer->stop();
                totalTime = 0;
                elapsedTime = 0;
                break;
            case MPDState::PLAY:
                m_timer->start();
                break;
            default:
                break;
        }
        update();
    });
    m_timer->start();
}


void TipsWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QString text = QString("%1:%2 / %3:%4").arg(elapsedTime/60).arg(elapsedTime%60)
                                    .arg(totalTime/60).arg(totalTime%60);

    setFixedWidth(fontMetrics().width(text)+6);

    QPainter painter(this);

    QPen pen(Qt::white);
    painter.setPen(pen);

    QTextOption option;
    option.setAlignment(Qt::AlignCenter);
    painter.drawText(rect(), text, option);
}

void TipsWidget::onSongChanged(MPDSong _song){
    static bool firsttime = true;

    //reset
    this->totalTime = _song.totalTime;
    if(firsttime)
        this->elapsedTime = m_interface->getElapsedTime();
    else
        this->elapsedTime = 0;

    firsttime = false;
}
