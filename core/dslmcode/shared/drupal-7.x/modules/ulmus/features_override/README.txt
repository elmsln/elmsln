Features Override (Drupal 7-2.x)
--------------------------------

This module add a new Features exportable called "Feature Overrides" that 
are used to export overridden changes to other Features.  It requires at
least the 7.x-1.0-rc1 release of Features.

To use, install this module and enable it.  When you create a new feature from 
the Structure/Features page, two new exportables called "Feature Overrides" 
will be displayed in the drop-down list.  The first one allows you to override
all of the changes of a specific component.  The second "Individual Advanced"
allows you to select exactly which line-by-line changes are exported.
Select the Overrode exportable and then select which components you wish to 
export  overrides for.  Only components that are currently overridden will be 
shown as checkboxes.

Maintainers
-----------
- mpotter (Mike Potter)


Basic Usage
-----------
1) Create normal features and enable them.  

2) Make changes to the site using the normal Drupal UI.

3) Go to the admin/structure/features page and you should see some of your 
Features marked as "Overridden"

4) Click the "Create Feature" tab.

5) Enter a name for your Override feature.  

6) Click the "Edit components" drop-down and select "Feature Overrides".  
A list of overridden components will be shown.  For example, if you changed a 
field in a content type, that field name will be shown in the list of 
overrides.  If you changed something in a view, that view name will be in the 
list.  Check the boxes next to the overrides you wish to save.

7) Click the "Download Feature" button at the bottom of the screen.  This will 
create your Override Feature module code and save it to a local file.  Upload 
that file to your server and place it into your normal sites/all/modules 
directory.

8) Go to the Modules page and Enable your new override module.

9) Clear the Drupal cache.

10) Now when you visit the admin/structure/features you should see your new 
override feature and the original features should no longer be marked as 
"Overridden".


Merging new changes into an existing Override
---------------------------------------------
Once you have created an Override feature, it's easy to add additional changes 
to it:

1) Make changes to the site via the Drupal UI

2) Visit admin/structure/features and you should see both the original code 
feature marked as "Overridden" as well as the Override feature marked as 
"Overridden"

3) Click the Recreate link for the Override feature.  

4) Select any new overrides from the Component dropdown list as needed.  
Download your new feature.

You can accomplish this same task using Drush:

drush features-update override-feature

5) Now visit the Features admin page and nothing should be marked as Overridden
again.

NOTE: You want to update/recreate the Override feature and NOT the original 
feature.  If you recreate the original feature, then ALL of the overrides (the
existing ones in the Override module and the new changes) will be written to 
the original feature.  Probably not what you wanted (see next section)

Rebuilding the Original Feature without the Overrides
-----------------------------------------------------
Sometimes you want to make a change and have that change saved with the 
original feature and not with the Override.  Here are the steps to accomplish 
this:

1) Make the changes you need to the site via the Drupal UI

2) Visit admin/structure/features and you should see both the original code 
feature marked as "Overridden" as well as the Override feature marked as 
"Overridden"

3) Click the "Create Feature" tab to create a new feature

4) Create a new Override feature by entering a name and description, then 
select the overrides you want to save from the Feature Override section of the
Components drop-down menu

5) Click Download Feature and install this new module on your site.  Let's 
call it "New Changes".  So now we have the "Original Feature", the first 
"Override Feature", and the new "New Changes" feature.  All three should 
display in the Features Admin page in their Default state.

6) From the Features Admin page, uncheck the "New Changes" feature you created
in step 5, then click Save.  This will undo the recent changes.

7) From the Features Admin page, uncheck the box next to the "Override Feature"
that you originally created (NOT the New one you made in step 5) and click 
Save.  This will undo the changes made by the first Override module.

8) If the original feature shows as "Overridden" or "Needs Review", click on 
it and click the Revert button to ensure it is in it's original state.

9) From the Features Admin page, check the box next to the "New Changes" 
feature you created in step 5 to enable is and click Save.  Now the database 
reflects the original feature plus the new changes.

10) Click the Recreate link for the original Feature.  Click the Download link
and install the updated feature.  Or use the drush command: 
"drush features-update original-feature".  This will export the original
feature code along with the New Changes code.

11) You no longer need the New Changes feature.  You can disable it and remove
it from your site if you wish.  If you don't remove it completely, at least 
ensure that it is disabled in the Feature Admin page.

12) Finally, check the box next to the Override feature to re-enable that 
feature.  Now you have the original code plus the New changes stored in the 
original feature, but you still have the additional Overrides in the seperate 
Override module.

Once you understand the above steps you will also realize that there are other
ways to accomplish this same task.  For example, you could have disabled the 
Override module first, then made your changes and just recreated the original 
feature directly.  However, the above procedure is the most complete and 
reflects the real-life situation where the changes have already been made to 
the site and you need to somehow capture those changes back into the original 
feature.

Adding or Removing specific Override lines
------------------------------------------
An Override feature is simply a list of code changes that need to be made to 
the current configuration. Only code *differences* are stored in the Override 
feature.

To view these specific line-by-line code differences, click the Default link 
next to your Override module from the Features admin page, then click the  
Review Overrides tab.  This will show the Overrides currently exported as 
individual lines (along with the normal "diff" listing below).

To change which specific lines are exported, click the Recreate tab, then
open the Components dropdown.  Select the "Features Overrides Individual" 
(advanced) tab.  Then click the "Refine" link next to the component you want
to adjust.  Each specific override line will be shown as a checkbox.  Simply
check or uncheck the lines desired.  Then click the Download button to create
a new version of your Override feature.

In the main Features Admin page there is also a new Review Overrides tab.  
This will show a list of any new overrides no matter which module that relate 
to.  This is a very useful debugging tool for determining where changes have 
been made to your site.  The Overrides tab will tell you the exact Component 
being overridden. The normal "Review Overrides" tab in Features only shows the 
raw code "diffs" and sometimes cannot show the full context of the change.  The 
new Review Overrides tab can show you exactly what the change is and where it 
is made (which View changed, which field changed, etc).
