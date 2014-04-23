; elmsmedia make file for d.o. usage
core = "7.x"
api = "2"

; +++++ Modules +++++

projects[fastclick][version] = "1.2"
projects[fastclick][subdir] = "contrib"

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = "contrib"

projects[ctools][version] = "1.4"
projects[ctools][subdir] = "contrib"

projects[context][version] = "3.1"
projects[context][subdir] = "contrib"

projects[devel][version] = "1.3"
projects[devel][subdir] = "contrib"

projects[profiler_builder][version] = "1.x-dev"
projects[profiler_builder][subdir] = "contrib"

projects[entity_iframe][version] = "1.x-dev"
projects[entity_iframe][subdir] = "contrib"

projects[features][version] = "2.0"
projects[features][subdir] = "contrib"

projects[entityreference][version] = "1.1"
projects[entityreference][subdir] = "contrib"

projects[typogrify][version] = "1.0-rc8"
projects[typogrify][subdir] = "contrib"

projects[video_filter][version] = "3.1"
projects[video_filter][subdir] = "contrib"

projects[imce][version] = "1.7"
projects[imce][subdir] = "contrib"

projects[og][version] = "2.6"
projects[og][subdir] = "contrib"

projects[entity][version] = "1.5"
projects[entity][subdir] = "contrib"

projects[fitvids][version] = "1.14"
projects[fitvids][subdir] = "contrib"

projects[imagefield_focus][version] = "1.0"
projects[imagefield_focus][subdir] = "contrib"

projects[libraries][version] = "2.1"
projects[libraries][subdir] = "contrib"

projects[masquerade][version] = "1.0-rc7"
projects[masquerade][subdir] = "contrib"

projects[mediaelement][version] = "1.2"
projects[mediaelement][subdir] = "contrib"

projects[module_filter][version] = "1.8"
projects[module_filter][subdir] = "contrib"

projects[pathauto][version] = "1.2"
projects[pathauto][subdir] = "contrib"

projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = "contrib"

projects[token][version] = "1.5"
projects[token][subdir] = "contrib"

projects[transliteration][version] = "3.1"
projects[transliteration][subdir] = "contrib"

projects[httprl][version] = "1.12"
projects[httprl][subdir] = "contrib"

projects[regions][version] = "1.6"
projects[regions][subdir] = "contrib"

projects[textbook][version] = "4.0-alpha1"
projects[textbook][subdir] = "contrib"

projects[restws][version] = "2.1"
projects[restws][subdir] = "contrib"

projects[ckeditor_link][version] = "2.3"
projects[ckeditor_link][subdir] = "contrib"

projects[imce_wysiwyg][version] = "1.0"
projects[imce_wysiwyg][subdir] = "contrib"

projects[jquery_update][version] = "2.x-dev"
projects[jquery_update][subdir] = "contrib"

projects[wysiwyg][version] = "2.2"
projects[wysiwyg][subdir] = "contrib"

projects[better_exposed_filters][version] = "3.0-beta3"
projects[better_exposed_filters][subdir] = "contrib"

projects[views][version] = "3.7"
projects[views][subdir] = "contrib"

projects[views_autocomplete_filters][version] = "1.0"
projects[views_autocomplete_filters][subdir] = "contrib"

projects[views_bulk_operations][version] = "3.1"
projects[views_bulk_operations][subdir] = "contrib"

projects[views_fluid_grid][version] = "3.0"
projects[views_fluid_grid][subdir] = "contrib"

; +++++ Themes +++++

; entity_iframe_theme
projects[entity_iframe_theme][type] = "theme"
projects[entity_iframe_theme][version] = "1.x-dev"
projects[entity_iframe_theme][subdir] = "contrib"

; zurb-foundation
projects[zurb-foundation][type] = "theme"
projects[zurb-foundation][version] = "4.0-beta1"
projects[zurb-foundation][subdir] = "contrib"

; rubik
projects[rubik][type] = "theme"
projects[rubik][version] = "4.0-beta9"
projects[rubik][subdir] = "contrib"

; tao
projects[tao][type] = "theme"
projects[tao][version] = "3.0-beta4"
projects[tao][subdir] = "contrib"

; +++++ Libraries +++++

; FitVids
libraries[fitvids][directory_name] = "fitvids"
libraries[fitvids][type] = "library"
libraries[fitvids][destination] = "libraries"
libraries[fitvids][download][type] = "get"
libraries[fitvids][download][url] = "https://raw.github.com/davatron5000/FitVids.js/master/jquery.fitvids.js"

