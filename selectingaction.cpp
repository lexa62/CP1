#include "selectingaction.h"
#include "crc32.h"
#include <QFileSystemModel>
#include <QtGui>
#include <QBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <enumAlgorithm.h>

SelectingAction::SelectingAction(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label1 = new QLabel("Select algorithm:");
    QLabel *label2 = new QLabel("Select files for creating/checking hash:");
    getHashButton = new QPushButton("Get hash");
    checkHashButton = new QPushButton("Check hash");
    comboBox = new QComboBox();
    QStringList stringList;
    stringList << "md5" << "crc32";
    comboBox->addItems(stringList);

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
    vbox->addWidget(label1);
    vbox->addWidget(comboBox);
    vbox->addWidget(label2);
    vbox->addWidget(treeView);
    hbox->addWidget(getHashButton);
    hbox->addWidget(checkHashButton);
    vbox->addLayout(hbox);
    vbox->setAlignment(Qt::AlignTop);
    setLayout(vbox);
    setWindowTitle("Hashcount");

    connect(getHashButton, SIGNAL(clicked()), this, SLOT(getHash()));
    connect(checkHashButton, SIGNAL(clicked()), this, SLOT(checkHash()));
}

void SelectingAction::getHash()
{
    QFileInfoList list = getSelectedFiles();
    if(!list.empty())
        emit createHashReady(getSelectedFiles(), WidgetType::hashView);
}

void SelectingAction::checkHash()
{
    QFileInfoList list = getSelectedFiles();
    if(list.count() == 1)
        emit createHashReady(getSelectedFiles(), WidgetType::checkHashFile);
}


QFileInfoList SelectingAction::getSelectedFiles()
{
    algorithmType = comboBox->currentIndex();
    QFileInfoList filesInfoList;
    if(treeView->selectionModel()->hasSelection())
    {
        QModelIndexList indexList = treeView->selectionModel()->selectedRows();
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
    }
    return filesInfoList;
}

SelectingAction::~SelectingAction()
{
    qDebug()<<"~SelectingAction()";
    //delete fileSystemModel;
}

int SelectingAction::getAlgorithmType()
{
    return algorithmType;
}
