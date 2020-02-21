// @ts-nocheck
const rewriteImports = require('rollup-plugin-rewrite-imports');
const production = true;
module.exports = function() {
  return {
    input: 'src/custom.js',
    treeshake: !!production,
    output: {
      file: `build/custom.es6-amd.js`,
      format: 'esm',
      sourcemap: false,
    },
    plugins: [
      rewriteImports(`../../build/es6-amd/node_modules/`),
    ],
  };
};