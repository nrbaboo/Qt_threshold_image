#include "dialog.h"
#include "ui_dialog.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

inline QImage  cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;

        // only create our color table once

        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
        return image;
    }

    default:
    {
       break;
    }

    }

    return QImage();
}

inline QPixmap cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::updateImage1()
{
    QPixmap imgIn = cvMatToQPixmap(image);
    ui->label->setPixmap(imgIn);
    ui->label->setScaledContents(true);
    ui->label->show();
}
void Dialog::on_btn_loadImg_clicked()
{
    image = imread("D://1.jpg", 1);       // read an image
   /* namedWindow("My Image");            // create image window named "My Image"
    imshow("My Image", image);*/
    updateImage1();
}

void Dialog::on_btn_loadImg2_clicked()
{
    image = imread("D://1.jpg", 0);       // read an image
    updateImage1();
}

void Dialog::on_btn_binary_clicked()
{
     Mat image = cv::imread("D://1.jpg", 0);
     Mat dst;
     threshold(image, dst, ui->slider_binary->value(), 255, THRESH_BINARY);

     QPixmap imgIn = cvMatToQPixmap(dst);
     ui->label_2->setPixmap(imgIn);
     ui->label_2->setScaledContents(true);
     ui->label_2->show();
}
