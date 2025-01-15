#ifndef CREDITCARD_H
#define CREDITCARD_H

#include "PaymentMethod.h"

/**
 * @brief this class is a wrapper for the robot clas that simulates a credit
 *card payment system it inherits from the payment method class.
 **/
class CreditCard : public PaymentMethod {
 private:
  std::string creditCardNumber = "0";

 public:
  /**
   * @brief Constructs a new CreditCard object inherits from PaymentMethod.
   * @param robot - robot object that is being wrapped to add this classes
   *functionality to it.
   * @param amount - integer representing how much money the drone cost
   * @param id - id number to sync the credit card wrapper with the robot in the
   *simulation
   * @param creditNum - Credit card number to be charged for the purchase. Smal
   *note we just implemented this for simlulation purposes so no data security
   *is being used so do not input real credit card numbers
   **/
  CreditCard(Robot* robot, int amount, int id, std::string creditNum);

  /**
   * @brief resets the balance variable to zero.
   **/
  void resetBalance();
};

#endif  // CREDITCARD_H
