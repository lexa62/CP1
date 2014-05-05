#ifndef SELECTINGACTION_H
#define SELECTINGACTION_H

#include <QWidget>
#include <QTreeView>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QDirModel>

class SelectingAction : public QWidget
{
    Q_OBJECT

public:
    explicit SelectingAction(QWidget *parent = 0);
    ~SelectingAction();

public slots:
    void getSelectedFiles();

signals:
    void createHashReady(QFileInfoList);

private:
    QPushButton *getHashButton;
    QPushButton *checkHashButton;
    QTreeView *treeView;
    QFileSystemModel *fileSystemModel;
};

#endif // SELECTINGACTION_H
