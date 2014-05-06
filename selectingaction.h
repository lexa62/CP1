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
    ~SelectingAction();
    int getAlgorithmType();

public slots:
    void getSelectedFiles();

signals:
    void createHashReady(QFileInfoList);

private:
    int algorithmType;
    QPushButton *getHashButton;
    QPushButton *checkHashButton;
    QComboBox *comboBox;
    QTreeView *treeView;
    QFileSystemModel *fileSystemModel;
};

#endif // SELECTINGACTION_H
