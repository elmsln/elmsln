/*global require:true*/
/*global module:true*/
/*global process:true*/
/*global __dirname:true*/
(function(){
	"use strict";

	var RSVP = require( 'rsvp' );
	var fs = require( 'fs-extra' );
	var path = require( 'path' );

	var workerFarm = require( '@filamentgroup/worker-farm' );
	var workers = workerFarm(require.resolve( path.join( __dirname, "convert" ) ) );

	RSVP.on( 'error', function(err){
		process.stderr.write( err.stack );
	});

	var colorsRegx = /\.colors\-([^\.]+)/i;

	var isColorWord = function( val ){
		var acceptable = ["black","silver","gray","white","maroon","red","purple","fuchsia","green","lime","olive","yellow","navy","blue","teal","aqua","aliceblue","antiquewhite","aqua","aquamarine","azure","beige","bisque","black","blanchedalmond","blue","blueviolet","brown","burlywood","cadetblue","chartreuse","chocolate","coral","cornflowerblue","cornsilk","crimson","cyan","darkblue","darkcyan","darkgoldenrod","darkgray","darkgreen","darkgrey","darkkhaki","darkmagenta","darkolivegreen","darkorange","darkorchid","darkred","darksalmon","darkseagreen","darkslateblue","darkslategray","darkslategrey","darkturquoise","darkviolet","deeppink","deepskyblue","dimgray","dimgrey","dodgerblue","firebrick","floralwhite","forestgreen","fuchsia","gainsboro","ghostwhite","gold","goldenrod","gray","green","greenyellow","grey","honeydew","hotpink","indianred","indigo","ivory","khaki","lavender","lavenderblush","lawngreen","lemonchiffon","lightblue","lightcoral","lightcyan","lightgoldenrodyellow","lightgray","lightgreen","lightgrey","lightpink","lightsalmon","lightseagreen","lightskyblue","lightslategray","lightslategrey","lightsteelblue","lightyellow","lime","limegreen","linen","magenta","maroon","mediumaquamarine","mediumblue","mediumorchid","mediumpurple","mediumseagreen","mediumslateblue","mediumspringgreen","mediumturquoise","mediumvioletred","midnightblue","mintcream","mistyrose","moccasin","navajowhite","navy","oldlace","olive","olivedrab","orange","orangered","orchid","palegoldenrod","palegreen","paleturquoise","palevioletred","papayawhip","peachpuff","peru","pink","plum","powderblue","purple","red","rosybrown","royalblue","saddlebrown","salmon","sandybrown","seagreen","seashell","sienna","silver","skyblue","slateblue","slategray","slategrey","snow","springgreen","steelblue","tan","teal","thistle","tomato","turquoise","violet","wheat","white","whitesmoke","yellow","yellowgreen"];
		return acceptable.indexOf( val ) > -1;
	};
	// test if value is a valid hex
	var isHex = function( val ){
		return (/^[0-9a-f]{3}(?:[0-9a-f]{3})?$/i).test( val );
	};


	var Colorfy = function( filepath, extraColors, opts ){
		opts = opts || {};

		var colors = this._getColorConfig( filepath, extraColors );

		this.originalContents = fs.readFileSync( filepath ).toString( 'utf-8' );
		this.originalFilepath = filepath.replace( colorsRegx, "" );
		this.originalFilename = path.basename( this.originalFilepath );
		this.ofnNoExt = path.basename( this.originalFilepath, path.extname(this.originalFilepath) );
		this.filepath = filepath;
		this.extraColors = extraColors;
		this.colors = colors;
		this.colornames = Object.keys(this.colors);
		this.colorFiles = {};
		this.dynamicColorOnly = opts.dynamicColorOnly;
	};


	Colorfy.prototype.writeFiles = function( destFolder, colorFiles ){
		destFolder = destFolder || "";
		colorFiles = colorFiles || this.colorFiles;
		var filesWritten = [];

		if( !fs.existsSync( destFolder ) ){
			fs.mkdirpSync( destFolder );
		}
		if (this.dynamicColorOnly !== true) {
			fs.writeFileSync( path.join( destFolder, this.originalFilename ), this.originalContents );
		}

		for (var filepath in colorFiles) {
			if (colorFiles.hasOwnProperty(filepath)) {
				fs.writeFileSync( path.join( destFolder, filepath ), colorFiles[ filepath ] );
				filesWritten.push( path.join( destFolder, filepath ) );
			}
		}

		return filesWritten;
	};

	var _convert = function( colors, originalFilepath, ofnNoExt, originalContents, callback ){
		var color = "",
			newFilePath = "",
			newFilename = "";
		var files = [];
		workerFarm.revive(workers);

		for( var name in colors ){
			if( colors.hasOwnProperty(name) ){
				color = colors[name];

				newFilePath = path.join( path.dirname( originalFilepath ), ofnNoExt + "-" + name + path.extname( originalFilepath ) );
				newFilename = path.basename( newFilePath );


				files.push({
					contents: originalContents,
					name: newFilename,
					color: color
				});
			}
		}

		var contents = [];


		var endWorkers = function(err) {
			// kill child processes
			var result = workerFarm.end(workers, function() {
				callback(err, 'done');
			});

			// worker end returns early if the workers are already killed
			//
			if( result === false ){
				callback(err, 'done');
			}
		};


		var handler = function( err, output ){
			if( err ){
				endWorkers( err );
			} else {
				contents.push( output );

				if( contents.length === files.length ){
					callback(null, contents);
					endWorkers( null );
				}
			}
		};

		if( files.length === 0 ){
			callback(null, contents);
			callback(null, 'done');
		} else {
			files.forEach(function( file ){
				workers( file.contents, file.name, file.color, handler );
			});
		}
	};

	Colorfy.prototype.getConvertedFiles = function( callback ){
		_convert( this.colors, this.originalFilepath, this.ofnNoExt, this.originalContents, function(err, contents){
			if( err ){
				callback( err, null );
			} else {
				callback( null, contents );
			}
		});
	};

	Colorfy.convert = function( colorfied, colors, originalFilepath, ofnNoExt, originalContents, handlers ){
		_convert( colors, originalFilepath, ofnNoExt, originalContents, function( self, err, contents){
			if( err ){
				handlers.collect( err, null );
			} else {
				if( contents === 'done' ){
					handlers.complete();
					return;
				}

				contents.forEach(function(newFile){
					var key = Object.keys( newFile )[0];
					self.colorFiles[ key ] = newFile[ key ];
				});

				handlers.collect( null, self );
			}
		}.bind( null, colorfied ), handlers);
	};

	Colorfy.prototype.convert = function( handlers ){
		Colorfy.convert( this, this.colors, this.originalFilepath, this.ofnNoExt, this.originalContents, handlers );
	};

	Colorfy.prototype._getColorConfig = function( str, extraColors ){
		extraColors = extraColors || {};

		var colors = str.match( colorsRegx ), colorObj = {};

		if( colors ){
			colors = colors[ 1 ].split( "-" );
			colors.forEach( function( color, i ){
				if( extraColors[ color ] ){
					colorObj[ color ] = extraColors[ color ];
				} else if( isHex( color ) ){
					colorObj[ i ] = "#" + color;
				} else if( isColorWord( color ) ){
					colorObj[ color ] = color;
				}
			});
			return colorObj;
		}
		else {
			return colorObj;
		}
	}; //getColorConfig



	module.exports = Colorfy;
}());
