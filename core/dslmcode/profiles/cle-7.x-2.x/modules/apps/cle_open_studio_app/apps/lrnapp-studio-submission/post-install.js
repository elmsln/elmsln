var glob = require("glob");
var fs = require("fs");
var replace = require("replace");

// Find file
glob("bower_components/**/*.html",function (err,files) {
	if (err) throw err;
	files.forEach(function (item,index,array){
		console.log(item + " found");
     	// Read file
     	console.log(fs.readFileSync(item,'utf8'));
     	// Replace string
     	replace({
     		regex: "^<import.*polymer.html\W>",
     		replacement: "",
     		paths: [item],
     		recursive: true,
     		silent: true,
     	});
     	console.log("Replacement complete");
          // Read file
     	console.log(fs.readFileSync(item,'utf8'));
      });
});