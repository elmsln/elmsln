; mooc make file for d.o. usage
api = 2
core = 7.x

; ----------
; Ulmus Sub-distro
; ----------
projects[ulmus][type] = "module"
projects[ulmus][destination] = "modules/contrib"
projects[ulmus][subdir] = "contrib"
projects[ulmus][download][type] = "git"
projects[ulmus][download][branch] = "7.x-1.x"

; ----------
; MOOC Dependencies
; ----------
; Book
projects[book_title_override][version] = "1.0"
projects[book_title_override][subdir] = "contrib"
; Feeds
projects[feeds][version] = "2.x-dev"
projects[feeds][subdir] = "contrib"
projects[feeds][patch][] = "http://drupal.org/files/608408-feeds_drush_d7-57.patch"
projects[feeds_node_helper][version] = "1.x-dev"
projects[feeds_node_helper][subdir] = "contrib"
projects[feeds_tamper][version] = "1.0"
projects[feeds_tamper][subdir] = "contrib"
projects[feeds_xpathparser][version] = "1.0"
projects[feeds_xpathparser][subdir] = "contrib"
; Other
projects[book_copy][version] = "2.x-dev"
projects[book_copy][subdir] = "contrib"
projects[book_delete][version] = "1.0"
projects[book_delete][subdir] = "contrib"
projects[footnotes][version] = "2.x-dev"
projects[footnotes][subdir] = "contrib"
projects[footnotes][patch][] = "http://drupal.org/files/footnotes-wysiwyg_fix_js_error_ckeditor-1589130-6.patch"
projects[job_scheduler][version] = "2.0-alpha3"
projects[job_scheduler][subdir] = "contrib"
projects[linkchecker][version] = "1.2"
projects[linkchecker][subdir] = "contrib"
projects[scanner][version] = "1.x-dev"
projects[scanner][subdir] = "contrib"
projects[tipsy][version] = "1.0-rc1"
projects[tipsy][subdir] = "contrib"
; Outline Designer
projects[outline_designer][version] = "2.x-dev"
projects[outline_designer][subdir] = "contrib"
; Performance
projects[book_cache][version] = "1.x-dev"
projects[book_cache][subdir] = "contrib"
; Permissions
projects[hidden_nodes][version] = "1.4"
projects[hidden_nodes][subdir] = "contrib"
; Textbook
projects[speedreader][version] = "1.x-dev"
projects[speedreader][subdir] = "contrib"
; User interface
projects[lightbox2][version] = "1.x-dev"
projects[lightbox2][subdir] = "contrib"
projects[token_insert_entity][version] = "1.x-dev"
projects[token_insert_entity][subdir] = "contrib"
projects[token_insert][version] = "2.x-dev"
projects[token_insert][subdir] = "contrib"
; Other Dependencies
projects[token_filter][version] = "1.1"
projects[token_filter][subdir] = "contrib"
projects[views_data_export][version] = "3.0-beta8"
projects[views_data_export][subdir] = "contrib"

; +++++ Libraries +++++
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

; +++++ Patches +++++
;projects[apc][patch][] = "http://drupal.org/files/1567440_apc_drush_enable.patch"
