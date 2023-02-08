#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setConnection();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btn_openPath_clicked()
{
    QString filePath = QFileDialog::getExistingDirectory(this,tr("open director"),"D:/");
    ui->lineEdit_matrixPath->setText(filePath);
    QString qstrSavePath = ui->lineEdit_matrixPath->text();
    QDir dir(qstrSavePath);
    if(!dir.exists() || (qstrSavePath == ""))
    {
        return;
    }
}

void MainWindow::btn_calMatrix_clicked()
{
    cv::Point2f ptf_src_1(ui->dSpinBox_src_1_x->value(),ui->dSpinBox_src_1_y->value());
    cv::Point2f ptf_src_2(ui->dSpinBox_src_2_x->value(),ui->dSpinBox_src_2_y->value());
    cv::Point2f ptf_src_3(ui->dSpinBox_src_3_x->value(),ui->dSpinBox_src_3_y->value());
    cv::Point2f ptf_src_4(ui->dSpinBox_src_4_x->value(),ui->dSpinBox_src_4_y->value());
    cv::Point2f ptf_src_5(ui->dSpinBox_src_5_x->value(),ui->dSpinBox_src_5_y->value());
    cv::Point2f ptf_src_6(ui->dSpinBox_src_6_x->value(),ui->dSpinBox_src_6_y->value());
    cv::Point2f ptf_src_7(ui->dSpinBox_src_7_x->value(),ui->dSpinBox_src_7_y->value());
    cv::Point2f ptf_src_8(ui->dSpinBox_src_8_x->value(),ui->dSpinBox_src_8_y->value());
    cv::Point2f ptf_src_9(ui->dSpinBox_src_9_x->value(),ui->dSpinBox_src_9_y->value());

    cv::Point2f ptf_dist_1(ui->dSpinBox_dist_1_x->value(),ui->dSpinBox_dist_1_y->value());
    cv::Point2f ptf_dist_2(ui->dSpinBox_dist_2_x->value(),ui->dSpinBox_dist_2_y->value());
    cv::Point2f ptf_dist_3(ui->dSpinBox_dist_3_x->value(),ui->dSpinBox_dist_3_y->value());
    cv::Point2f ptf_dist_4(ui->dSpinBox_dist_4_x->value(),ui->dSpinBox_dist_4_y->value());
    cv::Point2f ptf_dist_5(ui->dSpinBox_dist_5_x->value(),ui->dSpinBox_dist_5_y->value());
    cv::Point2f ptf_dist_6(ui->dSpinBox_dist_6_x->value(),ui->dSpinBox_dist_6_y->value());
    cv::Point2f ptf_dist_7(ui->dSpinBox_dist_7_x->value(),ui->dSpinBox_dist_7_y->value());
    cv::Point2f ptf_dist_8(ui->dSpinBox_dist_8_x->value(),ui->dSpinBox_dist_8_y->value());
    cv::Point2f ptf_dist_9(ui->dSpinBox_dist_9_x->value(),ui->dSpinBox_dist_9_y->value());

    std::vector<cv::Point2f> pointSrc;
    std::vector<cv::Point2f> pointDist;

    pointSrc.push_back(ptf_src_1);
    pointSrc.push_back(ptf_src_2);
    pointSrc.push_back(ptf_src_3);
    pointSrc.push_back(ptf_src_4);
    pointSrc.push_back(ptf_src_5);
    pointSrc.push_back(ptf_src_6);
    pointSrc.push_back(ptf_src_7);
    pointSrc.push_back(ptf_src_8);
    pointSrc.push_back(ptf_src_9);

    pointDist.push_back(ptf_dist_1);
    pointDist.push_back(ptf_dist_2);
    pointDist.push_back(ptf_dist_3);
    pointDist.push_back(ptf_dist_4);
    pointDist.push_back(ptf_dist_5);
    pointDist.push_back(ptf_dist_6);
    pointDist.push_back(ptf_dist_7);
    pointDist.push_back(ptf_dist_8);
    pointDist.push_back(ptf_dist_9);

    cv::Mat affineMatrix = cv::estimateRigidTransform(pointSrc,pointDist,true);
    QString qstr_matDir = ui->lineEdit_matrixPath->text();
    QDir dir(qstr_matDir);
    if(!dir.exists()||qstr_matDir=="")
    {
        return;
    }
    std::string str_matPath = qstr_matDir.toStdString() + "/affineMatrix.mat";
    cv::FileStorage fs_writer(str_matPath,cv::FileStorage::WRITE);
    fs_writer.write("TransformMatrix",affineMatrix);
    fs_writer.release();


}

void MainWindow::btn_validation_clicked()
{
    QString qstr_matDir = ui->lineEdit_matrixPath->text();
    QDir dir(qstr_matDir);
    if(!dir.exists()||qstr_matDir=="")
    {
        return;
    }

    std::string str_matPath = qstr_matDir.toStdString() +  "/affineMatrix.mat";
    cv::FileStorage fs_reader(str_matPath,cv::FileStorage::READ);
    cv::Mat mat_affineMatrix;
    fs_reader["TransformMatrix"] >> mat_affineMatrix;

    std::vector<cv::Point2f> vec_srcPoint,vec_distPoint;
    cv::Point2f validationPoint_src(ui->dSpinBox_validationSrc_x->value(),ui->dSpinBox_validationSrc_y->value());
    vec_srcPoint.push_back(validationPoint_src);

    cv::transform(vec_srcPoint,vec_distPoint,mat_affineMatrix);

    ui->dSpinBox_validationDist_x->setValue(vec_distPoint[0].x);
    ui->dSpinBox_validationDist_y->setValue(vec_distPoint[0].y);

}

void MainWindow::setConnection()
{
    connect(ui->btn_openPath,SIGNAL(clicked()),this,SLOT(btn_openPath_clicked()));
    connect(ui->btn_createMatrix,SIGNAL(clicked()),this,SLOT(btn_calMatrix_clicked()));
    connect(ui->btn_validationMatrix,SIGNAL(clicked()),this,SLOT(btn_validation_clicked()));

}

