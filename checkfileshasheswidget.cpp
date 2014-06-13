#include "checkfileshasheswidget.h"
#include <QFileDialog>
#include <QHeaderView>
#include "enumTypes.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QHash>
#include <QProgressDialog>
#include "algorithminterface.h"
#include "crc32.h"
#include "md5.h"
#include "sha1.h"

CheckFilesHashesWidget::CheckFilesHashesWidget(int Type, QFileInfoList fileInfoList, QWidget *parent = 0) :
    QWidget(parent), algorithmType(Type)
{
    QLabel *label = new QLabel("Checking result:");
    connect(this, SIGNAL(closeApp()), this->parent(), SLOT(close()));
    QHash<QString, QString> hashContainer = getInfoFromFile();
    QVBoxLayout *vbox = new QVBoxLayout();
    filesTable = new QTableWidget(0, 3);
    vbox->addWidget(label);
    vbox->addWidget(filesTable);
    setLayout(vbox);
    QStringList labels;
    labels << "File Name" << "Hash" << "Status";
    filesTable->setHorizontalHeaderLabels(labels);
    //filesTable->setColumnWidth(1, 150);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    filesTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    filesTable->horizontalHeader()->setStretchLastSection(true);
    filesTable->setShowGrid(false);

    connect(this, SIGNAL(statusChanged(QString)), this->parent(), SLOT(changeStatus(QString)));
    fillFileTable(hashContainer, fileInfoList);
}

void CheckFilesHashesWidget::fillFileTable(QHash<QString, QString> hashContainer, QFileInfoList fileInfoList)
{
    QHash<QString, QString>::const_iterator i = hashContainer.constBegin();
    int ok = 0, notEqual = 0, notFound = 0, progress_num = 0;
    QProgressDialog progress("", "Abort", 0, hashContainer.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle("Create files hash...");
    progress.setMinimumDuration(0);
    for (;i != hashContainer.constEnd(); i++, progress_num++)
    {
        progress.setValue(progress_num);
        progress.setLabelText(tr("File number %1 of %2...").arg(progress_num+1).arg(hashContainer.count()));
        if (progress.wasCanceled())
            break;

        for(int j = 0; j < fileInfoList.count(); j++)
        {
            if(!i.key().compare(fileInfoList[j].fileName()))
            {
                QString createdHash = getHash(fileInfoList[j].absoluteFilePath());
                if(!i.value().compare(createdHash, Qt::CaseInsensitive))
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
    progress.setValue(hashContainer.count());
    emit statusChanged(tr("Ok: %1. Errors: %2 (Not found: %3. Not equal: %4)").arg(ok)
                       .arg(notFound+notEqual).arg(notFound).arg(notEqual));
}

QString CheckFilesHashesWidget::getHash(QString path)
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
            algorithm = new Sha1();
            break;
    }
    if(algorithm->calculateFile(path) != ErrorType::noError)
        hash = "file error";
    else
        hash = algorithm->getHashString();
    delete algorithm;
    return hash;
}

void CheckFilesHashesWidget::insertRow(QString fileName, QString createdHash, QString status)
{
    QTableWidgetItem *fileNameItem = new QTableWidgetItem(fileName);
    QTableWidgetItem *hashItem = new QTableWidgetItem(createdHash);
    QTableWidgetItem *statusItem = new QTableWidgetItem(status);
    statusItem->setTextAlignment(Qt::AlignCenter);
    int row = filesTable->rowCount();
    filesTable->insertRow(row);
    filesTable->setItem(row, 0, fileNameItem);
    filesTable->setItem(row, 1, hashItem);
    filesTable->setItem(row, 2, statusItem);
}

int CheckFilesHashesWidget::openFile()
{
    QString filePath = QFileDialog::getOpenFileUrl(this, "Select file with hashes", QDir::currentPath(),
                                           "Hash (*.md5 *.crc32 *.sha1);; All files (*)").toLocalFile();

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ErrorType::notOpened;
    fileInfoPath = filePath;
    return ErrorType::noError;
}

QHash<QString, QString> CheckFilesHashesWidget::getInfoFromFile()
{
    while(openFile() == ErrorType::notOpened)
    {
        int n = QMessageBox::warning(this, "Warning", "File not opened. Do you want to select another file",
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if (n == QMessageBox::No)
        {
            emit closeApp();
            break;
        }
    }
    QFile file(fileInfoPath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString text = in.readAll();
    QStringList lst;
    QHash<QString, QString> hashContainer;
    lst = text.split(QRegExp("\\n|\\r\\n|\\r|\\s\\*"), QString::SkipEmptyParts);
    for(int i = 1; i < lst.count(); i+=2)
    {
        hashContainer.insert(lst[i], lst[i-1]);
    }
    file.close();
    return hashContainer;
}
