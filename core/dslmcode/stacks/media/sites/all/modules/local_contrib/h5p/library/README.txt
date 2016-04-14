This folder contains the h5p general library. The files within this folder are not specific to any framework.

Any interaction with LMS, CMS or other frameworks is done through interfaces. Plattforms needs to implement
the H5PFrameworkInterface(in h5p.classes.php) and also do the following:

 - Provide a form for uploading h5p packages.
 - Place the uploaded h5p packages in a temporary directory
 +++

See existing implementations for details. For instance the Drupal h5p module located on drupal.org/project/h5p

We will make available documentations and tutorials for creating platform integrations in the future

The H5P PHP library is GPL licensed due to GPL code being used for purifying HTML provided by authors.