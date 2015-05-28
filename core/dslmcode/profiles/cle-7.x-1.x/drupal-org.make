; Collaborative learning environment make file
core = "7.x"
api = "2"

; ----------
; Ulmus Sub-distro
; ----------
projects[ulmus][type] = "module"
projects[ulmus][destination] = "modules/contrib"
projects[ulmus][subdir] = "contrib"
projects[ulmus][download][type] = "git"
projects[ulmus][download][branch] = "7.x-1.x"

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

