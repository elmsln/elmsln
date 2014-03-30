### Requirements

Modules:
* Ctools
* Libraries
* jQuery Update

jQuery update is required so that jQuery 1.7 is available to Caret.js & At.js, it won't work without it! This will require you configuring jQuery update at:
/admin/config/development/jquery_update

#### Installation

To get things going you'll need to install both Caret.js and At.js into the libraries dir in your install, normally sites/all/libraries.

Download both Caret.js and At.js from the releases page (links below) and rename and move them into the libraries dir lowercased with the version suffix removed.

https://github.com/ichord/Caret.js/releases
https://github.com/ichord/At.js/releases

Your structure should look like:
sites/all/libraries/caret.js
sites/all/libraries/at.js

Both folders should have an "src" folder within which contains the JavaScript files, for example:
sites/all/libraries/caret.js/src/jquery.caret.js
