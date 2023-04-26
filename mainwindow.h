#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::default_random_engine e;

private slots:
    void on_generateButton_clicked();

    void on_exportButton_clicked();

    void on_selectConfig_triggered();

    void on_exportAsHTML_triggered();

    void on_exportAsCSV_triggered();

    void on_fullScreen_triggered();

    void on_fillInDefault_1_2_clicked();

    void on_fillInDefault_3_4_clicked();

    void on_fillInDefault_5_7_clicked();

    void on_generateAction_triggered();
    
    void on_fillInDefaultGroupLeaders_clicked();

    void on_generateRandomSeed_clicked();

    void on_fillInDefaultSeperate_clicked();

    void on_selectConfigButton_clicked();

    void on_fillDefault_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
