#ifndef HASHCOUNT_H
#define HASHCOUNT_H
#include "selectingaction.h"
#include "hashviewwidget.h"
#include "checkfilehashwidget.h"

class HashCount : public QMainWindow
{
    Q_OBJECT

    public:
        HashCount();
        ~HashCount();
    public slots:
        void changeWidget(QFileInfoList, int widgetType);
    private:
        SelectingAction *selectingAction;
        HashViewWidget *hashViewWidget;
        CheckFileHashWidget *checkFileHashWidget;
};

#endif // HASHCOUNT_H
