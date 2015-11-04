Views Data Export
=================

Introduction
------------

This module is designed to provide a way to export large amounts of data from
views. It provides a display plugin that can rendered progressively in a batch.
Style plugins are include that support exporting in the following types:

* CSV
* Microsoft XLS
* Microsoft Doc
* Basic txt
* Simple xml.

Using the "Views Data Export" module
------------------------------------

1. Add a new "Data export" display to your view.
2. Change its "Style" to the desired export type. e.g. "CSV file".
3. Configure the options (such as name, quote, etc.). You can go back and do
   this at any time by clicking the gear icon next to the style plugin you just
   selected.
4. Give it a path in the Feed settings such as "path/to/view/csv".
5. Optionally, you can choose to attach this to another of your displays by
   updating the "Attach to:" option in feed settings.

Advanced usage
--------------

This module also exposes a drush command that can execute the view and save its
results to a file.

drush views-data-export [view-name] [display-id] [output-file]


History
-------

This module has its roots in the export module that was part of the views bonus
pack (http://drupal.org/project/views_bonus). However, massive changes were
needed to make the batch export functionality work, and so this fork was 
created. See: http://drupal.org/node/805960

