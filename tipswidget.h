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
