#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../FlightReviewPanel/flightpanel.h"
#include "ccontrolledtarget.h"

#include <memory>
#include "ccontrolledtarget.h"

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
    void resizeEvent(QResizeEvent * event);

    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
private:
    Ui::MainWindow *ui;

    QTimer _timer;
    float _modellingStepIntervalMilisec = 50;

    CControlledTarget _target;
    KeyDirection _curDirection;

    std::unique_ptr<FlightPanel> _overviewPanel;

    enum OnOff { ON, OFF};
    OnOff _active = OFF;
private slots:
    void startModelling();
    void dataProvide();
};

#endif // MAINWINDOW_H
