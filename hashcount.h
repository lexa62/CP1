#ifndef HASHCOUNT_H
#define HASHCOUNT_H
#include "selectingaction.h"
#include "hashviewwidget.h"
#include "checkfilehashwidget.h"
#include "checkfileshasheswidget.h"

class HashCount : public QMainWindow
{
    Q_OBJECT
    public:
        HashCount();

    public slots:
        void changeWidget(QFileInfoList, int widgetType);
        void changeStatus(QString message);

    private:
        SelectingAction *selectingAction;
        HashViewWidget *hashViewWidget;
        CheckFileHashWidget *checkFileHashWidget;
        CheckFilesHashesWidget *checkFilesHashesWidget;
};

#endif // HASHCOUNT_H
