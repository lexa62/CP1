#include "hashviewwidget.h"
#include <QLabel>
#include <QBoxLayout>
#include <QtGui>
#include "crc32.h"
#include <QHeaderView>
#include <QPushButton>
#include <QFileDialog>
#include <QProgressDialog>
#include "md5.h"
#include "enumAlgorithm.h"
#include "algorithminterface.h"

HashViewWidget::HashViewWidget(int type, QFileInfoList filesList, QWidget *parent) :
    algorithmType(type), selectedFileList(filesList), QWidget(parent)
{
    filesTable = new QTableWidget(0, 3);
    QStringList labels;
    labels << "File Name" << "Size" << "Hash";
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    //filesTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    filesTable->horizontalHeader()->setStretchLastSection(true);
    filesTable->setShowGrid(false);

    QLabel *label = new QLabel("Files:");
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
    QString fileName = QFileDialog::getSaveFileName(this, "Save File",
                                                    QDir::currentPath(),
                                                    "hash (*.crc32);; text files (*.txt)");
    qDebug() << fileName;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

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
    QProgressDialog progress("Create files hash...", "Abort", 0, selectedFileList.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(200);

    for (int i = 0; i < selectedFileList.size(); ++i)
    {
        progress.setValue(i);
        progress.setLabelText(tr("file number %1 of %2...").arg(i).arg(selectedFileList.count()));
        qApp->processEvents();
        if (progress.wasCanceled())
            break;

        QTableWidgetItem *fileNameItem = new QTableWidgetItem(selectedFileList[i].fileName());
        //fileNameItem->setFlags(fileNameItem->flags() ^ Qt::ItemIsEditable);
        QTableWidgetItem *sizeItem = new QTableWidgetItem(tr("%1 KB").arg(int((selectedFileList[i].size() + 1023) / 1024)));
        sizeItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
        //sizeItem->setFlags(sizeItem->flags() ^ Qt::ItemIsEditable);

        AlgorithmInterface *h;
        if(algorithmType == AlgorithmType::crc32)
            h = new Crc32();

            //QTableWidgetItem *hashItem = new QTableWidgetItem(h.getHashString());
        if(algorithmType == AlgorithmType::md5)
            h = new MD5();

        h->openFile(selectedFileList[i].absoluteFilePath());
        QTableWidgetItem *hashItem = new QTableWidgetItem(h->getHashString());

        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);
        filesTable->setItem(row, 1, sizeItem);
        filesTable->setItem(row, 2, hashItem);
        delete h;
    }
    progress.setValue(selectedFileList.count());
    filesTable->setSortingEnabled(true);
    filesTable->sortByColumn(0);
}
