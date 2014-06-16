; icor make file for d.o. usage
core = "7.x"
api = "2"

; +++++ Modules +++++

projects[fastclick][version] = "1.2"
projects[fastclick][subdir] = "contrib"

projects[admin_menu][version] = "3.0-rc4"
projects[admin_menu][subdir] = "contrib"

projects[ctools][version] = "1.4"
projects[ctools][subdir] = "contrib"

projects[google_chart_tools][version] = "1.4"
projects[google_chart_tools][subdir] = "contrib"

projects[context][version] = "3.2"
projects[context][subdir] = "contrib"

projects[date][version] = "2.6"
projects[date][subdir] = "contrib"

projects[devel][version] = "1.3"
projects[devel][subdir] = "contrib"

projects[profiler_builder][version] = "1.x-dev"
projects[profiler_builder][subdir] = "contrib"

projects[file_entity][version] = "2.x-dev"
projects[file_entity][subdir] = "contrib"

projects[features][version] = "2.0-beta2"
projects[features][subdir] = "contrib"

projects[features_override][version] = "2.0-beta2"
projects[features_override][subdir] = "contrib"

projects[entityreference][version] = "1.1"
projects[entityreference][subdir] = "contrib"

projects[entityreference_dynamicselect_widget][version] = "1.0"
projects[entityreference_dynamicselect_widget][subdir] = "contrib"

projects[link][version] = "1.1"
projects[link][subdir] = "contrib"

projects[makemeeting][version] = "2.0-rc4"
projects[makemeeting][subdir] = "contrib"

projects[yuml][version] = "1.x-dev"
projects[yuml][subdir] = "contrib"

projects[typogrify][version] = "1.0-rc8"
projects[typogrify][subdir] = "contrib"

projects[video_filter][version] = "3.1"
projects[video_filter][subdir] = "contrib"

projects[lti_tool_provider][version] = "1.x-dev"
projects[lti_tool_provider][subdir] = "contrib"

projects[imce][version] = "1.7"
projects[imce][subdir] = "contrib"

projects[og][version] = "2.6"
projects[og][subdir] = "contrib"

projects[og_clone][version] = "1.x-dev"
projects[og_clone][subdir] = "contrib"

projects[boxes][version] = "1.1"
projects[boxes][subdir] = "contrib"

projects[entity][version] = "1.5"
projects[entity][subdir] = "contrib"

projects[entityreference_dynamicselect_widget][version] = "1.0"
projects[entityreference_dynamicselect_widget][subdir] = "contrib"

projects[libraries][version] = "2.1"
projects[libraries][subdir] = "contrib"

projects[masquerade][version] = "1.0-rc7"
projects[masquerade][subdir] = "contrib"

projects[menu_breadcrumb][version] = "1.3"
projects[menu_breadcrumb][subdir] = "contrib"

projects[module_filter][version] = "1.7"
projects[module_filter][subdir] = "contrib"

projects[node_clone][version] = "1.0-rc1"
projects[node_clone][subdir] = "contrib"

projects[profile2][version] = "1.3"
projects[profile2][subdir] = "contrib"

projects[restws][version] = "2.1"
projects[restws][subdir] = "contrib"

projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = "contrib"

projects[sco_node][version] = "1.x-dev"
projects[sco_node][subdir] = "contrib"

projects[transliteration][version] = "3.1"
projects[transliteration][subdir] = "contrib"

projects[entitycache][version] = "1.1"
projects[entitycache][subdir] = "contrib"

projects[quiz][version] = "4.0-beta2"
projects[quiz][subdir] = "contrib"

projects[cloze][version] = "1.0-alpha3"
projects[cloze][subdir] = "contrib"

projects[grouping_question][version] = "4.4"
projects[grouping_question][subdir] = "contrib"

projects[image_target_question][version] = "4.4-beta2"
projects[image_target_question][subdir] = "contrib"

projects[regions][version] = "1.5"
projects[regions][subdir] = "contrib"

projects[textbook][version] = "4.0"
projects[textbook][subdir] = "contrib"

projects[delta][version] = "3.0-beta11"
projects[delta][subdir] = "contrib"

projects[ckeditor_link][version] = "2.3"
projects[ckeditor_link][subdir] = "contrib"

projects[imce_wysiwyg][version] = "1.0"
projects[imce_wysiwyg][subdir] = "contrib"

projects[jquery_update][version] = "2.3"
projects[jquery_update][subdir] = "contrib"

projects[lightbox2][version] = "1.0-beta1"
projects[lightbox2][subdir] = "contrib"

projects[wysiwyg][version] = "2.2"
projects[wysiwyg][subdir] = "contrib"

projects[editableviews][version] = "1.0-beta5"
projects[editableviews][subdir] = "contrib"

projects[eva][version] = "1.2"
projects[eva][subdir] = "contrib"

projects[views][version] = "3.7"
projects[views][subdir] = "contrib"

projects[views_bulk_operations][version] = "3.1"
projects[views_bulk_operations][subdir] = "contrib"

projects[views_simple_pager][version] = "1.0-alpha2"
projects[views_simple_pager][subdir] = "contrib"

projects[views_timelinejs][version] = "1.x-dev"
projects[views_timelinejs][subdir] = "contrib"

projects[views_xml_backend][version] = "1.0-alpha4"
projects[views_xml_backend][subdir] = "contrib"

projects[cis_connector][version] = "1.x-dev"
projects[cis_connector][subdir] = "contrib"

projects[entity_iframe][version] = "1.x-dev"
projects[entity_iframe][subdir] = "contrib"

projects[httprl][version] = "1.12"
projects[httprl][subdir] = "contrib"

projects[h5p][version] = "1.x-dev"
projects[h5p][subdir] = "contrib"


; +++++ Themes +++++

; blank
projects[blank][type] = "theme"
projects[blank][version] = "1.x-dev"
projects[blank][subdir] = "contrib"

projects[entity_iframe][type] = "theme"
projects[entity_iframe][version] = "1.x-dev"
projects[entity_iframe][subdir] = "contrib"

; +++++ Libraries +++++

; CKEditor
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.1/ckeditor_3.6.6.1.tar.gz"

; jQuery Colorpicker
libraries[colorpicker][directory_name] = "colorpicker"
libraries[colorpicker][type] = "library"
libraries[colorpicker][destination] = "libraries"
libraries[colorpicker][download][type] = "get"
libraries[colorpicker][download][url] = "http://www.eyecon.ro/colorpicker/colorpicker.zip"

; OAuth Drupal fork
libraries[oauth][directory_name] = "oauth"
libraries[oauth][type] = "library"
libraries[oauth][destination] = "libraries"
libraries[oauth][download][type] = "get"
libraries[oauth][download][url] = "https://github.com/juampy72/OAuth-PHP/archive/master.zip"

; allow for custom meta controllers to enable deep querying
projects[restws][patch][] = "http://drupal.org/files/restws_meta_controls-2053147-1.patch"

