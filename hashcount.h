#ifndef HASHCOUNT_H
#define HASHCOUNT_H
#include "selectingaction.h"
#include "hashviewwidget.h"

class HashCount : public QMainWindow
{
    Q_OBJECT

    public:
        HashCount();
        ~HashCount();
    public slots:
        void changeWidget(QFileInfoList);
    private:
        SelectingAction *selectingAction;
        HashViewWidget *hashViewWidget;
};

#endif // HASHCOUNT_H
