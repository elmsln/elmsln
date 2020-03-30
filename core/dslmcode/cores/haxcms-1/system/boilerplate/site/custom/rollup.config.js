// @ts-nocheck
const { terser } = require('rollup-plugin-terser');
const rewriteImports = require('rollup-plugin-rewrite-imports');
const production = true;
module.exports = function() {
  return {
    input: 'src/custom.js',
    treeshake: !!production,
    output: {
      file: `build/custom.es6.js`,
      format: 'esm',
      sourcemap: false,
    },
    plugins: [
      rewriteImports(`../../build/es6/node_modules/`),
      // only minify if in production
      production && terser(),
    ],
  };
};