# Load balancing/Handover algorithm for cellular/WLAN integrated networks using Data Analytics

This project aims to create proper scenario in order to investigate load balacing and handover for cellular/WLAN integrated networks. Therefore, once we have the scenario that we desired we'll be able to treat, understand and propose new ideas by analyzing the data and using data analystics/machine learning techniques. 

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

The core of ns-3 requires a gcc/g++ installation of 4.9 or greater (Linux), or a recent version of clang compiler (OS X, Linux, or BSD), and Python 2.7 or greater.
Please follow: [ns-3 prerequisites](https://www.nsnam.org/wiki/Installation#Prerequisites)
After that, check if everything is okay:
```
python bake.py check
```

### Installing 
Building ns-3:
```
./waf configure --enable-examples
./waf
```

### Example
Running one example file:
```
cd ns-3.29/
./test.py 
cp examples/tutorial/second.cc scratch/
./waf --run scratch/second
```

## ns-3 notes
This is ns-3-allinone.

If you have downloaded this in tarball release format, this directory
contains some released ns-3 version, along with 3rd party components
necessary to support all optional ns-3 features, such as Python
bindings and the Network Animator.  In this case, just run the
script build.py; all the components, plus ns-3 itself, will thus be
built.  This directory also contains the bake build tool, which allows
access to several additional modules including the Network Simulation
Cradle, Direct Code Execution environment, and click and openflow 
extensions for ns-3.

If you have downloaded this from mercurial, the download.py script will
download bake, netanim, pybindgen, and ns-3-dev.  The usage to use
basic ns-3 (netanim and ns-3-dev) is to type:
./download.py
./build.py
and cd into ns-3-dev for further work.  Consult the bake documentation
on how to use bake to access optional ns-3 components.
