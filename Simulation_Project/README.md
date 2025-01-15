<a name="br1"></a> 

Team-001-09

[Caleb](mailto:sanne118@umn.edu)[ ](mailto:sanne118@umn.edu)[Sannes](mailto:sanne118@umn.edu)[ ](mailto:sanne118@umn.edu)sanne118

[Ethan](mailto:tenle005@umn.edu)[ ](mailto:tenle005@umn.edu)[Tenley](mailto:tenle005@umn.edu)[ ](mailto:tenle005@umn.edu)tenle005

Project Overview



What is the project about (overview of the whole project, not just the hw4)?



This project simulates a drone delivery system that allows the user to schedule drone

deliveries from a package pickup location to a dropoff point that has a recipient which is

a simulated human or robot.

●

How to run the simulation (overview of the whole project, not just the hw4)?

○ To run the visualization of the simulation you need to follow these steps:


\# Go to the project directory

cd /path/to/repo/project

\# Build the project

make -j

\# Run the project (./build/web-app <port> <web folder>)

./build/bin/transit\_service 8081 apps/transit\_service/web/

In a web browser, navigate to <http://127.0.0.1:8081>[ ](http://127.0.0.1:8081)and you should see a

visualization. Note: You may not be able to bind to the port. If you started the

transit\_service with a different port, you will need to change the link to that

port.



Navigate to [http://127.0.0.1:8081/schedule.htm](http://127.0.0.1:8081/schedule.html)[l](http://127.0.0.1:8081/schedule.html)[ ](http://127.0.0.1:8081/schedule.html)and you should see a page to

schedule the delivery.

**

*Note: 8081 will depend on what port you used. If you use port 8082, then it will*

*be [http://127.0.0.1:8082*](http://127.0.0.1:8082)[ ](http://127.0.0.1:8082)instead.*



To schedule a delivery you will need to head to the schedule delivery page. There you

will be prompted to:



Name the delivery

Select the search strategy

Select the drone type/delivery speed

Select a pickup location and a dropoff location for the delivery

Enter a fake credit card number

Then schedule the delivery



What does the simulation do specifically (individual features i.e. movement of entities etc)

(overview of the whole project, not just the hw4)?



After scheduling a delivery the delivery will enter a delivery queue that the drone works

through. Once the drone has been assigned to a delivery it will move to the pickup

location of the package. The drone navigates the paths available using the search

strategy you selected. Once the drone has picked up the package it will then move

towards the drop off location there it will deliver the package to the robot and celebrate.

Then there will be a notification on the bottom of the schedule page indicating the time



<a name="br2"></a> 

the package was delivered in and whether or not it was delivered on time. If it was not

delivered on time the robot’s funds will be refunded.



New Feature -> Timer

○ What does it do?

Packages must be delivered before their time runs out.



When the delivery is scheduled, the human decides what type of

delivery they want. There are different speed drones to choose from,

like normal drone, fasterdrone, rocket boosted drone, via decorator

The faster delivery options cost more money

Once the delivery is scheduled, if the package doesn't arrive before the

time runs out, the delivery is free and the human is refunded their

money.



Why is it significantly interesting?



It is useful for tracking the duration of an event or activity within the simulation.

In a drone delivery system, a timer could be used to measure how long it takes

for a package to be delivered and whether the delivery was on time or late. This

can influence customer satisfaction metrics and the performance evaluation of

the delivery service.



The concepts add a layer of realism and complexity to the simulation, enabling it

to more closely mimic the variances and unpredictabilities found in real-world

scenarios. This helps make the simulation a more effective tool for testing,

planning, and research.



How does it add to the existing work?



The Timer feature is integrated into the Drone decorators to track the delivery

time. When a drone is assigned a delivery, the timer starts, and upon completion

of the delivery, it reports the time taken. The timer status, including whether the

delivery has timed out or not, is sent to the controller which could then relay

this information to the view (client-side JavaScript).



Overall, these decorators and the Timer class seamlessly blend with the

object-oriented design, demonstrating polymorphism (through strategies and

decorators), encapsulation (separation of concerns), and communication

between different components in a Model-View-Controller architecture. This

structure enables flexible and extensible code, allowing for easy modifications

and addition of new features.





Which design pattern did you choose to implement it and why?



Decorator. We used decorator because it is a structural design pattern that is

great for adding new behaviors to objects. It does this by attaching new

behaviors to objects by placing these objects inside special wrapper objects that

contain the behaviors.

Instruction to use this new feature (if the new feature is not user interactable, please

mention this as well)



<a name="br3"></a> 



To use this new feature you will need to go to the scheduling page where you

start requesting a delivery as you normally would. Then when you get to delivery

speed you will select which type of drone you need here it will also display the

costs and the delivery speed guarantee time. Then before you schedule the

delivery you will need to enter a credit card number. Once a delivery is delivered

it will give you a notification over the map on the scheduling page stating so. It

will also display a green/red notification at the bottom of the page displaying the

time remaining on the timer and whether or not the package was delivered on

time.


Limitations 
    
Sometimes the drone will appear to instantly complete the delivery if the simulation tab is not actively open

Faster drones can sometimes overshoot their delivery point slightly slowing them down



Sprint **retrospective**

****

What worked well?







Communication. Team members regularly had meetings to work on and discuss

the project in a collaborative manner.

Utilization of Version Control Systems. Git helps manage code changes, facilitate

collaboration across different parts of the project, and keep the codebase stable.

Defined Roles and Responsibilities. Each team member knew what they were

responsible for and when team members know what is expected of them, they

can focus on their tasks without confusion and overlap, leading to efficient

progress.



What didn’t go well?



Attention to detail. Some errors that we had while coding were caused by simple

mistakes such as spelling and missing semicolons.



Started later than we should have. We started working on the project ~1 week

before it was due thinking this would be ample time to work on the project as

we thought we had a solid idea of what to do. But then we ran into errors that

were major headaches and we underestimated the challenge of integrating the

frontend with the backend.



How could we improve?



Pay attention to the little details because if you don’t it will cause a lot of issues.

Start working on the project as soon as possible so there is a good idea of how

much work is needed to be done.



Note that the Youtube Video is quite unpolished as we ran into some bugs late in the project meaning this was a very last minute job to get this video out the door. 
Youtube Link https://youtu.be/pCCJBCOZ_8M