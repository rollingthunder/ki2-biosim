Simple biotope simulator to write AI for characters
========================

This simple project is to be used for teaching an aritifial intelligence lecture.

Most of the AI stuff goes to model::perform_step(), the basic idea is that you need to know little else.


Building
========

We need C++11 compiler. Not a problem with Windows, on Linux/Mac we need a really new version of gcc, e.g., 4.6.3. The better alternative is clang. It is automatically included with XCode or development tools on a Mac and is of a fresh enough version 3.2. Under Linux use your repository system to install clang++, e.g., `apt-get install clang` under Debian and Ubuntu.

Further depencency is wxwidgets toolkit. Use your repository system or `brew` to install it on Linux/Mac. (On Linux you need to install libwxgtkk2.8-dev; merely installing `libwx*-header` and its dependencies does not help in Ubuntu Linux.) Download it and build it yourself under Windows, the URL is http://www.wxwidgets.org/. For building under Windows utilise the provided VisualStudio solution file.

Author
======

This was written by Tobias Werner for usage in the class.

