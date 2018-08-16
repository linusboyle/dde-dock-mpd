#ifndef ICONLABEL_H
#define ICONLABEL_H

#include <QLabel>

class IconLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IconLabel(QWidget* parent = nullptr);
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent*) override;
};

#endif // ICONLABEL_H
