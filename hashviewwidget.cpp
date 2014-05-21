#include "hashviewwidget.h"
#include <QLabel>
#include <QBoxLayout>
#include <QtGui>
#include "crc32.h"
#include "md5.h"
#include "sha1.h"
#include <QHeaderView>
#include <QPushButton>
#include <QFileDialog>
#include <QProgressDialog>
#include <QErrorMessage>
#include "enumTypes.h"
#include "algorithminterface.h"

HashViewWidget::HashViewWidget(int type, QFileInfoList filesList, QWidget *parent) :
    QWidget(parent), algorithmType(type), selectedFileList(filesList)
{
    filesTable = new QTableWidget(0, 3);
    QStringList labels;
    labels << "File Name" << "Size (KB)" << "Hash";
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    filesTable->horizontalHeader()->setStretchLastSection(true);
    filesTable->setShowGrid(false);
    filesTable->setSortingEnabled(false);

    QLabel *label = new QLabel("Result for selected files:");
    saveButton = new QPushButton("Save results");
    QVBoxLayout *vbox = new QVBoxLayout();
    vbox->addWidget(label);
    vbox->addWidget(filesTable);
    vbox->addWidget(saveButton);
    setLayout(vbox);
    connect(saveButton, SIGNAL(clicked()), SLOT(saveFilesHash()));
}

void HashViewWidget::saveFilesHash()
{
    QString fileSuffix;
    QString fileFilter;
    switch (algorithmType)
    {
        case AlgorithmType::crc32:
            fileSuffix = "*.crc32";
            break;
        case AlgorithmType::md5:
            fileSuffix = "*.md5";
            break;
        case AlgorithmType::sha1:
            fileSuffix = "*.sha1";
            break;
        default:
            break;
    }
    fileFilter = tr("hash (%1);; text files (*.txt)").arg(fileSuffix);
    QString filePath = QFileDialog::getSaveFileUrl(this, "Save File", QDir::currentPath(), fileFilter).toLocalFile();
    qDebug() << filePath;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QErrorMessage *mes = new QErrorMessage(this);
        mes->showMessage(tr("File not opened (path: %1)").arg(filePath));
        return;
    }

    QTextStream out(&file);
    int count = filesTable->rowCount();
    for(int i = 0; i < count; i++)
    {
        out << filesTable->item(i, 2)->text() << " *" + filesTable->item(i, 0)->text()<< "\n";
    }
    file.close();
}

HashViewWidget::~HashViewWidget()
{
    qDebug()<<"~HashViewWidget()";
    delete filesTable;
}

void HashViewWidget::addTableItems()
{
    QProgressDialog progress("", "Abort", 0, selectedFileList.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle("Create files hash...");
    progress.setMinimumDuration(0);

    for (int i = 0; i < selectedFileList.size(); i++)
    {
        progress.setValue(i);
        progress.setLabelText(tr("File number %1 of %2...").arg(i+1).arg(selectedFileList.count()));
        if (progress.wasCanceled())
            break;

        QTableWidgetItem *fileNameItem = new QTableWidgetItem(selectedFileList[i].fileName());
        QTableWidgetItem *sizeItem = new QTableWidgetItem();
        sizeItem->setData(Qt::DisplayRole, (selectedFileList[i].size() + 1023) / 1024);
        sizeItem->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *hashItem = new QTableWidgetItem(getHash(selectedFileList[i].absoluteFilePath()));

        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);
        filesTable->setItem(row, 1, sizeItem);
        filesTable->setItem(row, 2, hashItem);
    }
    progress.setValue(selectedFileList.count());
    filesTable->setSortingEnabled(true);
    filesTable->sortByColumn(0);
}

QString HashViewWidget::getHash(QString path)
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
