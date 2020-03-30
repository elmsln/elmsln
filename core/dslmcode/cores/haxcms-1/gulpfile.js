const gulp = require('gulp');
const terser = require('gulp-terser');
gulp.task(
  "default", () => {
    // now work on all the other files
    gulp.src('./build/es6/**/*.js')
    .pipe(terser({
        ecma: 2017,
        keep_fnames: true,
        mangle: true,
        module: true,
      }))
      .pipe(gulp.dest('./build/es6/'));
    // now work on all the other files
    return gulp.src('./build/es6-amd/**/*.js')
    .pipe(terser({
        keep_fnames: true,
        mangle: true,
        module: false,
        safari10: true,
      }))
      .pipe(gulp.dest('./build/es6-amd/'));
  }
);