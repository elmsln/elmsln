; editorial make file for d.o. usage
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
; Editorial Dependencies
; ----------

