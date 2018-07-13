# M-DART

[Software Diagram](https://www.draw.io/?state=%7B"ids":%5B"1baedZCdRMubKkNbw4RqnQqFeQgDtPncD"%5D,"action":"open","userId":"112644069261546685875"%7D "Magnus Software Diagram")
-

Style Guides
-
[ROS Framework](http://wiki.ros.org/StyleGuide)

[C++](http://wiki.ros.org/CppStyleGuide)

[Python](http://wiki.ros.org/PyStyleGuide)

Useful commands:
-
run from anywhere:

    rosrun mdart AVC_path_planner

run from anywhere:

    rosrun mdart vehicle_dynamics

run from anywhere:

    rosrun mdart serial_gateway

run from anywhere:

    sudo apt-get install ros-kinetic-urg-node

run from catkin_ws/src/mdart:

    git remote add upstream https://github.com/iscumd/mdart.git

run from catkin_ws/src/mdart:

    git pull upstream master

Dependency on ros serial added:
-
run from catkin_ws/src/:

    git clone https://github.com/wjwwood/serial.git

run from catkin_ws/src/serial:

    Build: make

run from catkin_ws/src/serial:

    Install: make install

TO-DO:
-
setup ros params

unit testing

reformat according to style guides

brendon needs to make arbitrator node

[write the rest of the code](https://www.reddit.com/r/restofthefuckingowl/)
