#include "CreditCard.h"

CreditCard::CreditCard(Robot* robot, int amount, int id, std::string creditNum)
    : PaymentMethod(robot, amount, id) {
  creditCardNumber = creditNum;
}

void CreditCard::resetBalance() {
  std::cout << "Reset Balance\n";
  creditCardNumber = "0";
  balance = 0;
}
