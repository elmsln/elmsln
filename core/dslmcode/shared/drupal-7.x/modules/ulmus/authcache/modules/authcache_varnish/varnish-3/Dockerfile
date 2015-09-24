FROM ubuntu:trusty
RUN apt-get update && apt-get install -y \
    varnish \
    make
COPY ./ /tmp/authcache_varnish/
CMD make -j8 -C /tmp/authcache_varnish/test
