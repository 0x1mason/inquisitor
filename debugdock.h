#ifndef DEBUGDOCK_H
#define DEBUGDOCK_H
#include<QCloseEvent>
#include <QDockWidget>

class DebugDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit DebugDock(QWidget *parent = 0);

signals:

public slots:

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // DEBUGDOCK_H
