#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "include/Eigen/Core"
#include <iostream>
#include "include/Compress.h"

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

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

    void on_rb_Fast_toggled(bool checked);

    void on_rb_Lee_toggled(bool checked);

    void on_rb_Naive_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QLabel *statusLabel;
    std::string strMsg;
    Compress::DCTFunction DCTFunct = Compress::Fast_Fft;

};
#endif // MAINWINDOW_H
