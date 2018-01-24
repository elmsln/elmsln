; api_router make file for d.o. usage
core = "7.x"
api = "2"

; api_router core includes everything needed to power api_router
projects[api_router_core][version] = "1.x-dev"
projects[api_router_core][subdir] = "contrib"
