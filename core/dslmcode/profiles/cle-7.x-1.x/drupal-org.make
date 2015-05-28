; Collaborative learning environment make file
core = "7.x"
api = "2"

; ----------
; START ELMSLN Core Dependencies
; ----------
; Administration
projects[admin_menu_dropdown][version] = "3.0-alpha1"
projects[admin_menu_dropdown][subdir] = "contrib"
projects[admin_menu_dropdown][patch][] = "https://www.drupal.org/files/issues/admin_menu_dropdown-fix-js-aggregation-1221668-8.patch"
projects[admin_menu][version] = "3.0-rc5"
projects[admin_menu][subdir] = "contrib"
projects[admin_theme][version] = "1.0"
projects[admin_theme][subdir] = "contrib"
projects[module_filter][version] = "2.0"
projects[module_filter][subdir] = "contrib"
; Chaos tool suite
projects[ctools][version] = "1.7"
projects[ctools][subdir] = "contrib"
; Context
projects[context][version] = "3.6"
projects[context][subdir] = "contrib"
; Entity
projects[replicate][version] = "1.1"
projects[replicate][subdir] = "contrib"
projects[entity][version] = "1.6"
projects[entity][subdir] = "contrib"
; Fields
projects[entityreference][version] = "1.1"
projects[entityreference][subdir] = "contrib"
projects[entityreference_prepopulate][version] = "1.3"
projects[entityreference_prepopulate][subdir] = "contrib"
projects[field_group][version] = "1.4"
projects[field_group][subdir] = "contrib"
projects[link][version] = "1.3"
projects[link][subdir] = "contrib"
projects[prepopulate][version] = "2.x-dev"
projects[prepopulate][subdir] = "contrib"
; Menu
projects[menu_attributes][version] = "1.0-rc3"
projects[menu_attributes][subdir] = "contrib"
projects[special_menu_items][version] = "2.0"
projects[special_menu_items][subdir] = "contrib"

; Other
projects[better_formats][version] = "1.0-beta1"
projects[better_formats][subdir] = "contrib"
projects[chosen][version] = "2.0-beta4"
projects[chosen][subdir] = "contrib"
projects[defaultconfig][version] = "1.x-dev"
projects[defaultconfig][subdir] = "contrib"
projects[diff][version] = "3.2"
projects[diff][subdir] = "contrib"
projects[elements][version] = "1.4"
projects[elements][subdir] = "contrib"
projects[fastclick][version] = "1.3"
projects[fastclick][subdir] = "contrib"
projects[libraries][version] = "2.1"
projects[libraries][subdir] = "contrib"
projects[pathauto][version] = "1.2"
projects[pathauto][subdir] = "contrib"
projects[placeholder][version] = "1.1"
projects[placeholder][subdir] = "contrib"
projects[restws][version] = "2.4"
projects[restws][subdir] = "contrib"
projects[restws][patch][] = "https://www.drupal.org/files/issues/restws-image-support-2320083-7.patch"
projects[role_export][version] = "1.x-dev"
projects[role_export][subdir] = "contrib"
projects[role_export][patch][] = "https://www.drupal.org/files/issues/role_export-expand-auto-repair-support-2492377-2.patch"
projects[strongarm][version] = "2.0"
projects[strongarm][subdir] = "contrib"
projects[masquerade][version] = "1.0-rc7"
projects[masquerade][subdir] = "contrib"
projects[token][version] = "1.6"
projects[token][subdir] = "contrib"
projects[transliteration][version] = "3.2"
projects[transliteration][subdir] = "contrib"
; Input filters
projects[typogrify][version] = "1.0-rc10"
projects[typogrify][subdir] = "contrib"
projects[video_filter][version] = "3.1"
projects[video_filter][subdir] = "contrib"
; Performance and scalability
projects[advagg][version] = "2.10"
projects[advagg][subdir] = "contrib"
projects[blockcache_alter][version] = "1.0"
projects[blockcache_alter][subdir] = "contrib"
projects[httprl][version] = "1.14"
projects[httprl][subdir] = "contrib"
projects[imageinfo_cache][version] = "3.5"
projects[imageinfo_cache][subdir] = "contrib"
projects[entitycache][version] = "1.2"
projects[entitycache][subdir] = "contrib"
; Textbook
projects[textbook][version] = "1.0"
projects[textbook][subdir] = "contrib"
; UUID
projects[uuid][version] = "1.x-dev"
projects[uuid][subdir] = "contrib"
; User interface
projects[addanother][version] = "2.2"
projects[addanother][subdir] = "contrib"
projects[back_to_top][version] = "1.4"
projects[back_to_top][subdir] = "contrib"
projects[ckeditor_link][version] = "2.3"
projects[ckeditor_link][subdir] = "contrib"
projects[ds][version] = "2.10"
projects[ds][subdir] = "contrib"
projects[imce][version] = "1.9"
projects[imce][subdir] = "contrib"
projects[imce_crop][version] = "1.1"
projects[imce_crop][subdir] = "contrib"
projects[imce_mkdir][version] = "1.0"
projects[imce_mkdir][subdir] = "contrib"
projects[imce_wysiwyg][version] = "1.0"
projects[imce_wysiwyg][subdir] = "contrib"
projects[jammer][version] = "1.4"
projects[jammer][subdir] = "contrib"
projects[jquery_update][version] = "2.5"
projects[jquery_update][subdir] = "contrib"
projects[wysiwyg][version] = "2.x-dev"
projects[wysiwyg][subdir] = "contrib"
projects[wysiwyg_template][version] = "2.x-dev"
projects[wysiwyg_template][subdir] = "contrib"
; Views
projects[better_exposed_filters][version] = "3.2"
projects[better_exposed_filters][subdir] = "contrib"
projects[views][version] = "3.11"
projects[views][subdir] = "contrib"
projects[views][patch][] = "https://www.drupal.org/files/1979926-views-reset_fetch_data-2.patch"
projects[views_autocomplete_filters][version] = "1.2"
projects[views_autocomplete_filters][subdir] = "contrib"
projects[views_bulk_operations][version] = "3.2"
projects[views_bulk_operations][subdir] = "contrib"
; Features
projects[features][version] = "2.5"
projects[features][subdir] = "contrib"
projects[features_override][version] = "2.0-rc2"
projects[features_override][subdir] = "contrib"
; ELMSLN Core
projects[cis_connector][version] = "1.x-dev"
projects[cis_connector][subdir] = "contrib"

