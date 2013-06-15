Module for Fib use in web browsers with JavaScript
==================================================

path: ./add_ons/webbrowser/javascript/

This folder contains the module for using Fib objects in web browsers with
JavaScript.
For this, in the sub directory "lib" two JavaScript libraries are created
(>make), which contain the basic functionality to load and evaluate Fib objects.
The libraries are the same, except that "libfib_dbg.js" contains code to
output debugging information for the Fib object. So with "libfib_dbg.js" it
is more easy to find bugs in Fib objects (e. g. where loading the Fib object
or evaluating it fails).

This libraries can be used for HTML pages.

The sub directory "test" contains examples, how the libraries can be used
to use Fib objects in web pages. (Note: Because of file loading issues, the
web pages and the Fib object files should be online, on the same domain.)


The module makes use of emscripten (see http://github.com/kripken/emscripten),
so it has to be installed in order to run make.

Also you have to provide the Fib database (the folder "fibDatabase"), with
the Fib objects needed, if you make use of it. So the "fibDatabase" folder
with the used database files should be accessible for your web application
(copy the folder "fibDatabase" from "fib/" into the folder of the web
application).