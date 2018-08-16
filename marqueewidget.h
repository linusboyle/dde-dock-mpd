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
