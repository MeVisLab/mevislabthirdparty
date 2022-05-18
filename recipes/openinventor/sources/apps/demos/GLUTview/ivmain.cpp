// #define USE_GLEW 1
// #define SETUP_WINDOW_ELEMENT 1

#if defined(WIN32)
# include <windows.h>
#endif
#if defined(USE_GLEW)
# include <GL/glew.h>
#endif
#if defined(__APPLE__)
# include <OpenGL/gl.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glut.h>
#endif
#include <Inventor/SoInventor.h>
#include <stdlib.h>
#include <iostream>

extern SoSeparator *ivScene(const char *file);

SbBool delaySensorActive = FALSE;
SbBool firstEvent = TRUE;
SoSeparator *root;
SoSceneManager *sceneMgr;
int W = 400;
int H = 400;

void
reshape(int w, int h)
{
   sceneMgr->setWindowSize(SbVec2s(w,h));
   sceneMgr->setSize(SbVec2s(w,h));

   W= w; H= h;

   sceneMgr->render();

   glutSwapBuffers();
}

void
renderScene(void * /* clientData */, SoSceneManager *mgr)
{
   mgr->render();

   glutSwapBuffers();
}

void
redraw(void)
{
   sceneMgr->render();

   glutSwapBuffers();
}

void
visibilityChanged(int state)
{
   if(state == GLUT_VISIBLE)
      sceneMgr->activate();
   else
      sceneMgr->deactivate();
}

void
idle(void)
{
   SoSensorManager *sensorMgr= SoDB::getSensorManager();

   sensorMgr->processTimerQueue();
   sensorMgr->processDelayQueue(TRUE);
}

void
processDelayQueue(int)
{
   SoSensorManager *sensorMgr= SoDB::getSensorManager();

   sensorMgr->processDelayQueue(FALSE);
}

void
sensorQueueChanged(void * /* clientData */ )
{
   SoSensorManager *sensorMgr= SoDB::getSensorManager();

   if(sensorMgr->isDelaySensorPending()) {
      if(! delaySensorActive) {
         unsigned int timeout= SoDB::getDelaySensorTimeout().getMsecValue();
         glutTimerFunc(timeout, processDelayQueue, 0);

         delaySensorActive= TRUE;
      }
   }
}

void
mouseButton(int button, int state, int x, int y)
{
   SoMouseButtonEvent *mbe= new SoMouseButtonEvent;

   mbe->setTime(SbTime::getTimeOfDay());

   switch(button) {
      case GLUT_LEFT_BUTTON:
         mbe->setButton(SoMouseButtonEvent::BUTTON1);
         break;
      case GLUT_MIDDLE_BUTTON:
         mbe->setButton(SoMouseButtonEvent::BUTTON2);
         break;
      case GLUT_RIGHT_BUTTON:
         mbe->setButton(SoMouseButtonEvent::BUTTON3);
         break;
      default:
         mbe->setButton(SoMouseButtonEvent::ANY);
         break;
   }
   mbe->setState((state == GLUT_UP) ? SoButtonEvent::UP : SoButtonEvent::DOWN);
   mbe->setPosition(SbVec2s(x, H - y - 1));

   int modifiers= glutGetModifiers();
   mbe->setShiftDown(modifiers & GLUT_ACTIVE_SHIFT);
   mbe->setCtrlDown(modifiers & GLUT_ACTIVE_CTRL);
   mbe->setAltDown(modifiers & GLUT_ACTIVE_ALT);

   sceneMgr->processEvent(mbe);
}

void
mouseMotion(int x, int y)
{
   SoLocation2Event *l2e= new SoLocation2Event;

   l2e->setTime(SbTime::getTimeOfDay());
   l2e->setPosition(SbVec2s(x, H - y - 1));

//    int modifiers= glutGetModifiers();
//    l2e->setShiftDown(modifiers & GLUT_ACTIVE_SHIFT);
//    l2e->setCtrlDown(modifiers & GLUT_ACTIVE_CTRL);
//    l2e->setAltDown(modifiers & GLUT_ACTIVE_ALT);

   sceneMgr->processEvent(l2e);

#ifdef SETUP_WINDOW_ELEMENT
   if(firstEvent) {
      SoState *state = sceneMgr->getHandleEventAction()->getState();
      if(state) {
         SoWindowElement::set(state, getNormalWindow(), getNormalContext(), getDisplay(), sceneMgr->getGLRenderAction());
         firstEvent = FALSE;
      }
   }
#endif
}

