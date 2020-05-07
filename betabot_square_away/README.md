# Betabot Moving in Square

- [Betabot Moving in Square](#betabot-moving-in-square)
  - [Project Description](#project-description)
  - [GUIDE](#guide)
  - [After you implement the pkg state your reflection below](#after-you-implement-the-pkg-state-your-reflection-below)
    - [How did you plan the task?](#how-did-you-plan-the-task)
    - [What ROS REPs did you used?](#what-ros-reps-did-you-used)
    - [How we could increase the overall performance?](#how-we-could-increase-the-overall-performance)
    - [List the most time consuming problems you faced](#list-the-most-time-consuming-problems-you-faced)
  - [Demo](#demo)
  - [Screenshot](#screenshot)
      - [NAME:](#name)
      - [ID:](#id)

## Project Description 

Create a ROS package with custom service/action c++/python to move the betabot in gazebo, the movement
triggered will have to be a square, like in the image below:
Betabot movement Use the data passed to this topic /move_betabot_in_square_custom to change the way
betabot moves. Depending on the side value, the service must move the robot in a square
movement based on the side given. Also, the robot must repeat the shape as many times as
indicated in the repetitions variable of the message. Finally, it must return True if everything
went OK in the success variable.


## GUIDE

1. Create a new launch file, called start_betabot_move_custom_service_server.launch,
that launches the new betabot_move_custom_service_server.py file.
2. Test that when calling this new /move_betabot_in_square_custom service, betabot
moves accordingly. This means, the square is performed taking into account the side
and repetitions variables.
3. Create a new service client that calls the service /move_betabot_in_square_custom,
and makes betabot moves in a small square twice and in a bigger square once.
It will be called betabot_move_custom_service_client.py. The launch that starts it will
be called call_betabot_move_in_square_custom_service_server.launch.
4. Refer to this tutorial for more help.
The BetabotCustomServiceMessage.srv will be something like this:

```sh
float64 side # The distance of each side of the square
int32 repetitions # The number of times the betabot robot has to execute the square
movement when the service is called
---
bool success # Did it achieve it?
```

>NOTE: The side variable doesn’t represent the real distance along each size of the square.It’s just a variable that will be used to change the size of the square. The bigger the size variable is, the bigger the square performed by the robot will be. You can use any robot pkg.

>To make you project standout try another shape and to use filtered `odemtry` data.

---

## After you implement the pkg state your reflection below

### How did you plan the task?
I used the server/client method. The client sends the square side length and the number of repeatitions to the server. In my implementation, the client sends four parameters: two for the large square and two for the small square. The server, based on the recieved parameters, moves making a square using the functions in the class.
The algorithm itself was based on using Twist msgs to move the robot. This worked fine when moving forward, however, turning around was challenging. To do it right, I needed to get the yaw of the robot and it's targeted yaw (+90) and let the robot turn till it reaches the desired angle.

### What ROS REPs did you used?
Using the Ros conventions in the code and folders.

### How we could increase the overall performance?
Have more feedback from the odom data for both the angles or the forward direction.

### List the most time consuming problems you faced
Solving the problem of the robot when turning around 90 degrees.
---

## Demo
Add unlisted youtube/drive video
Sorry it's so slow :"(
[Demo](https://drive.google.com/drive/folders/1jv-rVjbIb7YVUmlJ_LgjPshhcoX4sHNp)

## Screenshot

[image](MoveSquare.png)

Note: The srv file is put in betabot_msgs
---

#### NAME: Dina Adel
#### ID: 201601463

---
