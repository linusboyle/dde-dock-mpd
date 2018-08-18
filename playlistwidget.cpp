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

#include "playlistwidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include "mpdinterface.h"
#include "clickablelabel.h"

#define FIX_WIDTH 300
#define SPACING 2

PlaylistWidget::PlaylistWidget(QWidget* parent):
        DScrollArea(parent)
{
    m_widget = new QWidget(this);
    m_layout = new QVBoxLayout();
    m_interface =  MPDInterface::instance();

    m_layout->setSpacing(SPACING);

    m_widget->setLayout(m_layout);
    m_widget->setFixedWidth(FIX_WIDTH);

    m_widget->setStyleSheet("QLabel {"
                            "color: white;"
                            "}");

    setWidget(m_widget);
    setFixedWidth(FIX_WIDTH);
    setFrameStyle(QFrame::NoFrame);
    setAutoHideScrollBar(false);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color:transparent;");

    connect(m_interface,&MPDInterface::playlistChanged,this,&PlaylistWidget::onPlaylistChanged);

    this->onPlaylistChanged();
}

void PlaylistWidget::onPlaylistChanged(){
    QList<QString> playlist = m_interface->getPlaylist();

    while(QLayoutItem* item = m_layout->takeAt(0)){
        delete item->widget();
        delete item;
    }

    int height = SPACING;
    for(auto songname: playlist){
        ClickableLabel* item = new ClickableLabel(m_widget);
        item->setObjectName("PlaylistItem");
        item->setText(songname);
        item->setStyleSheet("ClickableLabel:hover {"
                            "background-color:rgba(255, 255, 255, .1);"
                            "color:mistyrose;"
                            "}");

        connect(item,&ClickableLabel::clicked,this,&PlaylistWidget::onSongSelected);

        height += item->height();
        height += SPACING;

        m_layout->addWidget(item);
    }

    m_widget->setFixedHeight(height);

    height = qMin(height,200);

    this->setFixedHeight(height);
}

void PlaylistWidget::onSongSelected(){
    ClickableLabel *song = qobject_cast<ClickableLabel*>(sender());
    int index = m_layout->indexOf(song);

    if(index < 0) {
        qDebug()<<"selected song not found,plz report this bug to github";
    } else {
        m_interface->playSong(index);
    }
}
