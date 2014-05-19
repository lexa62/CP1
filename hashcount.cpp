#include "hashcount.h"
#include "hashviewwidget.h"
#include "QtGui"
#include "enumAlgorithm.h"

HashCount::HashCount()
{
    selectingAction = new SelectingAction(this);
    setCentralWidget(selectingAction);
    resize(700, 500);
    connect(selectingAction, SIGNAL(createHashReady(QFileInfoList, int)), this, SLOT(changeWidget(QFileInfoList, int)));
}

HashCount::~HashCount()
{
    qDebug()<<"~HashCount()";
    //delete hashViewWidget;
    //delete selectingAction;
}

void HashCount::changeWidget(QFileInfoList list, int widgetType)
{
    if(widgetType == WidgetType::hashView)
    {
        hashViewWidget = new HashViewWidget(selectingAction->getAlgorithmType(), list, this);
        setCentralWidget(hashViewWidget);
        hashViewWidget->addTableItems();
    }
    else if(widgetType == WidgetType::checkHashFile)
    {
        checkFileHashWidget = new CheckFileHashWidget(selectingAction->getAlgorithmType(), list, this);
        resize(400, 100);
        setCentralWidget(checkFileHashWidget);
    }
    else if(widgetType == WidgetType::checkHashFiles)
    {
        checkFilesHashesWidget = new CheckFilesHashesWidget(selectingAction->getAlgorithmType(), list, this);
        setCentralWidget(checkFilesHashesWidget);
    }
}
