#ifndef CHECKFILEHASHWIDGET_H
#define CHECKFILEHASHWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include "QLineEdit"
#include <QPushButton>
#include <QPixmap>
#include <QLabel>

class CheckFileHashWidget : public QWidget
{
    Q_OBJECT

    public:
        CheckFileHashWidget(int Type, QFileInfoList list, QWidget *parent = 0);

    signals:
        void statusChanged(QString status);

    public slots:
        void checkLines(QString string);
        void compareFileAndLine();

    private:
        int algorithmType;
        QLineEdit *hashLine;
        QLineEdit *inputLine;
        QPushButton *compareWithFile;
        QPixmap icon;
        QLabel *labelIcon;
        QString getHash(QString path);
};

#endif // CHECKFILEHASHWIDGET_H
