
Profiler
--------
Profiler is a library that allows an install profile to be defined as a Drupal
`.info` file rather than as a standard PHP script. The benefits of using
Profiler for an install profile are:

- Simpler creation and management of install profiles.
- Reduced custom code and complexity in managing installation tasks and
  configuration.
- Inheritance between install profiles and definition of sub-profiles that can
  override specific aspects of base profiles.
- Simplified migration path between Drupal 6.x and 7.x install profiles.


Implementing Profiler in an install profile
-------------------------------------------
Profiler can be placed in any directory belonging to your install profile. If
installed as a standard library the correct location for Profiler is:

    profiles/[yourprofile]/libraries/profiler

If using a drush make makefile for packaging/distribution, drush make can place
Profiler in the standard location with the following lines:

    libraries[profiler][download][type] = "get"
    libraries[profiler][download][url] = "http://ftp.drupal.org/files/projects/profiler-7.x-2.0-beta1.tar.gz"

Profiler expects that the `.profile` file initializes the profiler API with the
following lines of code:

    <?php
    !function_exists('profiler_v2') ? require_once('libraries/profiler/profiler.inc') : FALSE;
    profiler_v2('yourprofile');

In addition to your profile `.info` file (see below) you may define a
`hook_install()` for your install profile allowing you to run any custom code
at the very end of the install process. You can add this function to your
`.profile` file or a separate `.install` file:

    function yourprofile_install() {
      // My custom setup code
    }

Summary of files:

- `yourprofile.make`: drush make file including directives for retrieving
  profiler and unpacking it in the proper location.
- `yourprofile.info`: info file containing the core definition of your install
  profile.
- `yourprofile.profile`: contains snippet of code for initializing profiler.
- `yourprofile.install`: optional file for defining custom code in 
  `hook_install()`.


The `.info` file
----------------
Each install profile `.info` file is a plain text file that adheres to the
Drupal `.info` file syntax. See the included `example.info` for an example of a
working install profile `.info` file.


### Core options

The following are core options for defining information about your install
profile and enabling various components. Options that require additional
modules to be included in your install profile are noted below.

- `name`

  The name of the install profile.

        name = My install profile

- `description`

  A short description of the install profile.

        description = A custom install profile for video blogging.

- `core`

  The Drupal core version for which this install profile is intended.

        core = 6.x

- `base`

  A base install profile from which the current `.info` file should inherit
  properties.

        base = profile_foo

- `dependencies`

  An array of Drupal core, contrib, or feature modules to be enabled for this
  install profile. Need not include the modules defined by
  `drupal_required_modules()`, ie. block, filter, node, system and user. Any
  dependencies of the listed modules will also be detected and enabled.

        dependencies[] = book
        dependencies[] = color
        dependencies[] = views
        dependencies[] = myblog

  The following syntax can be used to disable/exclude core modules that would
  otherwise be inherited from a base install profile:

        dependencies[book] = 0

- `theme`

  The name of the default theme to be enabled for this install profile

        theme = bluemarine

- `variables`

  A keyed array of variables and their corresponding values.

        variables[site_frontpage] = admin

- `users`

  A keyed array of account objects. Each user object is passed nearly directly
  to user_save(). The following are some common keys you will want to provide:

  - uid: The user id for the account
  - name: The username for the account
  - mail: The email address for the account
  - roles: A comma separated list of roles for this account
  - status: Status for the account (1 is active, 0 is blocked)

        users[admin][uid] = 1
        users[admin][name] = admin
        users[admin][mail] = admin@example.com
        users[admin][roles] = administrator,manager
        users[admin][status] = 1

  Note: the user password is assigned a randomly generated string and may not
  be directly specified in your `.info` file. Even an md5 hashed password
  exposes a serious vulnerability because of widespread reverse-lookup
  databases.

- `nodes`

  A keyed array of node objects. Each node object is passed nearly directly to
  node_save(). The following are some common keys you will want to provide:

  - type: The node type
  - title: Title text for the node
  - body: Body text for the node
  - uid: The user ID of the node author

        nodes[hello][type] = blog
        nodes[hello][title] = Hello world!
        nodes[hello][body][und][0][value] = Lorem ipsum dolor sit amet...
        nodes[hello][body][und][0][format] = filtered_html
        nodes[hello][uid] = 1

  - menu: To add the node to a menu

        nodes[hello][menu][link_title] = Hello world!
        nodes[hello][menu][menu_name] = secondary-links

- `terms`

  A keyed array of term objects. Each term object is passed nearly directly to
  taxonomy_term_save(). The following are some common keys you will want to
  provide:

  - name: The term name
  - description: Optional. The term description
  - weight: Optional. An explicit weight for this term
  - vocabulary_machine_name: The machine name of vocabulary ID to which this
    term belongs.

        terms[apples][name] = Apples
        terms[apples][description] = Delicious crunchy fruit.
        terms[apples][vocabulary_machine_name] = fruit


Maintainer
----------
- James Sansbury (q0rban)
