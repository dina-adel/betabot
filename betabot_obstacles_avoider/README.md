# Betabot Obstacle avoider

- [Betabot Obstacle avoider](#betabot-obstacle-avoider)
  - [Project Description](#project-description)
  - [After you implement the pkg state your reflection below](#after-you-implement-the-pkg-state-your-reflection-below)
    - [How did you plan the task?](#how-did-you-plan-the-task)
    - [what is your logic?](#what-is-your-logic)
    - [What ROS REPs did you used?](#what-ros-reps-did-you-used)
    - [How we could increase the overall performance?](#how-we-could-increase-the-overall-performance)
    - [List the most time consuming problems you faced](#list-the-most-time-consuming-problems-you-faced)
    - [Demo](#demo)
    - [Screenshot](#screenshot)
      - [NAME:](#name)
      - [ID:](#id)

## Project Description 

Create a ROS package with custom nodes c++/python to move the
betabot randomly in gazebo, the movement should be triggered then the robot
moves randomly while avoid objects based on laser scans reading based on the laser
scans.


>NOTE: DON'T process one ray of the laser scans array or it will be considered ultrasonic/IR sensor.try to come up with approach thats use the laser full potential. 

>To make you project standout try not to visit any place twice.

---

## After you implement the pkg state your reflection below

### How did you plan the task?
The first challenge was to understand the laser data and know which range corresponds to which direction with respect to the robot's pose. Then, after that, I started working on the logic in a python node.
### what is your logic?
First, I took three different readings from the laser scan. One for the front, one for the left and one fot the right direction. Then the robot checks if the area on the left, right, front is clear (based on given distances). If it is clear, the default for the robot is to move forward, else, it would turn around until it finds a clear path once again.
### What ROS REPs did you used?
Organizing the data and the code convention.
### How we could increase the overall performance?
Instead of only taking one laser beam in consideration for each direction, I should use more. Also, I think looking in only the three directions (front,left, right) is not sufficient. There should be more laser ranges and directions taken into consideration.
### List the most time consuming problems you faced
Understanding the laser scan, and encountring a problem at first when all the readings of the laser scan was -inf.
---

### Demo
Add unlisted youtube/drive video

[Demo](https://drive.google.com/drive/folders/1jv-rVjbIb7YVUmlJ_LgjPshhcoX4sHNp)

### Screenshot

[image](yourscreenshot)

---

#### NAME: Dina Adel
#### ID: 201601463

---
