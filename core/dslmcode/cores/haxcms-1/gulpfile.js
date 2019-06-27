const gulp = require('gulp');
const terser = require('gulp-terser');
gulp.task(
  "default", async () => {
    // not sure why but polymer isn't picked up unless we do this
    await gulp.src('./build/es6/node_modules/@polymer/polymer/**/*.js')
      .pipe(terser({
        keep_fnames: true,
        mangle: false,
        compress: true,
        module: true
      }))
      .pipe(gulp.dest('./build/es6/node_modules/@polymer/polymer/'));
    // now work on all the other files
    return await gulp.src('./build/es6/**/*.js')
      .pipe(terser({
        keep_fnames: true,
        mangle: false,
        compress: true,
        module: true
      }))
      .pipe(gulp.dest('./build/es6/'));
  }
);