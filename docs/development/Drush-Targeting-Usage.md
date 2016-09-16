Drush is a very useful drupal development tool. In ELMSLN one can use drush as in any regular Drupal site, however there are some syntax changes in its use. This file explains how to use drush in ELMSLN to target specific sites, clusters of sites, and the entire system. The key difference between regular drupal targeting and ELMSLN targeting is that elms uses the @target structure so that the drush can understand which system should be targeted by the command. To find a list of targets on your ELMSLN install run the command:

    drush sa

Here are some basic targeting examples with commonly used commands:

    drush @elmsln cc all --y ##run command against every site found in elmsln
    drush @courses-all cc all --y ##run command against every site found JUST in the courses domain
    drush @network.sing100 en [module name] --y ##enable [module name] in every site in the sing100 network
    drush @stacks cc all --y ##runs a cache clear against everything in the system. 
    drush @courses.sing100 generate-content 20 ##adds 20 nodes to sing100 course (**Note: must enable devel_generate first)

    ** drush @courses.sing100 en devel_generate --y
    
A list of drush commands can be found at: https://groups.drupal.org/drush/commands. 
If you are interested in automating via drush check out: https://www.drupal.org/project/drush_recipes.
