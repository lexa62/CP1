#include "selectingaction.h"
#include "crc32.h"
#include <QFileSystemModel>
#include <QtGui>
#include <QBoxLayout>
#include <QHeaderView>
#include <QLabel>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstring>

#include "md5.h"


// Length of test block, number of test blocks.

#define TEST_BLOCK_LEN 1000
#define TEST_BLOCK_COUNT 1000


static void  MD5_file (char *);



// Digests a file and prints the result.

static void MD5_file (char *filename){

  ifstream file(filename);

  if (!file)
    cerr << filename <<" can't be opened" << endl;
  else {
    MD5 context(file);
    cout <<  "MD5 ("  << filename <<  ") = "  <<  context << endl;
  }
}



SelectingAction::SelectingAction(QWidget *parent) :
    QWidget(parent)
{
    MD5_file("e:\\1.txt");
    QLabel *label = new QLabel("Select files for creating/checking hash:");
    getHashButton = new QPushButton("Get hash");
    checkHashButton = new QPushButton("Check hash");

    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath("");
    treeView = new QTreeView();
    treeView->setModel(fileSystemModel);
    treeView->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    treeView->header()->setStretchLastSection(true);

    treeView->setAnimated(false);
    treeView->setIndentation(20);
    treeView->setSortingEnabled(true);
    treeView->sortByColumn(0, Qt::AscendingOrder);
    treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;
    vbox->addWidget(label);
    vbox->addWidget(treeView);
    hbox->addWidget(getHashButton);
    hbox->addWidget(checkHashButton);
    vbox->addLayout(hbox);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
    setWindowTitle("Hashcount");

    connect(getHashButton, SIGNAL(clicked()), this, SLOT(getSelectedFiles()));
}

void SelectingAction::getSelectedFiles()
{
    if(treeView->selectionModel()->hasSelection())
    {
        QModelIndexList indexList = treeView->selectionModel()->selectedRows();
        QFileInfoList filesInfoList;
        foreach (QModelIndex index, indexList)
        {
            QFileInfo fileInfo = fileSystemModel->fileInfo(index);
            if(fileInfo.isDir())
            {
                QDirIterator dirIIterator(fileInfo.absoluteFilePath(),QDirIterator::Subdirectories);
                while (dirIIterator.hasNext())
                {
                    dirIIterator.next();
                    if (QFileInfo(dirIIterator.filePath()).isFile())
                        filesInfoList.append(dirIIterator.fileInfo());
                }
            }
            else filesInfoList.append(fileInfo);
        }
        foreach (QFileInfo info, filesInfoList) {
            qDebug() << info.absoluteFilePath();
        }
        qDebug() << "Files count: " << filesInfoList.count();
        emit createHashReady(filesInfoList);
    }
}

SelectingAction::~SelectingAction()
{
    qDebug()<<"~SelectingAction()";
    //delete fileSystemModel;
}
