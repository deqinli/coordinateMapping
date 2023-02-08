#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setConnection();

private:
    Ui::MainWindow *ui;


private slots:
    void btn_openPath_clicked();
    void btn_calMatrix_clicked();
    void btn_validation_clicked();
};
#endif // MAINWINDOW_H
