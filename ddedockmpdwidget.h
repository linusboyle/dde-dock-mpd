#ifndef DDEDOCKMPDWIDGET_H
#define DDEDOCKMPDWIDGET_H

#include <QWidget>
#include <QFontDatabase>
#include "mpd_global.h"

class ClickableLabel;
class MarqueeWidget;
class MPDInterface;
class QSettings;
class QHBoxLayout;
class QVBoxLayout;

class DDEDockMPDWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DDEDockMPDWidget(QWidget *parent = nullptr);
    ~DDEDockMPDWidget();

    bool isEnabled();
    void setEnabled(bool flag);

public slots:
    void onStateChanged(MPDState);
    void onSongChanged(MPDSong);
    void onModeChanged(MPDPlayMode);

private:
    ClickableLabel *m_previousLabel;
    ClickableLabel *m_statusLabel;
    MarqueeWidget *m_titleLabel;
    ClickableLabel *m_nextLabel;
    ClickableLabel *m_playmodeLabel;

    MPDInterface* m_interface;
    QSettings* m_setting;

    QFont font;
    void initFont();
};
#endif // DDEDOCKMPDWIDGET_H
