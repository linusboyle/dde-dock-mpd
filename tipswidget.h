#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include <QFrame>

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
};

#endif // TIPSWIDGET_H
