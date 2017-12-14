
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
#include <crypt_aes.h>
#include <crypt_des.h>
#include <crypt_host.h>
#define ENCR 1

#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->pushButton, SIGNAL(pressed()), this, SLOT(cipher()));
}

void MainWindow::cipher()
{
    //check for radio button
    QVector<QRadioButton*> rButtonContainer;
    rButtonContainer.push_back(ui->radioButton);
    rButtonContainer.push_back(ui->radioButton_2);
    rButtonContainer.push_back(ui->radioButton_3);

    QString str;
    for(int i=0; i <rButtonContainer.size(); ++i){
       if(rButtonContainer[i]->isChecked())
            str+=rButtonContainer[i]->text();
       }
    //std::cout<<str.toStdString()<<std::endl;
    int size_key;
    if (str=="GOST28147") size_key = 32;
    else
        if (str=="AES") size_key = 16;
        else
            if (str=="DES") size_key = 8;
            else
            {
                QMessageBox messageBox;
                messageBox.critical(0, "Error", "Please, choose method of cipher!");
                messageBox.setFixedSize(500,200);
            }

    //check for password

    QString text_key = ui->textEdit->toPlainText();
    if (text_key.size()!=size_key)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Please, enter key of needed length");
        messageBox.setFixedSize(500,200);
    }
std::cout<<text_key.toStdString()<<std::endl;

    //check for text
    QString text_for_cipher = ui->textEdit_2->toPlainText();
    if (text_for_cipher.size()==0)
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Please, enter the text!");
        messageBox.setFixedSize(500,200);
    }
    else
        if (text_for_cipher.size()<=size_key)
        {
            ui->textEdit_3->clear();
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "Please, insrease the length of text:)");
            messageBox.setFixedSize(500,200);
        }

    int encdec = ENCR;
    //crypto of text
    if (text_for_cipher.size()<=size_key)
    switch (size_key)
    {
        case 8:
        {
            crypt_DES a(text_key);
            a.myCrypt(encdec, text_for_cipher.toStdString().c_str());
            readfile();
            break;
        }
        case 16:
        {
            crypt_AES b(text_key);
            b.myCrypt(encdec, text_for_cipher.toStdString().c_str());
            readfile();
            break;
        }
        case 32:
        {
            crypt_HOST c(text_key);
            c.myCrypt(encdec, text_for_cipher.toStdString().c_str());
            readfile();
            break;
        }
    }
}

void MainWindow::readfile()
{
    QString filename="res.txt";
    QFile file(filename);
    if(file.exists())
    {
        QString line;
        ui->textEdit_3->clear();
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            while (!stream.atEnd())
            {
                line = stream.readLine();
                ui->textEdit_3->setText(ui->textEdit_3->toPlainText()+line+"\n");
            }
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    QString filename="res.txt";
    QFile file(filename);
    file.remove();
    delete ui;
}

