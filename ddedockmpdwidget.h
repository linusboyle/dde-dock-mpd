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
