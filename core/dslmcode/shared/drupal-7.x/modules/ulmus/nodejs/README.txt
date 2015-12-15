Node.js integration
===================

This module adds Node.js integration to Drupal.

Setup
=====

1. Install Node.js.

1a. Install from a package manager:

https://github.com/joyent/node/wiki/Installing-Node.js-via-package-manager

1b. Install from the Node.js project website:

http://nodejs.org/download/

2. Install required Node.js modules with the Node Package Manager (NPM).

Make sure you are in the nodejs module directory - NPM needs the package.json
file that comes with the nodejs module to install the right modules.

    cd path/to/your/nodejs/module/directory
    npm install

3. Create a 'nodejs.config.js' file in your nodejs module directory.

Read the 'nodejs.config.js.example' file. A basic configuration can be as simple as:

    settings = {
      host: '*',
      resource: '/socket.io',
      serviceKey: 'CHANGE ME',
      backend: {
        port: 80,
        host: 'changeme.example.com',
      },
      debug: true,
      transports: ['polling', 'websocket']
    };

Set debug to false when you are happy with your setup.

4. Run the node server with the command:

    node server.js

To get a bunch of debug information, run server.js like this:

    DEBUG=* node server.js

