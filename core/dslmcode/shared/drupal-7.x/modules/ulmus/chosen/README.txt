-- SUMMARY --

Chosen uses the Chosen jQuery plugin to make your <select>
elements more user-friendly.


-- INSTALLATION --

  1. Download the Chosen jQuery plugin
  (http://harvesthq.github.io/chosen/ version 1.1.0 is recommended)
  and extract the file under sites/all/libraries.
  2. Download and enable the module.
  3. Configure at Administer > Configuration >
  User interface > Chosen (requires administer site configuration permission)

-- INSTALLATION VIA DRUSH --

 A Drush command is provided for easy installation of the Chosen plugin.

 drush chosenplugin

 The command will download the plugin and unpack it in "sites/all/libraries".
 It is possible to add another path as an option to the command, but not
 recommended unless you know what you are doing.

-- ACCESSIBILITY CONCERN --

There are accessibility problems with the main library as identified here:
	https://github.com/harvesthq/chosen/issues/264

-- TROUBLE SHOOTING --

  How to exlude a select field from becoming a chosen select.
    - go to the configuration page and add your field using the jquery "not"
      operator to the textarea with the comma seperated values.
      For date fields this could look like:
      select:not([name*='day'],[name*='year'],[name*='month'])
