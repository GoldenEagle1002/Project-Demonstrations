#include "NormalDrone.h"

NormalDrone::NormalDrone(Drone* baseDrone, int id)
    : DroneDecorator(baseDrone, id) {
  timer = 60;
}

void NormalDrone::adjustSpeedUp() {
  baseDrone_->setSpeed(baseDrone_->getSpeed() * 1);
}

void NormalDrone::resetSpeed() {
  baseDrone_->setSpeed(baseDrone_->getSpeed() / 1);
}

void NormalDrone::resetTimer() { timer = 60; }
