AUTHCACHE_VCL_FILE = $(CURDIR)/../example.vcl
DEFAULT_VCL =
AUTHCACHE_VCL = include \"$(AUTHCACHE_VCL_FILE)\";
AUTHCACHE_FORCE_SKIP_VCL = sub vcl_recv {if (req.restarts == 0) {set req.http.X-Authcache-Get-Key = \"skip\";}}
AUTHCACHE_FORCE_GET_VCL = sub vcl_recv {if (req.restarts == 0) {set req.http.X-Authcache-Get-Key = \"get\";}}

TESTS = def/*.vtc auc/*.vtc get/*.vtc skip/*.vtc
.PHONY: check $(TESTS)

check: $(TESTS)

def/*.vtc:
	varnishtest -Dvcl1="$(DEFAULT_VCL)" -Dvcl2="" -Dvcl3="" $@

auc/*.vtc:
	varnishtest -Dvcl1="$(AUTHCACHE_VCL)" -Dvcl2="" -Dvcl3="" $@

get/*.vtc:
	varnishtest -Dvcl1="$(AUTHCACHE_FORCE_GET_VCL)" -Dvcl2="$(AUTHCACHE_VCL)" -Dvcl3="" $@

skip/*.vtc:
	varnishtest -Dvcl1="$(AUTHCACHE_FORCE_SKIP_VCL)" -Dvcl2="$(AUTHCACHE_VCL)" -Dvcl3="" $@
