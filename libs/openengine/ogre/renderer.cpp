#include "renderer.hpp"
#include "fader.hpp"

#include "OgreRoot.h"
#include "OgreRenderWindow.h"
#include "OgreLogManager.h"
#include "OgreLog.h"

#include <assert.h>

using namespace Ogre;
using namespace OEngine::Render;

void OgreRenderer::cleanup()
{
  if (mFader)
    delete mFader;
  
  if(mRoot)
    delete mRoot;
  mRoot = NULL;
}

void OgreRenderer::start()
{
  mRoot->startRendering();
}

bool OgreRenderer::loadPlugins()
{
    #ifdef ENABLE_PLUGIN_GL
    mGLPlugin = new Ogre::GLPlugin();
    mRoot->installPlugin(mGLPlugin);
    #endif
    #ifdef ENABLE_PLUGIN_Direct3D9
    mD3D9Plugin = new Ogre::D3D9Plugin();
    mRoot->installPlugin(mD3D9Plugin);
    #endif
    #ifdef ENABLE_PLUGIN_CgProgramManager
    mCgPlugin = new Ogre::CgPlugin();
    mRoot->installPlugin(mCgPlugin);
    #endif
    #ifdef ENABLE_PLUGIN_OctreeSceneManager
    mOctreePlugin = new Ogre::OctreePlugin();
    mRoot->installPlugin(mOctreePlugin);
    #endif
    #ifdef ENABLE_PLUGIN_ParticleFX
    mParticleFXPlugin = new Ogre::ParticleFXPlugin();
    mRoot->installPlugin(mParticleFXPlugin);
    #endif
    #ifdef ENABLE_PLUGIN_BSPSceneManager
    mBSPPlugin = new Ogre::BspSceneManagerPlugin();
    mRoot->installPlugin(mBSPPlugin);
    #endif
    return true;
}

void OgreRenderer::update(float dt)
{
  mFader->update(dt);
}

void OgreRenderer::screenshot(const std::string &file)
{
  mWindow->writeContentsToFile(file);
}

float OgreRenderer::getFPS()
{
  return mWindow->getLastFPS();
}

bool OgreRenderer::configure(bool showConfig,
                             const std::string &cfgPath,
                             const std::string &logPath,
                             const std::string &pluginCfg,
                             bool _logging)
{
  // Set up logging first
  new LogManager;
  Log *log = LogManager::getSingleton().createLog(logPath + std::string("Ogre.log"));
  logging = _logging;

  if(logging)
    // Full log detail
    log->setLogDetail(LL_BOREME);
  else
    // Disable logging
    log->setDebugOutputEnabled(false);

#if defined(ENABLE_PLUGIN_GL) || defined(ENABLE_PLUGIN_Direct3D9) || defined(ENABLE_PLUGIN_CgProgramManager) || defined(ENABLE_PLUGIN_OctreeSceneManager) || defined(ENABLE_PLUGIN_ParticleFX) || defined(ENABLE_PLUGIN_BSPSceneManager)
  mRoot = new Root("", cfgPath, "");
  loadPlugins();
#else
  mRoot = new Root(pluginCfg, cfgPath, "");
#endif

  // Show the configuration dialog and initialise the system, if the
  // showConfig parameter is specified. The settings are stored in
  // ogre.cfg. If showConfig is false, the settings are assumed to
  // already exist in ogre.cfg.
  int result;
  if(showConfig)
    result = mRoot->showConfigDialog();
  else
    result = mRoot->restoreConfig();

  return !result;
}

bool OgreRenderer::configure(bool showConfig,
                             const std::string &cfgPath,
                             const std::string &pluginCfg,
                             bool _logging)
{
    return configure(showConfig, cfgPath, cfgPath, pluginCfg, _logging);
}

bool OgreRenderer::configure(bool showConfig,
                             const std::string &pluginCfg,
                             bool _logging)
{
    return configure(showConfig, "", pluginCfg, _logging);
}

void OgreRenderer::createWindow(const std::string &title)
{
  assert(mRoot);
  // Initialize OGRE window
  mWindow = mRoot->initialise(true, title, "");
}

void OgreRenderer::createScene(const std::string camName, float fov, float nearClip)
{
  assert(mRoot);
  assert(mWindow);
  // Get the SceneManager, in this case a generic one
  mScene = mRoot->createSceneManager(ST_GENERIC);

  // Create the camera
  mCamera = mScene->createCamera(camName);
  mCamera->setNearClipDistance(nearClip);
  mCamera->setFOVy(Degree(fov));

  // Create one viewport, entire window
  mView = mWindow->addViewport(mCamera);

  // Alter the camera aspect ratio to match the viewport
  mCamera->setAspectRatio(Real(mView->getActualWidth()) / Real(mView->getActualHeight()));
  
  mFader = new Fader();
}
