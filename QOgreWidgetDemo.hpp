#ifndef QOgreWidgetDemo_h__
#define QOgreWidgetDemo_h__

#include <OGRE/Ogre.h>

#include <QMainWindow>
#include <QCameraMan.h>

#include "IOgreEventHandler.hpp"

class QOgreWidget;

class QOgreWidgetDemo : public QMainWindow, public IOgreEventHandler {
    Q_OBJECT

public: // interface
    QOgreWidgetDemo();
    ~QOgreWidgetDemo();

    void setupRenderSystem();
    void setupResources();
    void createQtWidgets();
    void createScene();

private:
    QOgreWidget *mOgreWidget;

    Ogre::Root *mOgreRoot;
    Ogre::RenderWindow *mRenderWindow;
    Ogre::Viewport *mOgreViewport;
    Ogre::RenderSystem *mRenderSystem;
    Ogre::SceneManager *mSceneManager;
    Ogre::Camera *mCamera;
    
    OgreBites::QCameraMan* mCameraMan;
    
    int mMouseMoveXOld;
    int mMouseMoveYOld;
    
    // button event handler
private slots:
    void onZoomIn();
    void onZoomOut();
    
    // implements IQOgreEventHandler
    virtual void ogrePaintEvent(QPaintEvent *pEvent) {}
    virtual void ogreResizeEvent(QResizeEvent *rEvent) {}
    virtual void ogreUpdate() {}
    virtual void ogreMousePressEvent(QMouseEvent *event);
    virtual void ogreMouseMoveEvent(QMouseEvent *event);
};


#endif // QtOgreApplication_h__
