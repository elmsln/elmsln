Clazz.declarePackage ("J.adapter.smarter");
Clazz.load (["JU.P3"], "J.adapter.smarter.XtalSymmetry", ["java.lang.Boolean", "$.Float", "java.util.Hashtable", "JU.BS", "$.Lst", "$.M3", "$.M4", "$.P3i", "$.PT", "$.SB", "$.V3", "J.adapter.smarter.Atom", "JS.Symmetry", "JU.BSUtil", "$.Logger"], function () {
c$ = Clazz.decorateAsClass (function () {
this.asc = null;
this.acr = null;
this.symmetry = null;
this.unitCellParams = null;
this.baseUnitCell = null;
this.symmetryRange = 0;
this.doCentroidUnitCell = false;
this.centroidPacked = false;
this.packingError = 0;
this.filterSymop = null;
this.applySymmetryToBonds = false;
this.latticeCells = null;
this.ptSupercell = null;
this.matSupercell = null;
this.trajectoryUnitCells = null;
this.doNormalize = true;
this.doPackUnitCell = false;
this.baseSymmetry = null;
this.sym2 = null;
this.rminx = 0;
this.rminy = 0;
this.rminz = 0;
this.rmaxx = 0;
this.rmaxy = 0;
this.rmaxz = 0;
this.ptOffset = null;
this.unitCellOffset = null;
this.minXYZ = null;
this.maxXYZ = null;
this.minXYZ0 = null;
this.maxXYZ0 = null;
this.checkAll = false;
this.bondCount0 = 0;
this.dtype = 3;
this.unitCellTranslations = null;
this.latticeOp = 0;
this.latticeOnly = false;
this.noSymmetryCount = 0;
this.firstSymmetryAtom = 0;
this.ptTemp = null;
this.mTemp = null;
this.nVib = 0;
Clazz.instantialize (this, arguments);
}, J.adapter.smarter, "XtalSymmetry");
Clazz.prepareFields (c$, function () {
this.unitCellParams =  Clazz.newFloatArray (6, 0);
this.ptOffset =  new JU.P3 ();
});
Clazz.makeConstructor (c$, 
function () {
});
Clazz.defineMethod (c$, "set", 
function (reader) {
this.acr = reader;
this.asc = reader.asc;
this.getSymmetry ();
return this;
}, "J.adapter.smarter.AtomSetCollectionReader");
Clazz.defineMethod (c$, "getSymmetry", 
function () {
return (this.symmetry == null ? (this.symmetry = this.acr.getInterface ("JS.Symmetry")) : this.symmetry);
});
Clazz.defineMethod (c$, "setSymmetry", 
function (symmetry) {
return (this.symmetry = symmetry);
}, "J.api.SymmetryInterface");
Clazz.defineMethod (c$, "setSymmetryRange", 
 function (factor) {
this.symmetryRange = factor;
this.asc.setInfo ("symmetryRange", Float.$valueOf (factor));
}, "~N");
Clazz.defineMethod (c$, "setLatticeCells", 
 function () {
this.latticeCells = this.acr.latticeCells;
var isLatticeRange = (this.latticeCells[0] <= 555 && this.latticeCells[1] >= 555 && (this.latticeCells[2] == 0 || this.latticeCells[2] == 1 || this.latticeCells[2] == -1));
this.doNormalize = this.latticeCells[0] != 0 && (!isLatticeRange || this.latticeCells[2] == 1);
this.applySymmetryToBonds = this.acr.applySymmetryToBonds;
this.doPackUnitCell = this.acr.doPackUnitCell;
this.doCentroidUnitCell = this.acr.doCentroidUnitCell;
this.centroidPacked = this.acr.centroidPacked;
this.filterSymop = this.acr.filterSymop;
if (this.acr.strSupercell == null) this.setSupercellFromPoint (this.acr.ptSupercell);
});
Clazz.defineMethod (c$, "setSupercellFromPoint", 
function (pt) {
this.ptSupercell = pt;
if (pt == null) {
this.matSupercell = null;
return;
}this.matSupercell =  new JU.M4 ();
this.matSupercell.m00 = pt.x;
this.matSupercell.m11 = pt.y;
this.matSupercell.m22 = pt.z;
this.matSupercell.m33 = 1;
JU.Logger.info ("Using supercell \n" + this.matSupercell);
}, "JU.P3");
Clazz.defineMethod (c$, "setUnitCell", 
 function (info, matUnitCellOrientation, unitCellOffset) {
this.unitCellParams =  Clazz.newFloatArray (info.length, 0);
this.unitCellOffset = unitCellOffset;
for (var i = 0; i < info.length; i++) this.unitCellParams[i] = info[i];

this.asc.haveUnitCell = true;
this.asc.setCurrentModelInfo ("unitCellParams", this.unitCellParams);
if (this.asc.isTrajectory) {
if (this.trajectoryUnitCells == null) {
this.trajectoryUnitCells =  new JU.Lst ();
this.asc.setInfo ("unitCells", this.trajectoryUnitCells);
}this.trajectoryUnitCells.addLast (this.unitCellParams);
}this.asc.setGlobalBoolean (2);
this.getSymmetry ().setUnitCell (this.unitCellParams, false);
if (unitCellOffset != null) {
this.symmetry.setOffsetPt (unitCellOffset);
this.asc.setCurrentModelInfo ("unitCellOffset", unitCellOffset);
}if (matUnitCellOrientation != null) {
this.symmetry.initializeOrientation (matUnitCellOrientation);
this.asc.setCurrentModelInfo ("matUnitCellOrientation", matUnitCellOrientation);
}}, "~A,JU.M3,JU.P3");
Clazz.defineMethod (c$, "addSpaceGroupOperation", 
function (xyz, andSetLattice) {
if (andSetLattice) this.setLatticeCells ();
this.symmetry.setSpaceGroup (this.doNormalize);
return this.symmetry.addSpaceGroupOperation (xyz, 0);
}, "~S,~B");
Clazz.defineMethod (c$, "setLatticeParameter", 
function (latt) {
this.symmetry.setSpaceGroup (this.doNormalize);
this.symmetry.setLattice (latt);
}, "~N");
Clazz.defineMethod (c$, "applySymmetryFromReader", 
function (readerSymmetry) {
this.asc.setCoordinatesAreFractional (this.acr.iHaveFractionalCoordinates);
this.setUnitCell (this.acr.unitCellParams, this.acr.matUnitCellOrientation, this.acr.unitCellOffset);
this.setAtomSetSpaceGroupName (this.acr.sgName);
this.setSymmetryRange (this.acr.symmetryRange);
if (this.acr.doConvertToFractional || this.acr.fileCoordinatesAreFractional) {
this.setLatticeCells ();
var doApplySymmetry = true;
if (this.acr.ignoreFileSpaceGroupName || !this.acr.iHaveSymmetryOperators) {
if (!this.acr.merging || readerSymmetry == null) readerSymmetry = this.acr.getNewSymmetry ();
doApplySymmetry = readerSymmetry.createSpaceGroup (this.acr.desiredSpaceGroupIndex, (this.acr.sgName.indexOf ("!") >= 0 ? "P1" : this.acr.sgName), this.acr.unitCellParams);
} else {
this.acr.doPreSymmetry ();
readerSymmetry = null;
}this.packingError = this.acr.packingError;
if (doApplySymmetry) {
if (readerSymmetry != null) this.symmetry.setSpaceGroupFrom (readerSymmetry);
this.applySymmetryLattice ();
if (readerSymmetry != null && this.filterSymop == null) this.setAtomSetSpaceGroupName (readerSymmetry.getSpaceGroupName ());
}}if (this.acr.iHaveFractionalCoordinates && this.acr.merging && readerSymmetry != null) {
var atoms = this.asc.atoms;
for (var i = this.asc.getLastAtomSetAtomIndex (), n = this.asc.ac; i < n; i++) readerSymmetry.toCartesian (atoms[i], true);

this.asc.setCoordinatesAreFractional (false);
this.acr.addVibrations = false;
}return this.symmetry;
}, "J.api.SymmetryInterface");
Clazz.defineMethod (c$, "setAtomSetSpaceGroupName", 
 function (spaceGroupName) {
this.asc.setCurrentModelInfo ("spaceGroup", spaceGroupName + "");
}, "~S");
Clazz.defineMethod (c$, "applySymmetryLattice", 
 function () {
if (!this.asc.coordinatesAreFractional || this.symmetry.getSpaceGroup () == null) return;
this.sym2 = null;
var maxX = this.latticeCells[0];
var maxY = this.latticeCells[1];
var maxZ = Math.abs (this.latticeCells[2]);
this.firstSymmetryAtom = this.asc.getLastAtomSetAtomIndex ();
var bsAtoms = null;
this.rminx = this.rminy = this.rminz = 3.4028235E38;
this.rmaxx = this.rmaxy = this.rmaxz = -3.4028235E38;
var pt0 = null;
if (this.acr.fillRange != null) {
if (this.asc.bsAtoms == null) this.asc.bsAtoms =  new JU.BS ();
bsAtoms = this.asc.bsAtoms;
bsAtoms.setBits (this.firstSymmetryAtom, this.asc.ac);
this.doPackUnitCell = false;
this.minXYZ =  new JU.P3i ();
this.maxXYZ = JU.P3i.new3 (1, 1, 1);
var oabc =  new Array (4);
for (var i = 0; i < 4; i++) oabc[i] = JU.P3.newP (this.acr.fillRange[i]);

this.adjustRangeMinMax (oabc);
if (this.sym2 == null) {
this.sym2 =  new JS.Symmetry ();
this.sym2.getUnitCell (this.acr.fillRange, false, null);
}this.applyAllSymmetry (this.acr.ms, bsAtoms);
pt0 =  new JU.P3 ();
var atoms = this.asc.atoms;
for (var i = this.asc.ac; --i >= this.firstSymmetryAtom; ) {
pt0.setT (atoms[i]);
this.symmetry.toCartesian (pt0, false);
this.sym2.toFractional (pt0, false);
if (this.acr.fixJavaFloat) JU.PT.fixPtFloats (pt0, 100000.0);
if (!this.isWithinCell (this.dtype, pt0, 0, 1, 0, 1, 0, 1, this.packingError)) bsAtoms.clear (i);
}
return;
}var offset = null;
this.nVib = 0;
var va = null;
var vb = null;
var vc = null;
this.baseSymmetry = this.symmetry;
var supercell = this.acr.strSupercell;
var oabc = null;
var isSuper = (supercell != null && supercell.indexOf (",") >= 0);
if (isSuper) {
oabc = this.symmetry.getV0abc (supercell);
if (oabc != null) {
this.minXYZ =  new JU.P3i ();
this.maxXYZ = JU.P3i.new3 (maxX, maxY, maxZ);
this.symmetry.setMinMaxLatticeParameters (this.minXYZ, this.maxXYZ);
pt0 = JU.P3.newP (oabc[0]);
va = JU.P3.newP (oabc[1]);
vb = JU.P3.newP (oabc[2]);
vc = JU.P3.newP (oabc[3]);
this.adjustRangeMinMax (oabc);
}}var iAtomFirst = this.asc.getLastAtomSetAtomIndex ();
if (this.rminx == 3.4028235E38) {
this.matSupercell = null;
supercell = null;
oabc = null;
} else {
var doPack0 = this.doPackUnitCell;
this.doPackUnitCell = doPack0;
if (this.asc.bsAtoms == null) this.asc.bsAtoms = JU.BSUtil.newBitSet2 (0, this.asc.ac);
bsAtoms = this.asc.bsAtoms;
this.applyAllSymmetry (this.acr.ms, null);
this.doPackUnitCell = doPack0;
var atoms = this.asc.atoms;
var atomCount = this.asc.ac;
for (var i = iAtomFirst; i < atomCount; i++) {
this.symmetry.toCartesian (atoms[i], true);
bsAtoms.set (i);
}
this.symmetry = null;
this.symmetry = this.getSymmetry ();
this.setUnitCell ( Clazz.newFloatArray (-1, [0, 0, 0, 0, 0, 0, va.x, va.y, va.z, vb.x, vb.y, vb.z, vc.x, vc.y, vc.z]), null, offset);
this.setAtomSetSpaceGroupName (oabc == null || supercell == null ? "P1" : "cell=" + supercell);
this.symmetry.setSpaceGroup (this.doNormalize);
this.symmetry.addSpaceGroupOperation ("x,y,z", 0);
if (pt0 != null) this.symmetry.toFractional (pt0, true);
for (var i = iAtomFirst; i < atomCount; i++) {
this.symmetry.toFractional (atoms[i], true);
if (pt0 != null) atoms[i].sub (pt0);
}
this.asc.haveAnisou = false;
this.asc.setCurrentModelInfo ("matUnitCellOrientation", null);
}this.minXYZ =  new JU.P3i ();
this.maxXYZ = JU.P3i.new3 (maxX, maxY, maxZ);
this.symmetry.setMinMaxLatticeParameters (this.minXYZ, this.maxXYZ);
if (oabc == null) {
this.applyAllSymmetry (this.acr.ms, bsAtoms);
return;
}if (this.acr.forcePacked || this.doPackUnitCell) {
var bs = this.asc.bsAtoms;
var atoms = this.asc.atoms;
if (bs == null) bs = this.asc.bsAtoms = JU.BSUtil.newBitSet2 (0, this.asc.ac);
for (var i = bs.nextSetBit (iAtomFirst); i >= 0; i = bs.nextSetBit (i + 1)) {
if (!this.isWithinCell (this.dtype, atoms[i], this.minXYZ.x, this.maxXYZ.x, this.minXYZ.y, this.maxXYZ.y, this.minXYZ.z, this.maxXYZ.z, this.packingError)) bs.clear (i);
}
}});
Clazz.defineMethod (c$, "adjustRangeMinMax", 
 function (oabc) {
var pa =  new JU.P3 ();
var pb =  new JU.P3 ();
var pc =  new JU.P3 ();
if (this.acr.forcePacked) {
pa.setT (oabc[1]);
pb.setT (oabc[2]);
pc.setT (oabc[3]);
pa.scale (this.packingError);
pb.scale (this.packingError);
pc.scale (this.packingError);
}oabc[0].scaleAdd2 (this.minXYZ.x, oabc[1], oabc[0]);
oabc[0].scaleAdd2 (this.minXYZ.y, oabc[2], oabc[0]);
oabc[0].scaleAdd2 (this.minXYZ.z, oabc[3], oabc[0]);
oabc[0].sub (pa);
oabc[0].sub (pb);
oabc[0].sub (pc);
var pt = JU.P3.newP (oabc[0]);
this.symmetry.toFractional (pt, true);
this.setSymmetryMinMax (pt);
oabc[1].scale (this.maxXYZ.x - this.minXYZ.x);
oabc[2].scale (this.maxXYZ.y - this.minXYZ.y);
oabc[3].scale (this.maxXYZ.z - this.minXYZ.z);
oabc[1].scaleAdd2 (2, pa, oabc[1]);
oabc[2].scaleAdd2 (2, pb, oabc[2]);
oabc[3].scaleAdd2 (2, pc, oabc[3]);
for (var i = 0; i < 3; i++) {
for (var j = i + 1; j < 4; j++) {
pt.add2 (oabc[i], oabc[j]);
if (i != 0) pt.add (oabc[0]);
this.symmetry.toFractional (pt, false);
this.setSymmetryMinMax (pt);
}
}
this.symmetry.toCartesian (pt, false);
pt.add (oabc[1]);
this.symmetry.toFractional (pt, false);
this.setSymmetryMinMax (pt);
this.minXYZ = JU.P3i.new3 (Clazz.doubleToInt (Math.min (0, Math.floor (this.rminx + 0.001))), Clazz.doubleToInt (Math.min (0, Math.floor (this.rminy + 0.001))), Clazz.doubleToInt (Math.min (0, Math.floor (this.rminz + 0.001))));
this.maxXYZ = JU.P3i.new3 (Clazz.doubleToInt (Math.max (1, Math.ceil (this.rmaxx - 0.001))), Clazz.doubleToInt (Math.max (1, Math.ceil (this.rmaxy - 0.001))), Clazz.doubleToInt (Math.max (1, Math.ceil (this.rmaxz - 0.001))));
}, "~A");
Clazz.defineMethod (c$, "setSymmetryMinMax", 
 function (c) {
if (this.rminx > c.x) this.rminx = c.x;
if (this.rminy > c.y) this.rminy = c.y;
if (this.rminz > c.z) this.rminz = c.z;
if (this.rmaxx < c.x) this.rmaxx = c.x;
if (this.rmaxy < c.y) this.rmaxy = c.y;
if (this.rmaxz < c.z) this.rmaxz = c.z;
}, "JU.P3");
Clazz.defineMethod (c$, "isWithinCell", 
function (dtype, pt, minX, maxX, minY, maxY, minZ, maxZ, slop) {
return (pt.x > minX - slop && pt.x < maxX + slop && (dtype < 2 || pt.y > minY - slop && pt.y < maxY + slop) && (dtype < 3 || pt.z > minZ - slop && pt.z < maxZ + slop));
}, "~N,JU.P3,~N,~N,~N,~N,~N,~N,~N");
Clazz.defineMethod (c$, "applyAllSymmetry", 
 function (ms, bsAtoms) {
if (this.asc.ac == 0) return;
this.noSymmetryCount = (this.asc.baseSymmetryAtomCount == 0 ? this.asc.getLastAtomSetAtomCount () : this.asc.baseSymmetryAtomCount);
this.asc.setTensors ();
this.bondCount0 = this.asc.bondCount;
this.finalizeSymmetry (this.symmetry);
var operationCount = this.symmetry.getSpaceGroupOperationCount ();
this.dtype = Clazz.floatToInt (this.symmetry.getUnitCellInfoType (6));
this.symmetry.setMinMaxLatticeParameters (this.minXYZ, this.maxXYZ);
if (this.doCentroidUnitCell) this.asc.setInfo ("centroidMinMax",  Clazz.newIntArray (-1, [this.minXYZ.x, this.minXYZ.y, this.minXYZ.z, this.maxXYZ.x, this.maxXYZ.y, this.maxXYZ.z, (this.centroidPacked ? 1 : 0)]));
if (this.ptSupercell != null) {
this.asc.setCurrentModelInfo ("supercell", this.ptSupercell);
switch (this.dtype) {
case 3:
this.minXYZ.z *= Clazz.floatToInt (Math.abs (this.ptSupercell.z));
this.maxXYZ.z *= Clazz.floatToInt (Math.abs (this.ptSupercell.z));
case 2:
this.minXYZ.y *= Clazz.floatToInt (Math.abs (this.ptSupercell.y));
this.maxXYZ.y *= Clazz.floatToInt (Math.abs (this.ptSupercell.y));
case 1:
this.minXYZ.x *= Clazz.floatToInt (Math.abs (this.ptSupercell.x));
this.maxXYZ.x *= Clazz.floatToInt (Math.abs (this.ptSupercell.x));
}
}if (this.doCentroidUnitCell || this.doPackUnitCell || this.symmetryRange != 0 && this.maxXYZ.x - this.minXYZ.x == 1 && this.maxXYZ.y - this.minXYZ.y == 1 && this.maxXYZ.z - this.minXYZ.z == 1) {
this.minXYZ0 = JU.P3.new3 (this.minXYZ.x, this.minXYZ.y, this.minXYZ.z);
this.maxXYZ0 = JU.P3.new3 (this.maxXYZ.x, this.maxXYZ.y, this.maxXYZ.z);
if (ms != null) {
ms.setMinMax0 (this.minXYZ0, this.maxXYZ0);
this.minXYZ.set (Clazz.floatToInt (this.minXYZ0.x), Clazz.floatToInt (this.minXYZ0.y), Clazz.floatToInt (this.minXYZ0.z));
this.maxXYZ.set (Clazz.floatToInt (this.maxXYZ0.x), Clazz.floatToInt (this.maxXYZ0.y), Clazz.floatToInt (this.maxXYZ0.z));
}switch (this.dtype) {
case 3:
this.minXYZ.z--;
this.maxXYZ.z++;
case 2:
this.minXYZ.y--;
this.maxXYZ.y++;
case 1:
this.minXYZ.x--;
this.maxXYZ.x++;
}
}var nCells = (this.maxXYZ.x - this.minXYZ.x) * (this.maxXYZ.y - this.minXYZ.y) * (this.maxXYZ.z - this.minXYZ.z);
var cartesianCount = (this.asc.checkSpecial ? this.noSymmetryCount * operationCount * nCells : this.symmetryRange > 0 ? this.noSymmetryCount * operationCount : this.symmetryRange < 0 ? 1 : 1);
var cartesians =  new Array (cartesianCount);
for (var i = 0; i < this.noSymmetryCount; i++) this.asc.atoms[i + this.firstSymmetryAtom].bsSymmetry = JU.BS.newN (operationCount * (nCells + 1));

var pt = 0;
var unitCells =  Clazz.newIntArray (nCells, 0);
this.unitCellTranslations =  new Array (nCells);
var iCell = 0;
var cell555Count = 0;
var absRange = Math.abs (this.symmetryRange);
var checkCartesianRange = (this.symmetryRange != 0);
var checkRangeNoSymmetry = (this.symmetryRange < 0);
var checkRange111 = (this.symmetryRange > 0);
if (checkCartesianRange) {
this.rminx = this.rminy = this.rminz = 3.4028235E38;
this.rmaxx = this.rmaxy = this.rmaxz = -3.4028235E38;
}var symmetry = this.symmetry;
var lastSymmetry = symmetry;
this.latticeOp = symmetry.getLatticeOp ();
this.checkAll = (this.asc.atomSetCount == 1 && this.asc.checkSpecial && this.latticeOp >= 0);
this.latticeOnly = (this.asc.checkLatticeOnly && this.latticeOp >= 0);
var pttemp = null;
var op = symmetry.getSpaceGroupOperation (0);
if (this.doPackUnitCell) {
pttemp =  new JU.P3 ();
this.ptOffset.set (0, 0, 0);
}for (var tx = this.minXYZ.x; tx < this.maxXYZ.x; tx++) for (var ty = this.minXYZ.y; ty < this.maxXYZ.y; ty++) for (var tz = this.minXYZ.z; tz < this.maxXYZ.z; tz++) {
this.unitCellTranslations[iCell] = JU.V3.new3 (tx, ty, tz);
unitCells[iCell++] = 555 + tx * 100 + ty * 10 + tz;
if (tx != 0 || ty != 0 || tz != 0 || cartesians.length == 0) continue;
for (pt = 0; pt < this.noSymmetryCount; pt++) {
var atom = this.asc.atoms[this.firstSymmetryAtom + pt];
if (ms != null) {
symmetry = ms.getAtomSymmetry (atom, this.symmetry);
if (symmetry !== lastSymmetry) {
if (symmetry.getSpaceGroupOperationCount () == 0) this.finalizeSymmetry (lastSymmetry = symmetry);
op = symmetry.getSpaceGroupOperation (0);
}}var c = JU.P3.newP (atom);
op.rotTrans (c);
symmetry.toCartesian (c, false);
if (this.doPackUnitCell) {
symmetry.toUnitCell (c, this.ptOffset);
pttemp.setT (c);
symmetry.toFractional (pttemp, false);
if (this.acr.fixJavaFloat) JU.PT.fixPtFloats (pttemp, 100000.0);
if (bsAtoms == null) atom.setT (pttemp);
 else if (atom.distance (pttemp) < 0.0001) bsAtoms.set (atom.index);
 else {
bsAtoms.clear (atom.index);
continue;
}}if (bsAtoms != null) atom.bsSymmetry.clearAll ();
atom.bsSymmetry.set (iCell * operationCount);
atom.bsSymmetry.set (0);
if (checkCartesianRange) this.setSymmetryMinMax (c);
if (pt < cartesianCount) cartesians[pt] = c;
}
if (checkRangeNoSymmetry) {
this.rminx -= absRange;
this.rminy -= absRange;
this.rminz -= absRange;
this.rmaxx += absRange;
this.rmaxy += absRange;
this.rmaxz += absRange;
}cell555Count = pt = this.symmetryAddAtoms (0, 0, 0, 0, pt, iCell * operationCount, cartesians, ms);
}


if (checkRange111) {
this.rminx -= absRange;
this.rminy -= absRange;
this.rminz -= absRange;
this.rmaxx += absRange;
this.rmaxy += absRange;
this.rmaxz += absRange;
}iCell = 0;
for (var tx = this.minXYZ.x; tx < this.maxXYZ.x; tx++) for (var ty = this.minXYZ.y; ty < this.maxXYZ.y; ty++) for (var tz = this.minXYZ.z; tz < this.maxXYZ.z; tz++) {
iCell++;
if (tx != 0 || ty != 0 || tz != 0) pt = this.symmetryAddAtoms (tx, ty, tz, cell555Count, pt, iCell * operationCount, cartesians, ms);
}


if (iCell * this.noSymmetryCount == this.asc.ac - this.firstSymmetryAtom) this.duplicateAtomProperties (iCell);
this.setSymmetryOps ();
this.asc.setCurrentModelInfo ("presymmetryAtomIndex", Integer.$valueOf (this.firstSymmetryAtom));
this.asc.setCurrentModelInfo ("presymmetryAtomCount", Integer.$valueOf (this.noSymmetryCount));
this.asc.setCurrentModelInfo ("latticeDesignation", symmetry.getLatticeDesignation ());
this.asc.setCurrentModelInfo ("unitCellRange", unitCells);
this.asc.setCurrentModelInfo ("unitCellTranslations", this.unitCellTranslations);
this.baseUnitCell = this.unitCellParams;
this.unitCellParams =  Clazz.newFloatArray (6, 0);
this.reset ();
}, "J.adapter.smarter.MSInterface,JU.BS");
Clazz.defineMethod (c$, "symmetryAddAtoms", 
 function (transX, transY, transZ, baseCount, pt, iCellOpPt, cartesians, ms) {
var isBaseCell = (baseCount == 0);
var addBonds = (this.bondCount0 > this.asc.bondIndex0 && this.applySymmetryToBonds);
var atomMap = (addBonds ?  Clazz.newIntArray (this.noSymmetryCount, 0) : null);
if (this.doPackUnitCell) this.ptOffset.set (transX, transY, transZ);
var range2 = this.symmetryRange * this.symmetryRange;
var checkRangeNoSymmetry = (this.symmetryRange < 0);
var checkRange111 = (this.symmetryRange > 0);
var checkSymmetryMinMax = (isBaseCell && checkRange111);
checkRange111 = new Boolean (checkRange111 & !isBaseCell).valueOf ();
var nOperations = this.symmetry.getSpaceGroupOperationCount ();
var checkSpecial = (nOperations == 1 && !this.doPackUnitCell ? false : this.asc.checkSpecial);
var checkSymmetryRange = (checkRangeNoSymmetry || checkRange111);
var checkDistances = (checkSpecial || checkSymmetryRange);
var addCartesian = (checkSpecial || checkSymmetryMinMax);
var symmetry = this.symmetry;
if (checkRangeNoSymmetry) baseCount = this.noSymmetryCount;
var atomMax = this.firstSymmetryAtom + this.noSymmetryCount;
var ptAtom =  new JU.P3 ();
var code = null;
var subSystemId = '\u0000';
for (var iSym = 0; iSym < nOperations; iSym++) {
if (isBaseCell && iSym == 0 || this.latticeOnly && iSym > 0 && iSym != this.latticeOp) continue;
var pt0 = (checkSpecial ? pt : checkRange111 ? baseCount : 0);
var spinOp = (this.asc.vibScale == 0 ? symmetry.getSpinOp (iSym) : this.asc.vibScale);
for (var i = this.firstSymmetryAtom; i < atomMax; i++) {
var a = this.asc.atoms[i];
if (a.ignoreSymmetry) continue;
if (this.asc.bsAtoms != null && !this.asc.bsAtoms.get (i)) continue;
if (ms == null) {
symmetry.newSpaceGroupPoint (iSym, a, ptAtom, transX, transY, transZ);
} else {
symmetry = ms.getAtomSymmetry (a, this.symmetry);
symmetry.newSpaceGroupPoint (iSym, a, ptAtom, transX, transY, transZ);
code = symmetry.getSpaceGroupOperationCode (iSym);
if (code != null) {
subSystemId = code.charAt (0);
symmetry = ms.getSymmetryFromCode (code);
if (symmetry.getSpaceGroupOperationCount () == 0) this.finalizeSymmetry (symmetry);
}}if (this.acr.fixJavaFloat) JU.PT.fixPtFloats (ptAtom, 100000.0);
var c = JU.P3.newP (ptAtom);
symmetry.toCartesian (c, false);
if (this.doPackUnitCell) {
symmetry.toUnitCell (c, this.ptOffset);
ptAtom.setT (c);
symmetry.toFractional (ptAtom, false);
if (this.acr.fixJavaFloat) JU.PT.fixPtFloats (ptAtom, 100000.0);
if (!this.isWithinCell (this.dtype, ptAtom, this.minXYZ0.x, this.maxXYZ0.x, this.minXYZ0.y, this.maxXYZ0.y, this.minXYZ0.z, this.maxXYZ0.z, this.packingError)) continue;
}if (checkSymmetryMinMax) this.setSymmetryMinMax (c);
var special = null;
if (checkDistances) {
var minDist2 = 3.4028235E38;
if (checkSymmetryRange && (c.x < this.rminx || c.y < this.rminy || c.z < this.rminz || c.x > this.rmaxx || c.y > this.rmaxy || c.z > this.rmaxz)) continue;
var j0 = (this.checkAll ? this.asc.ac : pt0);
var name = a.atomName;
var id = (code == null ? a.altLoc : subSystemId);
for (var j = j0; --j >= 0; ) {
var pc = cartesians[j];
if (pc == null) continue;
var d2 = c.distanceSquared (pc);
if (checkSpecial && d2 < 0.0001) {
special = this.asc.atoms[this.firstSymmetryAtom + j];
if ((special.atomName == null || special.atomName.equals (name)) && special.altLoc == id) break;
special = null;
}if (checkRange111 && j < baseCount && d2 < minDist2) minDist2 = d2;
}
if (checkRange111 && minDist2 > range2) continue;
}var atomSite = a.atomSite;
if (special != null) {
if (addBonds) atomMap[atomSite] = special.index;
special.bsSymmetry.set (iCellOpPt + iSym);
special.bsSymmetry.set (iSym);
} else {
if (addBonds) atomMap[atomSite] = this.asc.ac;
var atom1 = this.asc.newCloneAtom (a);
if (this.asc.bsAtoms != null) this.asc.bsAtoms.set (atom1.index);
atom1.setT (ptAtom);
if (spinOp != 0 && atom1.vib != null) {
symmetry.getSpaceGroupOperation (iSym).rotate (atom1.vib);
atom1.vib.scale (spinOp);
}atom1.atomSite = atomSite;
if (code != null) atom1.altLoc = subSystemId;
atom1.bsSymmetry = JU.BSUtil.newAndSetBit (iCellOpPt + iSym);
atom1.bsSymmetry.set (iSym);
if (addCartesian) cartesians[pt++] = c;
var tensors = a.tensors;
if (tensors != null) {
atom1.tensors = null;
for (var j = tensors.size (); --j >= 0; ) {
var t = tensors.get (j);
if (t == null) continue;
if (nOperations == 1) atom1.addTensor (t.copyTensor (), null, false);
 else this.addRotatedTensor (atom1, t, iSym, false, symmetry);
}
}}}
if (addBonds) {
var bonds = this.asc.bonds;
var atoms = this.asc.atoms;
for (var bondNum = this.asc.bondIndex0; bondNum < this.bondCount0; bondNum++) {
var bond = bonds[bondNum];
var atom1 = atoms[bond.atomIndex1];
var atom2 = atoms[bond.atomIndex2];
if (atom1 == null || atom2 == null) continue;
var iAtom1 = atomMap[atom1.atomSite];
var iAtom2 = atomMap[atom2.atomSite];
if (iAtom1 >= atomMax || iAtom2 >= atomMax) this.asc.addNewBondWithOrder (iAtom1, iAtom2, bond.order);
}
}}
return pt;
}, "~N,~N,~N,~N,~N,~N,~A,J.adapter.smarter.MSInterface");
Clazz.defineMethod (c$, "duplicateAtomProperties", 
 function (nTimes) {
var p = this.asc.getAtomSetAuxiliaryInfoValue (-1, "atomProperties");
if (p != null) for (var entry, $entry = p.entrySet ().iterator (); $entry.hasNext () && ((entry = $entry.next ()) || true);) {
var key = entry.getKey ();
var val = entry.getValue ();
if (Clazz.instanceOf (val, String)) {
var data = val;
var s =  new JU.SB ();
for (var i = nTimes; --i >= 0; ) s.append (data);

p.put (key, s.toString ());
} else {
var f = val;
var fnew =  Clazz.newFloatArray (f.length * nTimes, 0);
for (var i = nTimes; --i >= 0; ) System.arraycopy (f, 0, fnew, i * f.length, f.length);

}}
}, "~N");
Clazz.defineMethod (c$, "finalizeSymmetry", 
 function (symmetry) {
var name = this.asc.getAtomSetAuxiliaryInfoValue (-1, "spaceGroup");
symmetry.setFinalOperations (name, this.asc.atoms, this.firstSymmetryAtom, this.noSymmetryCount, this.doNormalize, this.filterSymop);
if (this.filterSymop != null || name == null || name.equals ("unspecified!")) this.setAtomSetSpaceGroupName (symmetry.getSpaceGroupName ());
}, "J.api.SymmetryInterface");
Clazz.defineMethod (c$, "setSymmetryOps", 
 function () {
var operationCount = this.symmetry.getSpaceGroupOperationCount ();
if (operationCount > 0) {
var symmetryList =  new Array (operationCount);
for (var i = 0; i < operationCount; i++) symmetryList[i] = "" + this.symmetry.getSpaceGroupXyz (i, this.doNormalize);

this.asc.setCurrentModelInfo ("symmetryOperations", symmetryList);
this.asc.setCurrentModelInfo ("symmetryOps", this.symmetry.getSymmetryOperations ());
}this.asc.setCurrentModelInfo ("symmetryCount", Integer.$valueOf (operationCount));
});
Clazz.defineMethod (c$, "getOverallSpan", 
function () {
return (this.maxXYZ0 == null ? JU.V3.new3 (this.maxXYZ.x - this.minXYZ.x, this.maxXYZ.y - this.minXYZ.y, this.maxXYZ.z - this.minXYZ.z) : JU.V3.newVsub (this.maxXYZ0, this.minXYZ0));
});
Clazz.defineMethod (c$, "applySymmetryBio", 
function (thisBiomolecule, unitCellParams, applySymmetryToBonds, filter) {
if (this.latticeCells != null && this.latticeCells[0] != 0) {
JU.Logger.error ("Cannot apply biomolecule when lattice cells are indicated");
return;
}var particleMode = (filter.indexOf ("BYCHAIN") >= 0 ? 1 : filter.indexOf ("BYSYMOP") >= 0 ? 2 : 0);
this.doNormalize = false;
var biomts = thisBiomolecule.get ("biomts");
var biomtchains = thisBiomolecule.get ("chains");
if (biomts.size () < 2) return;
if (biomtchains.get (0).equals (biomtchains.get (1))) biomtchains = null;
this.symmetry = null;
if (!Float.isNaN (unitCellParams[0])) this.setUnitCell (unitCellParams, null, this.unitCellOffset);
this.getSymmetry ().setSpaceGroup (this.doNormalize);
this.addSpaceGroupOperation ("x,y,z", false);
var name = thisBiomolecule.get ("name");
this.setAtomSetSpaceGroupName (this.acr.sgName = name);
var len = biomts.size ();
this.applySymmetryToBonds = applySymmetryToBonds;
this.bondCount0 = this.asc.bondCount;
var addBonds = (this.bondCount0 > this.asc.bondIndex0 && applySymmetryToBonds);
var atomMap = (addBonds ?  Clazz.newIntArray (this.asc.ac, 0) : null);
this.firstSymmetryAtom = this.asc.getLastAtomSetAtomIndex ();
var atomMax = this.asc.ac;
var ht =  new java.util.Hashtable ();
var nChain = 0;
var atoms = this.asc.atoms;
switch (particleMode) {
case 1:
for (var i = atomMax; --i >= this.firstSymmetryAtom; ) {
var id = Integer.$valueOf (atoms[i].chainID);
var bs = ht.get (id);
if (bs == null) {
nChain++;
ht.put (id, bs =  new JU.BS ());
}bs.set (i);
}
this.asc.bsAtoms =  new JU.BS ();
for (var i = 0; i < nChain; i++) {
this.asc.bsAtoms.set (atomMax + i);
var a =  new J.adapter.smarter.Atom ();
a.set (0, 0, 0);
a.radius = 16;
this.asc.addAtom (a);
}
var ichain = 0;
for (var e, $e = ht.entrySet ().iterator (); $e.hasNext () && ((e = $e.next ()) || true);) {
var a = atoms[atomMax + ichain++];
var bs = e.getValue ();
for (var i = bs.nextSetBit (0); i >= 0; i = bs.nextSetBit (i + 1)) a.add (atoms[i]);

a.scale (1 / bs.cardinality ());
a.atomName = "Pt" + ichain;
a.chainID = e.getKey ().intValue ();
}
this.firstSymmetryAtom = atomMax;
atomMax += nChain;
break;
case 2:
this.asc.bsAtoms =  new JU.BS ();
this.asc.bsAtoms.set (atomMax);
var a = atoms[atomMax] =  new J.adapter.smarter.Atom ();
a.set (0, 0, 0);
for (var i = atomMax; --i >= this.firstSymmetryAtom; ) a.add (atoms[i]);

a.scale (1 / (atomMax - this.firstSymmetryAtom));
a.atomName = "Pt";
a.radius = 16;
this.asc.addAtom (a);
this.firstSymmetryAtom = atomMax++;
break;
}
if (filter.indexOf ("#<") >= 0) {
len = Math.min (len, JU.PT.parseInt (filter.substring (filter.indexOf ("#<") + 2)) - 1);
filter = JU.PT.rep (filter, "#<", "_<");
}for (var iAtom = this.firstSymmetryAtom; iAtom < atomMax; iAtom++) atoms[iAtom].bsSymmetry = JU.BSUtil.newAndSetBit (0);

for (var i = (biomtchains == null ? 1 : 0); i < len; i++) {
if (filter.indexOf ("!#") >= 0) {
if (filter.indexOf ("!#" + (i + 1) + ";") >= 0) continue;
} else if (filter.indexOf ("#") >= 0 && filter.indexOf ("#" + (i + 1) + ";") < 0) {
continue;
}var mat = biomts.get (i);
var chains = (biomtchains == null ? null : biomtchains.get (i));
for (var iAtom = this.firstSymmetryAtom; iAtom < atomMax; iAtom++) {
if (this.asc.bsAtoms != null && !this.asc.bsAtoms.get (iAtom)) continue;
if (chains != null && chains.indexOf (":" + this.acr.vwr.getChainIDStr (atoms[iAtom].chainID) + ";") < 0) continue;
try {
var atomSite = atoms[iAtom].atomSite;
var atom1;
if (addBonds) atomMap[atomSite] = this.asc.ac;
atom1 = this.asc.newCloneAtom (atoms[iAtom]);
if (this.asc.bsAtoms != null) this.asc.bsAtoms.set (atom1.index);
atom1.atomSite = atomSite;
mat.rotTrans (atom1);
atom1.bsSymmetry = JU.BSUtil.newAndSetBit (i);
if (addBonds) {
for (var bondNum = this.asc.bondIndex0; bondNum < this.bondCount0; bondNum++) {
var bond = this.asc.bonds[bondNum];
var iAtom1 = atomMap[atoms[bond.atomIndex1].atomSite];
var iAtom2 = atomMap[atoms[bond.atomIndex2].atomSite];
if (iAtom1 >= atomMax || iAtom2 >= atomMax) this.asc.addNewBondWithOrder (iAtom1, iAtom2, bond.order);
}
}} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
this.asc.errorMessage = "appendAtomCollection error: " + e;
} else {
throw e;
}
}
}
if (i > 0) this.symmetry.addBioMoleculeOperation (mat, false);
}
if (biomtchains != null) {
if (this.asc.bsAtoms == null) this.asc.bsAtoms = JU.BSUtil.newBitSet2 (0, this.asc.ac);
for (var iAtom = this.firstSymmetryAtom; iAtom < atomMax; iAtom++) this.asc.bsAtoms.clear (iAtom);

}this.noSymmetryCount = atomMax - this.firstSymmetryAtom;
this.asc.setCurrentModelInfo ("presymmetryAtomIndex", Integer.$valueOf (this.firstSymmetryAtom));
this.asc.setCurrentModelInfo ("presymmetryAtomCount", Integer.$valueOf (this.noSymmetryCount));
this.asc.setCurrentModelInfo ("biosymmetryCount", Integer.$valueOf (len));
this.asc.setCurrentModelInfo ("biosymmetry", this.symmetry);
this.finalizeSymmetry (this.symmetry);
this.setSymmetryOps ();
this.reset ();
}, "java.util.Map,~A,~B,~S");
Clazz.defineMethod (c$, "reset", 
 function () {
this.asc.coordinatesAreFractional = false;
this.asc.setCurrentModelInfo ("hasSymmetry", Boolean.TRUE);
this.asc.setGlobalBoolean (1);
});
Clazz.defineMethod (c$, "addRotatedTensor", 
function (a, t, iSym, reset, symmetry) {
if (this.ptTemp == null) {
this.ptTemp =  new JU.P3 ();
this.mTemp =  new JU.M3 ();
}return a.addTensor ((this.acr.getInterface ("JU.Tensor")).setFromEigenVectors (symmetry.rotateAxes (iSym, t.eigenVectors, this.ptTemp, this.mTemp), t.eigenValues, t.isIsotropic ? "iso" : t.type, t.id, t), null, reset);
}, "J.adapter.smarter.Atom,JU.Tensor,~N,~B,J.api.SymmetryInterface");
Clazz.defineMethod (c$, "setTensors", 
function () {
var n = this.asc.ac;
for (var i = this.asc.getLastAtomSetAtomIndex (); i < n; i++) {
var a = this.asc.atoms[i];
if (a.anisoBorU == null) continue;
a.addTensor (this.symmetry.getTensor (this.acr.vwr, a.anisoBorU), null, false);
if (Float.isNaN (a.bfactor)) a.bfactor = a.anisoBorU[7] * 100;
a.anisoBorU = null;
}
});
Clazz.defineMethod (c$, "setTimeReversal", 
function (op, timeRev) {
this.symmetry.setTimeReversal (op, timeRev);
}, "~N,~N");
Clazz.defineMethod (c$, "rotateToSuperCell", 
function (t) {
if (this.matSupercell != null) this.matSupercell.rotTrans (t);
}, "JU.V3");
Clazz.defineMethod (c$, "setSpinVectors", 
function () {
if (this.nVib > 0 || this.asc.iSet < 0 || !this.acr.vibsFractional) return this.nVib;
var i0 = this.asc.getAtomSetAtomIndex (this.asc.iSet);
var sym = this.getBaseSymmetry ();
for (var i = this.asc.ac; --i >= i0; ) {
var v = this.asc.atoms[i].vib;
if (v != null) {
if (v.modDim > 0) {
(v).setMoment ();
} else {
v = v.clone ();
sym.toCartesian (v, true);
this.asc.atoms[i].vib = v;
}this.nVib++;
}}
return this.nVib;
});
Clazz.defineMethod (c$, "scaleFractionalVibs", 
function () {
var params = this.getBaseSymmetry ().getUnitCellParams ();
var ptScale = JU.P3.new3 (1 / params[0], 1 / params[1], 1 / params[2]);
var i0 = this.asc.getAtomSetAtomIndex (this.asc.iSet);
for (var i = this.asc.ac; --i >= i0; ) {
var v = this.asc.atoms[i].vib;
if (v != null) {
v.scaleT (ptScale);
}}
});
Clazz.defineMethod (c$, "getBaseSymmetry", 
function () {
return (this.baseSymmetry == null ? this.symmetry : this.baseSymmetry);
});
Clazz.defineMethod (c$, "finalizeUnitCell", 
function (ptSupercell) {
if (ptSupercell != null && this.baseUnitCell != null) {
this.baseUnitCell[22] = Math.max (1, Clazz.floatToInt (ptSupercell.x));
this.baseUnitCell[23] = Math.max (1, Clazz.floatToInt (ptSupercell.y));
this.baseUnitCell[24] = Math.max (1, Clazz.floatToInt (ptSupercell.z));
}}, "JU.P3");
Clazz.defineStatics (c$,
"PARTICLE_NONE", 0,
"PARTICLE_CHAIN", 1,
"PARTICLE_SYMOP", 2);
});
