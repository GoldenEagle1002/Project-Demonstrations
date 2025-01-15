#include "FastDrone.h"

FastDrone::FastDrone(Drone* baseDrone, int id) : DroneDecorator(baseDrone, id) {
  timer = 40;
  adjustSpeedUp();
}

void FastDrone::adjustSpeedUp() {
  baseDrone_->setSpeed(baseDrone_->getSpeed() * 5);
}

void FastDrone::resetSpeed() {
  baseDrone_->setSpeed(baseDrone_->getSpeed() / 5);
}

void FastDrone::resetTimer() { timer = 40; }
