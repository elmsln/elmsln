module.exports = function(grunt) {
  "use strict";

  var theme_name = 'STARTER';

  var global_vars = {
    theme_name: theme_name,
    theme_css: 'css',
    theme_scss: 'scss'
  }

  grunt.initConfig({
    global_vars: global_vars,
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      dist: {
        options: {
          outputStyle: 'compressed',
          includePaths: ['<%= global_vars.theme_scss %>', require('node-bourbon').includePaths]
        },
        files: {
          '<%= global_vars.theme_css %>/<%= global_vars.theme_name %>.css': '<%= global_vars.theme_scss %>/<%= global_vars.theme_name %>.scss'
        }
      }
    },

    copy: {
      dist: {
        files: [
          {expand:true, cwd: 'bower_components/foundation/js', src: ['foundation/*.js'], dest: 'js/', filter: 'isFile'},
          {expand:true, cwd: 'bower_components/foundation/', src: ['foundation.min.js'], dest: 'js/', filter: 'isFile'},
          {expand:true, cwd: 'bower_components/foundation/js/vendor', src: ['fastclick.js'], dest: 'js/vendor', filter: 'isFile'},
          {expand:true, cwd: 'bower_components/foundation/js/vendor', src: ['jquery.cookie.js'], dest: 'js/vendor', filter: 'isFile'},
          {expand:true, cwd: 'bower_components/foundation/js/vendor', src: ['modernizr.js'], dest: 'js/vendor', filter: 'isFile'},
          {expand:true, cwd: 'bower_components/foundation/scss/foundation/components', src: '**/*.scss', dest: 'scss/vendor/foundation/components', filter: 'isFile'},
          {expand:true, cwd: 'bower_components/foundation/scss/foundation', src: '_functions.scss', dest: 'scss/vendor/foundation', filter: 'isFile'},
        ]
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
      }
    }
  });

  grunt.loadNpmTasks('grunt-sass');
  grunt.loadNpmTasks('grunt-contrib-copy');
  grunt.loadNpmTasks('grunt-contrib-watch');

  grunt.registerTask('build', ['sass', 'copy']);
  grunt.registerTask('default', ['build', 'watch']);
}