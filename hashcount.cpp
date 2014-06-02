#include "hashcount.h"
#include "hashviewwidget.h"
#include "QtGui"
#include "enumTypes.h"
#include <QStatusBar>

HashCount::HashCount()
{
    selectingAction = new SelectingAction(this);
    setCentralWidget(selectingAction);
    resize(700, 500);
    connect(selectingAction, SIGNAL(createHashReady(QFileInfoList, int)), this, SLOT(changeWidget(QFileInfoList, int)));
}

void HashCount::changeWidget(QFileInfoList list, int widgetType)
{
    switch(widgetType)
    {
        case WidgetType::hashView:
            hashViewWidget = new HashViewWidget(selectingAction->getAlgorithmType(), list, this);
            setCentralWidget(hashViewWidget);
            hashViewWidget->addTableItems();
            break;

        case WidgetType::checkHashFile:
            checkFileHashWidget = new CheckFileHashWidget(selectingAction->getAlgorithmType(), list, this);
            resize(400, 100);
            setCentralWidget(checkFileHashWidget);
            break;

        case WidgetType::checkHashFiles:
            checkFilesHashesWidget = new CheckFilesHashesWidget(selectingAction->getAlgorithmType(), list, this);
            setCentralWidget(checkFilesHashesWidget);
            break;

        default:
            break;
    }
}

void HashCount::changeStatus(QString message)
{
    statusBar()->showMessage(message);
}
