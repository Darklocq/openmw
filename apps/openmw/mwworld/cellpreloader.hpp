#ifndef OPENMW_MWWORLD_CELLPRELOADER_H
#define OPENMW_MWWORLD_CELLPRELOADER_H

#include <map>
#include <osg/ref_ptr>
#include <components/sceneutil/workqueue.hpp>

namespace Resource
{
    class SceneManager;
    class BulletShapeManager;
}

namespace MWWorld
{
    class CellStore;

    class CellPreloader
    {
    public:
        CellPreloader(Resource::SceneManager* sceneManager, Resource::BulletShapeManager* bulletShapeManager);

        /// Ask a background thread to preload rendering meshes and collision shapes for objects in this cell.
        /// @note The cell itself must be in State_Loaded or State_Preloaded.
        void preload(const MWWorld::CellStore* cell, double timestamp);

        /// Removes preloaded cells that have not had a preload request for a while.
        void updateCache(double timestamp);

        void setWorkQueue(osg::ref_ptr<SceneUtil::WorkQueue> workQueue);

    private:
        Resource::SceneManager* mSceneManager;
        Resource::BulletShapeManager* mBulletShapeManager;
        osg::ref_ptr<SceneUtil::WorkQueue> mWorkQueue;

        struct PreloadEntry
        {
            PreloadEntry(double timestamp, osg::ref_ptr<SceneUtil::WorkItem> workItem)
                : mTimeStamp(timestamp)
                , mWorkItem(workItem)
            {
            }
            PreloadEntry()
                : mTimeStamp(0.0)
            {
            }

            double mTimeStamp;
            osg::ref_ptr<SceneUtil::WorkItem> mWorkItem;
        };
        typedef std::map<const MWWorld::CellStore*, PreloadEntry> PreloadMap;

        // Cells that are currently being preloaded, or have already finished preloading
        PreloadMap mPreloadCells;
    };

}

#endif
