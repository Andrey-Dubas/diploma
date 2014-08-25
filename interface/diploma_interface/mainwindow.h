#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../FlightReviewPanel/flightpanel.h"
#include "ccontrolledtarget.h"

#include <memory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer timer;
    CControlledTarget _target;
    std::unique_ptr<FlightPanel> overviewPanel;

protected:
    void resizeEvent(QResizeEvent * event);
private:
    Ui::MainWindow *ui;
private slots:
    void dataProvide();
};

#endif // MAINWINDOW_H
