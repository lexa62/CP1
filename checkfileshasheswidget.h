#ifndef CHECKFILESHASHESWIDGET_H
#define CHECKFILESHASHESWIDGET_H
#include <QWidget>
#include <QFileInfo>
#include <QtGui>
#include <QLabel>
#include <QTableWidget>

class CheckFilesHashesWidget : public QWidget
{
    Q_OBJECT
    public:
        CheckFilesHashesWidget(int Type, QFileInfoList fileInfoList, QWidget *parent);

    signals:
        void statusChanged(QString status);
        void closeApp();

    private:
        QHash<QString, QString> getInfoFromFile();
        QString fileInfoPath;
        int algorithmType;
        QTableWidget *filesTable;
        QString getHash(QString path);
        void insertRow(QString fileName, QString createdHash, QString status);
        void fillFileTable(QHash<QString, QString> hashContainer, QFileInfoList fileInfoList);
        int openFile();
};

#endif // CHECKFILESHASHESWIDGET_H
