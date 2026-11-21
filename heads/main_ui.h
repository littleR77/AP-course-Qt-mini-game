#ifndef MAIN_UI_H
#define MAIN_UI_H

#include <QGraphicsView>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QMovie>
#include <QTimer>
#include<QPushButton>
#include "normal_mode.h"
#include <QApplication>
class main_ui : public QGraphicsView
{

    Q_OBJECT
public slots:
    void Hstartsignal();
public:
    main_ui();
signals:
    void normalsignal();
private slots:
    void normal_modebuttonclicked();
private:
    QPushButton* normalModeButton;
    Normal_mode* normalgame;
};






#endif // MAIN_UI_H
