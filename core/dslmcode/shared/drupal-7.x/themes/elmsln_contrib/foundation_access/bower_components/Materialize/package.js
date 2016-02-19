// package metadata file for Meteor.js

Package.describe({
  name: 'materialize:materialize',  // http://atmospherejs.com/materialize/materialize
  summary: 'Materialize (official): A modern responsive front-end framework based on Material Design',
<<<<<<< e65c74aae289a769861e434ed793b68185dc8ac0
  version: '0.97.6',
=======
  version: '0.97.5',
>>>>>>> Starting point for Materialize.
  git: 'https://github.com/Dogfalo/materialize.git'
});

Package.onUse(function (api) {
  api.versionsFrom('METEOR@1.0');

  api.use('jquery', 'client');
  api.imply('jquery', 'client');

  var assets = [
<<<<<<< e65c74aae289a769861e434ed793b68185dc8ac0
    'dist/fonts/roboto/Roboto-Bold.ttf',
    'dist/fonts/roboto/Roboto-Bold.woff',
    'dist/fonts/roboto/Roboto-Bold.woff2',
    'dist/fonts/roboto/Roboto-Light.ttf',
    'dist/fonts/roboto/Roboto-Light.woff',
    'dist/fonts/roboto/Roboto-Light.woff2',
    'dist/fonts/roboto/Roboto-Medium.ttf',
    'dist/fonts/roboto/Roboto-Medium.woff',
    'dist/fonts/roboto/Roboto-Medium.woff2',
    'dist/fonts/roboto/Roboto-Regular.ttf',
    'dist/fonts/roboto/Roboto-Regular.woff',
    'dist/fonts/roboto/Roboto-Regular.woff2',
    'dist/fonts/roboto/Roboto-Thin.ttf',
    'dist/fonts/roboto/Roboto-Thin.woff',
    'dist/fonts/roboto/Roboto-Thin.woff2',
=======
    'dist/font/material-design-icons/Material-Design-Icons.eot',
    'dist/font/material-design-icons/Material-Design-Icons.svg',
    'dist/font/material-design-icons/Material-Design-Icons.ttf',
    'dist/font/material-design-icons/Material-Design-Icons.woff',
    'dist/font/material-design-icons/Material-Design-Icons.woff2',
    'dist/font/roboto/Roboto-Bold.ttf',
    'dist/font/roboto/Roboto-Bold.woff',
    'dist/font/roboto/Roboto-Bold.woff2',
    'dist/font/roboto/Roboto-Light.ttf',
    'dist/font/roboto/Roboto-Light.woff',
    'dist/font/roboto/Roboto-Light.woff2',
    'dist/font/roboto/Roboto-Medium.ttf',
    'dist/font/roboto/Roboto-Medium.woff',
    'dist/font/roboto/Roboto-Medium.woff2',
    'dist/font/roboto/Roboto-Regular.ttf',
    'dist/font/roboto/Roboto-Regular.woff',
    'dist/font/roboto/Roboto-Regular.woff2',
    'dist/font/roboto/Roboto-Thin.ttf',
    'dist/font/roboto/Roboto-Thin.woff',
    'dist/font/roboto/Roboto-Thin.woff2',
>>>>>>> Starting point for Materialize.
  ];

  addAssets(api, assets);
  
  api.addFiles([
    'dist/js/materialize.js',
    'dist/css/materialize.css'
  ], 'client');

  api.export('Materialize', 'client');
});


function addAssets(api, assets){
  if(api.addAssets){
    api.addAssets(assets, 'client');
  } else {
    api.addFiles(assets, 'client', {isAsset: true});
  }
}
