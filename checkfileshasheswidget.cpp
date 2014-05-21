#include "checkfileshasheswidget.h"
#include <QFileDialog>
#include <QHeaderView>
#include "enumTypes.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHash>
#include "algorithminterface.h"
#include "crc32.h"
#include "md5.h"
#include "sha1.h"

void CheckFilesHashesWidget::fillFileTable(QHash<QString, QString> hashContainer, QFileInfoList fileInfoList)
{
    QHash<QString, QString>::const_iterator i = hashContainer.constBegin();
    int ok = 0, notEqual = 0, notFound = 0;
    for (;i != hashContainer.constEnd(); i++)
    {
        for(int j = 0; j < fileInfoList.count(); j++)
        {
            if(!i.key().compare(fileInfoList[j].fileName()))
            {
                QString createdHash = getHash(fileInfoList[j].absoluteFilePath());
                qDebug() << "file:" << i.key() << i.value();
                qDebug() << "created hash" << createdHash;
                if(!i.value().compare(createdHash))
                {
                    insertRow(fileInfoList[j].fileName(), createdHash, "ok");
                    ok++;
                }
                else
                {
                    insertRow(fileInfoList[j].fileName(), createdHash, "not equal");
                    notEqual++;
                }
                break;
            }
            else if(j == fileInfoList.count()-1)
            {
                insertRow(i.key(), i.value(), "file not found");
                notFound++;
            }
        }
    }
    statistics->setText(tr("Errors: %1\nOk: %2 Not found: %3 Not equal: %4").arg(notFound+notEqual)
                        .arg(ok).arg(notFound).arg(notEqual));
}

CheckFilesHashesWidget::CheckFilesHashesWidget(int Type, QFileInfoList fileInfoList, QWidget *parent = 0) :
    QWidget(parent), algorithmType(Type)
{
    try{
        QLabel *label = new QLabel("Checking result:");
        statistics = new QLabel();
        QHash<QString, QString> hashContainer = getInfoFromFile();
        QVBoxLayout *vbox = new QVBoxLayout();
        filesTable = new QTableWidget(0, 3);
        vbox->addWidget(label);
        vbox->addWidget(filesTable);
        vbox->addWidget(statistics);
        setLayout(vbox);
        QStringList labels;
        labels << "File Name" << "Hash" << "Status";
        filesTable->setHorizontalHeaderLabels(labels);
        filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
        filesTable->horizontalHeader()->setStretchLastSection(true);
        filesTable->setShowGrid(false);

        fillFileTable(hashContainer, fileInfoList);
    }
    catch(...)
    {
        int n = QMessageBox::critical(0, "Error", "File not opened. Application will be closed.", QMessageBox::Close);
        if (n == QMessageBox::Close)
            qApp->quit();
    }
}

QString CheckFilesHashesWidget::getHash(QString path)
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

void CheckFilesHashesWidget::insertRow(QString fileName, QString createdHash, QString status)
{
    QTableWidgetItem *fileNameItem = new QTableWidgetItem(fileName);
    QTableWidgetItem *hashItem = new QTableWidgetItem(createdHash);
    QTableWidgetItem *statusItem = new QTableWidgetItem(status);
    int row = filesTable->rowCount();
    filesTable->insertRow(row);
    filesTable->setItem(row, 0, fileNameItem);
    filesTable->setItem(row, 1, hashItem);
    filesTable->setItem(row, 2, statusItem);
}

QHash<QString, QString> CheckFilesHashesWidget::getInfoFromFile()
{
    QString filePath = QFileDialog::getOpenFileUrl(this, "Select file with hashes", QDir::currentPath(), "Hash (*.md5 *.crc32 *.sha1)").toLocalFile();
    qDebug() << filePath;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw "";
    }

    QTextStream in(&file);
    QString text = in.readAll();
    QStringList lst;
    QHash<QString, QString> hashContainer;
    lst = text.replace("*", "").split(QRegExp("\\s+"), QString::SkipEmptyParts);
    for(int i = 1; i < lst.count(); i+=2)
    {
        hashContainer.insert(lst[i], lst[i-1]);
    }
    file.close();
    return hashContainer;
}
