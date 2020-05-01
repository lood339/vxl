![VXL](logo1-quant.gif)
## Introduction: What is VXL?
VXL (the Vision-something-Libraries) is a collection of C++ libraries designed for computer vision research and implementation. It was created from TargetJr and the IUE with the aim of making a light, fast and consistent system. VXL is written in ANSI/ISO C++ and is designed to be portable over many platforms. The core libraries in VXL are:

A comprehensive description of the VXL project can be views at https://vxl.github.io/

This repository is for simple compilation in Mac OS.
It only compiles following libraries: vgl, vnl and vpgl in core and supporting libraries.  
Supporting liabaries: 
libclipper.a  libtestlib.a	libvcl.a  
libnetlib.a  	libv3p_netlib.a  	libvcsl.a  


MacOS:  
Assume we are in the directory: /Code  
git clone https://github.com/lood339/vxl.git  
cd vxl  
mkdir build  
cd build  
mkdir vxl_2.0  
cmake -DCMAKE_INSTALL_PREFIX:PATH=/Code/vxl/build/vxl_2.0 ../  
make -j4  
make install   

Then, the head files and library files will be in vxl_2.0  
To use vxl, you have to add two headfile folders

vxl_2.0/include/vxl/core   
vxl_2.0/include/vxl/vcl  

and the library folder

vxl_2.0/lib

In Xcode, add pathes to Header Search Paths, Library Search Paths and Runpath Search Paths  
