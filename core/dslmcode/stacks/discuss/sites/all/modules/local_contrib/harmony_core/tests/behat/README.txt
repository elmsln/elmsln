Behat tests
===========

Setup
-----

 1. Install Composer

    php -r "eval('?>'.file_get_contents('https://getcomposer.org/installer'));"
 
 2. Install Behat and dependencies via Composer

    php composer.phar install

 3. Copy behat.yml.example to behat.yml and modify

    mv behat.template.yml behat.yml
 
 4. Run Behat and examine test results!
 
    bin/behat


These instructions (and a fair chunk of files) have been swiped from commerce_kickstart, Harmony <3 Commerce Guys.
