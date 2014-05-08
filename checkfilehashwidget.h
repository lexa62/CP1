#ifndef CHECKFILEHASHWIDGET_H
#define CHECKFILEHASHWIDGET_H

#include <QWidget>
#include <QFileInfo>

class CheckFileHashWidget : public QWidget
{
    Q_OBJECT
public:
    CheckFileHashWidget(int algorithmType, QFileInfoList list, QWidget *parent = 0);

signals:

public slots:

};

#endif // CHECKFILEHASHWIDGET_H