; ----------
; Service Dependencies
; ----------
projects[og][version] = "2.7"
projects[og][subdir] = "contrib"

; ----------
; Optional, LTI a configured but underused option
; ----------
projects[lti_tool_provider][version] = "1.x-dev"
projects[lti_tool_provider][subdir] = "contrib"
projects[lti_tool_provider][patch][] = "https://www.drupal.org/files/issues/imscompliance-2389303-2.patch"

; ----------
; Themes
; ----------

; rubik
projects[rubik][type] = "theme"
projects[rubik][version] = "4.2"
projects[rubik][subdir] = "contrib"

; tao
projects[tao][type] = "theme"
projects[tao][version] = "3.1"
projects[tao][subdir] = "contrib"

; zurb-foundation
projects[zurb_foundation][type] = "theme"
projects[zurb_foundation][version] = "5.0-rc6"
projects[zurb_foundation][subdir] = "contrib"

; foundation_access
projects[foundation_access][type] = "theme"
projects[foundation_access][version] = "5.x-dev"
projects[foundation_access][subdir] = "contrib"

; ----------
; Libraries
; ----------
; CKEditor
libraries[ckeditor][directory_name] = "ckeditor"
libraries[ckeditor][type] = "library"
libraries[ckeditor][destination] = "libraries"
libraries[ckeditor][download][type] = "get"
libraries[ckeditor][download][url] = "http://download.cksource.com/CKEditor/CKEditor/CKEditor%203.6.6.1/ckeditor_3.6.6.1.tar.gz"

; jQuery Joyride
libraries[joyride][directory_name] = "joyride"
libraries[joyride][type] = "library"
libraries[joyride][destination] = "libraries"
libraries[joyride][download][type] = "get"
libraries[joyride][download][url] = "https://github.com/zurb/joyride/archive/v2.0.3.tar.gz"

; OAuth Drupal fork
libraries[oauth][directory_name] = "oauth"
libraries[oauth][type] = "library"
libraries[oauth][destination] = "libraries"
libraries[oauth][download][type] = "get"
libraries[oauth][download][url] = "https://github.com/juampy72/OAuth-PHP/archive/master.zip"

; ----------
; END ELMSLN Core Dependencies
; ----------

