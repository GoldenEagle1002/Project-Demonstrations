#include "Package.h"

#include "Robot.h"

Package::Package(JsonObject& obj) : IEntity(obj) {}

Vector3 Package::getDestination() const { return destination; }

std::string Package::getStrategyName() const { return strategyName; }

void Package::setStrategyName(std::string strategyName_) {
  strategyName = strategyName_;
}

void Package::update(double dt) {}

void Package::initDelivery(Robot* owner) {
  this->owner = owner;
  owner->requestedDelivery = false;
  requiresDelivery = false;
  destination = owner->getPosition();
}

std::string Package::getWrap() { return wrap; }

void Package::setWrap(std::string speed_) { wrap = speed_; }

void Package::handOff() {
  if (owner) {
    owner->receive(this);
  }
}

void Package::setTimer(double time) { timer = time; }

double Package::getTimer() { return timer; }
