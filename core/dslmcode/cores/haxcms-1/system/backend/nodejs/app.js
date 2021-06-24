// lib dependencies
const express = require('express');
const bodyParser = require('body-parser');
const fileUpload = require('express-fileupload');
const cookieParser = require('cookie-parser');
const helmet = require('helmet');
const app = express();
const server = require('http').Server(app);
// HAXcms core settings
const HAXCMS = require('./lib/HAXCMS.js');
// app settings
const port = 3000;
app.use(helmet({
  contentSecurityPolicy: false
}));
app.use(cookieParser());
app.use(fileUpload());
app.use(express.static("public"))
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use('/', (req, res, next) => {
  res.setHeader('Access-Control-Allow-Origin', 'http://localhost:8080');
	res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS, PUT, PATCH, DELETE');
  res.setHeader('Access-Control-Allow-Headers', 'X-Requested-With, Content-Type, Accept');
  res.setHeader('Content-Type', 'application/json');
  next();
});
// sites need rewriting to work with PWA routes without failing file location
// similar to htaccess
app.use('/sites/',(req, res) => {
  // previous will catch as json, undo that
  res.setHeader('Content-Type', 'text/html');
  // send file for the index even tho route says it's a path not on our file system
  // this way internal routing picks up and loads the correct content while
  // at the same time express has delivered us SOMETHING as the path in the request
  // url doesn't actually exist
  res.sendFile(req.url.replace(/\/(.*?)\/(.*)/, "/sites/$1/index.html"),
  {
    root: __dirname + "/public"
  });
});
//pre-flight requests
app.options('*', function(req, res) {
	res.send(200);
});
// app routes
const routes = {
  post: {
    login: require('./routes/login.js'),
    logout: require('./routes/logout.js'),
    revertCommit: require('./routes/revertCommit.js'),

    formLoad: require('./routes/formLoad.js'),
    formProcess: require('./routes/formProcess.js'),
    getConfig: require('./routes/getConfig.js'),
    setConfig: require('./routes/setConfig.js'),
    getNodeFields: require('./routes/getNodeFields.js'),
    setUserPhoto: require('./routes/setUserPhoto.js'),
    siteUpdateAlternateFormats: require('./routes/siteUpdateAlternateFormats.js'),
    getUserData: require('./routes/getUserData.js'),
    gitImportSite: require('./routes/gitImportSite.js'),
    listFiles: require('./routes/listFiles.js'),
    saveFile: require('./routes/saveFile.js'),
    saveOutline: require('./routes/saveOutline.js'),
    openapi: require('./routes/openapi.js'),

    createSite: require('./routes/createSite.js'),
    syncSite: require('./routes/syncSite.js'),
    publishSite: require('./routes/publishSite.js'),
    cloneSite: require('./routes/cloneSite.js'),
    archiveSite: require('./routes/archiveSite.js'),
    deleteSite: require('./routes/deleteSite.js'),
    downloadSite: require('./routes/downloadSite.js'),

    createNode: require('./routes/createNode.js'),
    saveNode: require('./routes/saveNode.js'),
    deleteNode: require('./routes/deleteNode.js'),
  },
  get: {
    logout: require('./routes/logout.js'),
    refreshAccessToken: require('./routes/refreshAccessToken.js'),
    listSites: require('./routes/listSites.js'),
    connectionSettings: require('./routes/connectionSettings.js'),
    generateAppStore: require('./routes/generateAppStore.js'),
  },
};
// these routes need to return a response without a JWT validation
const openRoutes = [
  'generateAppStore',
  'connectionSettings',
  'listSites',
  'login',
  'logout',
  'api',
  'options',
  'openapi',
  'refreshAccessToken'
];
// loop through methods and apply the route to the file to deliver it
// @todo ensure that we apply the same JWT checking that we do in the PHP side
// instead of a simple array of what to let go through we could put it into our
// routes object above and apply JWT requirement on paths in a better way
for (var method in routes) {
  for (var route in routes[method]) {
    app[method](`${HAXCMS.basePath}${HAXCMS.apiBase}${route}`, (req, res) => {
      const op = req.route.path.replace(`${HAXCMS.basePath}${HAXCMS.apiBase}`, '');
      const rMethod = req.method.toLowerCase();
      if (openRoutes.includes(op) || HAXCMS.validateJWT(req, res)) {
        // call the method
        routes[rMethod][op](req, res);
      }
      else {
        res.sendStatus(403);
      }
    });
  }
}

server.listen(port, (err) => {
	if (err) {
		throw err;
	}
  const open = require('open');
  // opens the url in the default browser 
  open('http://localhost:3000');
	/* eslint-disable no-console */
	console.log('http://localhost:3000');
});