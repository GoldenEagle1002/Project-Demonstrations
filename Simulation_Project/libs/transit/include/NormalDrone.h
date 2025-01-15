#ifndef NORMALDRONE_H_
#define NORMALDRONE_H_

#include "DroneDecorator.h"

/**
 * @class NormalDrone
 * @brief wrapper for a normal speed drone.
 **/
class NormalDrone : public DroneDecorator {
 public:
  /**
   * @brief creates a normal drone object by wrapping a normal base drone.
   * @param baseDrone - a pointer to the base drone that will be wrapped
   * @param id - an id to sync the wrapper with the drone in the simulation
   **/
  NormalDrone(Drone* baseDrone, int id);

 protected:
  /**
   * @brief doesn't increase drone speed but multiplies it by 1.
   **/
  void adjustSpeedUp();

  /**
   * @brief doesn't change the speed but divides it by one.
   **/
  void resetSpeed();

  void resetTimer();
};

#endif /* NORMALDRONE_H_ */
