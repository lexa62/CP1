#include "hashviewwidget.h"
#include <QLabel>
#include <QBoxLayout>
#include <QtGui>
#include "crc32.h"
#include <QHeaderView>
#include <QPushButton>
#include <QFileDialog>
#include <QProgressDialog>

HashViewWidget::HashViewWidget(QFileInfoList filesList, QWidget *parent) :
    QWidget(parent), selectedFileList(filesList)
{
    filesTable = new QTableWidget(0, 3);
    QStringList labels;
    labels << "File Name" << "Size" << "Hash";
    filesTable->setHorizontalHeaderLabels(labels);
    filesTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    filesTable->horizontalHeader()->setStretchLastSection(true);
    filesTable->setSortingEnabled(true);
    filesTable->sortByColumn(2, Qt::AscendingOrder);
    filesTable->setShowGrid(false);

    QProgressDialog progress("Create files hash...", "Abort", 0, selectedFileList.count(), this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(3000);

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

        Crc32 h(selectedFileList[i].absoluteFilePath());
        unsigned long piy = h.gethash();
        QString piy2;
        piy2.sprintf("%08lX", piy);
        QTableWidgetItem *hashItem = new QTableWidgetItem(piy2);

        int row = filesTable->rowCount();
        filesTable->insertRow(row);
        filesTable->setItem(row, 0, fileNameItem);
        filesTable->setItem(row, 1, sizeItem);
        filesTable->setItem(row, 2, hashItem);
    }
    progress.setValue(selectedFileList.count());
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
