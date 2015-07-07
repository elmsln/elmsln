; elmsmedia make file for d.o. usage
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
; ELMSMedia Dependencies
; ----------
; Entity
projects[entity_iframe][version] = "1.x-dev"
projects[entity_iframe][subdir] = "contrib"
; Fields
projects[video_embed_field][version] = "2.x-dev"
projects[video_embed_field][subdir] = "contrib"
; Other
projects[imagefield_focus][version] = "1.x-dev"
projects[imagefield_focus][subdir] = "contrib"
projects[mediaelement][version] = "1.x-dev"
projects[mediaelement][subdir] = "contrib"
projects[h5p][version] = "1.8"
projects[h5p][subdir] = "contrib"
; Views
projects[views_fluid_grid][version] = "3.x-dev"
projects[views_fluid_grid][subdir] = "contrib"
projects[eva][version] = "1.x-dev"
projects[eva][subdir] = "contrib"
projects[autocomplete_deluxe][version] = "2.1"
projects[autocomplete_deluxe][subdir] = "contrib"
