## Piwik modifications to libs/

In general, bug fixes and improvements are reported upstream.  Until these are
included upstream, we maintain a list of bug fixes and local mods made to
third-party libraries:

 * PclZip/
   - in r1960, ignore touch() - utime failed warning
   - line 5679, replaced `php_uname()` by `PHP_OS` (see [#2](https://github.com/piwik/component-decompress/issues/2))
