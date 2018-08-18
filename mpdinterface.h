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

#ifndef MPDINTERFACE_H
#define MPDINTERFACE_H

#include "mpd_global.h"
#include <QObject>

class QTimer;

class MPDInterface :public QObject
{
    Q_OBJECT
public:
    static inline MPDInterface* instance(){
        static MPDInterface* _instance = new MPDInterface();
        return _instance;
    }

    void inline free(){
        delete this;
    }

    bool connectMPD();

    QList<QString> getPlaylist();
    int getElapsedTime();
    int getTotalTime();
    MPDState getState();

    void playSong(int index);

    bool getRepeatMode();
    void switchRepeatMode();

    void changeState(MPDState state);
    void changeSong(MPDSong song);
    void changeMode(MPDPlayMode mode);
    void changePlaylist();

public slots:
    void toggleState();
    void nextSong();
    void previousSong();
    void togglePlayMode();

signals:
    void stateChanged(MPDState state);
    void songChanged(MPDSong song);
    void modeChanged(MPDPlayMode mode);
    void playlistChanged();

private slots:
    void onTimerElapsed();

private:
    MPDInterface(QObject *parent = nullptr);
    ~MPDInterface();

    QTimer* m_updateTimer;
};

#endif // MPDINTERFACE_H
