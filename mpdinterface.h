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
