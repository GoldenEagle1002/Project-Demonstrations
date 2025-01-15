#ifndef ROCKETDRONE_H_
#define ROCKETDRONE_H_

#include "DroneDecorator.h"

class RocketDrone : public DroneDecorator {
 public:
  RocketDrone(Drone* baseDrone, int id);

 protected:
  void adjustSpeedUp();

  void resetSpeed();

  void resetTimer();
};

#endif /* ROCKETDRONE_H_ */
