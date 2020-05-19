#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "include/Eigen/Core"
#include "Compress.h"
#include "DCT2.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QBitmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->scrollArea->takeWidget();
    ui->scrollArea->setWidget(ui->img);
    ui->img->setBackgroundRole(QPalette::Base);
    ui->img->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->img->setScaledContents(true);

    ui->scrollArea_2->takeWidget();
    ui->scrollArea_2->setWidget(ui->img_2);
    ui->img_2->setBackgroundRole(QPalette::Base);
    ui->img_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->img_2->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openBMP()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Select image"), "/git/dct2", tr("Image Files (*.bmp)"));

    QPixmap pixmap = QPixmap(fname);

    ui->img->setPixmap(QPixmap(pixmap)); //Verifico caricamento immagine visualizzandola


}

void MainWindow::on_parameters_clicked()
{
    ui->writeF->setValidator(new QIntValidator());
    int F = ui->writeF->text().toInt();
    ui->writeD->setValidator(new QIntValidator());
    int d = 0;
    if (ui->writeD->text().toInt() > 0 && ui->writeD->text().toInt() < (2*F - 2) ){
        d = ui->writeD->text().toInt();
    }else {
        QMessageBox msgBox;
        msgBox.setText("Parametro non valido");
        msgBox.exec();
    }

     const QPixmap* p = ui->img->pixmap();
     Eigen::MatrixXi m = pixmapToMatrix(p);
     Eigen::MatrixXi prova = Compress::DCTCompress(m, F, d);
     QImage result = matrixToPixmap(prova);
     ui->img_2->setPixmap(QPixmap::fromImage(result));
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    openBMP();
}

Eigen::MatrixXi MainWindow::pixmapToMatrix(const QPixmap* p)
{
    QImage image = p->toImage();
    Eigen::MatrixXi matrix(image.width(), image.height()); //For matrices, the number of rows is always passed first.

    //https://forum.qt.io/topic/68790/from-matrix-to-qimage-and-qpixmap/9

    for(int i=0;i<image.width();++i){
        for(int j=0;j<image.height();++j){
            matrix(i,j)=qGray(image.pixel(i,j));
        }
     }

    return matrix;
}

QImage MainWindow::matrixToPixmap(Eigen::MatrixXi m){
    int width = m.rows();
    int height = m.cols();

    QImage tmp(width, height, QImage::Format_Grayscale8); //https://doc.qt.io/qt-5/qimage.html#Format-enum

       for (int h=0; h<height; ++h) {
           for (int w=0; w<width; ++w) {
               tmp.setPixel(w, h, qRgb(m(w,h), m(w,h), m(w,h)));
           }
       }

    return tmp;
}
