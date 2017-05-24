# PID controller
This Project is the ninth task (Project 4 of Term 2) of the Udacity Self-Driving Car Nanodegree program. The main goal of the project is to implement PID controller in C++ to steer the self driving car around the track in a [Simulator](https://github.com/udacity/CarND-PID-Control-Project/releases).

The project was created with the Udacity [Starter Code](https://github.com/udacity/CarND-PID-Control-Project).

## About PID controller

A PID (Proportional, Integral, Derivative) controller is a control loop feedback controller which is widely used in different control systems. 

While the PID controller is easy to implement, but it is not so easy to tune.

## How it was tuned

Initially, the controller was tuned with so-called [Ziegler–Nichols method](http://staff.guilan.ac.ir/staff/users/chaibakhsh/fckeditor_repo/file/documents/Optimum%20Settings%20for%20Automatic%20Controllers%20(Ziegler%20and%20Nichols,%201942).pdf). Generally speaking, it requires to set _Kd_ and _Ki_ to 0 and gradually increase _Kp_ before the car runs with stable and consistent oscillations. This value of _Kp_  and the oscillation period can be used to calculate optimal pid controller parameters by the [method](http://www.mstarlabs.com/control/znrule.html). Unfortunatly, the controller with resulted parameters was able to drive car around the track but with a lot of wobbling. That is why, parameters were further tuned manually by try-and-error process.

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

