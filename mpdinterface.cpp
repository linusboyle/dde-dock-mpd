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

#include "mpdinterface.h"
#include <libmpd/libmpd.h>
#include <QDebug>
#include <QTimer>
#include "string.h"

static MpdObj* _mpdobj;

static void error_callback(MpdObj *mi,int errorid, char *msg, void *userdata)
{
     Q_UNUSED(mi);
     Q_UNUSED(userdata);
     qDebug()<<"Error: " << errorid << msg;
}

static void status_changed(MpdObj *mi,ChangedStatusType what){
    MPDInterface* interface = MPDInterface::instance();

    if(what&MPD_CST_SONGID){
       mpd_Song *song = mpd_playlist_get_current_song(mi);
       if(song){
           MPDSong _song = {song->artist,song->title,song->file,mpd_status_get_total_song_time(_mpdobj)};
           interface->changeSong(_song);
       }
    }

    if(what&MPD_CST_STATE){
        switch (mpd_player_get_state(mi)) {
            case MPD_PLAYER_PLAY:
                interface->changeState(MPDState::PLAY);
                break;
            case MPD_PLAYER_PAUSE:
                interface->changeState(MPDState::PAUSE);
                break;
            case MPD_PLAYER_STOP:
                interface->changeState(MPDState::STOP);
                break;
            default:
                break;
        }
    }

    if(what&MPD_CST_RANDOM){
        int mode = mpd_player_get_random(_mpdobj);

        if(mode) {
            interface->changeMode(MPDPlayMode::RANDOM);
        } else {
            interface->changeMode(MPDPlayMode::LIST);
        }
    }

    if(what&MPD_CST_PLAYLIST){
        interface->changePlaylist();
    }
    //TODO
    //more handle
}

MPDInterface::MPDInterface(QObject* parent)
                :QObject(parent)
{
    m_updateTimer = new QTimer(this);
}

void MPDInterface::changeState(MPDState state){
    emit stateChanged(state);
}

void MPDInterface::changeSong(MPDSong song){
    emit songChanged(song);
}

void MPDInterface::changeMode(MPDPlayMode mode){
    emit modeChanged(mode);
}

void MPDInterface::playSong(int index){
    mpd_Song* song = mpd_playlist_get_song_from_pos(_mpdobj,index);
    mpd_player_play_id(_mpdobj,song->id);
}

void MPDInterface::changePlaylist(){
    emit playlistChanged();
}

void MPDInterface::toggleState()
{
    switch (mpd_player_get_state(_mpdobj)) {
    case MPD_PLAYER_PLAY:
        mpd_player_pause(_mpdobj);
        break;
    case MPD_PLAYER_PAUSE:
    case MPD_PLAYER_STOP:
        mpd_player_play(_mpdobj);
        break;
    default:
        break;
    }
}

void MPDInterface::previousSong()
{
    mpd_player_prev(_mpdobj);
}

void MPDInterface::togglePlayMode()
{
    mpd_player_set_random(_mpdobj,!mpd_player_get_random(_mpdobj));
}

void MPDInterface::nextSong(){
    mpd_player_next(_mpdobj);
}

bool MPDInterface::connectMPD(){
    int port = 6600;
    char *hostname = getenv("MPD_HOST");
    char *_port = getenv("MPD_PORT");
    char *password = getenv("MPD_PASSWORD");
    /* set correct hostname */
    if(!hostname) {
        hostname = strdup("localhost");
    }
    if(_port){
        port = atoi(_port);
    }

    qDebug()<<"trying to connect to MPD server,hostname: "<<hostname <<" port: "<<port<<" password: "<<password;
    _mpdobj = mpd_new(hostname,port,password);
    mpd_signal_connect_error(_mpdobj,(ErrorCallback)error_callback,NULL);
    mpd_signal_connect_status_changed(_mpdobj,(StatusChangedCallback)status_changed,NULL);

    mpd_set_connection_timeout(_mpdobj,10);
    bool retval = !mpd_connect(_mpdobj);
    if(retval){
        m_updateTimer->setInterval(1000);//one second
        connect(m_updateTimer,&QTimer::timeout,this,&MPDInterface::onTimerElapsed);
        m_updateTimer->start();
    }

    return retval;
}

int MPDInterface::getElapsedTime()
{
    return mpd_status_get_elapsed_song_time(_mpdobj);
}

int MPDInterface::getTotalTime()
{
    return mpd_status_get_total_song_time(_mpdobj);
}

MPDState MPDInterface::getState()
{
    switch (mpd_player_get_state(_mpdobj)) {
        case MPD_PLAYER_PLAY:
            return MPDState::PLAY;
        case MPD_PLAYER_PAUSE:
            return MPDState::PAUSE;
        case MPD_PLAYER_STOP:
            return MPDState::STOP;
        default:
            Q_UNREACHABLE();
            break;
    }
}

MPDInterface::~MPDInterface(){
    if(_mpdobj){
        mpd_free(_mpdobj);
    }
}

void MPDInterface::onTimerElapsed(){
    mpd_status_update(_mpdobj);
}

bool MPDInterface::getRepeatMode(){
    return mpd_player_get_repeat(_mpdobj);
}

void MPDInterface::switchRepeatMode()
{
    mpd_player_set_repeat(_mpdobj,!mpd_player_get_repeat(_mpdobj));
}

QList<QString> MPDInterface::getPlaylist(){
    int listLength = mpd_playlist_get_playlist_length(_mpdobj);

    QList<QString> playlist;
    for(int i=0;i!=listLength;++i){
        mpd_Song* song = mpd_playlist_get_song_from_pos(_mpdobj,i);
        if(!song->title){
            playlist.push_back(QString("・") + QString(song->file));
        } else if (!song->artist){
            playlist.push_back(QString("・") + QString(song->title));
        } else {
            playlist.push_back(QString("・") + QString("%1 - %2").arg(song->artist).arg(song->title));
        }
    }

    return playlist;
}
