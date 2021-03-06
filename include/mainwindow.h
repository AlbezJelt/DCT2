#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "include/Eigen/Core"
#include <iostream>
#include "include/Compress.h"
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_parameters_clicked();
    void openBMP();
    Eigen::MatrixXi pixmapToMatrix(const QPixmap* p);
    QPixmap matrixToPixmap(Eigen::MatrixXi m);
    QPixmap matrixToPixmapMirror(Eigen::MatrixXi m);
    QPixmap resizeImg(const QPixmap* m, int width, int height);

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void on_rb_Fast_toggled(bool checked);

    void on_rb_Lee_toggled(bool checked);

    void on_rb_Naive_toggled(bool checked);

    void mouse_current_pos();
    void mouse_pressed();
    void mouse_left();

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    QLabel *statusLabel_2;
    std::string strMsg;
    Compress::DCTFunction DCTFunct = Compress::Fast_Fft;

    int widthT, heightT;


};
#endif // MAINWINDOW_H
