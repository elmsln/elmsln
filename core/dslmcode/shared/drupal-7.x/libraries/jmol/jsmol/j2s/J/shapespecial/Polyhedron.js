Clazz.declarePackage ("J.shapespecial");
Clazz.load (null, "J.shapespecial.Polyhedron", ["java.lang.Boolean", "$.Float", "java.util.Hashtable", "JU.AU", "$.BS", "$.Measure", "$.P3", "$.V3", "JM.Atom", "JS.SV", "JU.Escape", "$.Node", "$.Normix", "$.Point3fi"], function () {
c$ = Clazz.decorateAsClass (function () {
this.modelIndex = 0;
this.centralAtom = null;
this.vertices = null;
this.faces = null;
this.nVertices = 0;
this.collapsed = false;
this.bsFlat = null;
this.normals = null;
this.normixes = null;
this.smiles = null;
this.smarts = null;
this.pointGroup = null;
this.volume = null;
this.visible = true;
this.isFullyLit = false;
this.isValid = true;
this.colixEdge = 0;
this.visibilityFlags = 0;
this.info = null;
Clazz.instantialize (this, arguments);
}, J.shapespecial, "Polyhedron");
Clazz.makeConstructor (c$, 
function () {
});
Clazz.defineMethod (c$, "set", 
function (centralAtom, nVertices, nPoints, planeCount, otherAtoms, normals, bsFlat, planes, collapsed) {
this.centralAtom = centralAtom;
this.modelIndex = centralAtom.mi;
this.nVertices = nVertices;
this.vertices =  new Array (nPoints + 1);
this.normals =  new Array (planeCount);
this.bsFlat = bsFlat;
this.faces = JU.AU.newInt2 (planeCount);
for (var i = nPoints + 1; --i >= 0; ) this.vertices[i] = otherAtoms[i];

for (var i = planeCount; --i >= 0; ) this.normals[i] = JU.V3.newV (normals[i]);

for (var i = planeCount; --i >= 0; ) this.faces[i] = planes[i];

this.collapsed = collapsed;
return this;
}, "JM.Atom,~N,~N,~N,~A,~A,JU.BS,~A,~B");
Clazz.defineMethod (c$, "getInfo", 
function (vwr, isAll) {
if (isAll && this.info != null) return this.info;
var info =  new java.util.Hashtable ();
if (isAll) {
this.info = info;
info.put ("modelIndex", Integer.$valueOf (this.centralAtom.mi));
info.put ("modelNumber", Integer.$valueOf (this.centralAtom.getModelNumber ()));
info.put ("center", JU.P3.newP (this.centralAtom));
info.put ("atomNumber", Integer.$valueOf (this.centralAtom.getAtomNumber ()));
info.put ("atomName", this.centralAtom.getInfo ());
info.put ("element", this.centralAtom.getElementSymbol ());
info.put ("vertexCount", Integer.$valueOf (this.nVertices));
info.put ("faceCount", Integer.$valueOf (this.faces.length));
info.put ("volume", this.getVolume ());
if (this.smarts != null) info.put ("smarts", this.smarts);
if (this.smiles != null) info.put ("smiles", this.smiles);
if (this.pointGroup != null) info.put ("pointGroup", this.pointGroup.getPointGroupName ());
var energy = vwr.ms.getInfo (this.centralAtom.mi, "Energy");
if (energy != null) info.put ("energy", energy);
} else {
info.put ("bsFlat", this.bsFlat);
if (this.collapsed) info.put ("collapsed", Boolean.$valueOf (this.collapsed));
info.put ("ptRef", this.vertices[this.nVertices]);
}info.put ("atomIndex", Integer.$valueOf (this.centralAtom.i));
info.put ("vertices", JU.AU.arrayCopyPt (this.vertices, this.nVertices));
info.put ("faces", JU.AU.arrayCopyII (this.faces, this.faces.length));
var elemNos =  Clazz.newIntArray (this.nVertices, 0);
for (var i = 0; i < this.nVertices; i++) {
var pt = this.vertices[i];
elemNos[i] = (Clazz.instanceOf (pt, JU.Node) ? (pt).getElementNumber () : Clazz.instanceOf (pt, JU.Point3fi) ? (pt).sD : -2);
}
info.put ("elemNos", elemNos);
return info;
}, "JV.Viewer,~B");
Clazz.defineMethod (c$, "setInfo", 
function (info, at) {
try {
this.centralAtom = at[info.get ("atomIndex").intValue];
this.modelIndex = this.centralAtom.mi;
var lst = info.get ("vertices").getList ();
this.vertices =  new Array (lst.size () + 1);
this.nVertices = this.vertices.length - 1;
for (var i = this.nVertices; --i >= 0; ) this.vertices[i] = JS.SV.ptValue (lst.get (i));

lst = info.get ("elemNos").getList ();
for (var i = this.nVertices; --i >= 0; ) {
var n = lst.get (i).intValue;
if (n > 0) {
var p =  new JU.Point3fi ();
p.setT (this.vertices[i]);
p.sD = n;
this.vertices[i] = p;
}}
this.vertices[this.nVertices] = JS.SV.ptValue (info.get ("ptRef"));
lst = info.get ("faces").getList ();
this.faces = JU.AU.newInt2 (lst.size ());
this.normals =  new Array (this.faces.length);
var vAB =  new JU.V3 ();
for (var i = this.faces.length; --i >= 0; ) {
var lst2 = lst.get (i).getList ();
var a =  Clazz.newIntArray (lst2.size (), 0);
for (var j = a.length; --j >= 0; ) a[j] = lst2.get (j).intValue;

this.faces[i] = a;
this.normals[i] =  new JU.V3 ();
JU.Measure.getNormalThroughPoints (this.vertices[a[0]], this.vertices[a[1]], this.vertices[a[2]], this.normals[i], vAB);
}
this.bsFlat = JS.SV.getBitSet (info.get ("bsFlat"), false);
this.collapsed = info.containsKey ("collapsed");
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
return null;
} else {
throw e;
}
}
return this;
}, "java.util.Map,~A");
Clazz.defineMethod (c$, "getSymmetry", 
function (vwr, withPointGroup) {
this.info = null;
var sm = vwr.getSmilesMatcher ();
try {
if (this.smarts == null) {
this.smarts = sm.polyhedronToSmiles (this.faces, this.nVertices, null);
this.smiles = sm.polyhedronToSmiles (this.faces, this.nVertices, this.vertices);
}} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
} else {
throw e;
}
}
if (this.pointGroup == null && withPointGroup) this.pointGroup = vwr.ms.getSymTemp (true).setPointGroup (null, this.vertices, null, false, vwr.getFloat (570425382), vwr.getFloat (570425384), true);
}, "JV.Viewer,~B");
Clazz.defineMethod (c$, "getVolume", 
 function () {
if (this.volume != null) return this.volume;
var vAB =  new JU.V3 ();
var vAC =  new JU.V3 ();
var vTemp =  new JU.V3 ();
var v = 0;
for (var i = this.faces.length; --i >= 0; ) {
var face = this.faces[i];
for (var j = face.length - 2; --j >= 0; ) if (face[j + 2] >= 0) v += this.triangleVolume (face[j], face[j + 1], face[j + 2], vAB, vAC, vTemp);

}
return Float.$valueOf (v / 6);
});
Clazz.defineMethod (c$, "triangleVolume", 
 function (i, j, k, vAB, vAC, vTemp) {
vAB.setT (this.vertices[i]);
vAC.setT (this.vertices[j]);
vTemp.cross (vAB, vAC);
vAC.setT (this.vertices[k]);
return vAC.dot (vTemp);
}, "~N,~N,~N,JU.V3,JU.V3,JU.V3");
Clazz.defineMethod (c$, "getState", 
function (vwr) {
return "  var p = " + JU.Escape.e (this.getInfo (vwr, false)) + ";polyhedron @p" + (this.isFullyLit ? " fullyLit" : "") + ";" + (this.visible ? "" : "polyhedra ({" + this.centralAtom.i + "}) off;") + "\n";
}, "JV.Viewer");
Clazz.defineMethod (c$, "move", 
function (mat) {
this.info = null;
for (var i = 0; i < this.nVertices; i++) {
var p = this.vertices[i];
if (Clazz.instanceOf (p, JM.Atom)) p = this.vertices[i] = JU.P3.newP (p);
mat.rotTrans (p);
}
for (var i = this.normals.length; --i >= 0; ) mat.rotate (this.normals[i]);

this.normixes = null;
}, "JU.M4");
Clazz.defineMethod (c$, "getNormixes", 
function () {
if (this.normixes == null) {
this.normixes =  Clazz.newShortArray (this.normals.length, 0);
var bsTemp =  new JU.BS ();
for (var i = this.normals.length; --i >= 0; ) this.normixes[i] = (this.bsFlat.get (i) ? JU.Normix.get2SidedNormix (this.normals[i], bsTemp) : JU.Normix.getNormixV (this.normals[i], bsTemp));

}return this.normixes;
});
});
