
-- SUMMARY --

Code Format unit tests

These files are implementations for the SimpleTest Drupal module. There
is a bit of custom code here to make things go as smoothly as possible,
and a little bit of necessary setup. Here's what you'll need:


-- REQUIREMENTS --

* SimpleTest module, along with the patch in
  http://drupal.org/node/211823

* SimpleTest Framework
  https://sourceforge.net/project/showfiles.php?group_id=76550

* Text_Diff package from PEAR
  http://pear.php.net/package/Text_Diff


-- INSTALLATION --

* If not already done, install SimpleTest module and SimpleTest framework as
  usual.

* Apply above mentioned patch to SimpleTest module. See
  http://drupal.org/patch/apply for further information.

  FYI: This patch fixes some incompatibilities with our heavy OOP testing
  framework for coder_format. It should not break other tests.

* Download the Text_Diff package from PEAR into this directory, i.e.

  scripts/coder_format/tests/

  and extract the archive, and rename the folder from "Text_Diff-0.x.x" to
  "Text".

* If not already done, go to admin/build/modules, and enable Coder module.


-- USAGE --

* Go to admin/build/simpletest, and select Coder Format Tests, and run tests.


-- CUSTOMIZATIONS --

Currently, only the all.test is implemented, which is used to test
the overall output of coder_format_string_all(). Appropriate .phpt test
files are located in the sub-directory all/.

The internal format for coder_format tests is:

  TEST: Name of test

  --INPUT--
  // PHP code to input

  --EXPECT--
  // Coder cleaned code expected

Note that <?php and CVS Id tags are not necessary. If you would like to test for
those, additionally specify in the file head:

  FULL: 1

For temporary development work, you can add --ONLY-- to the end of a test
case to make it the test runner only run that one. This is useful for test
files that contain multiple tests.

-- CONTACT --

Current maintainers:
* Edward Z. Yang (ezyang)
* Daniel F. Kudwien (sun) - dev@unleashedmind.com

