#include "checkfilehashwidget.h"
#include "algorithminterface.h"
#include "enumTypes.h"
#include <QBoxLayout>
#include <QFileInfo>
#include "md5.h"
#include "sha1.h"
#include "crc32.h"
#include <QMessageBox>
#include <QFileDialog>

CheckFileHashWidget::CheckFileHashWidget(int Type, QFileInfoList list, QWidget *parent) :
    QWidget(parent), algorithmType(Type)
{
    QLabel *labelHash = new QLabel("File's hash:");
    QLabel *labelInput = new QLabel("Input hash for check:");
    labelIcon = new QLabel();
    compareWithFile = new QPushButton("Compare file");
    hashLine = new QLineEdit();
    inputLine = new QLineEdit();
    hashLine->setReadOnly(true);
    QVBoxLayout *vbox = new QVBoxLayout();
    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addWidget(inputLine);
    hbox->addWidget(labelIcon);
    hashLine->setText(getHash(list.at(0).absoluteFilePath()));
    vbox->setAlignment(Qt::AlignTop);
    vbox->addWidget(labelHash);
    vbox->addWidget(hashLine);
    vbox->addWidget(labelInput);
    vbox->addLayout(hbox);
    vbox->addWidget(compareWithFile);
    setLayout(vbox);
    connect(inputLine, SIGNAL(textChanged(QString)), SLOT(checkLines(QString)));
    connect(compareWithFile, SIGNAL(clicked()), SLOT(compareFileAndLine()));
}

void CheckFileHashWidget::checkLines(QString string)
{
    if(!string.compare(hashLine->text()))
        icon.load(":/monkey_ok.png");

    else
        icon.load(":/monkey_bad.png");
    labelIcon->resize(icon.size());
    labelIcon->setPixmap(icon);
}

void CheckFileHashWidget::compareFileAndLine()
{
    QString path = QFileDialog::getOpenFileUrl(this, "Open file", QDir::currentPath(), "All Files (*)").toLocalFile();
    inputLine->setText(getHash(path));
}

QString CheckFileHashWidget::getHash(QString path)
{
    QString hash;
    AlgorithmInterface *h;
    if(algorithmType == AlgorithmType::crc32)
        h = new Crc32();

    if(algorithmType == AlgorithmType::md5)
        h = new MD5();

    if(algorithmType == AlgorithmType::sha1)
        h = new Sha1();

    h->openFile(path);
    hash = h->getHashString();
    delete h;
    return hash;
}
