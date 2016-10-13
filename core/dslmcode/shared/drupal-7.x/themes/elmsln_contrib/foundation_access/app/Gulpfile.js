'use strict';

var gulp = require('gulp');
var sass = require('gulp-sass');
var sourcemaps = require('gulp-sourcemaps');
var jshint = require('gulp-jshint');
var stylish = require('jshint-stylish');
var browserSync = require('browser-sync');
var reload = browserSync.reload;
var shell = require('gulp-shell');
var prefix = require('gulp-autoprefixer');
var plumber = require('gulp-plumber');
var mainBowerFiles = require('main-bower-files');
var filter = require('gulp-filter');
var concat = require('gulp-concat');
var uglify = require('gulp-uglify');
var uglifyjs = require('gulp-uglifyjs');
var cssmin = require('gulp-minify-css');
var sassGlob = require('gulp-sass-glob');
var source = require('vinyl-source-stream');
var browserify = require('browserify');
var imagemin = require('gulp-imagemin');

var filterByExtension = function(extension){
  return filter(function(file){
    return file.path.match(new RegExp('.' + extension + '$'));
  });
};

gulp.task('sass', function() {
  return gulp.src('./src/sass/**/**/*.scss')
    .pipe(plumber({
      errorHandler: function (error) {
        console.log(error.message);
        this.emit('end');
    }}))
    .pipe(sassGlob())
    .pipe(sourcemaps.init())
    .pipe(sass().on('error', sass.logError))
    .pipe(prefix({browsers: ['last 4 versions']}))
    .pipe(sourcemaps.write())
    .pipe(gulp.dest('./dist/css'));
});

gulp.task('watch', function() {
  gulp.watch('src/sass/**/*.scss', ['sass']);
  gulp.watch(['src/js/**/**.js'], ['js']);
  gulp.watch(['src/images/*'], ['images']);
});

gulp.task('js', function () {
  // We are going to concatinate all of the partials
  // into the scripts.js file.
  var jsFiles = ['./src/js/**/**/**/**/*.js'];

  // Concat modules together
  gulp.src(jsFiles)
    .pipe(plumber({
      errorHandler: function (error) {
        console.log(error.message);
        this.emit('end');
    }}))
    .pipe(jshint('.jshintrc'))
    .pipe(jshint.reporter('jshint-stylish'))
    .pipe(browserify('./src/js/scripts.js').bundle())
    .pipe(source('scripts.js'))
    .pipe(gulp.dest('./dist/js'));
});

// Consolidate all of our bower dependancies into single js and css files.
gulp.task('bowerdependancies', function(){
  var mainFiles = mainBowerFiles();

  if(!mainFiles.length){
    // No main files found. Skipping....
    return;
  }

  var jsFilter = filterByExtension('js');

  return gulp.src(mainFiles)
    .pipe(jsFilter)
    .pipe(uglify())
    .pipe(concat('third-party.js'))
    .pipe(gulp.dest('./dist/js/'))
    .pipe(jsFilter.restore())
    .pipe(filterByExtension('css'))
    .pipe(cssmin())
    .pipe(concat('third-party.css'))
    .pipe(gulp.dest('./dist/css/'));
});

gulp.task('images', function () {
  return gulp.src("src/images/**.*")
    .pipe(imagemin([], {"verbose": false}))
    .pipe(gulp.dest("dist/images"));
});

//////////////////////////////
// BrowserSync Tasks
//////////////////////////////
gulp.task('browserSync', function () {
  browserSync.init([
    'dist/**/**',
    'fonts/**/*',
    './**/*.html',
  ]);
});

//////////////////////////////
// Server Tasks
//////////////////////////////
gulp.task('build', ['js', 'images', 'bowerdependancies']);
gulp.task('server', ['watch', 'browserSync', 'js', 'sass', 'bowerdependancies', 'images']);
gulp.task('default', ['watch', 'js', 'sass', 'bowerdependancies', 'images']);
