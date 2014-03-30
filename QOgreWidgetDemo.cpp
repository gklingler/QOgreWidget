#include "QOgreWidgetDemo.hpp"
#include "OGRE/RenderSystems/GL/OgreGLPlugin.h"
#include "QOgreWidget.hpp" // must be included after the OGRE plugin
#include "QCameraMan.h"

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>


void QOgreWidgetDemo::setupResources(void) {
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements()) {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i) {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
}


void QOgreWidgetDemo::setupRenderSystem() {
    // look for the openGL renderer in Ogre
    Ogre::RenderSystemList::const_iterator availableRendererIt = mOgreRoot->getAvailableRenderers().begin();
    
    while (availableRendererIt != mOgreRoot->getAvailableRenderers().end()) {
        Ogre::String rName = (*availableRendererIt)->getName();
        if (rName == "OpenGL Rendering Subsystem") {
            break;
        }
        ++availableRendererIt;
    }
    
    if (availableRendererIt == mOgreRoot->getAvailableRenderers().end()) {
        throw std::runtime_error("We were unable to find the OpenGL renderer in ogre's list, cannot continue");
    }
    
    // use the OpenGL renderer in the root config
    mRenderSystem = *availableRendererIt;
    mOgreRoot->setRenderSystem(mRenderSystem);
    mRenderWindow = mOgreRoot->initialise(false);
}


void QOgreWidgetDemo::createScene() {
    mSceneManager = mOgreRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE);
    mCamera = mSceneManager->createCamera("QOgreWidget_Cam");
    mCamera->setPosition(1.0, 1.0, 200);
    mCamera->setAutoAspectRatio(true);
    mCameraMan = new OgreBites::QCameraMan(mCamera);
    mCameraMan->setCamera(mCamera);
    
    mOgreViewport = mOgreWidget->getEmbeddedOgreWindow()->addViewport(mCamera);
    
    this->resize(640, 480);
    this->setWindowTitle("QOgreWidget demo");
    
    // Set the scene's ambient light
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    // Create an Entity
    Ogre::Entity *ogreHead = mSceneManager->createEntity("Head", "ogrehead.mesh");
    
    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode *headNode = mSceneManager->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
    
    // Create a Light and set its position
    Ogre::Light *light = mSceneManager->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
}

    
void QOgreWidgetDemo::createQtWidgets() {
    QGroupBox *mainGroup = new QGroupBox;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mOgreWidget = new QOgreWidget(mOgreRoot, this, mainGroup);
    QPushButton *buttonZoomIn = new QPushButton(tr("Zoom &In"));
    QPushButton *buttonZoomOut = new QPushButton(tr("Zoom &Out"));
    mainLayout->addWidget(buttonZoomIn);
    mainLayout->addWidget(buttonZoomOut);
    connect(buttonZoomIn, SIGNAL(released()), this, SLOT(onZoomIn()));
    connect(buttonZoomOut, SIGNAL(released()), this, SLOT(onZoomOut()));
    
    mainLayout->addWidget(mOgreWidget);
    mainGroup->setLayout(mainLayout);
    setCentralWidget(mainGroup);
}


void QOgreWidgetDemo::onZoomIn() {
    mCamera->moveRelative(Ogre::Vector3(0, 0, -10.0));
}


void QOgreWidgetDemo::onZoomOut() {
    mCamera->moveRelative(Ogre::Vector3(0, 0, 10));
}


void QOgreWidgetDemo::ogreMousePressEvent(QMouseEvent *event) {
    mCameraMan->injectMouseDown(*event);
}


void QOgreWidgetDemo::ogreMouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        std::cout << "mouse Moved (left button pressed)";
    } else if (event->buttons() & Qt::RightButton) {
        std::cout << "mouse Moved (right button pressed)";
    }
    int x = event->x();
    int y = event->y();
    int dx = mMouseMoveXOld - x;
    int dy = mMouseMoveYOld - y;
    
    mMouseMoveXOld = x;
    mMouseMoveYOld = y;
    
    mCameraMan->injectMouseMove(*event);
}


QOgreWidgetDemo::QOgreWidgetDemo() :
    mOgreRoot(new Ogre::Root("plugins.cfg")) {
    
    setupResources();
    setupRenderSystem();
    
    createQtWidgets();
    createScene();
    
    mOgreRoot->renderOneFrame();
    this->show(); // give focus to our application and make it visible
}


QOgreWidgetDemo::~QOgreWidgetDemo() {
    delete mOgreRoot;
    delete mOgreWidget;
}
