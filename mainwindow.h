#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>
#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <windows.h>
#include <time.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    QTimer *ptmr;
    QTimer *ptmr1;
    
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mousePressEvent (QMouseEvent* pe);
    int buttonsInfo(QMouseEvent*);
    ~MainWindow();
    
private:
    void zapolnenie(QString& s, bool nach = 1);
    void my_mouse(QMouseEvent* pe);
    
    QPushButton* start;
    QPushButton* pause;
    QPushButton* clear;
    QPushButton* one_step;
    QPushButton* random;
    
    bool speed; //increase or decrease
    QPushButton* increase;
    QPushButton* decrease;
    
private slots:
    void MySlot();
    void slot_ok();
    void slot_pause();
    void slot_one_step();
    void slot_clear();
    void slot_random();
    void slot_random1();
    
    void slot_plain();
    void slot_glider();
    void slot_relay();
    void slot_gosper_gun();
    void slot_fountain();
    void slot_popower();
    
    void slot_increase();
    void slot_decrease();
};

#endif // MAINWINDOW_H
