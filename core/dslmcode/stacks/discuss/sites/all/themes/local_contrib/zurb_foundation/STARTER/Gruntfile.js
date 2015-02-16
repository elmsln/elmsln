module.exports = function(grunt) {
  require('load-grunt-tasks')(grunt);

  var theme_name = 'STARTER';
  var base_theme_path = '../zurb_foundation';

  var global_vars = {
    theme_name: theme_name,
    theme_css: 'css',
    theme_scss: 'scss',
    base_theme_path: base_theme_path
  };

  var bourbon = require('node-bourbon').includePaths;

  // array of javascript libraries to include.
  var jsLibs = [
    '<%= global_vars.base_theme_path %>/js/vendor/placeholder.js',
    '<%= global_vars.base_theme_path %>/js/vendor/fastclick.js'
  ];

  // array of foundation javascript components to include.
  var jsFoundation = [
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.abide.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.accordion.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.alert.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.clearing.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.dropdown.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.equalizer.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.interchange.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.joyride.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.magellan.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.offcanvas.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.orbit.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.reveal.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.slider.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.tab.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.tooltip.js',
    '<%= global_vars.base_theme_path %>/js/foundation/foundation.topbar.js'
  ];

  // array of custom javascript files to include.
  var jsApp = [
    'js/_*.js'
  ];

  grunt.initConfig({
    global_vars: global_vars,
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      dist: {
        options: {
          outputStyle: 'compressed',
          includePaths: ['<%= global_vars.theme_scss %>', '<%= global_vars.base_theme_path %>/scss/'].concat(bourbon)
        },
        files: {
          '<%= global_vars.theme_css %>/<%= global_vars.theme_name %>.css': '<%= global_vars.theme_scss %>/<%= global_vars.theme_name %>.scss'
        }
      }
    },

    jshint: {
      options: {
        jshintrc: '.jshintrc'
      },
      all: [
        'Gruntfile.js',
        jsApp
      ]
    },

    uglify: {
      options: {
        sourceMap: false
      },
      dist: {
        files: {
          'js/libs.min.js': [jsLibs],
          'js/foundation.min.js': [jsFoundation],
          'js/app.min.js': [jsApp]
      }
      }
    },

    watch: {
      grunt: { files: ['Gruntfile.js'] },

      sass: {
        files: '<%= global_vars.theme_scss %>/**/*.scss',
        tasks: ['sass'],
        options: {
          livereload: true
        }
      },

      js: {
        files: [
          jsLibs,
          jsFoundation,
          '<%= jshint.all %>'
        ],
        tasks: ['jshint', 'uglify']
      }
    }
  });

  grunt.registerTask('build', ['jshint','uglify','sass']);
  grunt.registerTask('default', ['build', 'watch']);
};