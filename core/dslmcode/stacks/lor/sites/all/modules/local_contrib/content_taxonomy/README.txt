Content Taxonomy:
*****************

Migration from D6 to D7:

- backup your DB
- run the core upgrade path
- download and install the Content Migrate (CCK) module
- download and install the Content Taxonomy Migrate module
- goto Structure > Migrate and select your fields to upgrade
- clear caches
- check if the data is available or rollback

note: the content taxonomy module allows you to select the parent term, but all other advanced settings of content taxonomy will be lost.


Author:
-------
Matthias Hutterer
mh86@drupal.org
m_hutterer@hotmail.com
