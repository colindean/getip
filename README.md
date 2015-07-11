GetIP
====

Get the IP for the specified interface.

Building
--------

    make

Usage
-----

    ./getip interface

E.g.

    $ ./getip eth0
    192.168.1.100
    $

Alternatively, you can attempt to run `getip.c` directly as a script. It will be
compiled and stored in your `$TMPDIR`, only recompiling when it has been
changed or is absent.

    ./getip.c

License
-------
[![](http://i.creativecommons.org/p/zero/1.0/88x31.png)](http://creativecommons.org/publicdomain/zero/1.0/)

To the extent possible under law, @colindean has waived all copyright and
related or neighboring rights to getip.
