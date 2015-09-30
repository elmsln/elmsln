Clazz.declarePackage ("JV");
Clazz.load (["JU.SB", "$.V3", "JU.Elements"], "JV.JC", ["JU.PT"], function () {
c$ = Clazz.declareType (JV, "JC");
c$.getMacroList = Clazz.defineMethod (c$, "getMacroList", 
function () {
var s =  new JU.SB ();
for (var i = 0; i < JV.JC.macros.length; i += 2) s.append (JV.JC.macros[i]).append ("\t").append (JV.JC.macros[i + 1]).append ("\n");

return s.toString ();
});
c$.getMacro = Clazz.defineMethod (c$, "getMacro", 
function (key) {
for (var i = 0; i < JV.JC.macros.length; i += 2) if (JV.JC.macros[i].equals (key)) return JV.JC.macros[i + 1];

return null;
}, "~S");
c$.embedScript = Clazz.defineMethod (c$, "embedScript", 
function (s) {
return "\n/**" + "**** Jmol Embedded Script ****" + " \n" + s + "\n**/";
}, "~S");
c$.getShapeVisibilityFlag = Clazz.defineMethod (c$, "getShapeVisibilityFlag", 
function (shapeID) {
return 16 << Math.min (shapeID, 26);
}, "~N");
c$.shapeTokenIndex = Clazz.defineMethod (c$, "shapeTokenIndex", 
function (tok) {
switch (tok) {
case 1141899265:
case 1073741860:
return 0;
case 1678770178:
case 659488:
return 1;
case 1612189718:
return 2;
case 1611141176:
return 3;
case 1708058:
return 4;
case 1826248716:
return 5;
case 1746538509:
case 537006096:
return 6;
case 1113200652:
return 7;
case 1113200646:
return 8;
case 1115297793:
return 9;
case 1113200654:
return 10;
case 1113200642:
return 11;
case 1650071565:
return 12;
case 1113200647:
return 13;
case 1113200649:
return 14;
case 1113200650:
return 15;
case 1113198595:
return 16;
case 135175:
return 17;
case 135198:
return 18;
case 1113198597:
return 19;
case 1113198596:
return 20;
case 1276252167:
return 21;
case 135174:
return 23;
case 135176:
return 22;
case 135180:
return 24;
case 135402505:
return 25;
case 135182:
return 26;
case 1073877010:
return 27;
case 1073877011:
return 28;
case 135188:
return 29;
case 135190:
return 30;
case 537022465:
return 31;
case 1611272194:
return 34;
case 1679429641:
return 32;
case 1614417948:
return 33;
case 544771:
return 35;
case 1611272202:
return 36;
}
return -1;
}, "~N");
c$.getShapeClassName = Clazz.defineMethod (c$, "getShapeClassName", 
function (shapeID, isRenderer) {
if (shapeID < 0) return JV.JC.shapeClassBases[~shapeID];
return "J." + (isRenderer ? "render" : "shape") + (shapeID >= 9 && shapeID < 16 ? "bio." : shapeID >= 16 && shapeID < 23 ? "special." : shapeID >= 24 && shapeID < 30 ? "surface." : shapeID == 23 ? "cgo." : ".") + JV.JC.shapeClassBases[shapeID];
}, "~N,~B");
c$.isScriptType = Clazz.defineMethod (c$, "isScriptType", 
function (fname) {
return JU.PT.isOneOf (fname.substring (fname.lastIndexOf (".") + 1), ";pse;spt;png;pngj;jmol;zip;");
}, "~S");
c$.getEchoName = Clazz.defineMethod (c$, "getEchoName", 
function (type) {
return JV.JC.echoNames[type];
}, "~N");
c$.setZPosition = Clazz.defineMethod (c$, "setZPosition", 
function (offset, pos) {
return (offset & -49) | pos;
}, "~N,~N");
c$.setPointer = Clazz.defineMethod (c$, "setPointer", 
function (offset, pointer) {
return (offset & -4) | pointer;
}, "~N,~N");
c$.getPointer = Clazz.defineMethod (c$, "getPointer", 
function (offset) {
return offset & 3;
}, "~N");
c$.getPointerName = Clazz.defineMethod (c$, "getPointerName", 
function (pointer) {
return ((pointer & 1) == 0 ? "" : (pointer & 2) > 0 ? "background" : "on");
}, "~N");
c$.isOffsetAbsolute = Clazz.defineMethod (c$, "isOffsetAbsolute", 
function (offset) {
return ((offset & 64) != 0);
}, "~N");
c$.getOffset = Clazz.defineMethod (c$, "getOffset", 
function (xOffset, yOffset, isAbsolute) {
xOffset = Math.min (Math.max (xOffset, -500), 500);
yOffset = (Math.min (Math.max (yOffset, -500), 500));
var offset = ((xOffset & 1023) << 21) | ((yOffset & 1023) << 11) | (isAbsolute ? 64 : 0);
if (offset == JV.JC.LABEL_DEFAULT_OFFSET) offset = 0;
 else if (!isAbsolute && (xOffset == 0 || yOffset == 0)) offset |= 256;
return offset;
}, "~N,~N,~B");
c$.getXOffset = Clazz.defineMethod (c$, "getXOffset", 
function (offset) {
if (offset == 0) return 4;
var x = (offset >> 21) & 1023;
x = (x > 500 ? x - 1023 - 1 : x);
return x;
}, "~N");
c$.getYOffset = Clazz.defineMethod (c$, "getYOffset", 
function (offset) {
if (offset == 0) return 4;
var y = (offset >> 11) & 1023;
return (y > 500 ? y - 1023 - 1 : y);
}, "~N");
c$.getAlignment = Clazz.defineMethod (c$, "getAlignment", 
function (offset) {
return (offset & 12);
}, "~N");
c$.setHorizAlignment = Clazz.defineMethod (c$, "setHorizAlignment", 
function (offset, hAlign) {
return (offset & -13) | hAlign;
}, "~N,~N");
c$.getHorizAlignmentName = Clazz.defineMethod (c$, "getHorizAlignmentName", 
function (align) {
return JV.JC.hAlignNames[(align >> 2) & 3];
}, "~N");
c$.getJSVSyncSignal = Clazz.defineMethod (c$, "getJSVSyncSignal", 
function (script) {
return (script.length < 7 ? -1 : ("JSPECVIPEAKS: SELECT:JSVSTR:H1SIMUL").indexOf (script.substring (0, 7).toUpperCase ()));
}, "~S");
Clazz.defineStatics (c$,
"PDB_ANNOTATIONS", ";dssr;rna3d;dom;val;",
"databases",  Clazz.newArray (-1, ["dssr", "http://x3dna.bio.columbia.edu/dssr/report.php?id=%FILE&opts=--jmol%20--more", "dssrModel", "http://x3dna.bio.columbia.edu/dssr/report.php?POST?opts=--jmol --more&model=", "ligand", "http://www.rcsb.org/pdb/files/ligand/%FILE.cif", "mp", "http://www.materialsproject.org/materials/%FILE/cif", "nci", "http://cactus.nci.nih.gov/chemical/structure/%FILE", "cod", "http://www.crystallography.net/cod/cif/%c1/%c2%c3/%c4%c5/%FILE.cif", "nmr", "http://www.nmrdb.org/new_predictor?POST?molfile=", "nmrdb", "http://www.nmrdb.org/service/predictor?POST?molfile=", "pdb", "http://www.rcsb.org/pdb/files/%FILE.pdb.gz", "pdbe", "http://www.ebi.ac.uk/pdbe/entry-files/download/%FILE.cif", "pubchem", "http://pubchem.ncbi.nlm.nih.gov/rest/pug/compound/%FILE/SDF?record_type=3d", "map", "http://www.ebi.ac.uk/pdbe/api/%TYPE/%FILE?pretty=false&metadata=true", "rna3d", "http://rna.bgsu.edu/rna3dhub/%TYPE/download/%FILE"]),
"macros",  Clazz.newArray (-1, ["aflow", "http://aflowlib.mems.duke.edu/users/jmolers/jmol/spt/AFLOW.spt"]),
"copyright", "(C) 2015 Jmol Development",
"version", null,
"date", null,
"versionInt", 0);
{
var tmpVersion = null;
var tmpDate = null;
{
tmpVersion = Jmol.___JmolVersion; tmpDate = Jmol.___JmolDate;
}if (tmpDate != null) {
tmpDate = tmpDate.substring (7, 23);
}JV.JC.version = (tmpVersion != null ? tmpVersion : "(Unknown version)");
JV.JC.date = (tmpDate != null ? tmpDate : "(Unknown date)");
var v = -1;
try {
var s = JV.JC.version;
var i = s.indexOf (".");
if (i < 0) {
v = 100000 * Integer.parseInt (s);
s = null;
}if (s != null) {
v = 100000 * Integer.parseInt (s.substring (0, i));
s = s.substring (i + 1);
i = s.indexOf (".");
if (i < 0) {
v += 1000 * Integer.parseInt (s);
s = null;
}if (s != null) {
v += 1000 * Integer.parseInt (s.substring (0, i));
s = s.substring (i + 1);
i = s.indexOf ("_");
if (i >= 0) s = s.substring (0, i);
i = s.indexOf (" ");
if (i >= 0) s = s.substring (0, i);
v += Integer.parseInt (s);
}}} catch (e) {
if (Clazz.exceptionOf (e, NumberFormatException)) {
} else {
throw e;
}
}
JV.JC.versionInt = v;
}Clazz.defineStatics (c$,
"officialRelease", false,
"DEFAULT_HELP_PATH", "http://chemapps.stolaf.edu/jmol/docs/index.htm",
"STATE_VERSION_STAMP", "# Jmol state version ",
"EMBEDDED_SCRIPT_TAG", "**** Jmol Embedded Script ****",
"NOTE_SCRIPT_FILE", "NOTE: file recognized as a script file: ",
"SCRIPT_EDITOR_IGNORE", "\1## EDITOR_IGNORE ##",
"REPAINT_IGNORE", "\1## REPAINT_IGNORE ##",
"LOAD_ATOM_DATA_TYPES", ";xyz;vxyz;vibration;temperature;occupancy;partialcharge;",
"radiansPerDegree", (0.017453292519943295),
"allowedQuaternionFrames", "RC;RP;a;b;c;n;p;q;x;",
"EXPORT_DRIVER_LIST", "Idtf;Maya;Povray;Vrml;X3d;Tachyon;Obj");
c$.center = c$.prototype.center = JU.V3.new3 (0, 0, 0);
c$.axisX = c$.prototype.axisX = JU.V3.new3 (1, 0, 0);
c$.axisY = c$.prototype.axisY = JU.V3.new3 (0, 1, 0);
c$.axisZ = c$.prototype.axisZ = JU.V3.new3 (0, 0, 1);
c$.axisNX = c$.prototype.axisNX = JU.V3.new3 (-1, 0, 0);
c$.axisNY = c$.prototype.axisNY = JU.V3.new3 (0, -1, 0);
c$.axisNZ = c$.prototype.axisNZ = JU.V3.new3 (0, 0, -1);
c$.unitAxisVectors = c$.prototype.unitAxisVectors =  Clazz.newArray (-1, [JV.JC.axisX, JV.JC.axisY, JV.JC.axisZ, JV.JC.axisNX, JV.JC.axisNY, JV.JC.axisNZ]);
Clazz.defineStatics (c$,
"XY_ZTOP", 100,
"DEFAULT_PERCENT_VDW_ATOM", 23,
"DEFAULT_BOND_RADIUS", 0.15,
"DEFAULT_BOND_MILLIANGSTROM_RADIUS", Clazz.floatToShort (150.0),
"DEFAULT_STRUT_RADIUS", 0.3,
"DEFAULT_BOND_TOLERANCE", 0.45,
"DEFAULT_MIN_BOND_DISTANCE", 0.4,
"DEFAULT_MAX_CONNECT_DISTANCE", 100000000,
"DEFAULT_MIN_CONNECT_DISTANCE", 0.1,
"MINIMIZATION_ATOM_MAX", 200,
"MINIMIZE_FIXED_RANGE", 5.0,
"ENC_CALC_MAX_DIST", 3,
"ENV_CALC_MAX_LEVEL", 3,
"MOUSE_NONE", -1,
"MULTIBOND_NEVER", 0,
"MULTIBOND_WIREFRAME", 1,
"MULTIBOND_NOTSMALL", 2,
"MULTIBOND_ALWAYS", 3,
"MAXIMUM_AUTO_BOND_COUNT", 20,
"madMultipleBondSmallMaximum", 500,
"ANGSTROMS_PER_BOHR", 0.5291772,
"altArgbsCpk",  Clazz.newIntArray (-1, [0xFFFF1493, 0xFFBFA6A6, 0xFFFFFF30, 0xFF57178F, 0xFFFFFFC0, 0xFFFFFFA0, 0xFFD8D8D8, 0xFF505050, 0xFF404040, 0xFF105050]),
"argbsFormalCharge",  Clazz.newIntArray (-1, [0xFFFF0000, 0xFFFF4040, 0xFFFF8080, 0xFFFFC0C0, 0xFFFFFFFF, 0xFFD8D8FF, 0xFFB4B4FF, 0xFF9090FF, 0xFF6C6CFF, 0xFF4848FF, 0xFF2424FF, 0xFF0000FF]),
"argbsRwbScale",  Clazz.newIntArray (-1, [0xFFFF0000, 0xFFFF1010, 0xFFFF2020, 0xFFFF3030, 0xFFFF4040, 0xFFFF5050, 0xFFFF6060, 0xFFFF7070, 0xFFFF8080, 0xFFFF9090, 0xFFFFA0A0, 0xFFFFB0B0, 0xFFFFC0C0, 0xFFFFD0D0, 0xFFFFE0E0, 0xFFFFFFFF, 0xFFE0E0FF, 0xFFD0D0FF, 0xFFC0C0FF, 0xFFB0B0FF, 0xFFA0A0FF, 0xFF9090FF, 0xFF8080FF, 0xFF7070FF, 0xFF6060FF, 0xFF5050FF, 0xFF4040FF, 0xFF3030FF, 0xFF2020FF, 0xFF1010FF, 0xFF0000FF]));
c$.FORMAL_CHARGE_COLIX_RED = c$.prototype.FORMAL_CHARGE_COLIX_RED = JU.Elements.elementSymbols.length + JV.JC.altArgbsCpk.length;
c$.PARTIAL_CHARGE_COLIX_RED = c$.prototype.PARTIAL_CHARGE_COLIX_RED = JV.JC.FORMAL_CHARGE_COLIX_RED + JV.JC.argbsFormalCharge.length;
c$.PARTIAL_CHARGE_RANGE_SIZE = c$.prototype.PARTIAL_CHARGE_RANGE_SIZE = JV.JC.argbsRwbScale.length;
Clazz.defineStatics (c$,
"argbsRoygbScale",  Clazz.newIntArray (-1, [0xFFFF0000, 0xFFFF2000, 0xFFFF4000, 0xFFFF6000, 0xFFFF8000, 0xFFFFA000, 0xFFFFC000, 0xFFFFE000, 0xFFFFF000, 0xFFFFFF00, 0xFFF0F000, 0xFFE0FF00, 0xFFC0FF00, 0xFFA0FF00, 0xFF80FF00, 0xFF60FF00, 0xFF40FF00, 0xFF20FF00, 0xFF00FF00, 0xFF00FF20, 0xFF00FF40, 0xFF00FF60, 0xFF00FF80, 0xFF00FFA0, 0xFF00FFC0, 0xFF00FFE0, 0xFF00FFFF, 0xFF00E0FF, 0xFF00C0FF, 0xFF00A0FF, 0xFF0080FF, 0xFF0060FF, 0xFF0040FF, 0xFF0020FF, 0xFF0000FF]),
"argbsIsosurfacePositive", 0xFF5020A0,
"argbsIsosurfaceNegative", 0xFFA02050,
"ATOMID_AMINO_NITROGEN", 1,
"ATOMID_ALPHA_CARBON", 2,
"ATOMID_CARBONYL_CARBON", 3,
"ATOMID_CARBONYL_OXYGEN", 4,
"ATOMID_O1", 5,
"ATOMID_ALPHA_ONLY_MASK", 4,
"ATOMID_PROTEIN_MASK", 14,
"ATOMID_O5_PRIME", 6,
"ATOMID_C5_PRIME", 7,
"ATOMID_C4_PRIME", 8,
"ATOMID_C3_PRIME", 9,
"ATOMID_O3_PRIME", 10,
"ATOMID_C2_PRIME", 11,
"ATOMID_C1_PRIME", 12,
"ATOMID_O4_PRIME", 78,
"ATOMID_NUCLEIC_MASK", 8128,
"ATOMID_NUCLEIC_PHOSPHORUS", 13,
"ATOMID_PHOSPHORUS_ONLY_MASK", 8192,
"ATOMID_DISTINGUISHING_ATOM_MAX", 14,
"ATOMID_CARBONYL_OD1", 14,
"ATOMID_CARBONYL_OD2", 15,
"ATOMID_CARBONYL_OE1", 16,
"ATOMID_CARBONYL_OE2", 17,
"ATOMID_N1", 32,
"ATOMID_C2", 33,
"ATOMID_N3", 34,
"ATOMID_C4", 35,
"ATOMID_C5", 36,
"ATOMID_C6", 37,
"ATOMID_O2", 38,
"ATOMID_N7", 39,
"ATOMID_C8", 40,
"ATOMID_N9", 41,
"ATOMID_N4", 42,
"ATOMID_N2", 43,
"ATOMID_N6", 44,
"ATOMID_C5M", 45,
"ATOMID_O6", 46,
"ATOMID_O4", 47,
"ATOMID_S4", 48,
"ATOMID_C7", 49,
"ATOMID_TERMINATING_OXT", 64,
"ATOMID_H5T_TERMINUS", 72,
"ATOMID_O5T_TERMINUS", 73,
"ATOMID_O1P", 74,
"ATOMID_OP1", 75,
"ATOMID_O2P", 76,
"ATOMID_OP2", 77,
"ATOMID_O2_PRIME", 79,
"ATOMID_H3T_TERMINUS", 88,
"ATOMID_HO3_PRIME", 89,
"ATOMID_HO5_PRIME", 90,
"GROUPID_ARGININE", 2,
"GROUPID_ASPARAGINE", 3,
"GROUPID_ASPARTATE", 4,
"GROUPID_CYSTEINE", 5,
"GROUPID_GLUTAMINE", 6,
"GROUPID_GLUTAMATE", 7,
"GROUPID_HISTIDINE", 9,
"GROUPID_LYSINE", 12,
"GROUPID_PROLINE", 15,
"GROUPID_TRYPTOPHAN", 19,
"GROUPID_AMINO_MAX", 24,
"GROUPID_NUCLEIC_MAX", 42,
"GROUPID_WATER", 42,
"GROUPID_SOLVENT_MIN", 45,
"GROUPID_ION_MIN", 46,
"GROUPID_ION_MAX", 48,
"predefinedVariable",  Clazz.newArray (-1, ["@_1H _H & !(_2H,_3H)", "@_12C _C & !(_13C,_14C)", "@_14N _N & !(_15N)", "@solvent water, (_g>=45 & _g<48)", "@ligand _g=0|!(_g<46,protein,nucleic,water)", "@turn structure=1", "@sheet structure=2", "@helix structure=3", "@helix310 substructure=7", "@helixalpha substructure=8", "@helixpi substructure=9"]),
"predefinedStatic",  Clazz.newArray (-1, ["@amino _g>0 & _g<=23", "@acidic asp,glu", "@basic arg,his,lys", "@charged acidic,basic", "@negative acidic", "@positive basic", "@neutral amino&!(acidic,basic)", "@polar amino&!hydrophobic", "@cyclic his,phe,pro,trp,tyr", "@acyclic amino&!cyclic", "@aliphatic ala,gly,ile,leu,val", "@aromatic his,phe,trp,tyr", "@cystine within(group, (cys.sg or cyx.sg) and connected(cys.sg or cyx.sg))", "@buried ala,cys,ile,leu,met,phe,trp,val", "@surface amino&!buried", "@hydrophobic ala,gly,ile,leu,met,phe,pro,trp,tyr,val", "@mainchain backbone", "@small ala,gly,ser", "@medium asn,asp,cys,pro,thr,val", "@large arg,glu,gln,his,ile,leu,lys,met,phe,trp,tyr", "@c nucleic & ([C] or [DC] or within(group,_a=42))", "@g nucleic & ([G] or [DG] or within(group,_a=43))", "@cg c,g", "@a nucleic & ([A] or [DA] or within(group,_a=44))", "@t nucleic & ([T] or [DT] or within(group,_a=45 | _a=49))", "@at a,t", "@i nucleic & ([I] or [DI] or within(group,_a=46) & !g)", "@u nucleic & ([U] or [DU] or within(group,_a=47) & !t)", "@tu nucleic & within(group,_a=48)", "@ions _g>=46&_g<48", "@alpha _a=2", "@backbone protein&(_a>=1&_a<6|_a>=64&_a<72)|nucleic&(_a>=6&_a<14|_a>=72)", "@spine protein&_a>=1&_a<4|nucleic&_a>=6&_a<14&_a!=12", "@sidechain (protein,nucleic) & !backbone", "@base nucleic & !backbone", "@dynamic_flatring search('[a]')"]),
"MODELKIT_ZAP_STRING", "5\n\nC 0 0 0\nH .63 .63 .63\nH -.63 -.63 .63\nH -.63 .63 -.63\nH .63 -.63 -.63",
"MODELKIT_ZAP_TITLE", "Jmol Model Kit",
"ZAP_TITLE", "zapped",
"ADD_HYDROGEN_TITLE", "Viewer.AddHydrogens",
"DEFAULT_FONTFACE", "SansSerif",
"DEFAULT_FONTSTYLE", "Plain",
"MEASURE_DEFAULT_FONTSIZE", 15,
"AXES_DEFAULT_FONTSIZE", 14,
"SHAPE_BALLS", 0,
"SHAPE_STICKS", 1,
"SHAPE_HSTICKS", 2,
"SHAPE_SSSTICKS", 3,
"SHAPE_STRUTS", 4,
"SHAPE_LABELS", 5,
"SHAPE_MEASURES", 6,
"SHAPE_STARS", 7,
"SHAPE_MIN_HAS_SETVIS", 8,
"SHAPE_HALOS", 8,
"SHAPE_MIN_SECONDARY", 9,
"SHAPE_BACKBONE", 9,
"SHAPE_TRACE", 10,
"SHAPE_CARTOON", 11,
"SHAPE_STRANDS", 12,
"SHAPE_MESHRIBBON", 13,
"SHAPE_RIBBONS", 14,
"SHAPE_ROCKETS", 15,
"SHAPE_MAX_SECONDARY", 16,
"SHAPE_MIN_SPECIAL", 16,
"SHAPE_DOTS", 16,
"SHAPE_DIPOLES", 17,
"SHAPE_VECTORS", 18,
"SHAPE_GEOSURFACE", 19,
"SHAPE_ELLIPSOIDS", 20,
"SHAPE_MAX_SIZE_ZERO_ON_RESTRICT", 21,
"SHAPE_POLYHEDRA", 21,
"SHAPE_MIN_HAS_ID", 22,
"SHAPE_MIN_MESH_COLLECTION", 22,
"SHAPE_DRAW", 22,
"SHAPE_MAX_SPECIAL", 23,
"SHAPE_CGO", 23,
"SHAPE_MIN_SURFACE", 24,
"SHAPE_ISOSURFACE", 24,
"SHAPE_CONTACT", 25,
"SHAPE_LCAOCARTOON", 26,
"SHAPE_LAST_ATOM_VIS_FLAG", 26,
"SHAPE_MO", 27,
"SHAPE_NBO", 28,
"SHAPE_PMESH", 29,
"SHAPE_PLOT3D", 30,
"SHAPE_MAX_SURFACE", 30,
"SHAPE_MAX_MESH_COLLECTION", 30,
"SHAPE_ECHO", 31,
"SHAPE_MAX_HAS_ID", 32,
"SHAPE_BBCAGE", 32,
"SHAPE_MAX_HAS_SETVIS", 33,
"SHAPE_UCCAGE", 33,
"SHAPE_AXES", 34,
"SHAPE_HOVER", 35,
"SHAPE_FRANK", 36,
"SHAPE_MAX", 37,
"VIS_BOND_FLAG", 32,
"VIS_BALLS_FLAG", 16,
"VIS_LABEL_FLAG", 512,
"VIS_BACKBONE_FLAG", 8192,
"VIS_CARTOON_FLAG", 32768,
"ALPHA_CARBON_VISIBILITY_FLAG", 1040384,
"shapeClassBases",  Clazz.newArray (-1, ["Balls", "Sticks", "Hsticks", "Sssticks", "Struts", "Labels", "Measures", "Stars", "Halos", "Backbone", "Trace", "Cartoon", "Strands", "MeshRibbon", "Ribbons", "Rockets", "Dots", "Dipoles", "Vectors", "GeoSurface", "Ellipsoids", "Polyhedra", "Draw", "CGO", "Isosurface", "Contact", "LcaoCartoon", "MolecularOrbital", "NBO", "Pmesh", "Plot3D", "Echo", "Bbcage", "Uccage", "Axes", "Hover", "Frank"]),
"SCRIPT_COMPLETED", "Script completed",
"JPEG_EXTENSIONS", ";jpg;jpeg;jpg64;jpeg64;");
c$.IMAGE_TYPES = c$.prototype.IMAGE_TYPES = ";jpg;jpeg;jpg64;jpeg64;gif;gift;pdf;ppm;png;pngj;pngt;";
c$.IMAGE_OR_SCENE = c$.prototype.IMAGE_OR_SCENE = ";jpg;jpeg;jpg64;jpeg64;gif;gift;pdf;ppm;png;pngj;pngt;scene;";
{
{
}}Clazz.defineStatics (c$,
"LABEL_MINIMUM_FONTSIZE", 6,
"LABEL_MAXIMUM_FONTSIZE", 63,
"LABEL_DEFAULT_FONTSIZE", 13,
"LABEL_DEFAULT_X_OFFSET", 4,
"LABEL_DEFAULT_Y_OFFSET", 4,
"LABEL_OFFSET_MAX", 500,
"LABEL_OFFSET_MASK", 0x3FF,
"LABEL_FLAGY_OFFSET_SHIFT", 11,
"LABEL_FLAGX_OFFSET_SHIFT", 21,
"LABEL_FLAGS", 0x07F,
"LABEL_POINTER_FLAGS", 0x003,
"LABEL_POINTER_NONE", 0x000,
"LABEL_POINTER_ON", 0x001,
"LABEL_POINTER_BACKGROUND", 0x002,
"TEXT_ALIGN_SHIFT", 0x002,
"TEXT_ALIGN_FLAGS", 0x00C,
"TEXT_ALIGN_NONE", 0x000,
"TEXT_ALIGN_LEFT", 0x004,
"TEXT_ALIGN_CENTER", 0x008,
"TEXT_ALIGN_RIGHT", 0x00C,
"LABEL_ZPOS_FLAGS", 0x030,
"LABEL_ZPOS_GROUP", 0x010,
"LABEL_ZPOS_FRONT", 0x020,
"LABEL_EXPLICIT", 0x040,
"LABEL_CENTERED", 0x100,
"LABEL_DEFAULT_OFFSET", 8396800,
"ECHO_TOP", 0,
"ECHO_BOTTOM", 1,
"ECHO_MIDDLE", 2,
"ECHO_XY", 3,
"ECHO_XYZ", 4,
"echoNames",  Clazz.newArray (-1, ["top", "bottom", "middle", "xy", "xyz"]),
"hAlignNames",  Clazz.newArray (-1, ["", "left", "center", "right"]),
"JSV_NOT", -1,
"JSV_SEND_JDXMOL", 0,
"JSV_SETPEAKS", 7,
"JSV_SELECT", 14,
"JSV_STRUCTURE", 21,
"JSV_SEND_H1SIMULATE", 28,
"SMILES_EXPLICIT_H", 0x001,
"SMILES_TOPOLOGY", 0x002,
"SMILES_NOAROMATIC", 0x004,
"SMILES_BIO", 0x100,
"SMILES_BIO_ALLOW_UNMACHED_RINGS", 0x101,
"SMILES_BIO_CROSSLINK", 0x102,
"SMILES_BIO_COMMENT", 0x104,
"SMILES_TYPE_SMILES", 0x010000,
"SMILES_TYPE_SMARTS", 0x020000,
"SMILES_MATCH_ALL", 0x100000,
"SMILES_MATCH_ONE", 0x200000,
"SMILES_RETURN_FIRST", 0x400000,
"READER_NOT_FOUND", "File reader was not found:");
});
