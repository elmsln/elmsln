This folder contains the h5p general library. The files within this folder are not specific to any framework.

Any interaction with LMS, CMS or other frameworks is done through interfaces. Plattforms needs to implement
the following interfaces in order for the h5p libraries to work:

 - TODO: Fill in here

In addition frameworks need to do the following:

 - Provide a form for uploading h5p packages.
 - Place the uploaded h5p packages in a temporary directory

See existing implementations for details. For instance the Drupal h5p module located on drupal.org/project/h5p