The Quiz module lets you create graded assessments in Drupal. A Quiz is given as
a series of questions. Answers are then stored in the database. Scores and
results are displayed during or after the quiz. Administrators can provide
automatic or manual feedback. See all the features below! This module can be
used as

*   an object in a larger LMS, or a supplemental classroom activity
*   a standalone activity (audio, video, rich text in questions/answers)
*   a self-learning program, using adaptive mode with multiple answer tries
*   a training program, with multiple improving attempts

## Features

*   Extensive Views, Rules integration through Entity API
*   Integration with H5P making 20+
    [content types](http://h5p.org/content-types-and-applications) available
*   OO Question API
*   Very configurable feedback times and options
*   Pre-attempt questionnaires (through Field API)
*   Views and Views Bulk Operations for managing questions/results
*   Drag and drop ordering of questions/answers/pages
*   Configurable questions per page
*   Devel generate support (dummy Quiz/Question/Result data)
*   Question randomization, from per-Quiz pool or taxonomy category
*   Certainty-based marking
*   Multiple attempts per user
*   Lots of unit test coverage
*   Adaptive mode and feedback
*   Build on last attempt mode
*   Timed quizzes
*   Question reuse across multiple Quizzes
*   Robust Quiz/Question versioning
*   AJAX quiz taking
*   And many more...

## Question types included

*   H5P - 20 [H5P content types](http://h5p.org/content-types-and-applications)
    available
    *   4.x - included
    *   5.x - https://www.drupal.org/project/quiz_h5p
*   True or false
*   Multiple choice
*   Short answers
*   Long answers
*   Scale
*   Question directions
*   Matching
*   Drag and drop (with lines) - moved to
    https://www.drupal.org/project/quiz_ddlines

## Quiz addons

*   [Charts](http://drupal.org/project/charts) - used by Quiz stats to render
    some useful data
*   [jQuery Countdown](http://drupal.org/project/jquery_countdown) - provides
    jQuery timer for timed quizzes
*   [Views Data Export](http://drupal.org/project/views_data_export) - export
    Quiz results and user answers

## Other modules we like

*   [H5P - HTML5 learning objects](https://www.drupal.org/project/h5p)
*   [Course](https://www.drupal.org/project/course) - put multiple quizzes
    together
*   [Certificate](https://www.drupal.org/project/certificate) - award a
    certificate after passing a Course/Quiz

Check out the
[Quiz affiliated modules wiki](http://groups.drupal.org/node/177684)
to see a fuller list of modules that extend quiz.

## Upgrading from 7.x-4.x

If you do not have any custom question modules, an upgrade to 5.x is easy.

**Note:** There are core issues with MySQL 5.7, but only during the upgrade. See
[here](https://www.drupal.org/node/2812685#comment-11702775) if you have to use
MySQL 5.7 and Drupal 7. If you do have custom question modules, they may have to
be updated slightly to work with the 5.x version.

## Roadmap

*   [#2378365]
    *   Create multiple types of quizzes!
    *   Custom quiz defaults per type
    *   Optionally remove node dependency
*   [#2378359]
    *   Create multiple types of questions!
    *   Varying content fields per question
    *   Create audio questions, video questions, etc.

## Support

We have a big community supporting Quiz, and it's getting bigger! Let's make
this the best assessment engine, ever. [IRC](https://drupal.org/irc),
in #drupal-course (for Quiz, Course, Certificate module support)
[IRC](https://drupal.org/irc), in #drupal-edu (general edu talk), 
[Drupal groups](https://groups.drupal.org/quiz),
[The issue queue](https://www.drupal.org/project/issues/quiz)

## Help out

Please continue to help out with cleaning up the issue queue!
https://drupal.org/node/2280951 Have a feature request? Please open an issue in
the issue queue!

## Drupal 8

The D7 version of this module is being cleaned up so that a migration/port to
D8 will be easier.

## Credits

Many users have contributed lots of feature requests and bug reports. Previous
maintainers also deserve a lot of credit! Join the Quiz group at
http://groups.drupal.org/quiz to get involved! **Quiz is currently being
sponsored by:** djdevin@[DLC Solutions](http://www.dlc-solutions.com)/
[EthosCE](http://www.ethosce.com) for the 7.x-5.x branch **Previous sponsors**
[The e-learning company Amendor](http://amendor.com),
[The Norwegian Centre for ICT in Education](http://iktsenteret.no/english),
[Norwegian Centre for Integrated Care and Telemedicine](http://telemed.no/)
