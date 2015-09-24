; cis make file for d.o. usage
api = 2
core = 7.x

; ----------
; Ulmus Sub-distro
; ----------
projects[ulmus_core][version] = "1.x-dev"
projects[ulmus_core][subdir] = "contrib"

; ----------
; CIS Dependencies
; ----------
; Charting
projects[google_chart_tools][version] = "1.x-dev"
projects[google_chart_tools][subdir] = "contrib"
; Content
projects[field_redirection][version] = "2.6"
projects[field_redirection][subdir] = "contrib"
; Data
projects[data][version] = "1.0-alpha7"
projects[data][subdir] = "contrib"
; Database
projects[schema][version] = "1.2"
projects[schema][subdir] = "contrib"
; Date/Time
projects[date][version] = "2.8"
projects[date][subdir] = "contrib"
; Entity
projects[replicate_field_collection][version] = "1.x-dev"
projects[replicate_field_collection][subdir] = "contrib"
projects[replicate_ui][version] = "1.x-dev"
projects[replicate_ui][subdir] = "contrib"
; Fields
projects[email][version] = "1.3"
projects[email][subdir] = "contrib"
projects[field_collection][version] = "1.0-beta8"
projects[field_collection][subdir] = "contrib"
projects[field_hidden][version] = "1.7"
projects[field_hidden][subdir] = "contrib"
projects[field_permissions][version] = "1.0-beta2"
projects[field_permissions][subdir] = "contrib"
projects[phone][version] = "1.0-beta1"
projects[phone][subdir] = "contrib"
projects[select_or_other][version] = "2.22"
projects[select_or_other][subdir] = "contrib"
; Image
projects[smartcrop][version] = "1.x-dev"
projects[smartcrop][subdir] = "contrib"
; Media
projects[video_embed_field][version] = "2.x-dev"
projects[video_embed_field][subdir] = "contrib"
; Nodequeue
projects[nodequeue][version] = "2.0-beta1"
projects[nodequeue][subdir] = "contrib"
; Other
projects[auto_nodetitle][version] = "1.x-dev"
projects[auto_nodetitle][subdir] = "contrib"
projects[field_collection_table][version] = "1.0-beta2"
projects[field_collection_table][subdir] = "contrib"
projects[file_formatters][version] = "1.x-dev"
projects[file_formatters][subdir] = "contrib"
projects[imagefield_focus][version] = "1.x-dev"
projects[imagefield_focus][subdir] = "contrib"
projects[jquery_colorpicker][version] = "1.1"
projects[jquery_colorpicker][subdir] = "contrib"
projects[menu_block][version] = "2.6"
projects[menu_block][subdir] = "contrib"
projects[menu_position][version] = "1.1"
projects[menu_position][subdir] = "contrib"
projects[nocurrent_pass][version] = "1.0"
projects[nocurrent_pass][subdir] = "contrib"
projects[nodeaccess_nodereference][version] = "1.22"
projects[nodeaccess_nodereference][subdir] = "contrib"
projects[nodeaccess_nodereference][patch][] = "https://www.drupal.org/files/nodeaccess_nodereference-install-profile.patch"
projects[nodeaccess_userreference][version] = "3.10"
projects[nodeaccess_userreference][subdir] = "contrib"
projects[nodeaccess_userreference][patch][] = "https://www.drupal.org/files/nodeaccess_userreference-install-profile-3.patch"
projects[responsive_tables][version] = "2.x-dev"
projects[responsive_tables][subdir] = "contrib"
projects[unique_field][version] = "1.0-rc1"
projects[unique_field][subdir] = "contrib"
; Path breadcrumbs
projects[path_breadcrumbs][version] = "3.2"
projects[path_breadcrumbs][subdir] = "contrib"
projects[subpathauto][version] = "1.3"
projects[subpathauto][subdir] = "contrib"
; User interface
projects[breakpoints][version] = "1.3"
projects[breakpoints][subdir] = "contrib"
projects[options_element][version] = "1.12"
projects[options_element][subdir] = "contrib"
; Views
projects[editableviews][version] = "1.x-dev"
projects[editableviews][subdir] = "contrib"
projects[views_data_export][version] = "3.0-beta8"
projects[views_data_export][subdir] = "contrib"
projects[views_fluid_grid][version] = "3.x-dev"
projects[views_fluid_grid][subdir] = "contrib"

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

