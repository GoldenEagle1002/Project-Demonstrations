#include "RocketDrone.h"

RocketDrone::RocketDrone(Drone* baseDrone, int id)
    : DroneDecorator(baseDrone, id) {
  timer = 15;
  adjustSpeedUp();
}

void RocketDrone::adjustSpeedUp() {
  baseDrone_->setSpeed(baseDrone_->getSpeed() * 10);
}

void RocketDrone::resetSpeed() {
  baseDrone_->setSpeed(baseDrone_->getSpeed() / 10);
}

void RocketDrone::resetTimer() { timer = 15; }
