Clazz.declarePackage ("J.g3d");
c$ = Clazz.decorateAsClass (function () {
this.g = null;
this.p0 = null;
this.zb = null;
this.pb = null;
this.width = 0;
Clazz.instantialize (this, arguments);
}, J.g3d, "Pixelator");
Clazz.makeConstructor (c$, 
function (graphics3d) {
this.g = graphics3d;
this.setBuf ();
}, "J.g3d.Graphics3D");
Clazz.defineMethod (c$, "setBuf", 
function () {
this.zb = this.g.zbuf;
this.pb = this.g.pbuf;
});
Clazz.defineMethod (c$, "clearPixel", 
function (offset, z) {
if (this.zb[offset] > z) this.zb[offset] = 2147483647;
}, "~N,~N");
Clazz.defineMethod (c$, "addPixel", 
function (offset, z, p) {
this.zb[offset] = z;
this.pb[offset] = p;
}, "~N,~N,~N");
