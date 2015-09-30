Clazz.declarePackage ("JS");
Clazz.load (["J.api.SmilesMatcherInterface"], "JS.SmilesMatcher", ["JU.AU", "$.BS", "$.PT", "JS.InvalidSmilesException", "$.SmilesAtom", "$.SmilesBond", "$.SmilesGenerator", "$.SmilesParser", "JU.BSUtil", "$.Node", "$.Point3fi"], function () {
c$ = Clazz.declareType (JS, "SmilesMatcher", null, J.api.SmilesMatcherInterface);
Clazz.defineMethod (c$, "checkFlag", 
 function (flags, flag) {
return (flags & flag) == flag;
}, "~N,~N");
Clazz.overrideMethod (c$, "getLastException", 
function () {
return JS.InvalidSmilesException.getLastError ();
});
Clazz.overrideMethod (c$, "getMolecularFormula", 
function (pattern, isSmarts) {
JS.InvalidSmilesException.clear ();
var search = JS.SmilesParser.getMolecule (pattern, isSmarts);
search.createTopoMap (null);
search.nodes = search.jmolAtoms;
return search.getMolecularFormula (!isSmarts, null, false);
}, "~S,~B");
Clazz.overrideMethod (c$, "getSmiles", 
function (atoms, ac, bsSelected, bioComment, flags) {
JS.InvalidSmilesException.clear ();
if (this.checkFlag (flags, 256)) {
var bioAllowUnmatchedRings = this.checkFlag (flags, 257);
var bioAddCrossLinks = this.checkFlag (flags, 258);
return ( new JS.SmilesGenerator ()).getBioSmiles (atoms, ac, bsSelected, bioAllowUnmatchedRings, bioAddCrossLinks, bioComment);
}var explicitH = this.checkFlag (flags, 1);
var topologyOnly = this.checkFlag (flags, 2);
var getAromatic = !this.checkFlag (flags, 4);
return ( new JS.SmilesGenerator ()).getSmiles (atoms, ac, bsSelected, explicitH, topologyOnly, getAromatic);
}, "~A,~N,JU.BS,~S,~N");
Clazz.overrideMethod (c$, "areEqual", 
function (smiles1, smiles2) {
JS.InvalidSmilesException.clear ();
var result = this.findPriv (smiles1, JS.SmilesParser.getMolecule (smiles2, false), (smiles1.indexOf ("*") >= 0 ? 131072 : 1114112) | 4194304 | 8192);
return (result == null ? -1 : result.length);
}, "~S,~S");
Clazz.defineMethod (c$, "areEqualTest", 
function (smiles, molecule) {
var ret = this.findPriv (smiles, molecule, 5316608);
return (ret != null && ret.length == 1);
}, "~S,JS.SmilesSearch");
Clazz.overrideMethod (c$, "find", 
function (pattern, smiles, isSmarts, firstMatchOnly) {
JS.InvalidSmilesException.clear ();
smiles = JS.SmilesParser.cleanPattern (smiles);
pattern = JS.SmilesParser.cleanPattern (pattern);
var search = JS.SmilesParser.getMolecule (smiles, false);
return this.findPriv (pattern, search, (isSmarts ? 131072 : 1114112) | (firstMatchOnly ? 4194304 : 0) | 12288);
}, "~S,~S,~B,~B");
Clazz.overrideMethod (c$, "getRelationship", 
function (smiles1, smiles2) {
if (smiles1 == null || smiles2 == null || smiles1.length == 0 || smiles2.length == 0) return "";
var mf1 = this.getMolecularFormula (smiles1, false);
var mf2 = this.getMolecularFormula (smiles2, false);
if (!mf1.equals (mf2)) return "none";
var check;
var n1 = JS.SmilesMatcher.countStereo (smiles1);
var n2 = JS.SmilesMatcher.countStereo (smiles2);
check = (n1 == n2 && this.areEqual (smiles2, smiles1) > 0);
if (!check) {
var s = smiles1 + smiles2;
if (s.indexOf ("/") >= 0 || s.indexOf ("\\") >= 0 || s.indexOf ("@") >= 0) {
if (n1 == n2 && n1 > 0) {
smiles1 = this.reverseChirality (smiles1);
check = (this.areEqual (smiles1, smiles2) > 0);
if (check) return "enantiomers";
}check = (this.areEqual ("/nostereo/" + smiles2, smiles1) > 0);
if (check) return (n1 == n2 ? "diastereomers" : "ambiguous stereochemistry!");
}return "constitutional isomers";
}return "identical";
}, "~S,~S");
Clazz.overrideMethod (c$, "reverseChirality", 
function (smiles) {
smiles = JU.PT.rep (smiles, "@@", "!@");
smiles = JU.PT.rep (smiles, "@", "@@");
smiles = JU.PT.rep (smiles, "!@@", "@");
smiles = JU.PT.rep (smiles, "@@SP", "@SP");
smiles = JU.PT.rep (smiles, "@@OH", "@OH");
smiles = JU.PT.rep (smiles, "@@TB", "@TB");
return smiles;
}, "~S");
Clazz.overrideMethod (c$, "getSubstructureSet", 
function (pattern, atoms, ac, bsSelected, flags) {
return this.matchPriv (pattern, atoms, ac, bsSelected, null, flags | 2097152 | 4096);
}, "~S,~A,~N,JU.BS,~N");
Clazz.overrideMethod (c$, "getSubstructureSets", 
function (smarts, atoms, ac, flags, bsSelected, ret, vRings) {
JS.InvalidSmilesException.clear ();
var sp =  new JS.SmilesParser (true);
var search = null;
search = sp.parse ("");
search.firstMatchOnly = false;
search.matchAllAtoms = false;
search.jmolAtoms = atoms;
search.jmolAtomCount = Math.abs (ac);
search.setSelected (bsSelected);
search.getRingData (true, flags, vRings);
search.asVector = false;
search.subSearches =  new Array (1);
search.getSelections ();
var bsDone =  new JU.BS ();
for (var i = 0; i < smarts.length; i++) {
if (smarts[i] == null || smarts[i].length == 0 || smarts[i].startsWith ("#")) {
ret.addLast (null);
continue;
}search.clear ();
var ss = sp.getSearch (search, JS.SmilesParser.cleanPattern (smarts[i]), flags);
search.subSearches[0] = ss;
var bs = JU.BSUtil.copy (search.search (false));
ret.addLast (bs);
bsDone.or (bs);
if (bsDone.cardinality () == ac) return;
}
}, "~A,~A,~N,~N,JU.BS,JU.Lst,~A");
Clazz.overrideMethod (c$, "getSubstructureSetArray", 
function (pattern, atoms, ac, bsSelected, bsAromatic, flags) {
return this.matchPriv (pattern, atoms, ac, bsSelected, bsAromatic, flags | 2097152 | 8192);
}, "~S,~A,~N,JU.BS,JU.BS,~N");
Clazz.overrideMethod (c$, "polyhedronToSmiles", 
function (faces, atomCount, points) {
var atoms =  new Array (atomCount);
for (var i = 0; i < atomCount; i++) {
atoms[i] =  new JS.SmilesAtom ();
var pt = (points == null ? null : points[i]);
atoms[i].elementNumber = (pt == null ? -2 : Clazz.instanceOf (pt, JU.Node) ? (pt).getElementNumber () : Clazz.instanceOf (pt, JU.Point3fi) ? (pt).sD : -2);
atoms[i].index = i;
}
var nBonds = 0;
for (var i = faces.length; --i >= 0; ) {
var face = faces[i];
var n = face.length;
for (var j = n; --j >= 0; ) {
var iatom = face[j];
if (iatom < 0 || iatom >= atomCount) continue;
var iatom2 = face[(j + 1) % n];
if (iatom2 < 0 || iatom2 >= atomCount) iatom2 = face[(j + 2) % n];
if (iatom2 < 0 || iatom2 >= atomCount) continue;
if (atoms[iatom].getBondTo (atoms[iatom2]) == null) {
var b =  new JS.SmilesBond (atoms[iatom], atoms[iatom2], 1, false);
b.index = nBonds++;
}}
}
for (var i = 0; i < atomCount; i++) {
var n = atoms[i].bondCount;
if (n == 0 || n != atoms[i].bonds.length) atoms[i].bonds = JU.AU.arrayCopyObject (atoms[i].bonds, n);
}
return this.getSmiles (atoms, atomCount, JU.BSUtil.newBitSet2 (0, atomCount), null, 4 | (points == null ? 2 : 65536));
}, "~A,~N,~A");
Clazz.overrideMethod (c$, "getCorrelationMaps", 
function (pattern, atoms, atomCount, bsSelected, flags) {
return this.matchPriv (pattern, atoms, atomCount, bsSelected, null, flags | 2097152 | 12288);
}, "~S,~A,~N,JU.BS,~N");
Clazz.defineMethod (c$, "findPriv", 
 function (pattern, search, flags) {
var bsAromatic =  new JU.BS ();
search.createTopoMap (bsAromatic);
return this.matchPriv (pattern, search.jmolAtoms, -search.jmolAtoms.length, null, bsAromatic, flags);
}, "~S,JS.SmilesSearch,~N");
Clazz.defineMethod (c$, "matchPriv", 
 function (pattern, atoms, ac, bsSelected, bsAromatic, flags) {
JS.InvalidSmilesException.clear ();
try {
var search = JS.SmilesParser.getMolecule (pattern, this.checkFlag (flags, 131072));
search.jmolAtoms = atoms;
if (Clazz.instanceOf (atoms, Array)) search.bioAtoms = atoms;
search.jmolAtomCount = Math.abs (ac);
if (ac < 0) search.isSmilesFind = true;
search.setSelected (bsSelected);
search.getSelections ();
search.bsRequired = null;
search.setRingData (bsAromatic);
search.firstMatchOnly = this.checkFlag (flags, 4194304);
search.matchAllAtoms = this.checkFlag (flags, 1048576);
switch (flags & 61440) {
case 4096:
search.asVector = false;
return search.search (false);
case 8192:
search.asVector = true;
var vb = search.search (false);
return vb.toArray ( new Array (vb.size ()));
case 12288:
search.getMaps = true;
var vl = search.search (false);
return vl.toArray (JU.AU.newInt2 (vl.size ()));
}
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
e.printStackTrace ();
if (JS.InvalidSmilesException.getLastError () == null) JS.InvalidSmilesException.clear ();
throw  new JS.InvalidSmilesException (JS.InvalidSmilesException.getLastError ());
} else {
throw e;
}
}
return null;
}, "~S,~A,~N,JU.BS,JU.BS,~N");
c$.countStereo = Clazz.defineMethod (c$, "countStereo", 
 function (s) {
s = JU.PT.rep (s, "@@", "@");
var i = s.lastIndexOf ('@') + 1;
var n = 0;
for (; --i >= 0; ) if (s.charAt (i) == '@') n++;

return n;
}, "~S");
Clazz.overrideMethod (c$, "cleanSmiles", 
function (smiles) {
return JS.SmilesParser.cleanPattern (smiles);
}, "~S");
Clazz.defineStatics (c$,
"SMILES_MODE_BITSET", 0x001000,
"SMILES_MODE_ARRAY", 0x002000,
"SMILES_MODE_MAP", 0x003000,
"SMILES_MODE_MASK", 0x00F000);
});
