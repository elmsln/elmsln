$Source:


MODULE
------
Revision Deletion


DESCRIPTION/FEATURES
--------------------
* Enables the ability to mass delete aging node revisions. Possible settings include node type, the age of node revision before being deleted, along with a cron frequency setting. The revisions may be deleted after review on an administer page as well. This module will NEVER delete the current revision of a node.

* Automate the process of deleting old revisions with the cron functionality.

IDEALLY SUITED FOR:
-------------------

-- Any site with limited database size. Aged revisions, if not needed anymore, can bloat the size of the drupal database. If 10MBs or less is your maximum database size, this module may help you recover space.

-- Collabrative writing/editing site. The revisions of node may pile up quickly during the article creation phase, but then the article/node stablizes and is rarely touched. If those 'in process' revisions are not needed long term, this automated tool may help clean up the node revisions table.


REQUIREMENTS
------------
Drupal 4.7.x, 5.x, 6.x, 7.x (download the version of Drupal you are using)


INSTALL/CONFIG
--------------
1. Move this folder into your modules directory like you would any other module.
2. Enable it from administer >> modules.
3. The module can be configured at administer >> settings >> revision_deletion. Select the cron frequency, the age before revisions are considered for deletion and the node types that should have their revisions deleted.

Deletions can be manually run at administer >> revision_deletion. A review screen will display all the node revisions that meet the settings criteria.


AUTHOR/MAINTAINER
------- 
Greg Holsclaw <gregh AT tech-wanderings DOT com>
