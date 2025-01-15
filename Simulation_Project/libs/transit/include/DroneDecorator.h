#ifndef DRONEDECORATOR_H_
#define DRONEDECORATOR_H_

#include "Drone.h"
#include "Package.h"

/**
 * @class DroneDecorator
 * @brief decorates drone objects allowing for futher functionality and in
 *particluar focuses on creating wrappers that adjust the speed of the base
 *drone.
 **/
class DroneDecorator : public Drone {
 public:
  /**
   * @brief Creates a DroneDecorator object and wrapes a basedrone within it.
   * @param baseDrone - The drone object that is being wrapped.
   * @param - id id number to sync the drone wrapper with the drone in the
   *simulation
   **/
  DroneDecorator(Drone* baseDrone, int id);

  /**
   * @brief ensures that wrapper and potentially the drone
   * within it are properly deleted and their memeory is freed.
   **/
  ~DroneDecorator();

  /**
   * @brief Inherits from the drone update but adds in the functionality of
   *updating the wrappers' timers.
   * @param dt - delta time.
   **/
  virtual void update(double dt);

  /**
   * @brief unwraps the wrapper from the drone object by returining a pointer to
   *the base drone object also resets the speed of the drone when doing so.
   * @return a drone pointer to the orignally wrapped drone.
   **/
  Drone* unwrap();

  /**
   * @brief abstract function which will adjust the speed of the drone in the
   *wrappers.
   **/
  virtual void adjustSpeedUp() = 0;

  /**
   * @brief abstract function which will reset the speed of the drone in the
   *wrappers.
   **/
  virtual void resetSpeed() = 0;

  virtual void resetTimer() = 0;

  Drone* baseDrone_;

 protected:
  double timer = 0;

  /**
   * @brief function which will give the postion of the wrapped drone.
   * @return vector containing the postion of the wrapped drone
   **/
  Vector3 getPosition() const;

  /**
   * @brief function which will give the direction of the wrapped drone.
   * @return vector containing the direction of the wrapped drone
   **/
  Vector3 getDirection() const;
};

#endif
