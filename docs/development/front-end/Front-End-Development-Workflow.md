### Front-end Development - Setting Up Foundation Access Theme:
1. Install dependencies
  * Git
  * Node
  * Npm
  * SASS
  * Grunt
  * Bower
2. `git clone --recursive https://github.com/elmsln/elmsln-developer.git elmsln`
3. `cd elmsln/system`
1. `git pull origin master` (or 1.x.x or whatever branch you want)
4. `cd core/dslmcode/shared/drupal-7.x/themes/elmsln_contrib/foundation_access/legacy`
5. `npm install`
6. `bower install`
7. `grunt`
8. Work from Foundation Access theme directory in SublimeText
9. SFTP grunt-compiled theme CSS, icons, or [template].tpl.php files into vagrant to make changes
10. To make template changes to a sub-theme, you must also sftp the desired sub-theme's .tpl files into vagrant

**Note:** to work on the templates of the various sub-themes, navigate to `elmsln/core/dslmcode/profiles/...`
As of now, due to the Zurb Foundation breakpoints mixins being compiled in Foundation Access, all theme CSS is handled in the Foundation Access theme, and templates (IE - page.tpl.php) are modified in the individual service sub-themes. Compiling SASS in a sub-theme and uploading the CSS would double the amount of CSS loaded for each theme and would override Foundation Access styles back to stock Zurb Foundation. Perhaps a better workflow can be figured out to distribute the css in a more efficient manner.
### Service / Authority sub theming
For a starting point Sub-theme to work from, see `core/dslmcode/profiles/ulmus-7.x-1.x/themes/SUB_foundation_access`. Rename all SUB in the files to whatever the service name is. OR, if you are sub-theming a service's sub-theme then you can name this to whatever make sense for your group. Just make sure that the SUB_foundation_access.info file is updated to reflect it being a sub-theme of a sub-theme.

### Viewing an ELMSLN theme in a browser

1. `cd elmsln`
2. `vagrant up`
3. To see the various themes in use: (combination of **foundation_access** and **SERVICE_foundation_access themes**)
  * CIS: `online.elmsln.local`
  * Course (MOOC) `courses.elmsln.local/COURSENAMEHERE`
  * Media `media.elmsln.local`

### Commit and Pull Request Instructions
1. Fork the `https://github.com/elmsln/elmsln` repo by clicking fork in the top right.
1. take your changes you've worked on, overwrite the files in the fork repo
1. create an issue in the issue queue `https://github.com/elmsln/elmsln/issues/new`
1. commit to the fork repo using a commit message of the format `#123: Issue Queue Title`
1. go to `https://github.com/elmsln/elmsln` and click `Pull requests`.
1. enter a description of the commit in the PR and issue it
1. Wait for travis-ci to test to ensure the build passes, then wait for a maintainer to merge your PR
1. Do a happy dance, you've made education better looking