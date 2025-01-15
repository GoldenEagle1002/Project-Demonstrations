#include "DroneDecorator.h"

DroneDecorator::DroneDecorator(Drone* baseDrone, int id) {
  this->baseDrone_ = baseDrone;
  this->id = id;
}
DroneDecorator::~DroneDecorator() {
  if (baseDrone_) delete baseDrone_;
}

void DroneDecorator::update(double dt) {
  if (timer > 0 && available == false) {
    timer = timer - dt;
  } else if (available == true) {
    resetTimer();
  }
  if (baseDrone_->getPackage() != nullptr) {
    Package* pack = baseDrone_->getPackage();
    pack->setTimer(timer);
  }
  baseDrone_->update(dt);
  available = baseDrone_->getAvailable();
}

Drone* DroneDecorator::unwrap() {
  resetSpeed();
  return baseDrone_;
}

Vector3 DroneDecorator::getPosition() const {
  return baseDrone_->getPosition();
}

Vector3 DroneDecorator::getDirection() const {
  return baseDrone_->getDirection();
}
