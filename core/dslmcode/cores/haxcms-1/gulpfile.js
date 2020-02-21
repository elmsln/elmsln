const gulp = require('gulp');
const terser = require('gulp-terser');
gulp.task(
  "default", async () => {
    // not sure why but polymer isn't picked up unless we do this
    await gulp.src('./build/es6/node_modules/@polymer/polymer/**/*.js')
      .pipe(terser({
        ecma: 2017,
        keep_fnames: true,
        mangle: false,
        module: true,
      }))
      .pipe(gulp.dest('./build/es6/node_modules/@polymer/polymer/'));
    // now work on all the other files
    await gulp.src('./build/es6/**/*.js')
      .pipe(terser({
        ecma: 2017,
        keep_fnames: true,
        mangle: false,
        module: true,
      }))
      .pipe(gulp.dest('./build/es6/'));
    // not sure why but polymer isn't picked up unless we do this
    await gulp.src('./build/es6-amd/node_modules/@polymer/polymer/**/*.js')
      .pipe(terser({
        keep_fnames: true,
        mangle: false,
        module: true,
        safari10: true,
      }))
      .pipe(gulp.dest('./build/es6-amd/node_modules/@polymer/polymer/'));
    // now work on all the other files
    return await gulp.src('./build/es6-amd/**/*.js')
      .pipe(terser({
        keep_fnames: true,
        mangle: false,
        module: true,
        safari10: true,
      }))
      .pipe(gulp.dest('./build/es6-amd/'));
  }
);