; ----------
; CLE Dependencies
; ----------
; Assessment entity
projects[assessment][version] = "1.x-dev"
projects[assessment][subdir] = "contrib"
; Fields
projects[field_hidden][version] = "1.7"
projects[field_hidden][subdir] = "contrib"
projects[date][version] = "2.8"
projects[date][subdir] = "contrib"
; Flag
projects[flag][version] = "3.6"
projects[flag][subdir] = "contrib"
; Media
projects[flexslider][version] = "2.0-alpha3"
projects[flexslider][subdir] = "contrib"
projects[smartcrop][version] = "1.x-dev"
projects[smartcrop][subdir] = "contrib"
projects[video_embed_field][version] = "2.x-dev"
projects[video_embed_field][subdir] = "contrib"
; Other
projects[imagefield_crop][version] = "2.x-dev"
projects[imagefield_crop][subdir] = "contrib"
projects[jquery_colorpicker][version] = "1.x-dev"
projects[jquery_colorpicker][subdir] = "contrib"
projects[quickpost_bookmarklet][version] = "2.x-dev"
projects[quickpost_bookmarklet][subdir] = "contrib"
projects[unique_field][version] = "1.0-rc1"
projects[unique_field][subdir] = "contrib"
projects[achievements][version] = "1.x-dev"
projects[achievements][subdir] = "contrib"
; Radioactivity
projects[radioactivity][version] = "2.10"
projects[radioactivity][subdir] = "contrib"
; Rules
projects[rules][version] = "2.9"
projects[rules][subdir] = "contrib"
projects[rules][patch][] = "https://www.drupal.org/files/issues/fix_errors_on_update-2090511-189.patch"
projects[voting_rules][version] = "1.0-alpha1"
projects[voting_rules][subdir] = "contrib"
; User interface
projects[masonry][version] = "2.x-dev"
projects[masonry][subdir] = "contrib"
; Views
projects[views_infinite_scroll][version] = "1.1"
projects[views_infinite_scroll][subdir] = "contrib"
projects[views_infinite_scroll][patch][] = "https://www.drupal.org/files/views_infinite_scroll-1806628-13.patch"

projects[editableviews][version] = "1.x-dev"
projects[editableviews][subdir] = "contrib"
; Voting
projects[rate][version] = "1.7"
projects[rate][subdir] = "contrib"
projects[votingapi][version] = "2.12"
projects[votingapi][subdir] = "contrib"
; Other dependencies
projects[masonry_views][version] = "1.0"
projects[masonry_views][subdir] = "contrib"
projects[rubric][version] = "1.x-dev"
projects[rubric][subdir] = "contrib"
projects[colorbox][version] = "2.8"
projects[colorbox][subdir] = "contrib"
projects[multiupload_imagefield_widget][version] = "1.3"
projects[multiupload_imagefield_widget][subdir] = "contrib"
projects[file_entity][version] = "2.x-dev"
projects[file_entity][subdir] = "contrib"
projects[select_or_other][version] = "2.22"
projects[select_or_other][subdir] = "contrib"
projects[eva][version] = "1.x-dev"
projects[eva][subdir] = "contrib"
projects[filefield_paths][version] = "1.0-beta4"
projects[filefield_paths][subdir] = "contrib"
projects[views_litepager][version] = "3.x-dev"
projects[views_litepager][subdir] = "contrib"
projects[replicate_field_collection][version] = "1.x-dev"
projects[replicate_field_collection][subdir] = "contrib"
projects[replicate_ui][version] = "1.x-dev"
projects[replicate_ui][subdir] = "contrib"
projects[field_collection][version] = "1.0-beta8"
projects[field_collection][subdir] = "contrib"
projects[replicate][version] = "1.1"
projects[replicate][subdir] = "contrib"
projects[field_collection_fieldset][version] = "2.5"
projects[field_collection_fieldset][subdir] = "contrib"
projects[field_collection_tabs][version] = "1.1"
projects[field_collection_tabs][subdir] = "contrib"
projects[textformatter][version] = "1.3"
projects[textformatter][subdir] = "contrib"
projects[multiupload_filefield_widget][version] = "1.13"
projects[multiupload_filefield_widget][subdir] = "contrib"


; ColorBox
libraries[colorbox][directory_name] = "colorbox"
libraries[colorbox][type] = "library"
libraries[colorbox][destination] = "libraries"
libraries[colorbox][download][type] = "get"
libraries[colorbox][download][url] = "https://github.com/jackmoore/colorbox/archive/master.zip"

; jQuery Colorpicker
libraries[colorpicker][directory_name] = "colorpicker"
libraries[colorpicker][type] = "library"
libraries[colorpicker][destination] = "libraries"
libraries[colorpicker][download][type] = "get"
libraries[colorpicker][download][url] = "http://www.eyecon.ro/colorpicker/colorpicker.zip"

