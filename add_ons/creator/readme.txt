
Fib creator
===========

In this folder the Fib creator submodul.
It is an application, with a grapical user interface, for creating and
changing Fib objects.


Compile
-------

>qmake fibCreator.pro
>make


The compiling process will need the Fib language library.
To create them you need to compile the fib language subsystem.
Go to the directory fib and call:
>make
>make test


Create localization
-------------------

To initializise the translation/localization run:
>lupdate fibCreator.pro
This will crerate the needed translation/localization in the subfolder
"translations".

Now you can provide the translations for the different languages (e. g.
with QT Linguist).

Then call:
>lrelease fibCreator.pro
to produce QM files out of TS files.
And copy these from the "translations" directory into the directory of the
executable (e. g. "bin/"):
>cp translations/*qm bin/


The translation process in short:

lupdate fibCreator.pro
linguist translations/*ts
lrelease fibCreator.pro
cp translations/*qm bin/


