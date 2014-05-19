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
signals:

public slots:

private:
    QHash<QString, QString> getInfoFromFile();
    int algorithmType;
    QLabel *statistics;
    QTableWidget *filesTable;
    QString getHash(QString path);
    void insertRow(QString fileName, QString createdHash, QString status);
};

#endif // CHECKFILESHASHESWIDGET_H
