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

#include <include/my_qlabel.h>

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

    //Setup image area 4
    ui->scrollArea_2->takeWidget();
    ui->scrollArea_2->setWidget(ui->img_scaled);
    ui->img_scaled->setBackgroundRole(QPalette::Base);
    ui->img_scaled->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->img_scaled->setScaledContents(true);

    //Setup image area 3
    ui->scrollArea_2->takeWidget();
    ui->scrollArea_2->setWidget(ui->lblMouse);
    ui->lblMouse->setBackgroundRole(QPalette::Base);
    ui->lblMouse->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->lblMouse->setScaledContents(true);


    statusLabel = new QLabel(this);
    statusLabel->setText("Ready...");
    ui->statusbar->addWidget(statusLabel, 1);

    statusLabel_2 = new QLabel(this);
    statusLabel_2->setText("");
    ui->statusbar->addWidget(statusLabel_2, 1);


    connect(ui->lblMouse, SIGNAL(Mouse_Pos()), this, SLOT(mouse_current_pos()));
    connect(ui->lblMouse, SIGNAL(Mouse_Pressed()), this, SLOT(mouse_pressed()));
    connect(ui->lblMouse, SIGNAL(Mouse_Left()), this, SLOT(mouse_left()));
    connect(ui->img, SIGNAL(Mouse_Pos()), this, SLOT(mouse_current_pos()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openBMP()
{
    ui->lblMouse->clear();
    ui->lblMouse->repaint();

    ui->img->clear();
    ui->img->repaint();

    QString fname = QFileDialog::getOpenFileName(this, tr("Select image"), "/git/dct2", tr("Image Files (*.bmp)"));
    try {
        QImage img = QImage(fname);
        if (img.format() != QImage::Format_Grayscale8) {
            img = img.convertToFormat(QImage::Format_Grayscale8);
        }
        QPixmap pixmap = QPixmap::fromImage(img);
        ui->img->setPixmap(QPixmap(pixmap));

        strMsg = QFileInfo(fname).fileName().toStdString() + '\t' + std::to_string(pixmap.width()) + 'x' + std::to_string(pixmap.height());
        statusLabel->setText(tr(strMsg.c_str()));

    } catch (const std::exception &e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
    }
}

void MainWindow::on_parameters_clicked()
{
    statusLabel_2->setText("Processing...");
    statusLabel_2->repaint();

    const QPixmap* p = ui->img->pixmap();

    ui->img_2->clear();
    ui->img_2->repaint();

    ui->lblMouse->clear();
    ui->lblMouse->repaint();

    if (!p){
        QMessageBox msgBox;
        msgBox.setText("Load an image first!");
        msgBox.exec();
        statusLabel->setText(tr(strMsg.c_str()));
        return;
    }
        int F = ui->writeF->text().toInt();
    if (F <= 0){
        QMessageBox msgBox;
        msgBox.setText("F is not correct. It must be F > 0");
        msgBox.exec();
        statusLabel->setText(tr(strMsg.c_str()));
        return;
    }
    int d = ui->writeD->text().toInt();
    if (!(d >= 0 && d <= (2*F - 2))){
        QMessageBox msgBox;
        msgBox.setText("d is not correct. It must be d <= (2f - 2)");
        msgBox.exec();
        statusLabel->setText(tr(strMsg.c_str()));
        return;
    }
    Eigen::MatrixXi in = pixmapToMatrix(p);
    try {
        Eigen::MatrixXi out = Compress::DCTCompress(in, F, d, DCTFunct);
        QPixmap result = matrixToPixmap(out);

        QPixmap img_s = resizeImg(ui->img->pixmap(), result.width(), result.height());
        ui->img_scaled->setPixmap(img_s);

        ui->img_2->setPixmap(result);
        ui->lblMouse->setPixmap(result);
        statusLabel_2->setText("Done!");
    } catch (const std::exception &e) {
        QMessageBox msgBox;
        msgBox.setText(e.what());
        msgBox.exec();
        statusLabel->setText(tr(strMsg.c_str()));
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

QPixmap MainWindow::matrixToPixmapMirror(Eigen::MatrixXi m){
    int width = m.rows();
    int height = m.cols();

    int widthImg = ui->img->pixmap()->width();
    int heightImg = ui->img->pixmap()->height();
    QImage tmp(widthImg, heightImg, QImage::Format_Grayscale8); //https://doc.qt.io/qt-5/qimage.html#Format-enum

    for (int h=0; h<heightImg; ++h) {
        for (int w=0; w<widthImg; ++w) {
            if (w >= width) {
                int t = -w - 1 + 2 * width; // width - ((w + 1)- width);
                tmp.setPixel(w, h, tmp.pixel(t,h));
            } else if (h >= height) {
                int t = -h - 1 + 2 * height; // height - ((h + 1)- height);
                tmp.setPixel(w, h, tmp.pixel(w,t));
            } else {
                tmp.setPixel(w, h, qRgb(m(w,h), m(w,h), m(w,h)));
            }
        }
    }

    return QPixmap::fromImage(tmp);
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

QPixmap MainWindow::resizeImg(const QPixmap* m, int w, int h)
{
    QImage image = m->toImage();
    QImage tmp(w, h, QImage::Format_Grayscale8);

    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            tmp.setPixel(j, i, image.pixel(j,i));
        }
    }
    return QPixmap::fromImage(tmp);
}

void MainWindow::on_rb_Fast_toggled(bool checked)
{
    if (checked)
        DCTFunct = Compress::Fast_Fft;
}

void MainWindow::on_rb_Lee_toggled(bool checked)
{
    if (checked)
        DCTFunct = Compress::Fast_Lee;
}

void MainWindow::on_rb_Naive_toggled(bool checked)
{
    if (checked)
        DCTFunct = Compress::Naive_custom;
}

void MainWindow::mouse_current_pos()
{
    QObject* obj = sender();

    if( obj == ui->lblMouse ) {
        if(ui->lblMouse->pixmap()!=0){
            int x = ui->lblMouse->x;
            int y = ui->lblMouse->y;

            int widthBox = ui->scrollArea_2->width();
            int heightBox = ui->scrollArea_2->height();

            double pX = (100 * x) / widthBox;
            double pY = (100 * y) / heightBox;

            int widthPic = ui->lblMouse->pixmap()->width();
            int heightPic = ui->lblMouse->pixmap()->height();

            int valX = (pX * widthPic) / 100;
            int valY = (pY * heightPic) / 100;

            QImage image = ui->lblMouse->pixmap()->toImage();
            QRgb pixColor = image.pixel(valX,valY);
            statusLabel_2->setText(QString("x = %1, y = %2 \t Gray Value = %3").arg(valX).arg(valY).arg(qGray(pixColor)));
        }

    } else if ( obj == ui->img ) {
        if(ui->img->pixmap()!=0){
            int x = ui->img->x;
            int y = ui->img->y;

            int widthBox = ui->scrollArea->width();
            int heightBox = ui->scrollArea->height();

            double pX = (100 * x) / widthBox;
            double pY = (100 * y) / heightBox;

            int widthPic = ui->img->pixmap()->width();
            int heightPic = ui->img->pixmap()->height();

            int valX = (pX * widthPic) / 100;
            int valY = (pY * heightPic) / 100;

            QImage image = ui->img->pixmap()->toImage();
            QRgb pixColor = image.pixel(valX,valY);
            statusLabel_2->setText(QString("x = %1, y = %2 \t Gray Value = %3").arg(valX).arg(valY).arg(qGray(pixColor)));
        }
    }
}

void MainWindow::mouse_pressed()
{
    if(ui->lblMouse->pixmap()!=0){
        ui->scrollArea_2->setWidget(ui->lblMouse);
        const QPixmap* p = ui->img_scaled->pixmap();
        ui->lblMouse->setPixmap(*p);
    }
}

void MainWindow::mouse_left()
{
    if(ui->lblMouse->pixmap()!=0){
        const QPixmap* p = ui->img_2->pixmap();
        ui->lblMouse->setPixmap(*p);
    }
}
