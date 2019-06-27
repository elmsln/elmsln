// may seem silly but this makes it so that the standard we established with
// how CDNs should operate outside of the HAXcms ecosystem can correctly dedup the file
// We pushed things out NOT being in a dist directory but yet our documentation
// for what to reference in all end-targets says this file should be outside of a dist directory
// so it is here and hopefully no one ever reads this :)
import "./dist/build-cms.js";
