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
    connect(this, SIGNAL(statusChanged(QString)), this->parent(), SLOT(changeStatus(QString)));
    hashLine->setText(getHash(list.at(0).absoluteFilePath()));
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
    if(!string.compare(hashLine->text(), Qt::CaseInsensitive))
        icon.load(":/icon_ok.png");

    else
        icon.load(":/icon_bad.png");
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
    AlgorithmInterface *algorithm;
    switch (algorithmType)
    {
        case AlgorithmType::crc32:
            algorithm = new Crc32();
            break;
        case AlgorithmType::md5:
            algorithm = new MD5();
            break;
        case AlgorithmType::sha1:
            algorithm = new Sha1();
            break;
        default:
            break;
    }
    if(algorithm->calculateFile(path) != ErrorType::noError)
        statusChanged("Error with file");
    else
        hash = algorithm->getHashString();
    delete algorithm;
    return hash;
}
