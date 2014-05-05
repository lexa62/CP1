#include "hashcount.h"
#include "hashviewwidget.h"
#include "QtGui"

HashCount::HashCount()
{
    selectingAction = new SelectingAction(this);
    setCentralWidget(selectingAction);
    resize(600, 500);
    connect(selectingAction, SIGNAL(createHashReady(QFileInfoList)), this, SLOT(changeWidget(QFileInfoList)));
    //windowSelection.show();
}

HashCount::~HashCount()
{
    qDebug()<<"~HashCount()";
    //delete hashViewWidget;
    //delete selectingAction;
}

void HashCount::changeWidget(QFileInfoList list)
{
    hashViewWidget = new HashViewWidget(list, this);
    hashViewWidget->show();
    setCentralWidget(hashViewWidget);


}
