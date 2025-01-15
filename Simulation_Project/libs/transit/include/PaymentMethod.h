#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H

#include "Package.h"
#include "Robot.h"
/**
 * @class PaymentMethod
 * @brief decorator class that simulates the idea that the robots are paying for
 *the delivery of the package.
 **/
class PaymentMethod : public Robot {
 protected:
  Robot* bot = nullptr;
  int balance = 0;

 public:
  /**
   * @brief creates a PaymentMethod object by wrapping a robot object also sets
   *objects postion based on the robot.
   * @param bot - A pointer to the robt object that will be wrapped
   **/
  PaymentMethod(Robot* bot, int amount, int id_);

  /**
   * @brief deconstructor for the wrapper.
   **/
  ~PaymentMethod();

  /**
   * @brief update function which uses the robot's update and also updates
   *whether the robot is available
   * @param dt - delta time
   **/
  void update(double dt);

  /**
   * @brief function to recive the delivered package and call reset package if
   *the package was late
   * @param p - pointer to the package object that is being delivered
   **/
  void receive(Package* p) override;

  /**
   * @brief abstract function that will reset the balance of a payment method
   *wrapper
   **/
  virtual void resetBalance() = 0;

  /**
   * @brief gets the postion of the wrapped robot
   * @return a vector containing the postion of the wrapped robot
   **/
  Vector3 getPosition() const;

  /**
   * @brief gets the direction of the wrapped robot
   * @return a vector containing the direction of the wrapped robot
   **/
  Vector3 getDirection() const;
};

#endif  // PAYMENTMETHOD_H
