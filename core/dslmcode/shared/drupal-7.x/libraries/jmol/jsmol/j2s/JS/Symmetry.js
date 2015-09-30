Clazz.declarePackage ("JS");
Clazz.load (["J.api.SymmetryInterface"], "JS.Symmetry", ["JU.BS", "$.Lst", "$.M3", "$.M4", "$.P3", "$.V3", "J.api.Interface", "JS.PointGroup", "$.SpaceGroup", "$.SymmetryInfo", "$.SymmetryOperation", "$.UnitCell", "JU.Escape", "$.Logger", "$.SimpleUnitCell"], function () {
c$ = Clazz.decorateAsClass (function () {
this.pointGroup = null;
this.spaceGroup = null;
this.symmetryInfo = null;
this.unitCell = null;
this.$isBio = false;
this.desc = null;
Clazz.instantialize (this, arguments);
}, JS, "Symmetry", null, J.api.SymmetryInterface);
Clazz.overrideMethod (c$, "isBio", 
function () {
return this.$isBio;
});
Clazz.makeConstructor (c$, 
function () {
});
Clazz.overrideMethod (c$, "setPointGroup", 
function (siLast, atomset, bsAtoms, haveVibration, distanceTolerance, linearTolerance, localEnvOnly) {
this.pointGroup = JS.PointGroup.getPointGroup (siLast == null ? null : (siLast).pointGroup, atomset, bsAtoms, haveVibration, distanceTolerance, linearTolerance, localEnvOnly);
return this;
}, "J.api.SymmetryInterface,~A,JU.BS,~B,~N,~N,~B");
Clazz.overrideMethod (c$, "getPointGroupName", 
function () {
return this.pointGroup.getName ();
});
Clazz.overrideMethod (c$, "getPointGroupInfo", 
function (modelIndex, asDraw, asInfo, type, index, scale) {
if (!asDraw && !asInfo && this.pointGroup.textInfo != null) return this.pointGroup.textInfo;
 else if (asDraw && this.pointGroup.isDrawType (type, index, scale)) return this.pointGroup.drawInfo;
 else if (asInfo && this.pointGroup.info != null) return this.pointGroup.info;
return this.pointGroup.getInfo (modelIndex, asDraw, asInfo, type, index, scale);
}, "~N,~B,~B,~S,~N,~N");
Clazz.overrideMethod (c$, "setSpaceGroup", 
function (doNormalize) {
if (this.spaceGroup == null) this.spaceGroup = (JS.SpaceGroup.getNull (true)).set (doNormalize);
}, "~B");
Clazz.overrideMethod (c$, "addSpaceGroupOperation", 
function (xyz, opId) {
return this.spaceGroup.addSymmetry (xyz, opId, false);
}, "~S,~N");
Clazz.overrideMethod (c$, "addBioMoleculeOperation", 
function (mat, isReverse) {
this.$isBio = this.spaceGroup.isBio = true;
return this.spaceGroup.addSymmetry ((isReverse ? "!" : "") + "[[bio" + mat, 0, false);
}, "JU.M4,~B");
Clazz.overrideMethod (c$, "setLattice", 
function (latt) {
this.spaceGroup.setLatticeParam (latt);
}, "~N");
Clazz.defineMethod (c$, "getSpaceGroup", 
function () {
return this.spaceGroup;
});
Clazz.overrideMethod (c$, "setSpaceGroupFrom", 
function (symmetry) {
this.spaceGroup = symmetry.getSpaceGroup ();
}, "J.api.SymmetryInterface");
Clazz.overrideMethod (c$, "createSpaceGroup", 
function (desiredSpaceGroupIndex, name, object) {
this.spaceGroup = JS.SpaceGroup.createSpaceGroup (desiredSpaceGroupIndex, name, object);
if (this.spaceGroup != null && JU.Logger.debugging) JU.Logger.debug ("using generated space group " + this.spaceGroup.dumpInfo (null));
return this.spaceGroup != null;
}, "~N,~S,~O");
Clazz.overrideMethod (c$, "getSpaceGroupInfoStr", 
function (name, cellInfo) {
return JS.SpaceGroup.getInfo (name, cellInfo);
}, "~S,J.api.SymmetryInterface");
Clazz.overrideMethod (c$, "getLatticeDesignation", 
function () {
return this.spaceGroup.getLatticeDesignation ();
});
Clazz.overrideMethod (c$, "setFinalOperations", 
function (name, atoms, iAtomFirst, noSymmetryCount, doNormalize, filterSymop) {
if (name != null && (name.startsWith ("bio") || name.indexOf (" *(") >= 0)) this.spaceGroup.name = name;
if (filterSymop != null) {
var lst =  new JU.Lst ();
lst.addLast (this.spaceGroup.operations[0]);
for (var i = 1; i < this.spaceGroup.operationCount; i++) if (filterSymop.contains (" " + (i + 1) + " ")) lst.addLast (this.spaceGroup.operations[i]);

this.spaceGroup = JS.SpaceGroup.createSpaceGroup (-1, name + " *(" + filterSymop.trim () + ")", lst);
}this.spaceGroup.setFinalOperations (atoms, iAtomFirst, noSymmetryCount, doNormalize);
}, "~S,~A,~N,~N,~B,~S");
Clazz.overrideMethod (c$, "getSpaceGroupOperation", 
function (i) {
return (i >= this.spaceGroup.operations.length ? null : this.spaceGroup.finalOperations == null ? this.spaceGroup.operations[i] : this.spaceGroup.finalOperations[i]);
}, "~N");
Clazz.overrideMethod (c$, "getSpaceGroupXyz", 
function (i, doNormalize) {
return this.spaceGroup.getXyz (i, doNormalize);
}, "~N,~B");
Clazz.overrideMethod (c$, "newSpaceGroupPoint", 
function (i, atom1, atom2, transX, transY, transZ) {
if (this.spaceGroup.finalOperations == null) {
if (!this.spaceGroup.operations[i].isFinalized) this.spaceGroup.operations[i].doFinalize ();
this.spaceGroup.operations[i].newPoint (atom1, atom2, transX, transY, transZ);
return;
}this.spaceGroup.finalOperations[i].newPoint (atom1, atom2, transX, transY, transZ);
}, "~N,JU.P3,JU.P3,~N,~N,~N");
Clazz.overrideMethod (c$, "rotateAxes", 
function (iop, axes, ptTemp, mTemp) {
return (iop == 0 ? axes : this.spaceGroup.finalOperations[iop].rotateAxes (axes, this.unitCell, ptTemp, mTemp));
}, "~N,~A,JU.P3,JU.M3");
Clazz.overrideMethod (c$, "getSpaceGroupOperationCode", 
function (iOp) {
return this.spaceGroup.operations[iOp].subsystemCode;
}, "~N");
Clazz.overrideMethod (c$, "setTimeReversal", 
function (op, val) {
this.spaceGroup.operations[op].setTimeReversal (val);
}, "~N,~N");
Clazz.overrideMethod (c$, "getSpinOp", 
function (op) {
return this.spaceGroup.operations[op].getSpinOp ();
}, "~N");
Clazz.overrideMethod (c$, "addLatticeVectors", 
function (lattvecs) {
return this.spaceGroup.addLatticeVectors (lattvecs);
}, "JU.Lst");
Clazz.overrideMethod (c$, "getLatticeOp", 
function () {
return this.spaceGroup.latticeOp;
});
Clazz.overrideMethod (c$, "getOperationRsVs", 
function (iop) {
return (this.spaceGroup.finalOperations == null ? this.spaceGroup.operations : this.spaceGroup.finalOperations)[iop].rsvs;
}, "~N");
Clazz.overrideMethod (c$, "getSiteMultiplicity", 
function (pt) {
return this.spaceGroup.getSiteMultiplicity (pt, this.unitCell);
}, "JU.P3");
Clazz.overrideMethod (c$, "addOp", 
function (code, rs, vs, sigma) {
this.spaceGroup.isSSG = true;
var s = JS.SymmetryOperation.getXYZFromRsVs (rs, vs, false);
var i = this.spaceGroup.addSymmetry (s, -1, true);
this.spaceGroup.operations[i].setSigma (code, sigma);
return s;
}, "~S,JU.Matrix,JU.Matrix,JU.Matrix");
Clazz.overrideMethod (c$, "getMatrixFromString", 
function (xyz, rotTransMatrix, allowScaling, modDim) {
return JS.SymmetryOperation.getMatrixFromString (null, xyz, rotTransMatrix, allowScaling);
}, "~S,~A,~B,~N");
Clazz.overrideMethod (c$, "getSpaceGroupName", 
function () {
return (this.symmetryInfo != null ? this.symmetryInfo.sgName : this.spaceGroup != null ? this.spaceGroup.getName () : this.unitCell != null && this.unitCell.name.length > 0 ? "cell=" + this.unitCell.name : "");
});
Clazz.overrideMethod (c$, "getSpaceGroupOperationCount", 
function () {
return (this.symmetryInfo != null ? this.symmetryInfo.symmetryOperations.length : this.spaceGroup != null && this.spaceGroup.finalOperations != null ? this.spaceGroup.finalOperations.length : 0);
});
Clazz.overrideMethod (c$, "getCoordinatesAreFractional", 
function () {
return this.symmetryInfo == null || this.symmetryInfo.coordinatesAreFractional;
});
Clazz.overrideMethod (c$, "getCellRange", 
function () {
return this.symmetryInfo.cellRange;
});
Clazz.overrideMethod (c$, "getSymmetryInfoStr", 
function () {
return this.symmetryInfo.infoStr;
});
Clazz.overrideMethod (c$, "getSymmetryOperations", 
function () {
return this.symmetryInfo == null ? this.spaceGroup.finalOperations : this.symmetryInfo.symmetryOperations;
});
Clazz.overrideMethod (c$, "isPeriodic", 
function () {
return (this.symmetryInfo == null ? false : this.symmetryInfo.isPeriodic ());
});
Clazz.overrideMethod (c$, "setSymmetryInfo", 
function (modelIndex, modelAuxiliaryInfo, unitCellParams) {
this.symmetryInfo =  new JS.SymmetryInfo ();
var params = this.symmetryInfo.setSymmetryInfo (modelAuxiliaryInfo, unitCellParams);
if (params == null) return;
this.setUnitCell (params, modelAuxiliaryInfo.containsKey ("jmolData"));
this.unitCell.moreInfo = modelAuxiliaryInfo.get ("moreUnitCellInfo");
modelAuxiliaryInfo.put ("infoUnitCell", this.getUnitCellAsArray (false));
this.setOffsetPt (modelAuxiliaryInfo.get ("unitCellOffset"));
var matUnitCellOrientation = modelAuxiliaryInfo.get ("matUnitCellOrientation");
if (matUnitCellOrientation != null) this.initializeOrientation (matUnitCellOrientation);
if (JU.Logger.debugging) JU.Logger.debug ("symmetryInfos[" + modelIndex + "]:\n" + this.unitCell.dumpInfo (true));
}, "~N,java.util.Map,~A");
Clazz.overrideMethod (c$, "haveUnitCell", 
function () {
return (this.unitCell != null);
});
Clazz.overrideMethod (c$, "checkUnitCell", 
function (uc, cell, ptTemp, isAbsolute) {
uc.toFractional (ptTemp, isAbsolute);
var slop = 0.02;
return (ptTemp.x >= cell.x - 1 - slop && ptTemp.x <= cell.x + slop && ptTemp.y >= cell.y - 1 - slop && ptTemp.y <= cell.y + slop && ptTemp.z >= cell.z - 1 - slop && ptTemp.z <= cell.z + slop);
}, "J.api.SymmetryInterface,JU.P3,JU.P3,~B");
Clazz.overrideMethod (c$, "setUnitCell", 
function (unitCellParams, setRelative) {
this.unitCell = JS.UnitCell.newA (unitCellParams, setRelative);
}, "~A,~B");
Clazz.overrideMethod (c$, "unitCellEquals", 
function (uc2) {
return ((uc2)).unitCell.isSameAs (this.unitCell);
}, "J.api.SymmetryInterface");
Clazz.overrideMethod (c$, "getUnitCellState", 
function () {
return (this.unitCell == null ? "" : this.unitCell.getState ());
});
Clazz.overrideMethod (c$, "getMoreInfo", 
function () {
return this.unitCell.moreInfo;
});
Clazz.defineMethod (c$, "getUnitsymmetryInfo", 
function () {
return this.unitCell.dumpInfo (false);
});
Clazz.overrideMethod (c$, "initializeOrientation", 
function (mat) {
this.unitCell.initOrientation (mat);
}, "JU.M3");
Clazz.overrideMethod (c$, "unitize", 
function (ptFrac) {
this.unitCell.unitize (ptFrac);
}, "JU.P3");
Clazz.overrideMethod (c$, "toUnitCell", 
function (pt, offset) {
this.unitCell.toUnitCell (pt, offset);
}, "JU.P3,JU.P3");
Clazz.overrideMethod (c$, "toSupercell", 
function (fpt) {
return this.unitCell.toSupercell (fpt);
}, "JU.P3");
Clazz.defineMethod (c$, "toFractional", 
function (pt, isAbsolute) {
if (!this.$isBio) this.unitCell.toFractional (pt, isAbsolute);
}, "JU.T3,~B");
Clazz.overrideMethod (c$, "toCartesian", 
function (fpt, ignoreOffset) {
if (!this.$isBio) this.unitCell.toCartesian (fpt, ignoreOffset);
}, "JU.T3,~B");
Clazz.overrideMethod (c$, "getUnitCellParams", 
function () {
return this.unitCell.getUnitCellParams ();
});
Clazz.overrideMethod (c$, "getUnitCellAsArray", 
function (vectorsOnly) {
return this.unitCell.getUnitCellAsArray (vectorsOnly);
}, "~B");
Clazz.overrideMethod (c$, "getTensor", 
function (vwr, parBorU) {
if (parBorU == null) return null;
if (this.unitCell == null) this.unitCell = JS.UnitCell.newA ( Clazz.newFloatArray (-1, [1, 1, 1, 90, 90, 90]), true);
return this.unitCell.getTensor (vwr, parBorU);
}, "JV.Viewer,~A");
Clazz.overrideMethod (c$, "getUnitCellVerticesNoOffset", 
function () {
return this.unitCell.getVertices ();
});
Clazz.overrideMethod (c$, "getCartesianOffset", 
function () {
return this.unitCell.getCartesianOffset ();
});
Clazz.overrideMethod (c$, "getFractionalOffset", 
function () {
return this.unitCell.getFractionalOffset ();
});
Clazz.overrideMethod (c$, "setOffsetPt", 
function (pt) {
this.unitCell.setOffset (pt);
}, "JU.T3");
Clazz.overrideMethod (c$, "setOffset", 
function (nnn) {
var pt =  new JU.P3 ();
JU.SimpleUnitCell.ijkToPoint3f (nnn, pt, 0);
this.unitCell.setOffset (pt);
}, "~N");
Clazz.overrideMethod (c$, "getUnitCellMultiplier", 
function () {
return this.unitCell.getUnitCellMultiplier ();
});
Clazz.overrideMethod (c$, "getCanonicalCopy", 
function (scale, withOffset) {
return this.unitCell.getCanonicalCopy (scale, withOffset);
}, "~N,~B");
Clazz.overrideMethod (c$, "getUnitCellInfoType", 
function (infoType) {
return this.unitCell.getInfo (infoType);
}, "~N");
Clazz.overrideMethod (c$, "getUnitCellInfo", 
function () {
return this.unitCell.dumpInfo (false);
});
Clazz.overrideMethod (c$, "isSlab", 
function () {
return this.unitCell.isSlab ();
});
Clazz.overrideMethod (c$, "isPolymer", 
function () {
return this.unitCell.isPolymer ();
});
Clazz.overrideMethod (c$, "setMinMaxLatticeParameters", 
function (minXYZ, maxXYZ) {
this.unitCell.setMinMaxLatticeParameters (minXYZ, maxXYZ);
}, "JU.P3i,JU.P3i");
Clazz.overrideMethod (c$, "checkDistance", 
function (f1, f2, distance, dx, iRange, jRange, kRange, ptOffset) {
return this.unitCell.checkDistance (f1, f2, distance, dx, iRange, jRange, kRange, ptOffset);
}, "JU.P3,JU.P3,~N,~N,~N,~N,~N,JU.P3");
Clazz.overrideMethod (c$, "getUnitCellVectors", 
function () {
return this.unitCell.getUnitCellVectors ();
});
Clazz.overrideMethod (c$, "getUnitCell", 
function (points, setRelative, name) {
this.unitCell = JS.UnitCell.newP (points, setRelative);
if (name != null) this.unitCell.name = name;
return this;
}, "~A,~B,~S");
Clazz.overrideMethod (c$, "isSupercell", 
function () {
return this.unitCell.isSupercell ();
});
Clazz.overrideMethod (c$, "notInCentroid", 
function (modelSet, bsAtoms, minmax) {
try {
var bsDelete =  new JU.BS ();
var iAtom0 = bsAtoms.nextSetBit (0);
var molecules = modelSet.getMolecules ();
var moleculeCount = molecules.length;
var atoms = modelSet.at;
var isOneMolecule = (molecules[moleculeCount - 1].firstAtomIndex == modelSet.am[atoms[iAtom0].mi].firstAtomIndex);
var center =  new JU.P3 ();
var centroidPacked = (minmax[6] == 1);
nextMol : for (var i = moleculeCount; --i >= 0 && bsAtoms.get (molecules[i].firstAtomIndex); ) {
var bs = molecules[i].atomList;
center.set (0, 0, 0);
var n = 0;
for (var j = bs.nextSetBit (0); j >= 0; j = bs.nextSetBit (j + 1)) {
if (isOneMolecule || centroidPacked) {
center.setT (atoms[j]);
if (this.isNotCentroid (center, 1, minmax, centroidPacked)) {
if (isOneMolecule) bsDelete.set (j);
} else if (!isOneMolecule) {
continue nextMol;
}} else {
center.add (atoms[j]);
n++;
}}
if (centroidPacked || n > 0 && this.isNotCentroid (center, n, minmax, false)) bsDelete.or (bs);
}
return bsDelete;
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
return null;
} else {
throw e;
}
}
}, "JM.ModelSet,JU.BS,~A");
Clazz.defineMethod (c$, "isNotCentroid", 
 function (center, n, minmax, centroidPacked) {
center.scale (1 / n);
this.toFractional (center, false);
if (centroidPacked) return (center.x + 0.000005 <= minmax[0] || center.x - 0.000005 > minmax[3] || center.y + 0.000005 <= minmax[1] || center.y - 0.000005 > minmax[4] || center.z + 0.000005 <= minmax[2] || center.z - 0.000005 > minmax[5]);
return (center.x + 0.000005 <= minmax[0] || center.x + 0.00005 > minmax[3] || center.y + 0.000005 <= minmax[1] || center.y + 0.00005 > minmax[4] || center.z + 0.000005 <= minmax[2] || center.z + 0.00005 > minmax[5]);
}, "JU.P3,~N,~A,~B");
Clazz.defineMethod (c$, "getDesc", 
 function (modelSet) {
return (this.desc == null ? (this.desc = (J.api.Interface.getInterface ("JS.SymmetryDesc", modelSet.vwr, "eval"))) : this.desc);
}, "JM.ModelSet");
Clazz.overrideMethod (c$, "getSymmetryInfoAtom", 
function (modelSet, bsAtoms, xyz, op, pt, pt2, id, type) {
return this.getDesc (modelSet).getSymmetryInfoAtom (bsAtoms, xyz, op, pt, pt2, id, type, modelSet);
}, "JM.ModelSet,JU.BS,~S,~N,JU.P3,JU.P3,~S,~N");
Clazz.overrideMethod (c$, "getSymmetryInfoString", 
function (modelSet, modelIndex, symOp, pt1, pt2, drawID, type) {
return this.getDesc (modelSet).getSymmetryInfoString (this, modelIndex, symOp, pt1, pt2, drawID, type, modelSet);
}, "JM.ModelSet,~N,~N,JU.P3,JU.P3,~S,~S");
Clazz.overrideMethod (c$, "getSpaceGroupInfo", 
function (modelSet, sgName) {
return this.getDesc (modelSet).getSpaceGroupInfo (this, -1, sgName, 0, null, null, null, modelSet);
}, "JM.ModelSet,~S");
Clazz.overrideMethod (c$, "getSymmetryInfo", 
function (modelSet, iModel, iAtom, uc, xyz, op, pt, pt2, id, type) {
return this.getDesc (modelSet).getSymmetryInfo (this, iModel, iAtom, uc, xyz, op, pt, pt2, id, type, modelSet);
}, "JM.ModelSet,~N,~N,J.api.SymmetryInterface,~S,~N,JU.P3,JU.P3,~S,~N");
Clazz.overrideMethod (c$, "fcoord", 
function (p) {
return JS.SymmetryOperation.fcoord (p);
}, "JU.T3");
Clazz.overrideMethod (c$, "getV0abc", 
function (def) {
if (this.unitCell == null) return null;
var m;
var isRev = false;
if (Clazz.instanceOf (def, String)) {
var sdef = def;
if (sdef.indexOf (";") < 0) sdef += ";0,0,0";
isRev = sdef.startsWith ("!");
if (isRev) sdef = sdef.substring (1);
var symTemp =  new JS.Symmetry ();
symTemp.setSpaceGroup (false);
var i = symTemp.addSpaceGroupOperation ("=" + sdef, 0);
if (i < 0) return null;
m = symTemp.getSpaceGroupOperation (i);
(m).doFinalize ();
} else {
m = (Clazz.instanceOf (def, JU.M3) ? JU.M4.newMV (def,  new JU.P3 ()) : def);
}var pts =  new Array (4);
var pt =  new JU.P3 ();
var m3 =  new JU.M3 ();
m.getRotationScale (m3);
m.getTranslation (pt);
if (isRev) {
m3.invert ();
m3.transpose ();
m3.rotate (pt);
pt.scale (-1);
} else {
m3.transpose ();
}this.unitCell.toCartesian (pt, false);
pts[0] = JU.V3.newV (pt);
pts[1] = JU.V3.new3 (1, 0, 0);
pts[2] = JU.V3.new3 (0, 1, 0);
pts[3] = JU.V3.new3 (0, 0, 1);
for (var i = 1; i < 4; i++) {
m3.rotate (pts[i]);
this.unitCell.toCartesian (pts[i], true);
}
return pts;
}, "~O");
Clazz.overrideMethod (c$, "getQuaternionRotation", 
function (abc) {
return (this.unitCell == null ? null : this.unitCell.getQuaternionRotation (abc));
}, "~S");
Clazz.overrideMethod (c$, "getFractionalOrigin", 
function () {
return this.unitCell.getFractionalOrigin ();
});
Clazz.overrideMethod (c$, "setAxes", 
function (scale, axisPoints, fixedOrigin, originPoint) {
var vertices = this.getUnitCellVerticesNoOffset ();
var offset = this.getCartesianOffset ();
if (fixedOrigin == null) originPoint.add2 (offset, vertices[0]);
 else offset = fixedOrigin;
axisPoints[0].scaleAdd2 (scale, vertices[4], offset);
axisPoints[1].scaleAdd2 (scale, vertices[2], offset);
axisPoints[2].scaleAdd2 (scale, vertices[1], offset);
}, "~N,~A,JU.P3,JU.P3");
Clazz.overrideMethod (c$, "getState", 
function (commands) {
var pt = this.getFractionalOffset ();
var loadUC = false;
if (pt != null && (pt.x != 0 || pt.y != 0 || pt.z != 0)) {
commands.append ("; set unitcell ").append (JU.Escape.eP (pt));
loadUC = true;
}pt = this.getUnitCellMultiplier ();
if (pt != null) {
commands.append ("; set unitcell ").append (JU.Escape.eP (pt));
loadUC = true;
}return loadUC;
}, "JU.SB");
Clazz.overrideMethod (c$, "getIterator", 
function (vwr, atom, atoms, bsAtoms, radius) {
return (J.api.Interface.getInterface ("JS.UnitCellIterator", vwr, "script")).set (this, atom, atoms, bsAtoms, radius);
}, "JV.Viewer,JM.Atom,~A,JU.BS,~N");
});
