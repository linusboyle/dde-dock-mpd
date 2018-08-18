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

#ifndef PLAYLISTWIDGET_H
#define PLAYLISTWIDGET_H


#include <dscrollarea.h>

DWIDGET_USE_NAMESPACE

class QVBoxLayout;
class MPDInterface;

class PlaylistWidget : public DScrollArea
{
    Q_OBJECT
public:
    PlaylistWidget(QWidget* parent = nullptr);

private:
    QVBoxLayout* m_layout;
    QWidget* m_widget;
    MPDInterface* m_interface;

private slots:
    void onPlaylistChanged();
    void onSongSelected();
};

#endif // PLAYLISTWIDGET_H
