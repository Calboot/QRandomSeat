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

    void on_fillInDefaultMasters_clicked();

    void on_generateRandomSeed_clicked();

    void on_fillInDefaultSeperate_clicked();

    void on_selectConfigButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
