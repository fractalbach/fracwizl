======================================================================
FRAC WIZ L
======================================================================

Fractalbach's WizardLy Battle 3D Game. This repo contains my crazy 
attempt to make an extremely portable, and epic, 3D game from scratch,
and maybe support software rendering.



======================================================================
Development: FIRST TIME SETUP
======================================================================

One day, the dev setup will be handled by a script like ./run/setup.sh
but that day is not this day. Until that day, setup is manual.

______________________________
Download and Install SDL2
------------------------------

cd external
git clone https://github.com/libsdl-org/SDL.git -b SDL2 --depth 1
cd SDL
./configure
make
sudo make install


______________________________
Download GLEW-2.2.0 from
------------------------------

https://github.com/nigels-com/glew/archive/refs/tags/glew-2.2.0.zip


______________________________
Install GLEW-2.2.0
------------------------------

make
sudo make install
make clean




======================================================================
Development: Build and Run
======================================================================


To build a development version,

	./run/build.sh

To run the development version,

	./out/wizl.out

To rebuild and run right after,

	./run/buildrun.sh



