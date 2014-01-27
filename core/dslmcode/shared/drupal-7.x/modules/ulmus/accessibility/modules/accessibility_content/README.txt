-- SUMMARY --

To ensure that your site’s content is as accessible as possible, this module checks all fields where users can enter formatting (i.e. the body field of an article).

-- INSTALLATION --

Content accessibility uses any tests you have installed under Admin > Accessibility > Tests and runs them against content found in any field that allows formatting (by default, any "Long text" field). To enable testing a field, under a field's  settings check the "Check this field for accessibility" checkbox. You can also prevent content from being saved if this field contains any errors.

For example, if you want to check the body field of the "Article" content type, you would navigate to Admin > Structure > Content Types > Aricle > Manage Fields, and click the "edit" link for the "Body" field. You will then be able to turn on accessibility testing for that field.

-- PERMISSIONS --

In order for users to see accessibility problems with a page, they must be granted the "Check content for accessibility" permission under Admin > People > Permissions.