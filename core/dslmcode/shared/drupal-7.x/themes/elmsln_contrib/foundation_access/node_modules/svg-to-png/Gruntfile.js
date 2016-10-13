/*global require:true*/
'use strict';

module.exports = function(grunt) {

	// Project configuration.
	grunt.initConfig({
		nodeunit: {
			files: ['test/*_test.js']
		},
		qunit: {
			files: ['test/phantom/index.html']
		},
		jshint: {
			options: {
				jshintrc: '.jshintrc'
			},
			gruntfile: {
				src: 'Gruntfile.js'
			},
			lib: {
				src: ['lib/**/*.js', '!lib/rsvp.js']
			},
			test: {
				src: ['test/**/*.js', '!test/phantom/vendor/*.js', '!test/phantom/phantomtest.js']
			},
		},
		watch: {
			gruntfile: {
				files: '<%= jshint.gruntfile.src %>',
				tasks: ['jshint:gruntfile']
			},
			lib: {
				files: '<%= jshint.lib.src %>',
				tasks: ['jshint:lib', 'nodeunit']
			},
			test: {
				files: '<%= jshint.test.src %>',
				tasks: ['jshint:test', 'nodeunit']
			},
		},
	});

	// These plugins provide necessary tasks.
	grunt.loadNpmTasks('grunt-contrib-nodeunit');
	grunt.loadNpmTasks('grunt-contrib-qunit');
	grunt.loadNpmTasks('grunt-contrib-jshint');
	grunt.loadNpmTasks('grunt-contrib-watch');

	grunt.task.registerTask( 'phantom-unit', 'A task to run the phantom tests', function(){
		var done = this.async();
		var phantomUnit = require( 'phantom-unit' );
		phantomUnit.test( "test/phantom/processing-file_test.js", function(){
			done();
		});
	});

	// Default task.
	grunt.registerTask('default', ['jshint', 'nodeunit', 'phantom-unit']);

};
