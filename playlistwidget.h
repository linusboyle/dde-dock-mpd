#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H


#include <dscrollarea.h>

DWIDGET_USE_NAMESPACE

class QVBoxLayout;
class MPDInterface;

class PlaylistWidget : public DScrollArea
{
    Q_OBJECT
public:
    PlaylistWidget(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_layout;
    QWidget* m_widget;
    MPDInterface* m_interface;

private slots:
    void onPlaylistChanged();
    void onSongSelected();
};

#endif // PLAYLISTWIDGET_H
