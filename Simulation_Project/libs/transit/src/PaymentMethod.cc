#include "PaymentMethod.h"
#include "SimulationModel.h"

PaymentMethod::PaymentMethod(Robot* bot, int amount, int id_) {
  this->bot = bot;
  id = id_;
  balance = amount;
  setPosition(bot->getPosition());
  setDirection(bot->getDirection());
}

PaymentMethod::~PaymentMethod() {
  if (bot) delete bot;
}

void PaymentMethod::update(double dt) {
  bot->update(dt);
  bot->requestedDelivery = requestedDelivery;
}

void PaymentMethod::receive(Package* p) {
  std::string name = "package";  // package->getName();

  if (p->getTimer() <= 0) {
    model->getController().sendDeliveryTimerStatus(name, 0, true);
    resetBalance();
  } else {
    int out = int(p->getTimer());
    model->getController().sendDeliveryTimerStatus(name, out, false);
  }

  bot->receive(p);
}

Vector3 PaymentMethod::getPosition() const { return bot->getPosition(); }

Vector3 PaymentMethod::getDirection() const { return bot->getDirection(); }
