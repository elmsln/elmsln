module.exports = function(grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        includePaths: ['bower_components/foundation/scss']
      },
      dist: {
        options: {
          outputStyle: 'compressed'
        },
        files: {
          'css/elmsmedia_foundation_access.css': 'scss/elmsmedia_foundation_access.scss'
        }        
      }
    },   
    // uglify: {
    //   myScripts: {
    //     files: [{
    //         expand: true,
    //         cwd: 'js/',
    //         src: '**.js',
    //         dest: 'js/',
    //         ext: '.min.js'
    //     }]
    //   }
    // },
    svgmin: {
      dist: {
        files: [{
          expand: true,
          cwd: 'icons/faccess-icons/svg',
          src: ['*.svg'],
          dest: 'icons/faccess-icons/source'
        }]
      }
    },
    grunticon: {
      myIcons: {
        files: [{
            expand: true,
            cwd: 'icons/faccess-icons/source',
            src: ['*.svg', '*.png'],
            dest: "icons/faccess-icons/output"
        }],
        options: {
          // Handle your options as you normally would here
          enhanceSVG: true,
          dynamicColorOnly: true
        }
      }
    },
    watch: {
      grunt: { files: ['Gruntfile.js'] },
      sass: {
        files: 'scss/**/*.scss',
        tasks: ['sass']
      }
    }
  });

  grunt.loadNpmTasks('grunt-sass');
  // grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-svgmin');
  grunt.loadNpmTasks('grunt-grunticon');

  // grunt.registerTask('uglify', ['uglify:myScripts']);
  grunt.registerTask('build', ['sass','svgmin','grunticon:myIcons']);
  grunt.registerTask('default', ['build','watch']);
}