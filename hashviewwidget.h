#ifndef HASHVIEWWIDGET_H
#define HASHVIEWWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QFileInfo>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>

class HashViewWidget : public QWidget
{
    Q_OBJECT
public:
    void addTableItems();
    HashViewWidget(int, QFileInfoList, QWidget *parent = 0);
    ~HashViewWidget();
public slots:
    void saveFilesHash();

private:
    int algorithmType;
    QTableWidget *filesTable;
    QFileInfoList selectedFileList;
    QPushButton *saveButton;
};

#endif // HASHVIEWWIDGET_H
