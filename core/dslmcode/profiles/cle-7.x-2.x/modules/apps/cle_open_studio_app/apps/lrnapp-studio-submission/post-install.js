var glob = require("glob");
var fs = require("fs");
var replace = require("replace-in-file");
var options = {
	files: [
		'bower_components/**/*.html'
	],
	from: [
		/<link .*polymer.html\W>/g,
		/<link .*iron-meta.html\W>/g
	],
	to: ' '
};

replace(options)
  .then(changedFiles => {
    console.log('Modified files:', changedFiles.join(', '));
  })
  .catch(error => {
    console.error('Error occurred:', error);
  });
