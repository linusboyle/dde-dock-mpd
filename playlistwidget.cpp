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
    setAutoHideScrollBar(true);
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
        item->setText(songname);

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
