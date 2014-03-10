#ifndef QTOGRE_QOGREWIDGET_H
#define QTOGRE_QOGREWIDGET_H

#include "OGRE/Ogre.h"
#include "IOgreEventHandler.hpp"

#include <QtOpenGL/QGLWidget>

//*********************************************************************************************************************
/** Qt widget that wraps an embedded ogre render window
 *
 * This classes only responsibility is to initialise the ogre render window. The Ogre::Root object
 * to be used must be supplied by the user and once initialised the intended usage is to extract the
 * ogre render window and manipulate it directly to create the desired scene. The underlying widget
 * takes care of rendering and resizing when necessary.
 */
class QOgreWidget : public QGLWidget {
    Q_OBJECT

public: // interface
    /** Constructor
     * @param parent is required because ogre needs to set it as it's parent during initialisation
     * @throws if parent is NULL
     * @post Ogre3D renderwindow has been created
     */
    QOgreWidget(Ogre::Root *ogreRoot, IOgreEventHandler *ogreEventHandler, QWidget *parent);

    Ogre::RenderWindow *getEmbeddedOgreWindow();

protected: // interface
    /** @name Inherited from QWidget
     */
    //@{
    virtual void paintEvent(QPaintEvent *pEvent);
    virtual void resizeEvent(QResizeEvent *rEvent);
    virtual void update();
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    //@}
    

private:
    Ogre::Root *mOgreRoot;
    Ogre::RenderWindow *mOgreRenderWindow;
    IOgreEventHandler *mOgreEventHandler;

}; // class

#endif // QTOGRE_QOGREWIDGET_H
