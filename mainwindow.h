#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtScript/qscriptvalue.h>
#include <QMainWindow>
#include <QString>
#include <string>
#include "cap.h"
#include "helpers.h"

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    std::unordered_map<const QString, const Cap* > capMap;
private:
    Ui::MainWindow *ui;


    void on_setup();

    void populateCapForm(const QString &capGroup);
      bool eventFilter(QObject *obj, QEvent *ev);
     //   static bool eFilter(QObject *obj, QMouseEvent *ev, QObject *context);
      //static bool mouseEventFilter(QObject *obj, QMouseEvent *ev, QObject *context);
      static QWidget *getWidgetForType(const Cap *cap);
      map<string, string> getCapKvps();
};

#endif // MAINWINDOW_H
