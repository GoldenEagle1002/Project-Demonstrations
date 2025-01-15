#ifndef FASTDRONE_H_
#define FASTDRONE_H_

#include "DroneDecorator.h"

/**
 * @class FastDrone
 * @brief wrapper for a drone that makes it go five times faster.
 **/
class FastDrone : public DroneDecorator {
 public:
  /**
   * @brief Creates a FastDrone object and wrapes a base drone within it.
   * @param baseDrone - A pointer to the drone object that is being wrapped.
   * @param id - id number to sync the drone wrapper with the drone in the
   *simulation
   **/
  FastDrone(Drone* baseDrone, int id);

 protected:
  /**
   * @brief increases drone speed by multiplyng it by five.
   **/
  void adjustSpeedUp();

  /**
   * @brief resets drone speed by dividing it by five.
   **/
  void resetSpeed();

  /**
   * @brief resets the drones timer to 40 delta time seconds.
   **/
  void resetTimer();
};

#endif /* FASTDRONE_H_ */
