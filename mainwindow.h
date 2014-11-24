#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtScript/qscriptvalue.h>
#include <QMainWindow>
#include <map>
#include "cap.h"
#include "helpers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::map<const QString, QSharedPointer<Cap> > capMap;

    void on_setup();

};

#endif // MAINWINDOW_H