void
mouseEnter(int state)
{
#ifdef SETUP_WINDOW_ELEMENT
   if(state == GLUT_ENTERED) {
      // update the windowElement for the handleEventAction as well
      // as the GLRenderAction to point to this window.
      //
      // Note: don't touch the windowElement if we are in the middle
      // of rendering (if we process event during render abort).
      //
      SoState *state = sceneMgr->getHandleEventAction()->getState();
      if(state) {
         SoWindowElement::set(state, getNormalWindow(), getNormalContext(), getDisplay(), sceneMgr->getGLRenderAction());
      }
      state = sceneMgr->getGLRenderAction()->getState();
      if(state && state->getDepth() == 1) {
	 SoWindowElement::set(state, getNormalWindow(), getNormalContext(), getDisplay(), sceneMgr->getGLRenderAction());
      }
   }
   else if(state == GLUT_LEFT) {
      // clear the windowElement from the actions now that we are
      // leaving the window.
      //
      // Note: don't touch the windowElement if we are in the middle
      // of rendering (if we process event during render abort).
      //
	
      // but first clear any currently highlighted object
      SoGLRenderAction *glAct = sceneMgr->getGLRenderAction();
      if(glAct) {
         SoLocateHighlight::turnOffCurrentHighlight(glAct);
      }

      SoState *state = sceneMgr->getHandleEventAction()->getState();
      if(state) {
         SoWindowElement::set(state, (Window)NULL, NULL, NULL, NULL);
      }
      state = sceneMgr->getGLRenderAction()->getState();
      if(state && state->getDepth() == 1) {
         SoWindowElement::set(state, (Window)NULL, NULL, NULL, NULL);
      }
   }
#endif
}

SbBool
buildScene(const char *file)
{
   root= new SoSeparator;
   root->ref();

   SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
   myCamera->position = SbVec3f(3,2,5.0);
   myCamera->heightAngle = M_PI/2.5;
   myCamera->nearDistance = 1.0;
   myCamera->farDistance = 35.0;
   myCamera->pointAt(SbVec3f(0,0,0));
   root->addChild(myCamera);
   root->addChild(new SoDirectionalLight);

   SoSeparator *scene = ivScene(file);
   if(!scene)
      return FALSE;

   root->addChild(scene);

   // Adjust camera to view entire scene.
   myCamera->viewAll(scene, SbViewportRegion(W,H));

   return TRUE;
}

int
main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   SoDB::init();
   SoNodeKit::init();
   SoInteraction::init();
   SoMeVis::init();

   if(!buildScene((argc == 1) ? NULL : argv[1])) {
      exit(1);
   }

   SoSensorManager *sensorMgr= SoDB::getSensorManager();
   sensorMgr->setChangedCallback(sensorQueueChanged, NULL);

   glutInitWindowSize(W,H);
   glutCreateWindow("GLUT Open Inventor Test");

#ifdef USE_GLEW
   GLenum err = glewInit();
   if(GLEW_OK != err) {
      // Problem: glewInit failed, something is seriously wrong.
      std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
   }
#endif

   glutDisplayFunc(redraw);
   glutReshapeFunc(reshape);
   glutVisibilityFunc(visibilityChanged);
   glutIdleFunc(idle);
   glutMouseFunc(mouseButton);
   glutMotionFunc(mouseMotion);
   glutPassiveMotionFunc(mouseMotion);
   glutEntryFunc(mouseEnter);
   glEnable(GL_DEPTH_TEST);

   sceneMgr= new SoSceneManager;
   sceneMgr->setRenderCallback(renderScene, NULL);
   sceneMgr->getGLRenderAction()->setViewportRegion(SbViewportRegion(W,H));
   sceneMgr->setBackgroundColor(SbColor(0.25,0.25,0.25));
   sceneMgr->activate();

   sceneMgr->setSceneGraph(root);

   glutMainLoop();

   return 0;             /* ANSI C requires main to return int. */
}
