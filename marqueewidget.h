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

#ifndef SCROLLTEXT_H
#define SCROLLTEXT_H

#include <QWidget>
class QTimer;

class MarqueeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarqueeWidget(QWidget *parent = 0);

public slots:
    void setText(QString text);

protected:
    virtual void paintEvent(QPaintEvent *) override;

private:
    QString m_text;
    bool scrollEnabled;
    int scrollPos;
    QTimer* m_timer;

private slots:
    virtual void ontimerTimeout();
};

#endif // SCROLLTEXT_H
