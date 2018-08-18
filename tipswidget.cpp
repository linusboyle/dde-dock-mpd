/*
 *  Author: Linus Boyle <linusboyle@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
        update();
    });

    connect(m_interface,&MPDInterface::stateChanged,this,&TipsWidget::onStateChanged);

    //startup init
    switch (m_interface->getState()) {
        case MPDState::PAUSE:
            totalTime = m_interface->getTotalTime();
            elapsedTime = m_interface->getElapsedTime();
            break;
        case MPDState::STOP:
            totalTime = 0;
            elapsedTime = 0;
            break;
        case MPDState::PLAY:
            totalTime = m_interface->getTotalTime();
            elapsedTime = m_interface->getElapsedTime();
            m_timer->start();
            break;
        default:
            break;
    }
}


void TipsWidget::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QString text = QString("%1:%2 / %3:%4").arg(elapsedTime/60,2,10,QChar('0')).arg(elapsedTime%60,2,10,QChar('0'))
                                    .arg(totalTime/60,2,10,QChar('0')).arg(totalTime%60,2,10,QChar('0'));

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

void TipsWidget::onStateChanged(MPDState state){
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
}
