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
    void fillFileTable(QHash<QString, QString> hashContainer, QFileInfoList fileInfoList);
    int openFile();
signals:
    void statusChanged(QString status);
public slots:

private:
    QHash<QString, QString> getInfoFromFile();
    QString fileInfoPath;
    int algorithmType;
    QTableWidget *filesTable;
    QString getHash(QString path);
    void insertRow(QString fileName, QString createdHash, QString status);
};

#endif // CHECKFILESHASHESWIDGET_H
