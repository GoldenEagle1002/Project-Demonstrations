#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

class Package;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the next delivery in the scheduler
   */
  void getNextDelivery();

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   */
  virtual void update(double dt);

  /**
   * @brief Removing the copy constructor operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;

  /**
   * @brief Removing the assignment operator
   * so that drones cannot be copied.
   */
  Drone& operator=(const Drone& drone) = delete;

  // Function to handle the package drop
  void dropPackage();

  /**
   * @brief gets the available variable.
   * @return the availalbe variable
   **/
  virtual bool getAvailable();

  /**
   * @brief gets the package variable.
   * @return a pointer to a package or a null pointer if there is none
   **/
  Package* getPackage();

  /**
   * @brief sets the speed of the drone.
   * @param speed_ a double that represents the new speed of the drone
   **/
  void setSpeed(double speed_);

 protected:
  /**
   * @brief defult constructor for a drone
   **/
  Drone() {}

  bool available = false;

 private:
  int timer;
  bool pickedUp = false;
  Package* package = nullptr;
  IStrategy* toPackage = nullptr;
  IStrategy* toFinalDestination = nullptr;
};

#endif
