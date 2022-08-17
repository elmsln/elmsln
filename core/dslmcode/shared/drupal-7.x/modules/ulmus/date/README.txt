Date
----
The Date module suite provides an API for handling date values, a field for
Drupal 7's Field API system, and a wealth of submodules for various purposes.

The following modules are included in the Date package, many of which have their
own README.txt files with further information:

* date_api/date_api.module:
  A dependency for all of the other modules, provides a slew of APIs for the
  other modules to leverage.

* date.module:
  Provides the Field API integration necessary to use date fields in the Drupal
  7 UI, or in custom modules.

* date_all_day/date_all_day.module:
  Provides the option to add an 'All Day' checkbox to toggle time on and off
  for date fields. It also contains the theme that displays the 'All Day' text
  on fields that have no time.

* date_context/date_context.module
  Provides integration with the Context module [1], allowing the date to be used
  as a condition on context definitions.

* date_popup/date_popup.module
  Adds a field widget for use with date and time fields that uses a jQuery-based
  calendar-style date picker and timepicker.

* date_repeat/date_repeat.module
  Provides an API for calculating repeating dates and times from iCal rules.

* date_repeat/date_repeat_field.module
  Creates the option of repeating date fields and manages Date fields that use
  the Date Repeat API.

* date_tools/date_tools.module
  Provides functionality for importing content with dates.

* date_views/date_views.module
  Adds integration with the Views module [2] for adding date fields and filters
  to views.


Credits / contact
--------------------------------------------------------------------------------
Currently maintained by Andrii Podanenko [3], Alex Schedrov [4], Damien McKenna
[5] and Vijaya Chandran Mani [6]. Previous maintainers included Angie Byron
[7], Arlin Sandbulte [8], David Goode [9], Derek Wright [10], developer-x [11]
and Peter Lieverdink [12].

Originally written and maintained by Karen Stevenson [13].

The best way to contact the authors is to submit an issue, be it a support
request, a feature request or a bug report, in the project issue queue:
  https://www.drupal.org/project/issues/date


References
--------------------------------------------------------------------------------
1: https://www.drupal.org/project/context
2: https://www.drupal.org/project/views
3: https://www.drupal.org/u/podarok
4: https://www.drupal.org/u/sanchiz
5: https://www.drupal.org/u/damienmckenna
6: https://www.drupal.org/u/vijaycs85
7: https://www.drupal.org/u/webchick
8: https://www.drupal.org/u/arlinsandbulte
9: https://www.drupal.org/user/291318
10: https://www.drupal.org/u/dww
11: https://www.drupal.org/user/399625
12: https://www.drupal.org/u/cafuego
13: https://www.drupal.org/u/karens
