##Feature Builder

Creating features can be a painstaking process. Way too much clicking. Using the features builder module will hopefully end this. 
There are still some kinks to work out. 

Follow these steps to get started:

**Step 1:** Access the features module by going to Structure-Feature-Build. 

**Step 2:** Go to Configuration and choose a name for the prefix. The configuration path should be: sites/all/modules/features/build

**Step 3:** In the command line run the command:

```mkdir -p /var/www/elmsln/domains/innovate/sing100/sites/all/modules/features/build```
This creates the files where the features will be built. 

**Step 4:** Next run the command: 

```chmod 777 /var/www/elmsln/domains/innovate/sing100/sites/all/modules/features/build```
This will allow the permissions for the features module to work.

**Step 5:** Go to Build, and then click Enable, then select Build.

**Step 6:** You will see the all of the features that were just built under Content, CTools, and Configuration.

**Step 7:** Selecting a certain feature will allow you to view what is included in the feature, make any changes,
and then download the feature.
