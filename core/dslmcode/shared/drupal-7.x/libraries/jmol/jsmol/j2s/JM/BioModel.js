Clazz.declarePackage ("JM");
Clazz.load (["JM.JmolBioModel", "$.JmolBioModelSet", "$.Model"], "JM.BioModel", ["java.lang.Boolean", "$.Character", "$.Float", "java.util.Hashtable", "JU.AU", "$.BS", "$.Lst", "$.PT", "$.SB", "J.api.Interface", "J.c.STR", "JM.Group", "JM.AlphaMonomer", "$.AlphaPolymer", "$.AminoPolymer", "$.Monomer", "$.Resolver", "JS.SV", "$.T", "JU.BSUtil", "$.Escape", "$.Logger"], function () {
c$ = Clazz.decorateAsClass (function () {
this.bioPolymerCount = 0;
this.bioPolymers = null;
this.isMutated = false;
this.defaultStructure = null;
this.vwr = null;
this.bx = null;
Clazz.instantialize (this, arguments);
}, JM, "BioModel", JM.Model, [JM.JmolBioModelSet, JM.JmolBioModel]);
Clazz.overrideMethod (c$, "getAllHeteroList", 
function (modelIndex) {
var htFull =  new java.util.Hashtable ();
var ok = false;
for (var i = this.ms.mc; --i >= 0; ) if (modelIndex < 0 || i == modelIndex) {
var ht = this.ms.getInfo (i, "hetNames");
if (ht == null) continue;
ok = true;
for (var entry, $entry = ht.entrySet ().iterator (); $entry.hasNext () && ((entry = $entry.next ()) || true);) {
var key = entry.getKey ();
htFull.put (key, entry.getValue ());
}
}
return (ok ? htFull : null);
}, "~N");
Clazz.overrideMethod (c$, "setAllProteinType", 
function (bs, type) {
var monomerIndexCurrent = -1;
var iLast = -1;
var bsModels = this.ms.getModelBS (bs, false);
this.setAllDefaultStructure (bsModels);
var at = this.ms.at;
var am = this.ms.am;
for (var i = bs.nextSetBit (0); i >= 0; i = bs.nextSetBit (i + 1)) {
if (iLast != i - 1) monomerIndexCurrent = -1;
monomerIndexCurrent = at[i].group.setProteinStructureType (type, monomerIndexCurrent);
var modelIndex = at[i].mi;
this.ms.proteinStructureTainted = am[modelIndex].structureTainted = true;
iLast = i = at[i].group.lastAtomIndex;
}
var lastStrucNo =  Clazz.newIntArray (this.ms.mc, 0);
for (var i = 0; i < this.ms.ac; ) {
var modelIndex = at[i].mi;
if (!bsModels.get (modelIndex)) {
i = am[modelIndex].firstAtomIndex + am[modelIndex].act;
continue;
}iLast = at[i].group.getStrucNo ();
if (iLast < 1000 && iLast > lastStrucNo[modelIndex]) lastStrucNo[modelIndex] = iLast;
i = at[i].group.lastAtomIndex + 1;
}
for (var i = 0; i < this.ms.ac; ) {
var modelIndex = at[i].mi;
if (!bsModels.get (modelIndex)) {
i = am[modelIndex].firstAtomIndex + am[modelIndex].act;
continue;
}if (at[i].group.getStrucNo () > 1000) at[i].group.setStrucNo (++lastStrucNo[modelIndex]);
i = at[i].group.lastAtomIndex + 1;
}
}, "JU.BS,J.c.STR");
Clazz.defineMethod (c$, "modelsOf", 
 function (bsAtoms, bsAtomsRet) {
var bsModels = JU.BS.newN (this.ms.mc);
var isAll = (bsAtoms == null);
var i0 = (isAll ? this.ms.ac - 1 : bsAtoms.nextSetBit (0));
for (var i = i0; i >= 0; i = (isAll ? i - 1 : bsAtoms.nextSetBit (i + 1))) {
var modelIndex = this.ms.am[this.ms.at[i].mi].trajectoryBaseIndex;
if (this.ms.isJmolDataFrameForModel (modelIndex)) continue;
bsModels.set (modelIndex);
bsAtomsRet.set (i);
}
return bsModels;
}, "JU.BS,JU.BS");
Clazz.overrideMethod (c$, "getAllDefaultStructures", 
function (bsAtoms, bsModified) {
var bsModels = this.modelsOf (bsAtoms, bsModified);
var ret =  new JU.SB ();
for (var i = bsModels.nextSetBit (0); i >= 0; i = bsModels.nextSetBit (i + 1)) if (this.ms.am[i].isBioModel && (this.ms.am[i]).defaultStructure != null) ret.append ((this.ms.am[i]).defaultStructure);

return ret.toString ();
}, "JU.BS,JU.BS");
Clazz.overrideMethod (c$, "calculateAllStuctures", 
function (bsAtoms, asDSSP, doReport, dsspIgnoreHydrogen, setStructure) {
var bsAllAtoms =  new JU.BS ();
var bsModelsExcluded = JU.BSUtil.copyInvert (this.modelsOf (bsAtoms, bsAllAtoms), this.ms.mc);
if (!setStructure) return this.ms.calculateStructuresAllExcept (bsModelsExcluded, asDSSP, doReport, dsspIgnoreHydrogen, false, false);
this.ms.recalculatePolymers (bsModelsExcluded);
var ret = this.ms.calculateStructuresAllExcept (bsModelsExcluded, asDSSP, doReport, dsspIgnoreHydrogen, true, false);
this.vwr.shm.resetBioshapes (bsAllAtoms);
this.ms.setStructureIndexes ();
return ret;
}, "JU.BS,~B,~B,~B,~B");
Clazz.overrideMethod (c$, "calculateAllStructuresExcept", 
function (alreadyDefined, asDSSP, doReport, dsspIgnoreHydrogen, setStructure, includeAlpha) {
var ret = "";
var bsModels = JU.BSUtil.copyInvert (alreadyDefined, this.ms.mc);
if (setStructure) this.setAllDefaultStructure (bsModels);
for (var i = bsModels.nextSetBit (0); i >= 0; i = bsModels.nextSetBit (i + 1)) if (this.ms.am[i].isBioModel) ret += (this.ms.am[i]).calculateStructures (asDSSP, doReport, dsspIgnoreHydrogen, setStructure, includeAlpha);

if (setStructure) this.ms.setStructureIndexes ();
return ret;
}, "JU.BS,~B,~B,~B,~B,~B");
Clazz.defineMethod (c$, "setAllDefaultStructure", 
function (bsModels) {
for (var i = bsModels.nextSetBit (0); i >= 0; i = bsModels.nextSetBit (i + 1)) if (this.ms.am[i].isBioModel) {
var m = this.ms.am[i];
if (m.defaultStructure == null) m.defaultStructure = this.getFullProteinStructureState (m.bsAtoms, 1073742158);
}
}, "JU.BS");
Clazz.overrideMethod (c$, "setAllStructureList", 
function (structureList) {
for (var iModel = this.ms.mc; --iModel >= 0; ) if (this.ms.am[iModel].isBioModel) {
var m = this.ms.am[iModel];
m.bioPolymers = JU.AU.arrayCopyObject (m.bioPolymers, m.bioPolymerCount);
for (var i = m.bioPolymerCount; --i >= 0; ) {
var bp = m.bioPolymers[i];
if (Clazz.instanceOf (bp, JM.AminoPolymer)) (bp).setStructureList (structureList);
}
}
}, "java.util.Map");
Clazz.overrideMethod (c$, "setAllConformation", 
function (bsAtoms) {
var bsModels = this.ms.getModelBS (bsAtoms, false);
for (var i = bsModels.nextSetBit (0); i >= 0; i = bsModels.nextSetBit (i + 1)) if (this.ms.am[i].isBioModel) {
var m = this.ms.am[i];
if (m.altLocCount > 0) for (var j = m.bioPolymerCount; --j >= 0; ) m.bioPolymers[j].setConformation (bsAtoms);

}
}, "JU.BS");
Clazz.overrideMethod (c$, "getAllPolymerPointsAndVectors", 
function (bs, vList, isTraceAlpha, sheetSmoothing) {
for (var i = 0; i < this.ms.mc; ++i) if (this.ms.am[i].isBioModel) {
var m = this.ms.am[i];
var last = 2147483646;
for (var ip = 0; ip < m.bioPolymerCount; ip++) last = m.bioPolymers[ip].getPolymerPointsAndVectors (last, bs, vList, isTraceAlpha, sheetSmoothing);

}
}, "JU.BS,JU.Lst,~B,~N");
Clazz.overrideMethod (c$, "calcSelectedMonomersCount", 
function () {
var bsSelected = this.vwr.bsA ();
for (var i = this.ms.mc; --i >= 0; ) if (this.ms.am[i].isBioModel) {
var m = this.ms.am[i];
for (var j = m.bioPolymerCount; --j >= 0; ) m.bioPolymers[j].calcSelectedMonomersCount (bsSelected);

}
});
Clazz.overrideMethod (c$, "getBioPolymerCountInModel", 
function (modelIndex) {
if (modelIndex < 0) {
var polymerCount = 0;
for (var i = this.ms.mc; --i >= 0; ) if (!this.ms.isTrajectorySubFrame (i) && this.ms.am[i].isBioModel) polymerCount += (this.ms.am[i]).getBioPolymerCount ();

return polymerCount;
}return (this.ms.isTrajectorySubFrame (modelIndex) || !this.ms.am[modelIndex].isBioModel ? 0 : (this.ms.am[modelIndex]).getBioPolymerCount ());
}, "~N");
Clazz.overrideMethod (c$, "calculateAllPolymers", 
function (groups, groupCount, baseGroupIndex, modelsExcluded) {
var checkConnections = !this.vwr.getBoolean (603979893);
if (groupCount < 0) groupCount = groups.length;
if (modelsExcluded != null) for (var j = 0; j < groupCount; ++j) {
var group = groups[j];
if (Clazz.instanceOf (group, JM.Monomer)) {
if ((group).bioPolymer != null && (!modelsExcluded.get (group.chain.model.modelIndex))) (group).setBioPolymer (null, -1);
}}
for (var i = 0, mc = this.ms.mc; i < mc; i++) if ((modelsExcluded == null || !modelsExcluded.get (i)) && this.ms.am[i].isBioModel) {
for (var j = baseGroupIndex; j < groupCount; ++j) {
var g = groups[j];
var model = g.getModel ();
if (!model.isBioModel || !(Clazz.instanceOf (g, JM.Monomer))) continue;
var doCheck = checkConnections && !this.ms.isJmolDataFrameForModel (this.ms.at[g.firstAtomIndex].mi);
var bp = ((g).bioPolymer == null ? JM.Resolver.allocateBioPolymer (groups, j, doCheck) : null);
if (bp == null || bp.monomerCount == 0) continue;
(model).addBioPolymer (bp);
j += bp.monomerCount - 1;
}
}
}, "~A,~N,~N,JU.BS");
Clazz.overrideMethod (c$, "recalculateAllPolymers", 
function (bsModelsExcluded, groups) {
for (var i = 0; i < this.ms.mc; i++) if (this.ms.am[i].isBioModel && !bsModelsExcluded.get (i)) (this.ms.am[i]).clearBioPolymers ();

this.calculateAllPolymers (groups, -1, 0, bsModelsExcluded);
}, "JU.BS,~A");
Clazz.overrideMethod (c$, "getGroupsWithinAll", 
function (nResidues, bs) {
var bsResult =  new JU.BS ();
var bsCheck = this.ms.getIterativeModels (false);
for (var iModel = this.ms.mc; --iModel >= 0; ) if (bsCheck.get (iModel) && this.ms.am[iModel].isBioModel) {
var m = this.ms.am[iModel];
for (var i = m.bioPolymerCount; --i >= 0; ) m.bioPolymers[i].getRangeGroups (nResidues, bs, bsResult);

}
return bsResult;
}, "~N,JU.BS");
Clazz.overrideMethod (c$, "calculateStruts", 
function (bs1, bs2) {
return this.getBioExt ().calculateAllstruts (this.vwr, this.ms, bs1, bs2);
}, "JU.BS,JU.BS");
Clazz.overrideMethod (c$, "recalculatePoints", 
function (modelIndex) {
if (modelIndex < 0) {
for (var i = this.ms.mc; --i >= 0; ) if (!this.ms.isTrajectorySubFrame (i) && this.ms.am[i].isBioModel) (this.ms.am[i]).recalculateLeadMidpointsAndWingVectors ();

return;
}if (!this.ms.isTrajectorySubFrame (modelIndex) && this.ms.am[modelIndex].isBioModel) (this.ms.am[modelIndex]).recalculateLeadMidpointsAndWingVectors ();
}, "~N");
Clazz.overrideMethod (c$, "getFullProteinStructureState", 
function (bsAtoms, mode) {
var taintedOnly = (mode == 1048579);
if (taintedOnly && !this.ms.proteinStructureTainted) return "";
var scriptMode = (mode == 1073742158 || mode == 1048579);
var atoms = this.ms.at;
var at0 = (bsAtoms == null ? 0 : bsAtoms.nextSetBit (0));
if (at0 < 0) return "";
if (bsAtoms != null && mode == 1052714) {
bsAtoms = JU.BSUtil.copy (bsAtoms);
for (var i = this.ms.ac; --i >= 0; ) if (Float.isNaN (atoms[i].group.getGroupParameter (1112539145)) || Float.isNaN (atoms[i].group.getGroupParameter (1112539146))) bsAtoms.clear (i);

}var at1 = (bsAtoms == null ? this.ms.ac : bsAtoms.length ()) - 1;
var im0 = atoms[at0].mi;
var im1 = atoms[at1].mi;
var lstStr =  new JU.Lst ();
var map =  new java.util.Hashtable ();
var cmd =  new JU.SB ();
for (var im = im0; im <= im1; im++) {
if (!this.ms.am[im].isBioModel) continue;
var m = this.ms.am[im];
if (taintedOnly && !m.structureTainted) continue;
var bsA =  new JU.BS ();
bsA.or (m.bsAtoms);
bsA.andNot (m.bsAtomsDeleted);
var i0 = bsA.nextSetBit (0);
if (i0 < 0) continue;
if (scriptMode) {
cmd.append ("  structure none ").append (JU.Escape.eBS (this.ms.getModelAtomBitSetIncludingDeleted (im, false))).append ("    \t# model=" + this.ms.getModelNumberDotted (im)).append (";\n");
}var ps;
for (var i = i0; i >= 0; i = bsA.nextSetBit (i + 1)) {
var a = atoms[i];
if (!(Clazz.instanceOf (a.group, JM.AlphaMonomer)) || (ps = (a.group).proteinStructure) == null || map.containsKey (ps)) continue;
lstStr.addLast (ps);
map.put (ps, Boolean.TRUE);
}
}
this.getStructureLines (bsAtoms, cmd, lstStr, J.c.STR.HELIX, scriptMode, mode);
this.getStructureLines (bsAtoms, cmd, lstStr, J.c.STR.SHEET, scriptMode, mode);
this.getStructureLines (bsAtoms, cmd, lstStr, J.c.STR.TURN, scriptMode, mode);
return cmd.toString ();
}, "JU.BS,~N");
Clazz.defineMethod (c$, "getStructureLines", 
 function (bsAtoms, cmd, lstStr, type, scriptMode, mode) {
var showMode = (mode == 135270926);
var nHelix = 0;
var nSheet = 0;
var nTurn = 0;
var sid = null;
var bs =  new JU.BS ();
var n = 0;
for (var i = 0, ns = lstStr.size (); i < ns; i++) {
var ps = lstStr.get (i);
if (ps.type !== type) continue;
bs.clearAll ();
var m1 = ps.findMonomer (bsAtoms, true);
var m2 = ps.findMonomer (bsAtoms, false);
if (m1 == null || m2 == null) continue;
var iModel = ps.apolymer.model.modelIndex;
var comment = (scriptMode ? "    \t# model=" + this.ms.getModelNumberDotted (iModel) : null);
var res1 = m1.getResno ();
var res2 = m2.getResno ();
var subtype = ps.subtype;
switch (type) {
case J.c.STR.HELIX:
case J.c.STR.TURN:
case J.c.STR.SHEET:
n++;
if (scriptMode) {
var stype = subtype.getBioStructureTypeName (false);
cmd.append ("  structure ").append (stype).append (" ").append (JU.Escape.eBS (ps.getAtoms (bs))).append (comment).append (" & (" + res1 + " - " + res2 + ")").append (";\n");
} else {
var str;
var nx;
switch (type) {
case J.c.STR.HELIX:
nx = ++nHelix;
sid = JU.PT.formatStringI ("%3N %3N", "N", nx);
str = "HELIX  %ID %3GROUPA %1CA %4RESA  %3GROUPB %1CB %4RESB";
var stype = null;
switch (subtype) {
case J.c.STR.HELIX:
case J.c.STR.HELIXALPHA:
stype = "  1";
break;
case J.c.STR.HELIX310:
stype = "  5";
break;
case J.c.STR.HELIXPI:
stype = "  3";
break;
}
if (stype != null) str += stype;
break;
case J.c.STR.SHEET:
nx = ++nSheet;
sid = JU.PT.formatStringI ("%3N %3A 0", "N", nx);
sid = JU.PT.formatStringS (sid, "A", "S" + nx);
str = "SHEET  %ID %3GROUPA %1CA%4RESA  %3GROUPB %1CB%4RESB";
break;
case J.c.STR.TURN:
default:
nx = ++nTurn;
sid = JU.PT.formatStringI ("%3N %3N", "N", nx);
str = "TURN   %ID %3GROUPA %1CA%4RESA  %3GROUPB %1CB%4RESB";
break;
}
str = JU.PT.formatStringS (str, "ID", sid);
str = JU.PT.formatStringS (str, "GROUPA", m1.getGroup3 ());
str = JU.PT.formatStringS (str, "CA", m1.getLeadAtom ().getChainIDStr ());
str = JU.PT.formatStringI (str, "RESA", res1);
str = JU.PT.formatStringS (str, "GROUPB", m2.getGroup3 ());
str = JU.PT.formatStringS (str, "CB", m2.getLeadAtom ().getChainIDStr ());
str = JU.PT.formatStringI (str, "RESB", res2);
cmd.append (str);
if (showMode) cmd.append (" strucno= ").appendI (ps.strucNo);
cmd.append ("\n");
}}
}
if (n > 0) cmd.append ("\n");
return n;
}, "JU.BS,JU.SB,JU.Lst,J.c.STR,~B,~N");
Clazz.overrideMethod (c$, "getAllSequenceBits", 
function (specInfo, bs) {
var bsResult =  new JU.BS ();
if (specInfo.length > 0) {
if (bs == null) bs = this.vwr.getAllAtoms ();
var am = this.ms.am;
for (var i = this.ms.mc; --i >= 0; ) if (am[i].isBioModel) {
var m = am[i];
var lenInfo = specInfo.length;
for (var ip = 0; ip < m.bioPolymerCount; ip++) {
var sequence = m.bioPolymers[ip].getSequence ();
var j = -1;
while ((j = sequence.indexOf (specInfo, ++j)) >= 0) m.bioPolymers[ip].getPolymerSequenceAtoms (j, lenInfo, bs, bsResult);

}
}
}return bsResult;
}, "~S,JU.BS");
Clazz.defineMethod (c$, "getAllBasePairBits", 
 function (specInfo) {
var bsA = null;
var bsB = null;
var vHBonds =  new JU.Lst ();
if (specInfo.length == 0) {
bsA = bsB = this.vwr.getAllAtoms ();
this.calcAllRasmolHydrogenBonds (bsA, bsB, vHBonds, true, 1, false, null);
} else {
for (var i = 0; i < specInfo.length; ) {
bsA = this.ms.getSequenceBits (specInfo.substring (i, ++i), null);
if (bsA.nextSetBit (0) < 0) continue;
bsB = this.ms.getSequenceBits (specInfo.substring (i, ++i), null);
if (bsB.nextSetBit (0) < 0) continue;
this.calcAllRasmolHydrogenBonds (bsA, bsB, vHBonds, true, 1, false, null);
}
}var bsAtoms =  new JU.BS ();
for (var i = vHBonds.size (); --i >= 0; ) {
var b = vHBonds.get (i);
bsAtoms.set (b.atom1.i);
bsAtoms.set (b.atom2.i);
}
return bsAtoms;
}, "~S");
Clazz.overrideMethod (c$, "calcAllRasmolHydrogenBonds", 
function (bsA, bsB, vHBonds, nucleicOnly, nMax, dsspIgnoreHydrogens, bsHBonds) {
var am = this.ms.am;
if (vHBonds == null) {
var bsAtoms = bsA;
if (bsB != null && !bsA.equals (bsB)) (bsAtoms = JU.BSUtil.copy (bsA)).or (bsB);
var bsDelete =  new JU.BS ();
var bsOK =  new JU.BS ();
var models = this.ms.am;
var bonds = this.ms.bo;
for (var i = this.ms.bondCount; --i >= 0; ) {
var bond = bonds[i];
if ((bond.order & 28672) == 0) continue;
if (bsAtoms.get (bond.atom1.i)) bsDelete.set (i);
 else bsOK.set (models[bond.atom1.mi].trajectoryBaseIndex);
}
for (var i = this.ms.mc; --i >= 0; ) if (models[i].isBioModel) (models[i]).hasRasmolHBonds = bsOK.get (i);

if (bsDelete.nextSetBit (0) >= 0) this.ms.deleteBonds (bsDelete, false);
}for (var i = this.ms.mc; --i >= 0; ) if (am[i].isBioModel && !this.ms.isTrajectorySubFrame (i)) (am[i]).getRasmolHydrogenBonds (bsA, bsB, vHBonds, nucleicOnly, nMax, dsspIgnoreHydrogens, bsHBonds);

}, "JU.BS,JU.BS,JU.Lst,~B,~N,~B,JU.BS");
Clazz.defineMethod (c$, "getRasmolHydrogenBonds", 
 function (bsA, bsB, vHBonds, nucleicOnly, nMax, dsspIgnoreHydrogens, bsHBonds) {
var doAdd = (vHBonds == null);
if (doAdd) vHBonds =  new JU.Lst ();
if (nMax < 0) nMax = 2147483647;
var asDSSX = (bsB == null);
var bp;
var bp1;
if (asDSSX && this.bioPolymerCount > 0) {
this.calculateDssx (vHBonds, false, dsspIgnoreHydrogens, false);
} else {
for (var i = this.bioPolymerCount; --i >= 0; ) {
bp = this.bioPolymers[i];
var type = bp.getType ();
if ((nucleicOnly || type != 1) && type != 2) continue;
var isRNA = bp.isRna ();
var isAmino = (type == 1);
if (isAmino) bp.calcRasmolHydrogenBonds (null, bsA, bsB, vHBonds, nMax, null, true, false);
for (var j = this.bioPolymerCount; --j >= 0; ) {
if ((bp1 = this.bioPolymers[j]) != null && (isRNA || i != j) && type == bp1.getType ()) {
bp1.calcRasmolHydrogenBonds (bp, bsA, bsB, vHBonds, nMax, null, true, false);
}}
}
}if (vHBonds.size () == 0 || !doAdd) return;
this.hasRasmolHBonds = true;
for (var i = 0; i < vHBonds.size (); i++) {
var bond = vHBonds.get (i);
var atom1 = bond.atom1;
var atom2 = bond.atom2;
if (atom1.isBonded (atom2)) continue;
var index = this.ms.addHBond (atom1, atom2, bond.order, bond.getEnergy ());
if (bsHBonds != null) bsHBonds.set (index);
}
}, "JU.BS,JU.BS,JU.Lst,~B,~N,~B,JU.BS");
Clazz.overrideMethod (c$, "calculateStraightnessAll", 
function () {
this.getBioExt ().calculateStraightnessAll (this.vwr, this.ms);
});
Clazz.overrideMethod (c$, "mutate", 
function (bs, group, sequence) {
return this.getBioExt ().mutate (this.vwr, bs, group, sequence);
}, "JU.BS,~S,~A");
Clazz.makeConstructor (c$, 
function (modelSet, modelIndex, trajectoryBaseIndex, jmolData, properties, auxiliaryInfo) {
Clazz.superConstructor (this, JM.BioModel, []);
this.vwr = modelSet.vwr;
this.set (modelSet, modelIndex, trajectoryBaseIndex, jmolData, properties, auxiliaryInfo);
this.isBioModel = true;
modelSet.bioModelset = this;
this.clearBioPolymers ();
}, "JM.ModelSet,~N,~N,~S,java.util.Properties,java.util.Map");
Clazz.defineMethod (c$, "clearBioPolymers", 
 function () {
this.bioPolymers =  new Array (8);
this.bioPolymerCount = 0;
});
Clazz.overrideMethod (c$, "getBioPolymerCount", 
function () {
return this.bioPolymerCount;
});
Clazz.overrideMethod (c$, "fixIndices", 
function (modelIndex, nAtomsDeleted, bsDeleted) {
this.fixIndicesM (modelIndex, nAtomsDeleted, bsDeleted);
this.recalculateLeadMidpointsAndWingVectors ();
}, "~N,~N,JU.BS");
Clazz.defineMethod (c$, "recalculateLeadMidpointsAndWingVectors", 
 function () {
for (var ip = 0; ip < this.bioPolymerCount; ip++) this.bioPolymers[ip].recalculateLeadMidpointsAndWingVectors ();

});
Clazz.overrideMethod (c$, "freeze", 
function () {
this.freezeM ();
this.bioPolymers = JU.AU.arrayCopyObject (this.bioPolymers, this.bioPolymerCount);
return true;
});
Clazz.defineMethod (c$, "addSecondaryStructure", 
function (type, structureID, serialID, strandCount, startChainID, startSeqcode, endChainID, endSeqcode, istart, iend, bsAssigned) {
for (var i = this.bioPolymerCount; --i >= 0; ) if (Clazz.instanceOf (this.bioPolymers[i], JM.AlphaPolymer)) (this.bioPolymers[i]).addStructure (type, structureID, serialID, strandCount, startChainID, startSeqcode, endChainID, endSeqcode, istart, iend, bsAssigned);

}, "J.c.STR,~S,~N,~N,~N,~N,~N,~N,~N,~N,JU.BS");
Clazz.defineMethod (c$, "calculateStructures", 
 function (asDSSP, doReport, dsspIgnoreHydrogen, setStructure, includeAlpha) {
if (this.bioPolymerCount == 0 || !setStructure && !asDSSP) return "";
this.ms.proteinStructureTainted = this.structureTainted = true;
if (setStructure) for (var i = this.bioPolymerCount; --i >= 0; ) if (!asDSSP || this.bioPolymers[i].monomers[0].getNitrogenAtom () != null) this.bioPolymers[i].clearStructures ();

if (!asDSSP || includeAlpha) for (var i = this.bioPolymerCount; --i >= 0; ) if (Clazz.instanceOf (this.bioPolymers[i], JM.AlphaPolymer)) (this.bioPolymers[i]).calculateStructures (includeAlpha);

return (asDSSP ? this.calculateDssx (null, doReport, dsspIgnoreHydrogen, setStructure) : "");
}, "~B,~B,~B,~B,~B");
Clazz.defineMethod (c$, "calculateDssx", 
 function (vHBonds, doReport, dsspIgnoreHydrogen, setStructure) {
var haveProt = false;
var haveNucl = false;
for (var i = 0; i < this.bioPolymerCount && !(haveProt && haveNucl); i++) {
if (this.bioPolymers[i].isNucleic ()) haveNucl = true;
 else if (Clazz.instanceOf (this.bioPolymers[i], JM.AminoPolymer)) haveProt = true;
}
var s = "";
if (haveProt) s += (J.api.Interface.getOption ("dssx.DSSP", this.vwr, "ms")).calculateDssp (this.bioPolymers, this.bioPolymerCount, vHBonds, doReport, dsspIgnoreHydrogen, setStructure);
if (haveNucl && this.auxiliaryInfo.containsKey ("dssr") && vHBonds != null) s += this.vwr.getAnnotationParser ().getHBonds (this.ms, this.modelIndex, vHBonds, doReport);
return s;
}, "JU.Lst,~B,~B,~B");
Clazz.defineMethod (c$, "getConformation", 
function (conformationIndex, doSet, bsSelected, bsRet) {
var nAltLocs = this.altLocCount;
var bsConformation = this.getConformationBS (conformationIndex, bsSelected);
if (bsConformation == null) return;
if (conformationIndex >= 0) {
if (nAltLocs > 0) for (var i = this.bioPolymerCount; --i >= 0; ) this.bioPolymers[i].getConformation (bsConformation, conformationIndex);

var bs =  new JU.BS ();
var altLocs = this.ms.getAltLocListInModel (this.modelIndex);
for (var c = this.altLocCount; --c >= 0; ) if (c != conformationIndex) bsConformation.andNot (this.ms.getAtomBitsMDa (1048607, altLocs.substring (c, c + 1), bs));

}if (bsConformation.nextSetBit (0) >= 0) {
bsRet.or (bsConformation);
if (doSet) for (var j = this.bioPolymerCount; --j >= 0; ) this.bioPolymers[j].setConformation (bsConformation);

}}, "~N,~B,JU.BS,JU.BS");
Clazz.defineMethod (c$, "addBioPolymer", 
 function (polymer) {
if (this.bioPolymers.length == 0) this.clearBioPolymers ();
if (this.bioPolymerCount == this.bioPolymers.length) this.bioPolymers = JU.AU.doubleLength (this.bioPolymers);
polymer.bioPolymerIndexInModel = this.bioPolymerCount;
this.bioPolymers[this.bioPolymerCount++] = polymer;
}, "JM.BioPolymer");
Clazz.overrideMethod (c$, "getBioBranches", 
function (biobranches) {
var bsBranch;
for (var j = 0; j < this.bioPolymerCount; j++) {
bsBranch =  new JU.BS ();
this.bioPolymers[j].getRange (bsBranch, this.isMutated);
var iAtom = bsBranch.nextSetBit (0);
if (iAtom >= 0) {
if (biobranches == null) biobranches =  new JU.Lst ();
biobranches.addLast (bsBranch);
}}
return biobranches;
}, "JU.Lst");
Clazz.overrideMethod (c$, "getAllPolymerInfo", 
function (bs, info) {
this.getBioExt ().getAllPolymerInfo (this.ms, bs, info);
}, "JU.BS,java.util.Map");
Clazz.defineMethod (c$, "getBioExt", 
 function () {
return (this.bx == null ? (this.bx = (J.api.Interface.getInterface ("JM.BioExt", this.vwr, "script"))) : this.bx);
});
Clazz.overrideMethod (c$, "getFullPDBHeader", 
function () {
if (this.modelIndex < 0) return "";
var info = this.auxiliaryInfo.get ("fileHeader");
if (info != null) return info;
info = this.vwr.getCurrentFileAsString ("biomodel");
var ichMin = info.length;
for (var i = JM.BioModel.pdbRecords.length; --i >= 0; ) {
var ichFound;
var strRecord = JM.BioModel.pdbRecords[i];
switch (ichFound = (info.startsWith (strRecord) ? 0 : info.indexOf ("\n" + strRecord))) {
case -1:
continue;
case 0:
this.auxiliaryInfo.put ("fileHeader", "");
return "";
default:
if (ichFound < ichMin) ichMin = ++ichFound;
}
}
info = info.substring (0, ichMin);
this.auxiliaryInfo.put ("fileHeader", info);
return info;
});
Clazz.overrideMethod (c$, "getPdbData", 
function (type, ctype, isDraw, bsSelected, out, tokens, pdbCONECT, bsWritten) {
this.getBioExt ().getPdbDataM (this, this.vwr, type, ctype, isDraw, bsSelected, out, tokens, pdbCONECT, bsWritten);
}, "~S,~S,~B,JU.BS,JU.OC,~A,JU.SB,JU.BS");
Clazz.overrideMethod (c$, "resetRasmolBonds", 
function (bs) {
var bsDelete =  new JU.BS ();
this.hasRasmolHBonds = false;
var am = this.ms.am;
var bo = this.ms.bo;
for (var i = this.ms.bondCount; --i >= 0; ) {
var bond = bo[i];
if ((bond.order & 28672) != 0 && am[bond.atom1.mi].trajectoryBaseIndex == this.modelIndex) bsDelete.set (i);
}
if (bsDelete.nextSetBit (0) >= 0) this.ms.deleteBonds (bsDelete, false);
this.getRasmolHydrogenBonds (bs, bs, null, false, 2147483647, false, null);
}, "JU.BS");
Clazz.overrideMethod (c$, "getDefaultLargePDBRendering", 
function (sb, maxAtoms) {
var bs =  new JU.BS ();
if (this.getBondCount () == 0) bs = this.bsAtoms;
if (bs !== this.bsAtoms) for (var i = 0; i < this.bioPolymerCount; i++) this.bioPolymers[i].getRange (bs, this.isMutated);

if (bs.nextSetBit (0) < 0) return;
var bs2 =  new JU.BS ();
if (bs === this.bsAtoms) {
bs2 = bs;
} else {
for (var i = 0; i < this.bioPolymerCount; i++) if (this.bioPolymers[i].getType () == 0) this.bioPolymers[i].getRange (bs2, this.isMutated);

}if (bs2.nextSetBit (0) >= 0) sb.append ("select ").append (JU.Escape.eBS (bs2)).append (";backbone only;");
if (this.act <= maxAtoms) return;
sb.append ("select ").append (JU.Escape.eBS (bs)).append (" & connected; wireframe only;");
if (bs !== this.bsAtoms) {
bs2.clearAll ();
bs2.or (this.bsAtoms);
bs2.andNot (bs);
if (bs2.nextSetBit (0) >= 0) sb.append ("select " + JU.Escape.eBS (bs2) + " & !connected;stars 0.5;spacefill off;");
}}, "JU.SB,~N");
Clazz.overrideMethod (c$, "getAtomBitsStr", 
function (tokType, specInfo, bs) {
switch (tokType) {
default:
return  new JU.BS ();
case 1073741925:
return this.getAnnotationBits ("domains", 1073741925, specInfo);
case 1073742189:
return this.getAnnotationBits ("validation", 1073742189, specInfo);
case 1073741916:
return this.getAnnotationBits ("dssr", 1073741916, specInfo);
case 1073742128:
return this.getAnnotationBits ("rna3d", 1073742128, specInfo);
case 1073741864:
var s = specInfo;
bs =  new JU.BS ();
return (s.length % 2 != 0 ? bs : this.ms.getAtomBitsMDa (1087373318, this.getAllBasePairBits (s), bs));
case 1087373320:
return this.getAllSequenceBits (specInfo, null);
}
}, "~N,~S,JU.BS");
Clazz.overrideMethod (c$, "getAtomBitsBS", 
function (tokType, bsInfo, bs) {
var at = this.ms.at;
var ac = this.ms.ac;
var i = 0;
switch (tokType) {
case 3145764:
for (i = ac; --i >= 0; ) if (at[i].group.isCarbohydrate ()) bs.set (i);

break;
case 3145732:
for (i = ac; --i >= 0; ) if (at[i].isDna ()) bs.set (i);

break;
case 137363467:
case 3145760:
var type = (tokType == 137363467 ? J.c.STR.HELIX : J.c.STR.SHEET);
for (i = ac; --i >= 0; ) if (at[i].group.isWithinStructure (type)) bs.set (i);

break;
case 3145742:
for (i = ac; --i >= 0; ) if (at[i].isNucleic ()) bs.set (i);

break;
case 3145744:
for (i = ac; --i >= 0; ) if (at[i].isProtein ()) bs.set (i);

break;
case 3145746:
for (i = ac; --i >= 0; ) if (at[i].isPurine ()) bs.set (i);

break;
case 3145748:
for (i = ac; --i >= 0; ) if (at[i].isPyrimidine ()) bs.set (i);

break;
case 3145750:
for (i = ac; --i >= 0; ) if (at[i].isRna ()) bs.set (i);

break;
}
if (i < 0) return bs;
var i0 = bsInfo.nextSetBit (0);
if (i0 < 0) return bs;
i = 0;
switch (tokType) {
case 1095761937:
for (i = i0; i >= 0; i = bsInfo.nextSetBit (i + 1)) {
if (bs.get (i)) continue;
var iPolymer = at[i].group.getBioPolymerIndexInModel ();
bs.set (i);
for (var j = i; --j >= 0; ) if (at[j].group.getBioPolymerIndexInModel () == iPolymer) bs.set (j);
 else break;

for (; ++i < ac; ) if (at[i].group.getBioPolymerIndexInModel () == iPolymer) bs.set (i);
 else break;

}
break;
case 1641025539:
for (i = i0; i >= 0; i = bsInfo.nextSetBit (i + 1)) {
if (bs.get (i)) continue;
var structure = at[i].group.getStructure ();
bs.set (i);
for (var j = i; --j >= 0; ) if (at[j].group.getStructure () === structure) bs.set (j);
 else break;

for (; ++i < ac; ) if (at[i].group.getStructure () === structure) bs.set (i);
 else break;

}
break;
}
if (i == 0) JU.Logger.error ("MISSING getAtomBits entry for " + JS.T.nameOf (tokType));
return bs;
}, "~N,JU.BS,JU.BS");
Clazz.defineMethod (c$, "getAnnotationBits", 
 function (name, tok, specInfo) {
var bs =  new JU.BS ();
var pa = this.vwr.getAnnotationParser ();
var ann;
for (var i = this.ms.mc; --i >= 0; ) if ((ann = this.ms.getInfo (i, name)) != null) bs.or (pa.getAtomBits (this.vwr, specInfo, (this.ms.am[i]).getCachedAnnotationMap (name + " V ", ann), this.ms.am[i].dssrCache, tok, i, this.ms.am[i].bsAtoms));

return bs;
}, "~S,~N,~S");
Clazz.defineMethod (c$, "getCachedAnnotationMap", 
function (key, ann) {
var cache = (this.dssrCache == null && ann != null ? this.dssrCache =  new java.util.Hashtable () : this.dssrCache);
if (cache == null) return null;
var annotv = cache.get (key);
if (annotv == null && ann != null) {
annotv = (Clazz.instanceOf (ann, JS.SV) || Clazz.instanceOf (ann, java.util.Hashtable) ? ann : this.vwr.evaluateExpressionAsVariable (ann));
cache.put (key, annotv);
}return (Clazz.instanceOf (annotv, JS.SV) || Clazz.instanceOf (annotv, java.util.Hashtable) ? annotv : null);
}, "~S,~O");
Clazz.overrideMethod (c$, "getIdentifierOrNull", 
function (identifier) {
var len = identifier.length;
var pt = 0;
while (pt < len && JU.PT.isLetter (identifier.charAt (pt))) ++pt;

var bs = this.ms.getSpecNameOrNull (identifier.substring (0, pt), false);
if (pt == len) return bs;
if (bs == null) bs =  new JU.BS ();
var pt0 = pt;
while (pt < len && JU.PT.isDigit (identifier.charAt (pt))) ++pt;

var seqNumber = 0;
try {
seqNumber = Integer.parseInt (identifier.substring (pt0, pt));
} catch (nfe) {
if (Clazz.exceptionOf (nfe, NumberFormatException)) {
return null;
} else {
throw nfe;
}
}
var insertionCode = ' ';
if (pt < len && identifier.charAt (pt) == '^') if (++pt < len) insertionCode = identifier.charAt (pt);
var seqcode = JM.Group.getSeqcodeFor (seqNumber, insertionCode);
var bsInsert = this.ms.getSeqcodeBits (seqcode, false);
if (bsInsert == null) {
if (insertionCode != ' ') bsInsert = this.ms.getSeqcodeBits (Character.toUpperCase (identifier.charAt (pt)).charCodeAt (0), false);
if (bsInsert == null) return null;
pt++;
}bs.and (bsInsert);
if (pt >= len) return bs;
if (pt != len - 1) return null;
bs.and (this.ms.getChainBits (identifier.charCodeAt (pt)));
return bs;
}, "~S");
Clazz.defineStatics (c$,
"pdbRecords",  Clazz.newArray (-1, ["ATOM  ", "MODEL ", "HETATM"]));
});
