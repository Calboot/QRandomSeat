#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <cstdlib>
#define fu(x) for(int i=0;i<x;i++)
#define fd(y) for(int i=y;i>0;i--)
#define wh(b) while(b)
#define con continue
#define br break
using namespace std;

QString defaultRow1_2="8 13 16 19 21 22 24 28 31 34 37 38 40 44";
QString defaultRow3_4="1 3 6 7 10 12 14 15 17 18 20 35 36 42";
QString defaultRow5_7="2 4 5 9 11 23 25 26 27 29 30 32 33 39 41 43";
QString defaultGroupLeaders="2 4 10 16 19 20 23 24 25 26 27 28 29 30 31 32 33 34 38 39 43 44";
QString defaultSeperates="2 4\n2 5\n4 5\n1 39\n2 39\n3 39\n4 39\n5 39\n6 39\n7 39\n43 39\n44 39\n22 34\n22 20\n22 10\n22 40\n20 10\n20 40\n20 34\n10 40\n10 34\n40 34";
int seed;

void randomArray(QString s[],int len,int seed){
    default_random_engine ex;
    ex.seed(seed);

    bool b[len];
    QString t[len];
    int tmp;

    fu(len){
        b[i]=false;
        t[i]=s[i];
    }

    fu(len){
        do{
            tmp=ex()%len;
        }wh(b[tmp]);
        t[i]=s[tmp];
        b[tmp]=true;
    }

    fu(len){
        s[i]=t[i];
    }

}

bool isSeperated(QTableWidget *seat,QList<QString> qs){
    QTableWidgetItem *a,*b;
    QModelIndex indexOfA,indexOfB;
    fu(qs.length()/2-1){
        a=seat->findItems(qs.at((i+1)*2-1),Qt::MatchFlags::fromInt(0)).constFirst();
        b=seat->findItems(qs.at((i+1)*2),Qt::MatchFlags::fromInt(0)).constFirst();
        indexOfA=seat->indexFromItem(a);
        indexOfB=seat->indexFromItem(b);
        if(indexOfA.row()-indexOfB.row()<=1&&indexOfA.row()-indexOfB.row()>=-1&&indexOfA.column()-indexOfB.column()<=1&&indexOfA.column()-indexOfB.column()>=-1){
            return false;
        }
    }
    return true;
}

bool isElegible(QTableWidget *seat,string seperates){
    if(!seperates.empty()){
        QList<string> s;
        char cseperates[256];
        strcpy(cseperates,seperates.c_str());
        char *p;
        p=strtok(cseperates,"\n");
        wh(p){
            s.append(p);
            p=strtok(NULL,"\n");
        }
        QList<QString> qs;
        QList<string> l;
        fu(s.length()){
            char ct[16];
            strcpy(ct,s[i].c_str());
            string t=strtok(ct," ");
            qs.append(QString::fromStdString(t));
            t=strtok(NULL," ");
            qs.append(QString::fromStdString(t));
        }
        if(!isSeperated(seat,qs)){
            return false;
        }
    }
    return true;
}

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
    if(ui->volumn_1_2_input->text().isEmpty()){
        on_fillInDefault_1_2_clicked();
    }
    if(ui->volumn_3_4_input->text().isEmpty()){
        on_fillInDefault_3_4_clicked();
    }
    if(ui->volumn_5_7_input->text().isEmpty()){
        on_fillInDefault_5_7_clicked();
    }
    if(ui->groupLeaderListInput->text().isEmpty()){
        on_fillInDefaultGroupLeaders_clicked();
    }
    if(ui->seedInput->text().isEmpty()){
        on_generateRandomSeed_clicked();
    }
    //load config
    char crow1_2[128];
    strcpy(crow1_2,ui->volumn_1_2_input->text().toStdString().c_str());
    char crow3_4[128];
    strcpy(crow3_4,ui->volumn_3_4_input->text().toStdString().c_str());
    char crow5_7[128];
    strcpy(crow5_7,ui->volumn_5_7_input->text().toStdString().c_str());
    string sseperates=ui->seperateInput->toPlainText().toStdString();
    char cgl[128];
    strcpy(cgl,ui->groupLeaderListInput->text().toStdString().c_str());
    seed=ui->seedInput->text().toLongLong();
    e.seed(seed);
    //init arrays
    QString row1_2[14];
    QString row3_4[14];
    QString row5_7[16];
    QList<QString> gl;
    char *p;
    p=strtok(crow1_2," ");
    fu(14){
        row1_2[i]=p;
        if(p){
            p=strtok(NULL," ");
        }
    }
    p=strtok(crow3_4," ");
    fu(14){
        row3_4[i]=p;
        if(p){
            p=strtok(NULL," ");
        }
    }
    p=strtok(crow5_7," ");
    fu(16){
        row5_7[i]=p;
        if(p){
            p=strtok(NULL," ");
        }
    }
    string ts;
    p=strtok(cgl," ");
    while(p!=nullptr){
        ts=*p;
        gl.append(QString::fromStdString(ts));
        p=strtok(NULL," ");
    }

    do{
        //generate seat
        randomArray(row1_2,14,e());
        randomArray(row3_4,14,e()+1);
        randomArray(row5_7,16,e()+2);
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
    }wh(!isElegible(ui->seatTable,sseperates));
    int t;
    t=(e()+6)%7;
    ui->seatTable->item(t,0)->setText("*"+ui->seatTable->item(t,0)->text()+"*");
    t=(e()+1)%6;
    ui->seatTable->item(t,1)->setText("*"+ui->seatTable->item(t,1)->text()+"*");
    t=(e()+2)%6;
    ui->seatTable->item(t,2)->setText("*"+ui->seatTable->item(t,2)->text()+"*");
    t=(e()+3)%7;
    ui->seatTable->item(t,3)->setText("*"+ui->seatTable->item(t,3)->text()+"*");
    t=(e()+4)%6;
    ui->seatTable->item(t,4)->setText("*"+ui->seatTable->item(t,4)->text()+"*");
    t=(e()+5)%6;
    ui->seatTable->item(t,5)->setText("*"+ui->seatTable->item(t,5)->text()+"*");
    t=e()%6;
    ui->seatTable->item(t,6)->setText("*"+ui->seatTable->item(t,6)->text()+"*");

}


void MainWindow::on_exportButton_clicked()
{

}


void MainWindow::on_selectConfig_triggered()
{
    //select and read config file

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


void MainWindow::on_fillInDefaultGroupLeaders_clicked()
{
    ui->groupLeaderListInput->setText(defaultGroupLeaders);
}


void MainWindow::on_generateRandomSeed_clicked()
{
    srand(time(0));
    QString s;
    fu(15){
        s+=QChar(arc4random()%10+48);
    }
    ui->seedInput->setText(s);
}


void MainWindow::on_fillInDefaultSeperate_clicked()
{
    ui->seperateInput->setPlainText(defaultSeperates);
}


void MainWindow::on_selectConfigButton_clicked()
{
    //select and read config file
    on_selectConfig_triggered();
}


void MainWindow::on_fillDefault_triggered()
{
    on_fillInDefault_1_2_clicked();
    on_fillInDefault_3_4_clicked();
    on_fillInDefault_5_7_clicked();
    on_generateRandomSeed_clicked();
    on_fillInDefaultGroupLeaders_clicked();
    on_fillInDefaultSeperate_clicked();

}

