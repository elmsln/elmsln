Creates calendar displays of Views results.

Create a new calendar by using the calendar template for the desired
date field. See a link to create a view from a template at the top
of the Views listing page.

If the Calendar iCal module is enabled, an iCal feed can be
attached to the view.

For a quick and easy start, install the Date Tools module, then use
the Date Tools Wizard to create a content type with a date field
and a calendar that displays that field, all in a single step!


=========================================================
CACHING & PERFORMANCE
=========================================================

Calendars are very time-consuming to process, so caching is recommended.
You can set up caching options for your calendar in the Advanced section
of the View settings. Even setting a lifetime of 1 hour will provide some 
benefits if you can live with a calendar that is 1 hour out of date. 
Set the lifetime to the longest value possible. You will need to clear 
the caches manually or using custom code if the content of the calendar 
changes before the cache lifetime expires. 

The recommended settings for time-based caching are:

- Query results
Cache the query only when not using ajax. Do not cache the query
on any display that uses ajax for its results.

- Rendered output:
Always try to cache rendered output. Rendering the output is the most
time-consuming part of building a calendar. This is especially
important for the Year view, less important for the Day view.

As with all caching options, please test to be sure that caching
is working as desired.

If performance is a problem, or you have a lot of items in the calendar,
you may want to remove the Year view completely.