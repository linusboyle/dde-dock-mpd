#ifndef DDEDOCKMPDWIDGET_H
#define DDEDOCKMPDWIDGET_H

#include <QWidget>
#include <QFontDatabase>
#include "mpd_global.h"

class IconLabel;
class MarqueeWidget;
class MPDInterface;

class DDEDockMPDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DDEDockMPDWidget(QWidget *parent = nullptr);
    ~DDEDockMPDWidget();

public slots:
    void onStateChanged(MPDState);
    void onSongChanged(MPDSong);
    void onModeChanged(MPDPlayMode);

private:
    IconLabel *m_previousLabel;
    IconLabel *m_statusLabel;
    MarqueeWidget *m_titleLabel;
    IconLabel *m_nextLabel;
    IconLabel *m_playmodeLabel;

    MPDInterface* m_interface;

    QFont font;
    void initFont();

};
#endif // DDEDOCKMPDWIDGET_H
