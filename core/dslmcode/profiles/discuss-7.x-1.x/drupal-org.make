; discuss make file for d.o. usage
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
; Discuss Dependencies
; ----------
; Date/Time
projects[date][subdir] = "contrib"
projects[date][version] = "2.8"
; Fields
projects[inline_entity_form][subdir] = "contrib"
projects[inline_entity_form][version] = "1.5"
projects[machine_name][subdir] = "contrib"
projects[machine_name][version] = "1.0"
projects[short_scale_formatter][subdir] = "contrib"
projects[short_scale_formatter][version] = "1.1"
projects[viewfield][subdir] = "contrib"
projects[viewfield][version] = "2.0"
; Flags
projects[flag][subdir] = "contrib"
projects[flag][version] = "3.5"
; Harmony
projects[harmony_search][subdir] = "contrib"
projects[harmony_search][version] = "1.x-dev"
projects[harmony_access][subdir] = "contrib"
projects[harmony_access][version] = "1.x-dev"
; Input filters
projects[wysiwyg_filter][subdir] = "contrib"
projects[wysiwyg_filter][version] = "1.6-rc2"
; Other
projects[atjs][subdir] = "contrib"
projects[atjs][version] = "1.x-dev"
projects[exif_orientation][subdir] = "contrib"
projects[exif_orientation][version] = "1.0"
projects[entity_quote][subdir] = "contrib"
projects[entity_quote][version] = "1.x-dev"
projects[taxonomy_display][subdir] = "contrib"
projects[taxonomy_display][version] = "1.1"
; Search
projects[search_api][subdir] = "contrib"
projects[search_api][version] = "1.14"

; Views
projects[views_load_more][subdir] = "contrib"
projects[views_load_more][version] = "1.5"
; Features
projects[harmony_core][subdir] = "contrib"
projects[harmony_core][version] = "1.0-alpha4"

projects[readmorejs][subdir] = "contrib"
projects[readmorejs][version] = "1.0"

projects[timeago][subdir] = "contrib"
projects[timeago][version] = "2.3"

; libraries

; OAuth Drupal fork
libraries[oauth][directory_name] = "oauth"
libraries[oauth][type] = "library"
libraries[oauth][destination] = "libraries"
libraries[oauth][download][type] = "get"
libraries[oauth][download][url] = "https://github.com/juampy72/OAuth-PHP/archive/master.zip"

libraries[at.js][download][type] = "get"
libraries[at.js][download][url] = "https://github.com/ichord/At.js/archive/v0.5.2.tar.gz"
libraries[at.js][directory_name] = "at.js"
libraries[at.js][type] = "library"

libraries[caret.js][download][type] = "get"
libraries[caret.js][download][url] = "https://github.com/ichord/Caret.js/archive/v0.2.1.tar.gz"
libraries[caret.js][directory_name] = "caret.js"
libraries[caret.js][type] = "library"

libraries[colorpicker][download][type] = "get"
libraries[colorpicker][download][url] = "http://www.eyecon.ro/colorpicker/colorpicker.zip"
libraries[colorpicker][directory_name] = "colorpicker"
libraries[colorpicker][type] = "library"

libraries[placeholder][download][type] = "get"
libraries[placeholder][download][url] = "https://github.com/mathiasbynens/jquery-placeholder/archive/v2.0.8.tar.gz"
libraries[placeholder][directory_name] = "placeholder"
libraries[placeholder][type] = "library"

libraries[readmore.js][download][type] = "git"
libraries[readmore.js][download][url] = "https://github.com/jedfoster/Readmore.js.git"
libraries[readmore.js][directory_name] = "readmore.js"
libraries[readmore.js][type] = "library"

libraries[timeago][download][type] = "get"
libraries[timeago][download][url] = "http://timeago.yarp.com/jquery.timeago.js"
libraries[timeago][directory_name] = "timeago"
libraries[timeago][type] = "library"
