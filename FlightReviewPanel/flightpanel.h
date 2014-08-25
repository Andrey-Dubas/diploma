#ifndef FLIGHTPANEL_H
#define FLIGHTPANEL_H

#include <QFrame>
#include <QTimer>
#include "cflightvisualiser.h"

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

#include <QResizeEvent>

#include <memory>

class FlightPanel: public QWidget
{
    Q_OBJECT
public:
    explicit FlightPanel(QWidget *parent = 0);
    void setFrameRect(const QRect& rect);
    ~FlightPanel();
    void setTargetPosition(Point3D target);
    void setChaserPosition(Point3D chaser);
protected:
    void resizeEvent(QResizeEvent* event);

private:
    static const float controlHeight;
private:
    std::unique_ptr<QPushButton> up, down;
    std::unique_ptr<QPushButton> left, right;
    CFlightVisualiser wi;
    QTimer timer;

public slots:
    void tick();
};

#endif // FLIGHTPANEL_H
