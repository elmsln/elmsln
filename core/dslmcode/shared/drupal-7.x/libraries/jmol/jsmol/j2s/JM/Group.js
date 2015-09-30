Clazz.declarePackage ("JM");
Clazz.load (["java.lang.Short", "JV.JC"], "JM.Group", ["java.util.Hashtable", "JU.BS", "$.Quat", "J.c.STR", "JU.BSUtil", "$.Escape", "$.Logger"], function () {
c$ = Clazz.decorateAsClass (function () {
this.chain = null;
this.groupIndex = 0;
this.group1 = '\0';
this.firstAtomIndex = -1;
this.leadAtomIndex = -1;
this.lastAtomIndex = 0;
this.bsAdded = null;
this.seqcode = 0;
this.groupID = 0;
this.selectedIndex = 0;
this.shapeVisibilityFlags = 0;
Clazz.instantialize (this, arguments);
}, JM, "Group");
Clazz.makeConstructor (c$, 
function () {
});
Clazz.defineMethod (c$, "setGroup", 
function (chain, group3, seqcode, firstAtomIndex, lastAtomIndex) {
this.chain = chain;
this.seqcode = seqcode;
this.firstAtomIndex = firstAtomIndex;
this.lastAtomIndex = lastAtomIndex;
if (group3 != null && group3.length > 0) this.setGroupID (group3);
return this;
}, "JM.Chain,~S,~N,~N,~N");
Clazz.defineMethod (c$, "setGroupID", 
function (group3) {
}, "~S");
Clazz.defineMethod (c$, "isAdded", 
function (atomIndex) {
return this.bsAdded != null && this.bsAdded.get (atomIndex);
}, "~N");
Clazz.defineMethod (c$, "addAtoms", 
function (atomIndex) {
if (this.bsAdded == null) this.bsAdded =  new JU.BS ();
this.bsAdded.set (atomIndex);
}, "~N");
Clazz.defineMethod (c$, "setAtomBits", 
function (bs) {
bs.setBits (this.firstAtomIndex, this.lastAtomIndex + 1);
if (this.bsAdded != null) bs.or (this.bsAdded);
}, "JU.BS");
Clazz.defineMethod (c$, "isSelected", 
function (bs) {
var pt = bs.nextSetBit (this.firstAtomIndex);
return (pt >= 0 && pt <= this.lastAtomIndex || this.bsAdded != null && this.bsAdded.intersects (bs));
}, "JU.BS");
Clazz.defineMethod (c$, "setShapeVisibility", 
function (visFlag, isVisible) {
if (isVisible) {
this.shapeVisibilityFlags |= visFlag;
} else {
this.shapeVisibilityFlags &= ~visFlag;
}}, "~N,~B");
Clazz.defineMethod (c$, "getGroup3", 
function () {
return (this.groupID < 1 ? "" : JM.Group.group3Names[this.groupID]);
});
Clazz.defineMethod (c$, "getGroup1", 
function () {
return '?';
});
Clazz.defineMethod (c$, "getBioPolymerLength", 
function () {
return 0;
});
Clazz.defineMethod (c$, "getMonomerIndex", 
function () {
return -1;
});
Clazz.defineMethod (c$, "getStructure", 
function () {
return null;
});
Clazz.defineMethod (c$, "getStrucNo", 
function () {
return 0;
});
Clazz.defineMethod (c$, "getProteinStructureType", 
function () {
return J.c.STR.NOT;
});
Clazz.defineMethod (c$, "getProteinStructureSubType", 
function () {
return this.getProteinStructureType ();
});
Clazz.defineMethod (c$, "setProteinStructureType", 
function (type, monomerIndexCurrent) {
return -1;
}, "J.c.STR,~N");
Clazz.defineMethod (c$, "isProtein", 
function () {
return false;
});
Clazz.defineMethod (c$, "isNucleic", 
function () {
return false;
});
Clazz.defineMethod (c$, "isDna", 
function () {
return false;
});
Clazz.defineMethod (c$, "isRna", 
function () {
return false;
});
Clazz.defineMethod (c$, "isPurine", 
function () {
return false;
});
Clazz.defineMethod (c$, "isPyrimidine", 
function () {
return false;
});
Clazz.defineMethod (c$, "isCarbohydrate", 
function () {
return false;
});
Clazz.defineMethod (c$, "getResno", 
function () {
return (this.seqcode == -2147483648 ? 0 : this.seqcode >> 8);
});
Clazz.defineMethod (c$, "setResno", 
function (i) {
this.seqcode = JM.Group.getSeqcodeFor (i, this.getInsertionCode ());
}, "~N");
c$.getSeqNumberFor = Clazz.defineMethod (c$, "getSeqNumberFor", 
function (seqcode) {
return (JM.Group.haveSequenceNumber (seqcode) ? seqcode >> 8 : 2147483647);
}, "~N");
c$.haveSequenceNumber = Clazz.defineMethod (c$, "haveSequenceNumber", 
function (seqcode) {
return ((seqcode & 128) != 0);
}, "~N");
Clazz.defineMethod (c$, "getSeqcodeString", 
function () {
return JM.Group.getSeqcodeStringFor (this.seqcode);
});
c$.getSeqcodeFor = Clazz.defineMethod (c$, "getSeqcodeFor", 
function (seqNo, insCode) {
if (seqNo == -2147483648) return seqNo;
if (!((insCode >= 'A' && insCode <= 'Z') || (insCode >= 'a' && insCode <= 'z') || (insCode >= '0' && insCode <= '9') || insCode == '?' || insCode == '*')) {
if (insCode != ' ' && insCode != '\0') JU.Logger.warn ("unrecognized insertionCode:" + insCode);
insCode = '\0';
}return ((seqNo == 2147483647 ? 0 : (seqNo << 8) | 128)) + insCode.charCodeAt (0);
}, "~N,~S");
c$.getSeqcodeStringFor = Clazz.defineMethod (c$, "getSeqcodeStringFor", 
function (seqcode) {
if (seqcode == -2147483648) return null;
return (seqcode & 127) == 0 ? "" + (seqcode >> 8) : "" + (seqcode >> 8) + '^' + String.fromCharCode (seqcode & 127);
}, "~N");
Clazz.defineMethod (c$, "getInsertionCode", 
function () {
return (this.seqcode == -2147483648 ? '\0' : String.fromCharCode (this.seqcode & 127));
});
c$.getInsertionCodeFor = Clazz.defineMethod (c$, "getInsertionCodeFor", 
function (seqcode) {
return (seqcode & 127);
}, "~N");
c$.getInsertionCodeChar = Clazz.defineMethod (c$, "getInsertionCodeChar", 
function (seqcode) {
return (seqcode == -2147483648 ? '\0' : String.fromCharCode (seqcode & 127));
}, "~N");
Clazz.defineMethod (c$, "scaleToScreen", 
function (Z, mar) {
return this.chain.model.ms.vwr.tm.scaleToScreen (Z, mar);
}, "~N,~N");
Clazz.defineMethod (c$, "isCursorOnTopOf", 
function (atom, x, y, radius, champ) {
return this.chain.model.ms.isCursorOnTopOf (atom, x, y, radius, champ);
}, "JM.Atom,~N,~N,~N,JM.Atom");
Clazz.defineMethod (c$, "getModel", 
function () {
return this.chain.model;
});
Clazz.defineMethod (c$, "getSelectedMonomerCount", 
function () {
return 0;
});
Clazz.defineMethod (c$, "getSelectedMonomerIndex", 
function () {
return -1;
});
Clazz.defineMethod (c$, "isLeadAtom", 
function (atomIndex) {
return false;
}, "~N");
Clazz.defineMethod (c$, "getLeadAtomOr", 
function (atom) {
var a = this.getLeadAtom ();
return (a == null ? atom : a);
}, "JM.Atom");
Clazz.defineMethod (c$, "getLeadAtom", 
function () {
return null;
});
Clazz.defineMethod (c$, "getQuaternion", 
function (qType) {
return null;
}, "~S");
Clazz.defineMethod (c$, "getQuaternionFrame", 
function (atoms) {
if (this.lastAtomIndex - this.firstAtomIndex < 3) return null;
var pt = this.firstAtomIndex;
return JU.Quat.getQuaternionFrame (atoms[pt], atoms[++pt], atoms[++pt]);
}, "~A");
Clazz.defineMethod (c$, "setStrucNo", 
function (i) {
}, "~N");
Clazz.defineMethod (c$, "getHelixData", 
function (tokType, qType, mStep) {
return JU.Escape.escapeHelical (null, tokType, null, null, null);
}, "~N,~S,~N");
Clazz.defineMethod (c$, "isWithinStructure", 
function (type) {
return false;
}, "J.c.STR");
Clazz.defineMethod (c$, "getProteinStructureTag", 
function () {
return null;
});
Clazz.defineMethod (c$, "getStructureId", 
function () {
return "";
});
Clazz.defineMethod (c$, "getBioPolymerIndexInModel", 
function () {
return -1;
});
Clazz.defineMethod (c$, "isCrossLinked", 
function (g) {
return false;
}, "JM.Group");
Clazz.defineMethod (c$, "getCrossLinkLead", 
function (vReturn) {
return false;
}, "JU.Lst");
Clazz.defineMethod (c$, "isConnectedPrevious", 
function () {
return false;
});
Clazz.defineMethod (c$, "getNitrogenAtom", 
function () {
return null;
});
Clazz.defineMethod (c$, "getCarbonylOxygenAtom", 
function () {
return null;
});
Clazz.defineMethod (c$, "fixIndices", 
function (atomsDeleted, bsDeleted) {
this.firstAtomIndex -= atomsDeleted;
this.leadAtomIndex -= atomsDeleted;
this.lastAtomIndex -= atomsDeleted;
if (this.bsAdded != null) JU.BSUtil.deleteBits (this.bsAdded, bsDeleted);
}, "~N,JU.BS");
Clazz.defineMethod (c$, "getGroupInfo", 
function (igroup, ptTemp) {
var infoGroup =  new java.util.Hashtable ();
infoGroup.put ("groupIndex", Integer.$valueOf (igroup));
infoGroup.put ("groupID", Short.$valueOf (this.groupID));
var s = this.getSeqcodeString ();
if (s != null) infoGroup.put ("seqCode", s);
infoGroup.put ("_apt1", Integer.$valueOf (this.firstAtomIndex));
infoGroup.put ("_apt2", Integer.$valueOf (this.lastAtomIndex));
if (this.bsAdded != null) infoGroup.put ("addedAtoms", this.bsAdded);
infoGroup.put ("atomInfo1", this.chain.model.ms.getAtomInfo (this.firstAtomIndex, null, ptTemp));
infoGroup.put ("atomInfo2", this.chain.model.ms.getAtomInfo (this.lastAtomIndex, null, ptTemp));
infoGroup.put ("visibilityFlags", Integer.$valueOf (this.shapeVisibilityFlags));
return infoGroup;
}, "~N,JU.P3");
Clazz.defineMethod (c$, "getMinZ", 
function (atoms, minZ) {
minZ[0] = 2147483647;
for (var i = this.firstAtomIndex; i <= this.lastAtomIndex; i++) this.checkMinZ (atoms[i], minZ);

if (this.bsAdded != null) for (var i = this.bsAdded.nextSetBit (0); i >= 0; i = this.bsAdded.nextSetBit (i + 1)) this.checkMinZ (atoms[i], minZ);

}, "~A,~A");
Clazz.defineMethod (c$, "checkMinZ", 
 function (atom, minZ) {
var z = atom.sZ - Clazz.doubleToInt (atom.sD / 2) - 2;
if (z < minZ[0]) minZ[0] = Math.max (1, z);
}, "JM.Atom,~A");
Clazz.defineMethod (c$, "getGroupParameter", 
function (tok) {
return NaN;
}, "~N");
Clazz.defineMethod (c$, "getAtomIndex", 
function (name, offset) {
return -1;
}, "~S,~N");
Clazz.defineMethod (c$, "getBSSideChain", 
function () {
return  new JU.BS ();
});
Clazz.overrideMethod (c$, "toString", 
function () {
return "[" + this.getGroup3 () + "-" + this.getSeqcodeString () + "]";
});
Clazz.defineStatics (c$,
"standardGroupList", null);
c$.group3Names = c$.prototype.group3Names =  new Array (128);
Clazz.defineStatics (c$,
"specialAtomNames", null,
"SEQUENCE_NUMBER_FLAG", 0x80,
"INSERTION_CODE_MASK", 0x7F,
"SEQUENCE_NUMBER_SHIFT", 8);
});
