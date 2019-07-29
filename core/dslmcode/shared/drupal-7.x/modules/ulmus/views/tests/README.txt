Views Tests
```````````
All of the tests may be executed with the following command:

$ scripts/run-tests.sh --color --url http://example.com/ --php `which php` --concurrency 4 --verbose --directory 'sites/all/modules/contrib/views/tests' 2> /dev/null

Explanation:
  --color
    Colorizes the output. Optional.
  --url http://example.com/
    The name of the Drupal 7 hostname used locally for running tests, e.g.
    "http://drupal7.dev". Required.
  --php `which php`
    Tells the test runner the path to the PHP binary. Only necessary if the test
    runner is unable to find the path automatically or to use an alternative
    PHP binary. Optional.
  --cuncurrency 4
    Run multiple test processes simultaneously. Four appears to be a good
    balance between melting the computer and improving performance. Optional.
  --verbose
    Display results for all of the assertion statements after the summary
    details. Optional.
  --directory 'sites/all/modules/contrib/views/tests'
    Run all of the commands in the following directory. The path is relative to
    the Drupal installation's root directory. This will run all of Views' tests
    in one go, rather than either repeating the names of test groups or running
    multiple commands. Optional.
  2> /dev/null
    Outputs all error messages to /dev/null, i.e. hides them. Optional.
