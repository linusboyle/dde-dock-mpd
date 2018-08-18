#include "playlistwidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include "mpdinterface.h"
#include "clickablelabel.h"

#define FIX_WIDTH 300
#define SPACING 2

PlaylistWidget::PlaylistWidget(QWidget* parent):
        QScrollArea(parent)
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
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

    int height = 0;
    for(auto songname: playlist){
        ClickableLabel* item = new ClickableLabel(m_widget);
        item->setText(songname);

        //TODO
        //handle the click

        m_layout->addWidget(item);
        height += item->height();
        height += SPACING*2;
    }

    m_widget->setFixedHeight(height);

    height = qMin(height,200);

    this->setFixedHeight(height);
}
