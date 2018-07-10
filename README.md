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
rosrun mdart AVC_path_planner
rosrun mdart vehicle_dynamics
rosrun mdart serial_gateway

sudo apt-get install ros-kinetic-urg-node
git remote add upstream https://github.com/iscumd/mdart.git
git pull upstream master

Dependency on ros serial added:
-
git clone https://github.com/wjwwood/serial.git
Build: make
Install: make install

TO-DO:
-
setup ros params
unit testing
reformat according to style guides
brendon needs to make arbitrator node
[write the rest of the code](https://www.reddit.com/r/restofthefuckingowl/)
