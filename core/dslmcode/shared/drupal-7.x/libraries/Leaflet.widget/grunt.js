/*global module:false*/
module.exports = function(grunt) {

  grunt.loadNpmTasks('grunt-css');

  // Project configuration.
  grunt.initConfig({
    pkg: '<json:package.json>',
    meta: {
      banner: '/*! <%= pkg.title || pkg.name %> - v<%= pkg.version %> - ' +
        '<%= grunt.template.today("yyyy-mm-dd") %>\n' +
        '<%= pkg.homepage ? "* " + pkg.homepage + "\n" : "" %>' +
        '* Copyright (c) <%= grunt.template.today("yyyy") %> <%= pkg.author %>\n' +
        '* Licensed <%= _.pluck(pkg.licenses, "type").join(", ") %> */'
    },
    lint: {
      files: ['grunt.js', 'src/**/*.js', 'test/**/*.js']
    },
    qunit: {
      files: ['test/**/*.html']
    },
    concat: {
      dist: {
        src: [
          '<banner:meta.banner>',
          '<file_strip_banner:src/util/GeoJSONUtil.js>',
          '<file_strip_banner:src/layer/WidgetFeatureGroup.js>',
          '<file_strip_banner:src/layer/Path.js>',
          '<file_strip_banner:src/layer/FeatureGroup.js>',
          '<file_strip_banner:src/layer/Marker.js>',
          '<file_strip_banner:src/layer/Polyline.js>',
          '<file_strip_banner:src/layer/Polygon.js>',
          '<file_strip_banner:src/layer/MultiPolyLine.js>',
          '<file_strip_banner:src/layer/MultiPolygon.js>',
          '<file_strip_banner:src/Select.js>',
          '<file_strip_banner:src/Widget.js>'
        ],
        dest: 'dist/<%= pkg.name %>.js'
      }
    },
    min: {
      dist: {
        src: ['<banner:meta.banner>', '<config:concat.dist.dest>'],
        dest: 'dist/<%= pkg.name %>.min.js'
      }
    },
    cssmin: {
      dist: {
        src: ['<banner:meta.banner', '<file_strip_banner:dist/<%= pkg.name %>.css>', '<file_strip_banner:dist/Leaflet.select.css>'],
        dest: 'dist/<%= pkg.name %>.min.css'
      }
    },
    watch: {
      files: '<config:lint.files>',
      tasks: 'lint qunit'
    },
    jshint: {
      options: {
        curly: true,
        eqeqeq: true,
        immed: true,
        latedef: true,
        newcap: true,
        noarg: true,
        sub: true,
        undef: true,
        boss: true,
        eqnull: true,
        browser: true
      },
      globals: {
        L: true
      }
    },
    uglify: {}
  });

  // Default task.
  grunt.registerTask('default', 'lint qunit concat min cssmin');

};
