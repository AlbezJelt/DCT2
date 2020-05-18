#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/Eigen/Core"

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
    QImage matrixToPixmap(Eigen::MatrixXi m);

    void on_actionClose_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
