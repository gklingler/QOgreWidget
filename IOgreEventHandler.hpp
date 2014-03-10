#ifndef QOgreEventHandler_hpp__
#define QOgreEventHandler_hpp__

#include <QMouseEvent>
#include <QResizeEvent>
#include <QPaintEvent>

class IOgreEventHandler {
public:
    virtual void ogrePaintEvent(QPaintEvent *pEvent) = 0;
    virtual void ogreResizeEvent(QResizeEvent *rEvent) = 0;
    virtual void ogreUpdate() = 0;
    virtual void ogreMousePressEvent(QMouseEvent *event) = 0;
    virtual void ogreMouseMoveEvent(QMouseEvent *event) = 0;
};

#endif // QOgreEventHandler_hpp__