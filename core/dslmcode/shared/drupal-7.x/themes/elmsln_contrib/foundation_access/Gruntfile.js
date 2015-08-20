module.exports = function(grunt) {
  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    sass: {
      options: {
        includePaths: ['bower_components/foundation/scss']
      },
      dist: {
        files: {
          'css/app.css': 'scss/app.scss'
        }
      }
    },
    autoprefixer: {
  		options: {
  			browsers: ['last 2 versions', 'ie 8', 'ie 9']
  		},
  		dist:{
  			files:{
  			  'css/app.css':'css/app.css'
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
        tasks: ['sass', 'autoprefixer']
      }
    }
  });

  grunt.loadNpmTasks('grunt-sass');
  // grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-svgmin');
  grunt.loadNpmTasks('grunt-grunticon');
  grunt.loadNpmTasks('grunt-autoprefixer');

  // grunt.registerTask('uglify', ['uglify:myScripts']);
  grunt.registerTask('build', ['sass','autoprefixer','svgmin','grunticon:myIcons']);
  grunt.registerTask('default', ['build','watch']);
}
