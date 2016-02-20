pyfreenect2
===========

Python bindings to [libfreenect2](https://github.com/OpenKinect/libfreenect2).

Requirements
---------

- Python3 (python2 support : https://github.com/remexre/pyfreenect2)
- Numpy
- Scipy (as appropriated by python version) : 
- Python Imaging Library (used for scipy.misc.im* functions) : http://www.pythonware.com/products/pil/
- OpenCV

Installation
---------

To install, run `sudo python setup.py install`.

Usage
---------

For usage, see `test.py`.


TODO List
---------
 * ~~Make `test.py` actually display the frames~~
 * Implement Registration.apply (in py_Registration_apply)
 * Make the pipeline argument of Freenect2Device's constructor actually do something
 * Test everything

