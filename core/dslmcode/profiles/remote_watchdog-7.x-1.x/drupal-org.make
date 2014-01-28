; remote_watchdog make file for d.o. usage
core = "7.x"
api = "2"

; +++++ Modules +++++

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = "contrib"

projects[ctools][version] = "1.3"
projects[ctools][subdir] = "contrib"

projects[profiler_builder][version] = "1.x-dev"
projects[profiler_builder][subdir] = "contrib"

projects[entity][version] = "1.2"
projects[entity][subdir] = "contrib"

projects[module_filter][version] = "1.8"
projects[module_filter][subdir] = "contrib"

projects[restws][version] = "2.1"
projects[restws][subdir] = "contrib"

projects[entitycache][version] = "1.1"
projects[entitycache][subdir] = "contrib"

projects[seckit][version] = "1.6"
projects[seckit][subdir] = "contrib"

projects[jquery_update][version] = "2.3"
projects[jquery_update][subdir] = "contrib"

projects[entity_watchdog][version] = "1.x-dev"
projects[entity_watchdog][subdir] = "contrib"

projects[features][version] = "2.0-rc3"
projects[features][subdir] = "contrib"

; +++++ Themes +++++

; rubik
projects[rubik][type] = "theme"
projects[rubik][version] = "4.0-beta9"
projects[rubik][subdir] = "contrib"

; tao
projects[tao][type] = "theme"
projects[tao][version] = "3.0-beta4"
projects[tao][subdir] = "contrib"

; +++++ Libraries +++++

libraries[profiler][directory_name] = "profiler"
libraries[profiler][type] = "library"
libraries[profiler][destination] = "libraries"
libraries[profiler][download][type] = "get"
libraries[profiler][download][url] = "http://ftp.drupal.org/files/projects/profiler-7.x-2.x-dev.tar.gz"
