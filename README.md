# marsupial_g2o

This package provides a framework to solve non-linear optimization problem for 3D trajectory planning in a marsupial robot configuration. Specifically, the configuration consists of an unmanned aerial vehicle (UAV) tied to an unmanned ground vehicle (UGV). The result is a collision-free trajectory for UAV and tether.

The optimization assumes static UGV position and estimates the problem states such as UAV and tether related with: UAV  position,  tether length, and UAV trajectory time. 

Different components such as UAV and tether positions, distance obstacles and temporal aspects of the motion (velocities and accelerations) are encoded as constraint and objective function. In consequence, the problem determining the values of the states optimizing a weighted multi-objective function.

The components encoded as constraint and objective function are local with respect to the problem states. Thus, the optimization is solved by formulating the problem as a sparse factor graph. For that g2o is used as the engine for graph optimization [https://github.com/RainerKuemmerle/g2o].

## Documentation

## Installation

In this section you will find the installation instructions for making it work. Next section (prerequisites) tells you the environment in which the package has been tested.

### Prerrequisites and dependencies

This package has been designed and tested in a x86_64 machine under a Linux 18.04 operating system and ROS Melodic distribution. Besides, our update depends script lets you easilly install the following dependencies:

- G2O
- PCL
- lazy_theta_star
- upo_actions
- behavior_tree

### Instalation steps:

1- Clone this repository into the source of your catkin workspace. Please refer to http://wiki.ros.org/catkin/Tutorials/create_a_workspace to setup a new workspace.

2- Call the g2o_installation.sh script to install G2O required dependencies.

```
rosrun marsupial_g2o g2o_installation.sh
```

3- Finally call marsupial_installation.sh script to install marsupial_g2o package.

```
rosrun marsupial_g2o marsupial_installation.sh
```

## Usage

Five scenarios with different feature can be set to use the optimizer. S1: Open environment, S2: Narrow/constrained environment, S3: Confined environment, S4: Confined environment, S5: Open environment, as show the next figure.

<p align="center">
    <img src="worlds/5_scenarios.png" width="1000">
</p>

The package has a set of predefined configurations (and completely extendable according to the user's need) that relate the stage number, initial position number and ending position number. The initial position can be check in ```/cfg``` and the final position in ```/trees/resources/```.

To launch the optimizer just launch the provided ```launch/marsupial_optimization_trayectory.launch``` file. To manage the scenario and initial position predefined is recomend to use the parameter for this launch, ```scenario_number``` and ```num_pos_initial```. For example to use, S2 and initial position 2: 

```
roslaunch marsupial_g2o marsupial_optimization_trayectory.launch scenario_number:=2 num_pos_initial:=2
```

It will launch the NIX prototype inside the mockup given by the ESMERA consortium. The plaform accepts input command velocities with the ROS 'cmd_vel' topic. It also offers odometry measures in the 'odom' topic (to this date the estimation is the ground truth pose).


## Optional extras
