Clazz.declarePackage ("JU");
Clazz.load (["JU.V3"], "JU.Vibration", null, function () {
c$ = Clazz.decorateAsClass (function () {
this.modDim = -1;
this.modScale = NaN;
Clazz.instantialize (this, arguments);
}, JU, "Vibration", JU.V3);
Clazz.defineMethod (c$, "setCalcPoint", 
function (pt, t456, scale, modulationScale) {
switch (this.modDim) {
case -2:
break;
default:
pt.scaleAdd2 ((Math.cos (t456.x * 6.283185307179586) * scale), this, pt);
break;
}
return pt;
}, "JU.T3,JU.T3,~N,~N");
Clazz.defineMethod (c$, "getInfo", 
function (info) {
info.put ("vibVector", JU.V3.newV (this));
info.put ("vibType", (this.modDim == -2 ? "spin" : this.modDim == -1 ? "vib" : "mod"));
}, "java.util.Map");
Clazz.overrideMethod (c$, "clone", 
function () {
var v =  new JU.Vibration ();
v.setT (this);
v.modDim = this.modDim;
return v;
});
Clazz.defineMethod (c$, "setXYZ", 
function (vib) {
this.setT (vib);
}, "JU.T3");
Clazz.defineMethod (c$, "setType", 
function (type) {
this.modDim = type;
return this;
}, "~N");
Clazz.defineMethod (c$, "isNonzero", 
function () {
return this.x != 0 || this.y != 0 || this.z != 0;
});
Clazz.defineMethod (c$, "getOccupancy100", 
function (isTemp) {
return -2147483648;
}, "~B");
Clazz.defineStatics (c$,
"twoPI", 6.283185307179586,
"TYPE_VIBRATION", -1,
"TYPE_SPIN", -2);
});
