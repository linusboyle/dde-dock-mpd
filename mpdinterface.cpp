#include "mpdinterface.h"
#include <libmpd/libmpd.h>
#include <QDebug>
#include <QTimer>
#include "string.h"

//all the wrap is like a hack

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
    currentTotalTime = mpd_status_get_total_song_time(_mpdobj);

    emit songChanged(song);
}

void MPDInterface::changeMode(MPDPlayMode mode){
    emit modeChanged(mode);
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

void MPDInterface::toggleMode()
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

MPDInterface::~MPDInterface(){
    if(_mpdobj){
        mpd_free(_mpdobj);
    }
}

void MPDInterface::onTimerElapsed(){
    mpd_status_update(_mpdobj);
}
