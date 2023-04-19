#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools.h"

QString defaultRow1_2="8 13 16 19 21 22 24 28 31 34 37 38 40 44";
QString defaultRow3_4="1 3 6 7 10 12 14 15 17 18 20 35 36 42";
QString defaultRow5_7="2 4 10 16 19 20 23 24 25 26 27 28 29 30 31 32 33 34 38 39 43 44";
QString defaultMasters="2 4 10 16 19 20 23 24 25 26 27 28 29 30 31 32 33 34 38 39 43 44";
QString defaultSeperates="2 4\n2 5\n4 5\n1 39\n2 39\n3 39\n4 39\n5 39\n6 39\n7 39\n43 39\n44 39\n22 34\n22 20\n22 10\n22 40\n20 10\n20 40 \n20 34\n10 40\n10 34\n40 34";
int seed;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generateButton_clicked()
{
    QString srow1_2=ui->volumn_1_2_input->text();
    QString srow3_4=ui->volumn_3_4_input->text();
    QString srow5_7=ui->volumn_5_7_input->text();
    seed=ui->seedInput->text().toInt();
    //init arrays
    QString row1_2[14];
    fu(14){
        row1_2[i]=ui->seatTable->item(i/7,i%7)->text();
    }
    QString row3_4[14];
    fu(14){
        row3_4[i]=ui->seatTable->item(i/7+2,i%7)->text();
    }
    QString row5_7[16];
    fu(14){
        row5_7[i]=ui->seatTable->item(i/7+4,i%7)->text();
    }
    row5_7[14]=ui->seatTable->item(6,0)->text();
    row5_7[15]=ui->seatTable->item(6,3)->text();
    //generate seat
    randomArray(row1_2,seed);
    randomArray(row3_4,seed+1);
    randomArray(row5_7,seed+2);
    //set seat table
    fu(14){
        ui->seatTable->item(i/7,i%7)->setText(row1_2[i]);
    }
    fu(14){
        ui->seatTable->item(i/7+2,i%7)->setText(row3_4[i]);
    }
    fu(14){
        ui->seatTable->item(i/7+4,i%7)->setText(row5_7[i]);
    }
    ui->seatTable->item(6,0)->setText(row5_7[14]);
    ui->seatTable->item(6,3)->setText(row5_7[15]);
}


void MainWindow::on_exportButton_clicked()
{

}


void MainWindow::on_selectConfig_triggered()
{
    //select and read config file
    on_selectConfigButton_clicked();
}


void MainWindow::on_exportAsHTML_triggered()
{
    //export as html
}


void MainWindow::on_exportAsCSV_triggered()
{
    //export as csv
}


void MainWindow::on_fullScreen_triggered()
{
    //enter full-screen mode
    showFullScreen();
}


void MainWindow::on_fillInDefault_1_2_clicked()
{
    ui->volumn_1_2_input->setText(defaultRow1_2);
}


void MainWindow::on_fillInDefault_3_4_clicked()
{
    ui->volumn_3_4_input->setText(defaultRow3_4);
}


void MainWindow::on_fillInDefault_5_7_clicked()
{
    ui->volumn_5_7_input->setText(defaultRow5_7);
}


void MainWindow::on_generateAction_triggered()
{
    on_generateButton_clicked();
}


void MainWindow::on_fillInDefaultMasters_clicked()
{
    ui->masterListInput->setText(defaultMasters);
}


void MainWindow::on_generateRandomSeed_clicked()
{
    srand(time(0));
    QString s;
    fu(10){
        s+=QChar(arc4random()%10+48);
    }
    seed=s.toInt();
    ui->seedInput->setText(s);
}


void MainWindow::on_fillInDefaultSeperate_clicked()
{
    ui->seperateInput->setText(defaultSeperates);
}


void MainWindow::on_selectConfigButton_clicked()
{
    //select and read config file

}

