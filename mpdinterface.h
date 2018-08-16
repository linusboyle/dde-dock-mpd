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
    int getElapsedTime();

    void changeState(MPDState state);
    void changeSong(MPDSong song);
    void changeMode(MPDPlayMode mode);

public slots:
    void toggleState();
    void nextSong();
    void previousSong();
    void toggleMode();

signals:
    void stateChanged(MPDState state);
    void songChanged(MPDSong song);
    void modeChanged(MPDPlayMode mode);

private slots:
    void onTimerElapsed();

private:
    MPDInterface(QObject *parent = nullptr);
    ~MPDInterface();

    int currentTotalTime;
    QTimer* m_updateTimer;
};

#endif // MPDINTERFACE_H
