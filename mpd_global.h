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
