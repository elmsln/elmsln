This very basic documentation for during development.
Better docs will be generated closer to a full release.


The only items currently implented in the D7 version of Better Formats are:

1. Display options: When BF is enabled you will have permissions at
   admin/people/permissions to control per role display of:
   1. format tips
   2. format tips link
   3. format selection for [entity]

   #3 is actually several permissions. There is one for each entity in your site.

2. Simple field level default format.
   This allows you set a field level default format using the standard "Default Value"
   setting of a field. This is only possibly normally if you enter something in the
   text field for the field api to save the format too. BF gives you the ability
   to set the format WITHOUT having to set a value in the field.

   1. At admin/config/content/formats/settings enable "Use field default" option.
   2. Create a text type of field on one of your content types.
   3. Ensure you set the "Text processing" option to "Filtered text".
   4. Save the field.
   5. Now go back and edit the field you just saved. This is required because of
      how the field default value option works.
   6. You will now see a "Text format" dropdown below your field in the
      "Default Value" area. Set the default format in the dropdown.
   7. Save the field. Default will now be used on all new content forms for that field.

