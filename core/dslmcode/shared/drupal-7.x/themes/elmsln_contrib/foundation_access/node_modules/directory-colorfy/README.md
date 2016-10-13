# directory-colorfy [![Build Status](https://secure.travis-ci.org/filamentgroup/directory-colorfy.png?branch=master)](http://travis-ci.org/filamentgroup/directory-colorfy)

[![Filament Group](http://filamentgroup.com/images/fg-logo-positive-sm-crop.png) ](http://www.filamentgroup.com/)

Color up those SVGs

## Getting Started
Install the module with: `npm install directory-colorfy`

```javascript
var DirectoryColorfy = require('directory-colorfy');
var dc = new DirectoryColorfy( input, output, options );
dc.convert()
.then(function(){
// Next
});
```

## Documentation

### Required Params

#### Input
Type: `String`

Input folder of SVGs

#### Output
Type: `String`

Output folder


### Optional Params

#### options.colors
Type: `Object`
Default value: `{}`

A hash of colors to pass in with names.

Example:
```
{ "primary": "#ff0000" }
```

#### options.dynamicColorOnly
Type: `Boolean`
Default value: `false`

Allows you to tell directory-colorfy to ignore the original file when using colors.

For example, if given a file named like so: 

```
bear.colors-white.svg
```

And `dynamicColorOnly` is set to `true`:

```
{
	dynamicColorOnly: true
}
```

Only a single file will be generated:

```
bear-white.svg
```

## Examples

If the input directory has this file in it:

```
bear.colors-primary-blue-red.svg
```

And the color hash that is passed through is:

```
{ "primary": "green" }
```

The output folder should end up with:

```
bear-green.svg
bear-blue.svg
bear-red.svg
```

Which will all be completely filled in with their specific color.


## Contributing
In lieu of a formal styleguide, take care to maintain the existing coding style. Add unit tests for any new or changed functionality. Lint and test your code using [Grunt](http://gruntjs.com/).

## Release History
* 1.0.0 Make `convert` return a promise. Also, change from putting stylesheet in to just changing the `fill` and `stroke` attributes
* 0.4.0 Make sure custom color words override actual color words (e.g.
	red)
* 0.3.0 Make sure custom color words (e.g. primary, secondary) are
	acknowledged
* 0.2.0 No longer needs a dir as an input, can also take an array of files
* 0.1.0 First release

## License
Copyright (c) 2013 Jeffrey Lembeck & Filament Group  
Licensed under the MIT license.
