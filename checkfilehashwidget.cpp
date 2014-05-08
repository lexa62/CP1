#include "checkfilehashwidget.h"
#include "QLineEdit"
#include "algorithminterface.h"
#include "enumAlgorithm.h"
#include <QBoxLayout>
#include "md5.h"
#include "crc32.h"

CheckFileHashWidget::CheckFileHashWidget(int algorithmType, QFileInfoList list, QWidget *parent) :
    QWidget(parent)
{
    QLineEdit *line = new QLineEdit();
    QVBoxLayout *vbox = new QVBoxLayout();
    AlgorithmInterface *h;
    if(algorithmType == AlgorithmType::md5)
        h = new MD5();
    else if(algorithmType == AlgorithmType::crc32)
        h = new Crc32;
    h->openFile(list.first().absoluteFilePath());
    line->setText(h->getHashString());
    vbox->addWidget(line);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
    delete h;
}
