#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/Eigen/Core"
#include "include/Compress.h"
#include "include/DCT2.h"
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

    ui->writeF->setValidator(new QIntValidator(0,INT_MAX,this));
    ui->writeD->setValidator(new QIntValidator(0,INT_MAX,this));

    //Setup image area 1
    ui->scrollArea->takeWidget();
    ui->scrollArea->setWidget(ui->img);
    ui->img->setBackgroundRole(QPalette::Base);
    ui->img->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->img->setScaledContents(true);

    //Setup image area 2
    ui->scrollArea_2->takeWidget();
    ui->scrollArea_2->setWidget(ui->img_2);
    ui->img_2->setBackgroundRole(QPalette::Base);
    ui->img_2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->img_2->setScaledContents(true);

    statusLabel = new QLabel(this);
    statusLabel->setText("Ready...");
    ui->statusbar->addWidget(statusLabel, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openBMP()
{
    QString fname = QFileDialog::getOpenFileName(this, tr("Select image"), "/git/dct2", tr("Image Files (*.bmp)"));
    try {
        QImage img = QImage(fname);
        if (img.format() != QImage::Format_Grayscale8) {
            img = img.convertToFormat(QImage::Format_Grayscale8);
        }
        QPixmap pixmap = QPixmap::fromImage(img);
        ui->img->setPixmap(QPixmap(pixmap));

        std::string strMsg = QFileInfo(fname).fileName().toStdString() + '\t' + std::to_string(pixmap.width()) + 'x' + std::to_string(pixmap.height());
        statusLabel->setText(tr(strMsg.c_str()));

    } catch (const std::exception &e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void MainWindow::on_parameters_clicked()
{

    const QPixmap* p = ui->img->pixmap();
    if (!p){
        QMessageBox msgBox;
        msgBox.setText("Load an image first!");
        msgBox.exec();
        return;
    }
        int F = ui->writeF->text().toInt();
    if (F <= 0){
        QMessageBox msgBox;
        msgBox.setText("F is not correct. It must be F > 0");
        msgBox.exec();
        return;
    }
    int d = ui->writeD->text().toInt();
    if (!(d > 0 && d < (2*F - 2))){
        QMessageBox msgBox;
        msgBox.setText("d is not correct. It must be d < (2f - 2)");
        msgBox.exec();
        return;
    }
    Eigen::MatrixXi in = pixmapToMatrix(p);
    try {
        ui->statusbar->showMessage(tr("Processing..."));
        Eigen::MatrixXi out = Compress::DCTCompress(in, F, d);
        QPixmap result = matrixToPixmap(out);
        ui->img_2->setPixmap(result);
        ui->statusbar->showMessage(tr("Done!"));
    } catch (const std::exception &e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
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

    for(int i=0;i<image.width();++i){
        for(int j=0;j<image.height();++j){
            matrix(i,j)=qGray(image.pixel(i,j));
        }
    }

    return matrix;
}

QPixmap MainWindow::matrixToPixmap(Eigen::MatrixXi m){
    int width = m.rows();
    int height = m.cols();

    QImage tmp(width, height, QImage::Format_Grayscale8); //https://doc.qt.io/qt-5/qimage.html#Format-enum

    for (int h=0; h<height; ++h) {
        for (int w=0; w<width; ++w) {
            tmp.setPixel(w, h, qRgb(m(w,h), m(w,h), m(w,h)));
        }
    }

    return QPixmap::fromImage(tmp);
}
