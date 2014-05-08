#include "checkfilehashwidget.h"
#include "algorithminterface.h"
#include "enumAlgorithm.h"
#include <QBoxLayout>
#include "md5.h"
#include "crc32.h"
#include <QMessageBox>
#include <QFileDialog>

CheckFileHashWidget::CheckFileHashWidget(int Type, QFileInfoList list, QWidget *parent) :
    QWidget(parent), algorithmType(Type)
{
    QLabel *label = new QLabel("File's hash:");
    QLabel *label2 = new QLabel("Input hash for check:");
    label3 = new QLabel();
    compareWithFile = new QPushButton("Compare file");
    hashLine = new QLineEdit();
    inputLine = new QLineEdit();
    hashLine->setReadOnly(true);
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(inputLine);
    hbox->addWidget(label3);
    AlgorithmInterface *h;
    if(algorithmType == AlgorithmType::md5)
        h = new MD5();
    else if(algorithmType == AlgorithmType::crc32)
        h = new Crc32;
    h->openFile(list.first().absoluteFilePath());
    hashLine->setText(h->getHashString());
    vbox->addWidget(label);
    vbox->addWidget(hashLine);
    vbox->addWidget(label2);
    vbox->addLayout(hbox);
    vbox->addWidget(compareWithFile);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
    delete h;
    connect(inputLine, SIGNAL(textChanged(QString)), SLOT(checkLines(QString)));
    connect(compareWithFile, SIGNAL(clicked()), SLOT(compareFileAndLine()));
}

void CheckFileHashWidget::checkLines(QString string)
{
    if(!string.compare(hashLine->text()))
    {
        //QMessageBox::information(this, "information", "hash is right");
        icon.load("/home/lexa62/Qt/projects/hashcount/monkey_on_32x32.png");
        label3->resize(icon.size());
        label3->setPixmap(icon);
    }
    else
    {
        icon.load("/home/lexa62/Qt/projects/hashcount/monkey_off_32x32.png");
        label3->resize(icon.size());
        label3->setPixmap(icon);
    }
}

void CheckFileHashWidget::compareFileAndLine()
{
    QString path = QFileDialog::getOpenFileUrl(this, "Open file", QDir::currentPath(), "All Files (*)").path();
    AlgorithmInterface *h;
    switch (algorithmType)
    {
    case AlgorithmType::crc32:
        h = new Crc32();
        break;
    case AlgorithmType::md5:
        h = new MD5();
        break;
    default:
        break;
    }
    h->openFile(path);
    inputLine->setText(h->getHashString());
    delete h;
}
