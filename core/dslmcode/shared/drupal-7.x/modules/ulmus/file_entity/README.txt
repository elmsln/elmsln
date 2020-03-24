
If you want to translate file entities the Drupal 7 entity_translation module needs to be enabled.

Step 1) download and enable the file_entity module
Step 2) download and enable the entity_translation module
Step 3) enable the locale module and add your additional languages here:
/admin/config/regional/language , be sure to configure language detection as well, I prefer prefix, configure the prefix for all enabled languages.

Step 4)
go to the /admin/config/regional/entity_translation
page and check off the file entity type underneith "Translatable entity types"
then save, after you have done this, translation options for each enabled language will show up if you also enable the field translation option in the structure of your file entity type for 'managed fields' , so for instance alt field and the title field would be a good thing to enable translatable field option for.

Step 5) enable field translation on alt and title fields for file entity image type go to : /admin/structure/file-types/manage/image/fields

Step 6) Once you do this, you will get translation options for the translatable fields that have translatable field option enabled.
so to if you've correctly configured things you'll be able to add the translation in this page here: /file/1/translate

More translation usage with views:
Translate one file entity alt and title fields

and then create a view of unformated fields with the article type
add the image field to the view
save the view

hover your mouse over the image in the default language (most likely english /en) , the default language hover should show the image title in that language
switch language, hover the mouse over the image and this language (in my case French /fr ) the hover should display the image title in french.
