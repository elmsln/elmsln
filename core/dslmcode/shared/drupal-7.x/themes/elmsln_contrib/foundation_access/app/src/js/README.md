# Javascript Files

We would like the ability to compile everything all of our custom javascript and dependancies into a single file so that it makes it easier to include the javascript file in our pages. To do that, we are leveraging [Browserify](http://browserify.org/).

To add a bower installed library:
```
var eqjs = require('../../bower_components/eq.js/dist/eq.min.js');
```

To add a browserify library:
```
var waypoints = require('waypoints');
```
