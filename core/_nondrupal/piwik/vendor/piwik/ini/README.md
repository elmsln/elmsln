# Piwik/Ini

Read and write INI configurations.

[![Build Status](https://img.shields.io/travis/piwik/component-ini.svg?style=flat-square)](https://travis-ci.org/piwik/component-ini)
[![Coverage Status](https://img.shields.io/coveralls/piwik/component-ini/master.svg?style=flat-square)](https://coveralls.io/r/piwik/component-ini?branch=master)
[![Latest Version](https://img.shields.io/github/release/piwik/component-ini.svg?style=flat-square)](https://packagist.org/packages/piwik/component-ini)
[![](https://img.shields.io/packagist/dm/piwik/ini.svg?style=flat-square)](https://packagist.org/packages/piwik/ini)

## Installation

```json
composer require piwik/ini
```

## Why?

PHP provides a `parse_ini_file()` function to read INI files.

This component provides the following benefits over the built-in function:

- allows to write INI files
- classes can be used with dependency injection and mocked in unit tests
- throws exceptions instead of PHP errors
- better type supports:
  - parses boolean values (`true`/`false`, `on`/`off`, `yes`/`no`) to real PHP booleans ([instead of strings `"1"` and `""`](http://3v4l.org/JuvOT))
  - parses null to PHP `null` ([instead of an empty string](http://3v4l.org/KSoj2))
- works even if `parse_ini_file()` or `parse_ini_string()` is disabled in `php.ini` by falling back on an alternate implementation (can happen on some shared hosts)
- fixes [a PHP 5.3.3 bug](http://3v4l.org/jD1Lh)
- fixes [a parsing bug](http://3v4l.org/m24cT) present in PHP <= 5.4.4

## Usage

### Read

```php
$reader = new IniReader();

// Read a string
$array = $reader->readString($string);

// Read a file
$array = $reader->readFile('config.ini');
```

### Write

```php
$writer = new IniWriter();

// Write to a string
$string = $writer->writeToString($array);

// Write to a file
$writer->writeToFile('config.ini', $array);
```

## License

The Ini component is released under the [LGPL v3.0](http://choosealicense.com/licenses/lgpl-3.0/).

## Contributing

To run the unit tests:

```
vendor/bin/phpunit
```

To run the performance tests:

```
php -n vendor/bin/athletic -p tests/PerformanceTest
```
