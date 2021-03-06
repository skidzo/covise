USING(XERCESC)
USING(OsgCal)
using(VRML)
using(GDAL)
using(VehicleUtil)
using(TrafficSimulation)
using(OpenScenario)


covise_find_package(OpenSceneGraph 3.2.0 COMPONENTS osgTerrain)
COVISE_FIND_PACKAGE(osgTerrain)

set(HEADERS
  OpenScenarioPlugin.h
  ScenarioManager.h
  Maneuver.h
  Act.h
  Entity.h
  myFactory.h
  FollowTrajectory.h
  Trajectory.h
  CameraSensor.h
)
set(SOURCES
  OpenScenarioPlugin.cpp
  ScenarioManager.cpp
  Maneuver.cpp
  Act.cpp
  Entity.cpp
  myFactory.cpp
  FollowTrajectory.cpp
  Trajectory.cpp
  CameraSensor.cpp
)


INCLUDE_DIRECTORIES(
   ${OSGTERRAIN_INCLUDE_DIR}
)
# build the plugin "OpenScenarioPlugin" from the ingredients listed in HEADERS and SOURCES
cover_add_plugin(OpenScenarioPlugin ${HEADERS} ${SOURCES} ${OSGTERRAIN_LIBRARIES} ${EXTRA_LIBS} RoadTerrain SteeringWheel)
