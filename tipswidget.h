#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include <QFrame>
#include "mpd_global.h"

class MPDInterface;
class QTimer;

class TipsWidget : public QFrame
{
    Q_OBJECT
public:
    explicit TipsWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int elapsedTime;
    int totalTime;
    MPDInterface* m_interface;
    QTimer* m_timer;

private slots:
    void onSongChanged(MPDSong _song);
    void onStateChanged(MPDState state);
};

#endif // TIPSWIDGET_H
