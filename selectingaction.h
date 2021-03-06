#ifndef SELECTINGACTION_H
#define SELECTINGACTION_H

#include <QWidget>
#include <QTreeView>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QFileSystemModel>
#include <QDirModel>
#include <QComboBox>

class SelectingAction : public QWidget
{
    Q_OBJECT

public:
    explicit SelectingAction(QWidget *parent = 0);
    int getAlgorithmType();

public slots:
    void getHash();
    void checkHash();

signals:
    void createHashReady(QFileInfoList, int);

private:
    int algorithmType;
    QFileInfoList getSelectedFiles();
    QPushButton *getHashButton;
    QPushButton *checkHashButton;
    QComboBox *comboBox;
    QTreeView *treeView;
    QFileSystemModel *fileSystemModel;
};

#endif // SELECTINGACTION_H
