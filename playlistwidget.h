#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H


#include <QScrollArea>

class QVBoxLayout;
class MPDInterface;

class PlaylistWidget : public QScrollArea
{
public:
    PlaylistWidget(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_layout;
    QWidget* m_widget;
    MPDInterface* m_interface;

private slots:
    void onPlaylistChanged();
};

#endif // PLAYLISTWIDGET_H
