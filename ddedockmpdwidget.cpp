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

#include "ddedockmpdwidget.h"
#include "clickablelabel.h"
#include "marqueewidget.h"
#include "mpdinterface.h"

#include <QHBoxLayout>
#include <QDebug>
#include <QSettings>

DDEDockMPDWidget::DDEDockMPDWidget(QWidget *parent)
    : QWidget(parent),
      m_previousLabel(new ClickableLabel(this)),
      m_statusLabel(new ClickableLabel(this)),
      m_titleLabel(new MarqueeWidget(this)),
      m_nextLabel(new ClickableLabel(this)),
      m_playmodeLabel(new ClickableLabel(this)),
      m_setting(new QSettings("deepin","dde-dock-mpd",this))
{
    m_interface = MPDInterface::instance();
    if(!m_interface->connectMPD()){
        qDebug()<<"connection failed,plugin will be disabled";
        close();
    }

    qDebug()<<"connection established!";

    this->initFont();

    this->setStyleSheet("QLabel {"
                               "color: white;"
                               "}");

    m_statusLabel->setFont(font);
    m_previousLabel->setFont(font);
    m_nextLabel->setFont(font);
    m_playmodeLabel->setFont(font);

    m_previousLabel->setText(QChar(0xf048));
    m_nextLabel->setText(QChar(0xf051));

    //update ui
    connect(m_interface,&MPDInterface::stateChanged,this,&DDEDockMPDWidget::onStateChanged);
    connect(m_interface,&MPDInterface::songChanged,this,&DDEDockMPDWidget::onSongChanged);
    connect(m_interface,&MPDInterface::modeChanged,this,&DDEDockMPDWidget::onModeChanged);

    //update player
    connect(m_statusLabel,&ClickableLabel::clicked,m_interface,&MPDInterface::toggleState);
    connect(m_previousLabel,&ClickableLabel::clicked,m_interface,&MPDInterface::previousSong);
    connect(m_nextLabel,&ClickableLabel::clicked,m_interface,&MPDInterface::nextSong);
    connect(m_playmodeLabel,&ClickableLabel::clicked,m_interface,&MPDInterface::togglePlayMode);

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->addWidget(m_previousLabel);
    centralLayout->addWidget(m_statusLabel);
    centralLayout->addWidget(m_titleLabel);
    centralLayout->addWidget(m_nextLabel);
    centralLayout->addWidget(m_playmodeLabel);

    centralLayout->setSpacing(5);
    centralLayout->setMargin(0);

    setLayout(centralLayout);
}

bool DDEDockMPDWidget::isEnabled(){
    return m_setting->value("enabled",true).toBool();
}

void DDEDockMPDWidget::setEnabled(bool flag){
    m_setting->setValue("enabled",flag);
}

DDEDockMPDWidget::~DDEDockMPDWidget()
{
    if(m_interface){
        m_interface->free();
    }
}

void DDEDockMPDWidget::initFont(){
    int fontid = QFontDatabase::addApplicationFont(":/font/fa.otf");
    QStringList family = QFontDatabase::applicationFontFamilies(fontid);

    font.setFamily(family.at(0));
    font.setPointSize(11);
}

void DDEDockMPDWidget::onStateChanged(MPDState state){
    switch(state){
        case MPDState::PLAY:
            m_statusLabel->setText(QChar(0xf04b));
            break;
        case MPDState::PAUSE:
            m_statusLabel->setText(QChar(0xf04c));
            break;
        case MPDState::STOP:
            m_statusLabel->setText(QChar(0xf04c));
            m_titleLabel->setText("Player Stoped");
            break;
        default:
            break;
    }
}

void DDEDockMPDWidget::onSongChanged(MPDSong song){
    //"artist - title"
    //if not valid,show the filename
    if(!song.title){
        m_titleLabel->setText(QString(song.filename));
    } else if (!song.artist){
        m_titleLabel->setText(QString(song.title));
    } else {
        m_titleLabel->setText(QString("%1 - %2").arg(song.artist).arg(song.title));
    }
}

void DDEDockMPDWidget::onModeChanged(MPDPlayMode mode){
    switch (mode) {
        case MPDPlayMode::RANDOM:
            m_playmodeLabel->setText(QChar(0xf074));
            break;
        case MPDPlayMode::LIST:
            m_playmodeLabel->setText(QChar(0xf03a));
            break;
        default:
            break;
    }
}
