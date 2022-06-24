dwm - dynamic window manager
============================
dwm is an extremely fast, small, and dynamic window manager for X.
<img src="https://github.com/BlackcatRs/black-dwm-6.3/blob/01_4_notitle/img/blackdwm.png">

Requirements
------------
- For Debian or Debian based systems: `sudo apt install make gcc libx11-dev libxft-dev libxinerama-dev xorg`

- For Arch: `sudo pacman -S base-devel git libx11 libxft xorg-server xorg-xinit terminus-font`

Installation
------------
Edit config.mk to match your local setup (dwm is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install dwm (if
necessary as root):

    sudo make clean install


Running dwm
-----------
Add the following line to your .xinitrc to start dwm using startx:

    exec dwm

In order to display status info in the bar, you need to specify where black-dwm is cloned in your .bashrc file:
    ```bash
    ### Required by status bar script ###
    export DWM_PATH='~/git'
    ```

And then add the following line to run status bar script in .xinitrc file before `exec dwm` line:
    
    exec "$(DWM_PATH)/black-dwm-6.3/scripts/bar.sh" &

Configuration
-------------
The configuration of dwm is done by creating a custom config.def.h and (re)compiling the source code.

    make clean && make

Testing
-------------
You can test your modification without affecting your actual dwm configuration by setting up a virtual enviroment.

First you need  to install Xephyr: 

- For Debian or Debian based systems: `sudo apt install xserver-xephyr`

- For arch: `sudo pacman -S xorg-server-xephyr`

Create a window or virtual environment to display dwm:

    Xephyr -br -ac -noreset -screen 1680x1050 :1 &

Then run dwm inside this environment:

    DISPLAY=':1' $DWM_PATH/black-dwm-6.3/dwm &
    DISPLAY=':1' $DWM_PATH/black-dwm-6.3/scripts/bar.sh &