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
        HashViewWidget(int type, QFileInfoList filesList, QWidget *parent = 0);

    public slots:
        void saveFilesHash();

    signals:
        void statusChanged(QString status);

    private:
        int ok;
        int notOpened;
        int corruptData;
        int algorithmType;
        QTableWidget *filesTable;
        QFileInfoList selectedFileList;
        QPushButton *saveButton;
        QString getHash(QString path);
        void processStatus(int status);
};

#endif // HASHVIEWWIDGET_H
