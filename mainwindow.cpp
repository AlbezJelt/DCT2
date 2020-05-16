#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QGridLayout>

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

}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionOpen_triggered()
{
    openBMP();
}
