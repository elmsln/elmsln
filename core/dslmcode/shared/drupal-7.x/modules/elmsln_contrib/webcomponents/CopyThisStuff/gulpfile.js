const gulp = require('gulp');
const terser = require('gulp-terser');
const minifyJSTemplate = require('gulp-minify-html-literals');
gulp.task(
  "default", async () => {
    // now work on all the other files
    await gulp.src('./build/es6/**/*.js')
      .pipe(terser({
        ecma: 2017,
        keep_fnames: true,
        mangle: false,
        module: true,
      }))
      .pipe(minifyJSTemplate())
      .pipe(gulp.dest('./build/es6/'));
    // now work on all the other files
    return await gulp.src('./build/es6-amd/**/*.js')
      .pipe(terser({
        keep_fnames: true,
        mangle: false,
        module: true,
        safari10: true,
      }))
      .pipe(minifyJSTemplate())
      .pipe(gulp.dest('./build/es6-amd/'));
  }
);