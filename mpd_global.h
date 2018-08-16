#ifndef MPD_GLOBAL_H
#define MPD_GLOBAL_H

enum MPDState {
    PLAY = 0 ,
    PAUSE = 1 ,
    STOP = 2
};

struct MPDSong {
    char* artist;
    char* title;
    char* filename;
    int totalTime;
};

enum MPDPlayMode {
    RANDOM = 0,
    LIST = 1
};

#endif // MPD_GLOBAL_H
