#include "SimulationModel.h"

#include "CreditCard.h"
#include "DroneFactory.h"
#include "FastDrone.h"
#include "HelicopterFactory.h"
#include "HumanFactory.h"
#include "NormalDrone.h"
#include "PackageFactory.h"
#include "RobotFactory.h"
#include "RocketDrone.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  entityFactory.AddFactory(new DroneFactory());
  entityFactory.AddFactory(new PackageFactory());
  entityFactory.AddFactory(new RobotFactory());
  entityFactory.AddFactory(new HumanFactory());
  entityFactory.AddFactory(new HelicopterFactory());
}

SimulationModel::~SimulationModel() {
  // Delete dynamically allocated variables
  for (auto& [id, entity] : entities) {
    delete entity;
  }
  delete graph;
}

IEntity* SimulationModel::createEntity(JsonObject& entity) {
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = nullptr;
  if (myNewEntity = entityFactory.CreateEntity(entity)) {
    // Call AddEntity to add it to the view
    myNewEntity->linkModel(this);
    controller.addEntity(*myNewEntity);
    entities[myNewEntity->getId()] = myNewEntity;
  }

  return myNewEntity;
}

void SimulationModel::removeEntity(int id) { removed.insert(id); }

/// Schedules a Delivery for an object in the scene
void SimulationModel::scheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];

  // Add something for cost and credit card number

  std::string credit = details["credit"];

  std::string wrapper = details["wrapper"];
  int cost = 0;
  if (wrapper == "normal") {
    cost = -20;
  } else if (wrapper == "fast") {
    cost = -50;
  } else if (wrapper == "rocket") {
    cost = -100;
  }

  std::cout << name << ": " << start << " --> " << end << std::endl;

  PaymentMethod* receiver = nullptr;

  for (auto& [id, entity] : entities) {
    if (name == entity->getName()) {
      if (Robot* r = dynamic_cast<Robot*>(entity)) {
        if (r->requestedDelivery) {
          receiver = new CreditCard(r, cost, id, credit);
          entity = receiver;
          entity->linkModel(this);
          entities[id] = entity;
          break;
        }
      }
    }
  }

  Package* package = nullptr;

  for (auto& [id, entity] : entities) {
    if (name + "_package" == entity->getName()) {
      if (Package* p = dynamic_cast<Package*>(entity)) {
        if (p->requiresDelivery) {
          package = p;
          break;
        }
      }
    }
  }

  if (receiver && package) {
    package->initDelivery(receiver);
    std::string strategyName = details["search"];
    package->setStrategyName(strategyName);
    package->setWrap(wrapper);
    scheduledDeliveries.push_back(package);
    controller.sendEventToView("DeliveryScheduled", details);
  }
}

const routing::IGraph* SimulationModel::getGraph() { return graph; }

/// Updates the simulation
void SimulationModel::update(double dt) {
  Drone* droneHolder;
  Package* package;
  for (auto& [id, entity] : entities) {
    if (Drone* d = dynamic_cast<Drone*>(entity)) {
      if (d->getAvailable()) {
        droneHolder = d;
        // check if its wrapped by dynamically casting to it

        if (DroneDecorator* decorated =
                dynamic_cast<DroneDecorator*>(droneHolder)) {
          droneHolder = decorated->unwrap();
          entity = droneHolder;
          entity->linkModel(this);
          entities[id] = entity;
        }

        if (scheduledDeliveries.size() > 0) {
          package = scheduledDeliveries.front();

          if (package->getWrap() == "normal") {
            std::cout << "Normal\n";
            entity = new NormalDrone(droneHolder, id);

          } else if (package->getWrap() == "fast") {
            std::cout << "Fast\n";
            entity = new FastDrone(droneHolder, id);

          } else if (package->getWrap() == "rocket") {
            std::cout << "Rocket\n";
            entity = new RocketDrone(droneHolder, id);
          }
          entity->linkModel(this);
          entities[id] = entity;
        }
      }
    }

    entity->update(dt);

    controller.updateEntity(*entity);
  }
  for (int id : removed) {
    removeFromSim(id);
  }
  removed.clear();
}

void SimulationModel::stop(void) { controller.stop(); }

void SimulationModel::removeFromSim(int id) {
  IEntity* entity = entities[id];
  if (entity) {
    for (auto i = scheduledDeliveries.begin(); i != scheduledDeliveries.end();
         ++i) {
      if (*i == entity) {
        scheduledDeliveries.erase(i);
        break;
      }
    }
    controller.removeEntity(*entity);
    entities.erase(id);
    delete entity;
  }
}

IController& SimulationModel::getController() { return controller; }
