Clazz.declarePackage ("J.shapespecial");
Clazz.load (["J.shape.AtomShape", "JU.P3", "$.V3"], "J.shapespecial.Polyhedra", ["java.lang.Boolean", "$.Float", "java.util.Hashtable", "JU.AU", "$.BS", "$.Lst", "$.Measure", "$.P4", "$.PT", "$.SB", "J.c.PAL", "J.shapespecial.Polyhedron", "JU.BSUtil", "$.C", "$.Logger", "$.Normix"], function () {
c$ = Clazz.decorateAsClass (function () {
this.otherAtoms = null;
this.normalsT = null;
this.planesT = null;
this.polyhedronCount = 0;
this.polyhedrons = null;
this.drawEdges = 0;
this.radius = 0;
this.nVertices = 0;
this.faceCenterOffset = 0;
this.distanceFactor = NaN;
this.isCollapsed = false;
this.iHaveCenterBitSet = false;
this.bondedOnly = false;
this.haveBitSetVertices = false;
this.centers = null;
this.bsVertices = null;
this.bsVertexCount = null;
this.useUnitCell = false;
this.nPoints = 0;
this.planarParam = 0;
this.info = null;
this.align1 = null;
this.align2 = null;
this.vAB = null;
Clazz.instantialize (this, arguments);
}, J.shapespecial, "Polyhedra", J.shape.AtomShape);
Clazz.prepareFields (c$, function () {
this.otherAtoms =  new Array (251);
this.normalsT =  new Array (251);
this.planesT =  Clazz.newIntArray (250, 3, 0);
this.polyhedrons =  new Array (32);
this.align1 =  new JU.V3 ();
this.align2 =  new JU.V3 ();
this.vAB =  new JU.V3 ();
});
Clazz.overrideMethod (c$, "setProperty", 
function (propertyName, value, bs) {
if ("init" === propertyName) {
this.faceCenterOffset = 0.25;
this.distanceFactor = this.planarParam = NaN;
this.radius = 0.0;
this.nVertices = 0;
this.nPoints = 0;
this.bsVertices = null;
this.useUnitCell = false;
this.centers = null;
this.info = null;
this.bsVertexCount =  new JU.BS ();
this.bondedOnly = this.isCollapsed = this.iHaveCenterBitSet = false;
this.haveBitSetVertices = false;
if (Boolean.TRUE === value) this.drawEdges = 0;
return;
}if ("generate" === propertyName) {
if (!this.iHaveCenterBitSet) {
this.centers = bs;
this.iHaveCenterBitSet = true;
}this.deletePolyhedra ();
this.buildPolyhedra ();
return;
}if ("collapsed" === propertyName) {
this.isCollapsed = (value).booleanValue ();
return;
}if ("nVertices" === propertyName) {
var n = (value).intValue ();
if (n < 0) {
if (-n >= this.nVertices) {
this.bsVertexCount.setBits (this.nVertices, 1 - n);
this.nVertices = -n;
}} else {
this.bsVertexCount.set (this.nVertices = n);
}return;
}if ("centers" === propertyName) {
this.centers = value;
this.iHaveCenterBitSet = true;
return;
}if ("unitCell" === propertyName) {
this.useUnitCell = true;
return;
}if ("to" === propertyName) {
this.bsVertices = value;
return;
}if ("toBitSet" === propertyName) {
this.bsVertices = value;
this.haveBitSetVertices = true;
return;
}if ("toVertices" === propertyName) {
var points = value;
this.nPoints = points.length;
for (var i = this.nPoints; --i >= 0; ) this.otherAtoms[i] = points[i];

return;
}if ("faceCenterOffset" === propertyName) {
this.faceCenterOffset = (value).floatValue ();
return;
}if ("distanceFactor" === propertyName) {
this.distanceFactor = (value).floatValue ();
return;
}if ("planarParam" === propertyName) {
this.planarParam = (value).floatValue ();
return;
}if ("bonds" === propertyName) {
this.bondedOnly = true;
return;
}if ("info" === propertyName) {
this.info = value;
this.centers = JU.BSUtil.newAndSetBit ((this.info.get ("atomIndex")).intValue);
this.iHaveCenterBitSet = true;
return;
}if ("delete" === propertyName) {
if (!this.iHaveCenterBitSet) this.centers = bs;
this.deletePolyhedra ();
return;
}if ("on" === propertyName) {
if (!this.iHaveCenterBitSet) this.centers = bs;
this.setVisible (true);
return;
}if ("off" === propertyName) {
if (!this.iHaveCenterBitSet) this.centers = bs;
this.setVisible (false);
return;
}if ("noedges" === propertyName) {
this.drawEdges = 0;
return;
}if ("edges" === propertyName) {
this.drawEdges = 1;
return;
}if ("frontedges" === propertyName) {
this.drawEdges = 2;
return;
}if (propertyName.indexOf ("color") == 0) {
bs = ("colorThis" === propertyName && this.iHaveCenterBitSet ? this.centers : this.andBitSet (bs));
var colixEdge = ("colorPhase" === propertyName ? JU.C.getColix (((value)[0]).intValue ()) : 0);
for (var i = this.polyhedronCount; --i >= 0; ) if (bs.get (this.polyhedrons[i].centralAtom.i)) this.polyhedrons[i].colixEdge = colixEdge;

if ("colorPhase" === propertyName) value = (value)[1];
propertyName = "color";
}if (propertyName.indexOf ("translucency") == 0) {
bs = ("translucentThis".equals (value) && this.iHaveCenterBitSet ? this.centers : this.andBitSet (bs));
if (value.equals ("translucentThis")) value = "translucent";
}if ("token" === propertyName) {
var tok = (value).intValue ();
if (tok == 1073742182 && tok == 1073742060) {
} else {
this.setLighting (tok == 1073741964, bs);
}return;
}if ("radius" === propertyName) {
this.radius = (value).floatValue ();
return;
}if (propertyName === "symmetry") {
for (var i = this.polyhedronCount; --i >= 0; ) this.polyhedrons[i].getSymmetry (this.vwr, true);

return;
}if (propertyName === "deleteModelAtoms") {
var modelIndex = ((value)[2])[0];
for (var i = this.polyhedronCount; --i >= 0; ) {
this.polyhedrons[i].info = null;
if (this.polyhedrons[i].modelIndex == modelIndex) {
this.polyhedronCount--;
this.polyhedrons = JU.AU.deleteElements (this.polyhedrons, i, 1);
} else if (this.polyhedrons[i].modelIndex > modelIndex) {
this.polyhedrons[i].modelIndex--;
}}
}this.setPropAS (propertyName, value, bs);
}, "~S,~O,JU.BS");
Clazz.overrideMethod (c$, "getPropertyData", 
function (property, data) {
var iatom;
if (property === "points") {
iatom = (data[0]).intValue ();
for (var i = this.polyhedronCount; --i >= 0; ) {
if (this.polyhedrons[i].centralAtom.i == iatom) {
if (this.polyhedrons[i].collapsed) break;
data[1] = this.polyhedrons[i].vertices;
return true;
}}
return false;
}if (property === "move") {
var bs = data[0];
var mat = data[1];
for (var i = this.polyhedronCount; --i >= 0; ) {
var p = this.polyhedrons[i];
if (bs.get (p.centralAtom.i)) p.move (mat);
}
return true;
}if (property === "centers") {
var bs =  new JU.BS ();
var smiles = data[1];
var sm = (smiles == null ? null : this.vwr.getSmilesMatcher ());
var n = data[0];
if (sm != null) smiles = sm.cleanSmiles (smiles);
var nv = (smiles != null ? JU.PT.countChar (smiles, '*') : n == null ? -2147483648 : n.intValue ());
if (smiles != null && nv == 0) nv = -2147483648;
for (var i = this.polyhedronCount; --i >= 0; ) {
if (nv > 0 && this.polyhedrons[i].nVertices != nv || nv > -2147483648 && nv < 0 && this.polyhedrons[i].faces.length != -nv) continue;
if (smiles == null) {
bs.set (this.polyhedrons[i].centralAtom.i);
} else if (sm != null) {
this.polyhedrons[i].getSymmetry (this.vwr, false);
var smiles0 = this.polyhedrons[i].smiles;
try {
if (sm.areEqual (smiles, smiles0) > 0) bs.set (this.polyhedrons[i].centralAtom.i);
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
e.printStackTrace ();
} else {
throw e;
}
}
}}
data[2] = bs;
return true;
}if (property === "info") {
iatom = (data[0]).intValue ();
for (var i = this.polyhedronCount; --i >= 0; ) {
if (this.polyhedrons[i].centralAtom.i == iatom) {
data[1] = this.polyhedrons[i].getInfo (this.vwr, true);
return true;
}}
return false;
}return false;
}, "~S,~A");
Clazz.overrideMethod (c$, "getShapeDetail", 
function () {
var lst =  new JU.Lst ();
for (var i = 0; i < this.polyhedronCount; i++) lst.addLast (this.polyhedrons[i].getInfo (this.vwr, true));

return lst;
});
Clazz.defineMethod (c$, "setLighting", 
 function (isFullyLit, bs) {
for (var i = this.polyhedronCount; --i >= 0; ) if (bs.get (this.polyhedrons[i].centralAtom.i)) {
var normixes = this.polyhedrons[i].getNormixes ();
this.polyhedrons[i].isFullyLit = isFullyLit;
for (var j = normixes.length; --j >= 0; ) {
if (normixes[j] < 0 != isFullyLit) normixes[j] = ~normixes[j];
}
}
}, "~B,JU.BS");
Clazz.defineMethod (c$, "andBitSet", 
 function (bs) {
var bsCenters =  new JU.BS ();
for (var i = this.polyhedronCount; --i >= 0; ) bsCenters.set (this.polyhedrons[i].centralAtom.i);

bsCenters.and (bs);
return bsCenters;
}, "JU.BS");
Clazz.defineMethod (c$, "deletePolyhedra", 
 function () {
var newCount = 0;
var pid = J.c.PAL.pidOf (null);
for (var i = 0; i < this.polyhedronCount; ++i) {
var p = this.polyhedrons[i];
var iAtom = p.centralAtom.i;
if (this.centers.get (iAtom)) this.setColixAndPalette (0, pid, iAtom);
 else this.polyhedrons[newCount++] = p;
}
for (var i = newCount; i < this.polyhedronCount; ++i) this.polyhedrons[i] = null;

this.polyhedronCount = newCount;
});
Clazz.defineMethod (c$, "setVisible", 
 function (visible) {
for (var i = this.polyhedronCount; --i >= 0; ) {
var p = this.polyhedrons[i];
if (p != null && this.centers.get (p.centralAtom.i)) p.visible = visible;
}
}, "~B");
Clazz.defineMethod (c$, "buildPolyhedra", 
 function () {
var useBondAlgorithm = this.radius == 0 || this.bondedOnly;
var mode = (this.info != null ? 6 : this.nPoints > 0 ? 2 : this.haveBitSetVertices ? 4 : this.useUnitCell ? 5 : useBondAlgorithm ? 1 : 3);
var iter = (mode == 3 ? this.ms.getSelectedAtomIterator (null, false, false, false, false) : null);
for (var i = this.centers.nextSetBit (0); i >= 0; i = this.centers.nextSetBit (i + 1)) {
var atom = this.atoms[i];
var p = null;
switch (mode) {
case 4:
p = this.constructBitSetPolyhedron (atom);
break;
case 5:
p = this.constructUnitCellPolygon (atom, useBondAlgorithm);
break;
case 1:
p = this.constructBondsPolyhedron (atom, 0);
break;
case 2:
p = this.constructPointPolyhedron (atom);
break;
case 3:
this.vwr.setIteratorForAtom (iter, i, this.radius);
p = this.constructRadiusPolyhedron (atom, iter);
break;
case 6:
p =  new J.shapespecial.Polyhedron ().setInfo (this.info, this.vwr.ms.at);
break;
}
if (p != null) {
if (this.polyhedronCount == this.polyhedrons.length) this.polyhedrons = JU.AU.doubleLength (this.polyhedrons);
this.polyhedrons[this.polyhedronCount++] = p;
}if (this.haveBitSetVertices) break;
}
if (iter != null) iter.release ();
});
Clazz.defineMethod (c$, "constructPointPolyhedron", 
 function (atom) {
return this.validatePolyhedron (atom, this.nPoints, this.otherAtoms);
}, "JM.Atom");
Clazz.defineMethod (c$, "constructUnitCellPolygon", 
 function (atom, useBondAlgorithm) {
var unitcell = this.vwr.ms.getUnitCellForAtom (atom.i);
if (unitcell == null) return null;
var bsAtoms = JU.BSUtil.copy (this.vwr.getModelUndeletedAtomsBitSet (atom.mi));
if (this.bsVertices != null) bsAtoms.and (this.bsVertices);
if (bsAtoms.isEmpty ()) return null;
var iter = unitcell.getIterator (this.vwr, atom, this.atoms, bsAtoms, useBondAlgorithm ? 5 : this.radius);
if (!useBondAlgorithm) return this.constructRadiusPolyhedron (atom, iter);
var myBondingRadius = atom.getBondingRadius ();
if (myBondingRadius == 0) return null;
var bondTolerance = this.vwr.getFloat (570425348);
var minBondDistance = this.vwr.getFloat (570425364);
var minBondDistance2 = minBondDistance * minBondDistance;
var bondCount = 0;
while (iter.hasNext ()) {
var other = this.atoms[iter.next ()];
var otherRadius = other.getBondingRadius ();
var pt = iter.getPosition ();
var distance2 = atom.distanceSquared (pt);
if (!this.vwr.ms.isBondable (myBondingRadius, otherRadius, distance2, minBondDistance2, bondTolerance)) continue;
this.otherAtoms[bondCount++] = pt;
if (bondCount >= 250) break;
}
return this.constructBondsPolyhedron (atom, bondCount);
}, "JM.Atom,~B");
Clazz.defineMethod (c$, "constructBondsPolyhedron", 
 function (atom, bondCount) {
if (bondCount == 0) {
var bonds = atom.bonds;
if (bonds == null) return null;
for (var i = bonds.length; --i >= 0; ) {
var bond = bonds[i];
if (!bond.isCovalent ()) continue;
var other = bond.getOtherAtom (atom);
if (this.bsVertices != null && !this.bsVertices.get (i) || this.radius > 0 && other.distance (atom) > this.radius) continue;
this.otherAtoms[bondCount++] = other;
if (bondCount >= 250) break;
}
}return (bondCount < 3 || bondCount >= 250 || this.nVertices > 0 && !this.bsVertexCount.get (bondCount) ? null : this.validatePolyhedron (atom, bondCount, this.otherAtoms));
}, "JM.Atom,~N");
Clazz.defineMethod (c$, "constructBitSetPolyhedron", 
 function (atom) {
var otherAtomCount = 0;
for (var i = this.bsVertices.nextSetBit (0); i >= 0; i = this.bsVertices.nextSetBit (i + 1)) this.otherAtoms[otherAtomCount++] = this.atoms[i];

return this.validatePolyhedron (atom, otherAtomCount, this.otherAtoms);
}, "JM.Atom");
Clazz.defineMethod (c$, "constructRadiusPolyhedron", 
 function (atom, iter) {
var otherAtomCount = 0;
while (iter.hasNext ()) {
var other = this.atoms[iter.next ()];
var pt = iter.getPosition ();
if (pt == null) {
pt = other;
if (this.bsVertices != null && !this.bsVertices.get (other.i) || atom.distance (pt) > this.radius) continue;
}if (other.altloc != atom.altloc && other.altloc.charCodeAt (0) != 0 && atom.altloc.charCodeAt (0) != 0) continue;
if (otherAtomCount == 250) break;
this.otherAtoms[otherAtomCount++] = pt;
}
return (otherAtomCount < 3 || this.nVertices > 0 && !this.bsVertexCount.get (otherAtomCount) ? null : this.validatePolyhedron (atom, otherAtomCount, this.otherAtoms));
}, "JM.Atom,J.api.AtomIndexIterator");
Clazz.defineMethod (c$, "validatePolyhedron", 
 function (centralAtom, vertexCount, otherAtoms) {
var planeCount = 0;
var iCenter = vertexCount;
var nPoints = iCenter + 1;
var distMax = 0;
var dAverage = 0;
var planarParam = (Float.isNaN (this.planarParam) ? 0.98 : this.planarParam);
var points =  new Array (750);
points[iCenter] = otherAtoms[iCenter] = centralAtom;
for (var i = 0; i < iCenter; i++) {
points[i] = otherAtoms[i];
dAverage += points[iCenter].distance (points[i]);
}
dAverage = dAverage / iCenter;
var nother1 = iCenter - 1;
var nother2 = iCenter - 2;
var isComplex = (nother1 > 6);
var factor = (!Float.isNaN (this.distanceFactor) ? this.distanceFactor : 1.85);
var bs = JU.BS.newN (iCenter);
var isOK = (dAverage == 0);
while (!isOK && factor < 10.0) {
distMax = dAverage * factor;
bs.setBits (0, iCenter);
for (var i = 0; i < nother2; i++) for (var j = i + 1; j < nother1; j++) {
if (points[i].distance (points[j]) > distMax) continue;
for (var k = j + 1; k < iCenter; k++) {
if (points[i].distance (points[k]) > distMax || points[j].distance (points[k]) > distMax) continue;
bs.clear (i);
bs.clear (j);
bs.clear (k);
}
}

isOK = true;
for (var i = 0; i < iCenter; i++) if (bs.get (i)) {
isOK = false;
factor *= 1.05;
if (JU.Logger.debugging) {
JU.Logger.debug ("Polyhedra distanceFactor for " + iCenter + " atoms increased to " + factor + " in order to include " + otherAtoms[i]);
}break;
}
}
var faceCatalog = "";
var facetCatalog = "";
for (var i = 0; i < nother2; i++) for (var j = i + 1; j < nother1; j++) for (var k = j + 1; k < iCenter; k++) if (this.isPlanar (points[i], points[j], points[k], points[iCenter])) faceCatalog += this.faceId (i, j, k);



for (var j = 0; j < nother1; j++) for (var k = j + 1; k < iCenter; k++) {
if (this.isAligned (points[j], points[k], points[iCenter])) facetCatalog += this.faceId (j, k, -1);
}

var ptRef =  new JU.P3 ();
var p = this.planesT;
var plane =  new JU.P4 ();
var vTemp =  new JU.V3 ();
var collapsed = this.isCollapsed;
var offset = this.faceCenterOffset;
var fmax = 247;
var vmax = 250;
var rpt = J.shapespecial.Polyhedra.randomPoint;
var bsTemp = JU.Normix.newVertexBitSet ();
var normals = this.normalsT;
var htNormMap =  new java.util.Hashtable ();
var bsFlat =  new JU.BS ();
var doCheckPlane = isComplex;
for (var i = 0; i < nother2; i++) for (var j = i + 1; j < nother1; j++) {
if (points[i].distance (points[j]) > distMax) continue;
for (var k = j + 1; k < iCenter; k++) {
if (points[i].distance (points[k]) > distMax || points[j].distance (points[k]) > distMax) continue;
if (planeCount >= fmax) {
JU.Logger.error ("Polyhedron error: maximum face(" + fmax + ") -- reduce RADIUS or DISTANCEFACTOR");
return null;
}if (nPoints >= vmax) {
JU.Logger.error ("Polyhedron error: maximum vertex count(" + vmax + ") -- reduce RADIUS");
return null;
}var isFlat = (faceCatalog.indexOf (this.faceId (i, j, k)) >= 0);
var normal =  new JU.V3 ();
var isWindingOK = (isFlat ? this.getNormalFromCenter (rpt, points[i], points[j], points[k], false, normal) : this.getNormalFromCenter (points[iCenter], points[i], points[j], points[k], true, normal));
normal.scale (collapsed && !isFlat ? offset : 0.001);
var nRef = nPoints;
ptRef.setT (points[iCenter]);
if (collapsed && !isFlat) {
points[nPoints] = JU.P3.newP (points[iCenter]);
points[nPoints].add (normal);
otherAtoms[nPoints] = points[nPoints];
} else if (isFlat) {
ptRef.sub (normal);
nRef = iCenter;
if (this.useUnitCell) continue;
}var facet;
facet = this.faceId (i, j, -1);
if (collapsed || isFlat && facetCatalog.indexOf (facet) < 0) {
facetCatalog += facet;
p[planeCount] =  Clazz.newIntArray (-1, [isWindingOK ? i : j, isWindingOK ? j : i, nRef, isFlat ? -15 : -6]);
this.getNormalFromCenter (points[k], points[i], points[j], ptRef, false, normal);
if (isFlat) bsFlat.set (planeCount);
normals[planeCount++] = normal;
}facet = this.faceId (i, k, -1);
if (collapsed || isFlat && facetCatalog.indexOf (facet) < 0) {
facetCatalog += facet;
p[planeCount] =  Clazz.newIntArray (-1, [isWindingOK ? i : k, nRef, isWindingOK ? k : i, isFlat ? -15 : -5]);
this.getNormalFromCenter (points[j], points[i], ptRef, points[k], false, normal);
if (isFlat) bsFlat.set (planeCount);
normals[planeCount++] = normal;
}facet = this.faceId (j, k, -1);
if (collapsed || isFlat && facetCatalog.indexOf (facet) < 0) {
facetCatalog += facet;
p[planeCount] =  Clazz.newIntArray (-1, [nRef, isWindingOK ? j : k, isWindingOK ? k : j, isFlat ? -15 : -4]);
this.getNormalFromCenter (points[i], ptRef, points[j], points[k], false, normal);
if (isFlat) bsFlat.set (planeCount);
normals[planeCount++] = normal;
}if (!isFlat) {
if (collapsed) {
nPoints++;
} else {
p[planeCount] =  Clazz.newIntArray (-1, [isWindingOK ? i : j, isWindingOK ? j : i, k, -7]);
normals[planeCount] = normal;
if (!doCheckPlane || this.checkPlane (points, iCenter, p, normals, planeCount, plane, vTemp, htNormMap, planarParam, bsTemp)) planeCount++;
}}}
}

nPoints--;
if (JU.Logger.debugging) {
JU.Logger.info ("Polyhedron planeCount=" + planeCount + " nPoints=" + nPoints);
for (var i = 0; i < planeCount; i++) JU.Logger.info ("Polyhedron " + this.getKey (p[i], i));

}return  new J.shapespecial.Polyhedron ().set (centralAtom, iCenter, nPoints, planeCount, otherAtoms, normals, bsFlat, p, collapsed);
}, "JM.Atom,~N,~A");
Clazz.defineMethod (c$, "getNormalFromCenter", 
 function (ptCenter, ptA, ptB, ptC, isOutward, normal) {
var vAB =  new JU.V3 ();
var d = JU.Measure.getNormalThroughPoints (ptA, ptB, ptC, normal, vAB);
var isReversed = (JU.Measure.distanceToPlaneV (normal, d, ptCenter) > 0);
if (isReversed == isOutward) normal.scale (-1.0);
return !isReversed;
}, "JU.P3,JU.P3,JU.P3,JU.P3,~B,JU.V3");
Clazz.defineMethod (c$, "checkPlane", 
 function (points, ptCenter, planes, normals, index, plane, vNorm, htNormMap, planarParam, bsTemp) {
var p1 = planes[index];
plane = JU.Measure.getPlaneThroughPoints (points[p1[0]], points[p1[1]], points[p1[2]], vNorm, this.vAB, plane);
for (var j = 0; j < ptCenter; j++) {
this.vAB.sub2 (points[p1[0]], points[j]);
if (this.vAB.dot (vNorm) < -0.1) {
return false;
}}
var norm = normals[index];
var normix = Integer.$valueOf (JU.Normix.getNormixV (norm, bsTemp));
var list = htNormMap.get (normix);
if (list == null) {
var norms = JU.Normix.getVertexVectors ();
for (var e, $e = htNormMap.entrySet ().iterator (); $e.hasNext () && ((e = $e.next ()) || true);) {
if (norms[e.getKey ().intValue ()].dot (norm) > planarParam) {
list = e.getValue ();
break;
}}
}var ipt;
var match = this.getKey (p1, index);
if (list == null) {
htNormMap.put (normix, match);
} else {
for (var i = 0; i < 3; i++) {
if (list.indexOf ("_" + p1[i] + "_" + p1[(i + 1) % 3] + "_") >= 0) return false;
if ((ipt = list.indexOf ("_" + p1[(i + 1) % 3] + "_" + p1[i] + "_")) < 0) continue;
if (list.indexOf (";") == list.lastIndexOf (";")) {
ipt = JU.PT.parseInt (list.substring (list.indexOf (",") + 1));
var p0 = planes[ipt];
var n = p0.length - 1;
var pnew =  Clazz.newIntArray (p0.length, 0);
var found = false;
for (var i0 = 0, j = 0; i0 < n; i0++) {
pnew[j++] = p0[i0];
if (!found) for (var i1 = 0; i1 < 3; i1++) {
if (p0[i0] == p1[(i1 + 1) % 3] && p0[(i0 + 1) % n] == p1[i1]) {
pnew[j++] = p1[(i1 + 2) % 3];
found = true;
break;
}}
}
planes[ipt] = pnew;
list = JU.PT.rep (list, this.getKey (p0, ipt), this.getKey (pnew, ipt));
htNormMap.put (normix, list);
return false;
}}
htNormMap.put (normix, list + match);
}return true;
}, "~A,~N,~A,~A,~N,JU.P4,JU.V3,java.util.Map,~N,JU.BS");
Clazz.defineMethod (c$, "getKey", 
 function (p1, index) {
var sb =  new JU.SB ();
for (var i = 0, n = p1.length; i < n; i++) if (p1[i] >= 0) sb.append ("_").appendI (p1[i]);

sb.append ("_").appendI (p1[0]);
sb.append ("_,").appendI (index).append (";");
return sb.toString ();
}, "~A,~N");
Clazz.defineMethod (c$, "faceId", 
 function (i, j, k) {
return "[" + i + "," + j + "," + k + "]";
}, "~N,~N,~N");
Clazz.defineMethod (c$, "isAligned", 
 function (pt1, pt2, pt3) {
this.align1.sub2 (pt1, pt3);
this.align2.sub2 (pt2, pt3);
var angle = this.align1.angle (this.align2);
return (angle < 0.01 || angle > 3.13);
}, "JU.P3,JU.P3,JU.P3");
Clazz.defineMethod (c$, "isPlanar", 
 function (pt1, pt2, pt3, ptX) {
var norm =  new JU.V3 ();
var w = JU.Measure.getNormalThroughPoints (pt1, pt2, pt3, norm, this.vAB);
var d = JU.Measure.distanceToPlaneV (norm, w, ptX);
return (Math.abs (d) < J.shapespecial.Polyhedra.minDistanceForPlanarity);
}, "JU.P3,JU.P3,JU.P3,JU.P3");
Clazz.overrideMethod (c$, "setModelVisibilityFlags", 
function (bsModels) {
for (var i = this.polyhedronCount; --i >= 0; ) {
var p = this.polyhedrons[i];
if (this.ms.at[p.centralAtom.i].isDeleted ()) p.isValid = false;
p.visibilityFlags = (p.visible && bsModels.get (p.modelIndex) && !this.ms.isAtomHidden (p.centralAtom.i) && !this.ms.at[p.centralAtom.i].isDeleted () ? this.vf : 0);
if (p.visibilityFlags != 0) this.setShapeVisibility (this.atoms[p.centralAtom.i], true);
}
}, "JU.BS");
Clazz.overrideMethod (c$, "getShapeState", 
function () {
if (this.polyhedronCount == 0) return "";
var s =  new JU.SB ();
for (var i = 0; i < this.polyhedronCount; i++) if (this.polyhedrons[i].isValid) s.append (this.polyhedrons[i].getState (this.vwr));

if (this.drawEdges == 2) J.shape.Shape.appendCmd (s, "polyhedra frontedges");
 else if (this.drawEdges == 1) J.shape.Shape.appendCmd (s, "polyhedra edges");
s.append (this.vwr.getAtomShapeState (this));
for (var i = 0; i < this.polyhedronCount; i++) {
var p = this.polyhedrons[i];
if (p.isValid && p.colixEdge != 0 && this.bsColixSet.get (p.centralAtom.i)) J.shape.Shape.appendCmd (s, "select ({" + p.centralAtom.i + "}); color polyhedra " + (JU.C.isColixTranslucent (this.colixes[p.centralAtom.i]) ? "translucent " : "") + JU.C.getHexCode (this.colixes[p.centralAtom.i]) + " " + JU.C.getHexCode (p.colixEdge));
}
return s.toString ();
});
Clazz.defineStatics (c$,
"DEFAULT_DISTANCE_FACTOR", 1.85,
"DEFAULT_FACECENTEROFFSET", 0.25,
"EDGES_NONE", 0,
"EDGES_ALL", 1,
"EDGES_FRONT", 2,
"MAX_VERTICES", 250,
"FACE_COUNT_MAX", 247);
c$.randomPoint = c$.prototype.randomPoint = JU.P3.new3 (3141, 2718, 1414);
Clazz.defineStatics (c$,
"MODE_BONDING", 1,
"MODE_POINTS", 2,
"MODE_ITERATE", 3,
"MODE_BITSET", 4,
"MODE_UNITCELL", 5,
"MODE_INFO", 6,
"DEFAULT_PLANAR_PARAM", 0.98,
"minDistanceForPlanarity", 0.1);
});
