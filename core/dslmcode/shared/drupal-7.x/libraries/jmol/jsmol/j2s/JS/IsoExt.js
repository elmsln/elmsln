Clazz.declarePackage ("JS");
Clazz.load (["JS.ScriptExt"], "JS.IsoExt", ["java.lang.Boolean", "$.Float", "$.Short", "java.util.Hashtable", "JU.AU", "$.BS", "$.Lst", "$.M4", "$.P3", "$.PT", "$.Quat", "$.SB", "$.V3", "J.api.Interface", "J.atomdata.RadiusData", "J.c.VDW", "JS.SV", "$.ScriptEval", "$.T", "JU.BSUtil", "$.BoxInfo", "$.C", "$.Escape", "$.Logger", "$.Parser", "$.TempArray"], function () {
c$ = Clazz.declareType (JS, "IsoExt", JS.ScriptExt);
Clazz.makeConstructor (c$, 
function () {
Clazz.superConstructor (this, JS.IsoExt, []);
});
Clazz.overrideMethod (c$, "dispatch", 
function (iTok, b, st) {
this.chk = this.e.chk;
this.slen = this.e.slen;
this.st = st;
switch (iTok) {
case 23:
this.cgo ();
break;
case 25:
this.contact ();
break;
case 17:
this.dipole ();
break;
case 22:
this.draw ();
break;
case 24:
case 30:
case 29:
this.isosurface (iTok);
break;
case 26:
this.lcaoCartoon ();
break;
case 27:
case 28:
this.mo (b, iTok);
break;
}
return null;
}, "~N,~B,~A");
Clazz.defineMethod (c$, "dipole", 
 function () {
var eval = this.e;
var propertyName = null;
var propertyValue = null;
var iHaveAtoms = false;
var iHaveCoord = false;
var idSeen = false;
eval.sm.loadShape (17);
if (this.tokAt (1) == 1073742001 && this.listIsosurface (17)) return;
this.setShapeProperty (17, "init", null);
if (this.slen == 1) {
this.setShapeProperty (17, "thisID", null);
return;
}for (var i = 1; i < this.slen; ++i) {
propertyName = null;
propertyValue = null;
switch (this.getToken (i).tok) {
case 1048579:
propertyName = "all";
break;
case 1048589:
propertyName = "on";
break;
case 1048588:
propertyName = "off";
break;
case 12291:
propertyName = "delete";
break;
case 2:
case 3:
propertyName = "value";
propertyValue = Float.$valueOf (this.floatParameter (i));
break;
case 10:
if (this.tokAt (i + 1) == 10) {
this.setShapeProperty (17, "startSet", this.atomExpressionAt (i++));
} else {
propertyName = "atomBitset";
}case 1048577:
if (propertyName == null) propertyName = (iHaveAtoms || iHaveCoord ? "endSet" : "startSet");
propertyValue = this.atomExpressionAt (i);
i = eval.iToken;
if (this.tokAt (i + 1) == 0 && propertyName === "startSet") propertyName = "atomBitset";
iHaveAtoms = true;
break;
case 1048586:
case 8:
var pt = this.getPoint3f (i, true);
i = eval.iToken;
propertyName = (iHaveAtoms || iHaveCoord ? "endCoord" : "startCoord");
propertyValue = pt;
iHaveCoord = true;
break;
case 1678770178:
propertyName = "bonds";
break;
case 4102:
propertyName = "calculate";
if (this.tokAt (i + 1) == 10 || this.tokAt (i + 1) == 1048577) {
propertyValue = this.atomExpressionAt (++i);
i = eval.iToken;
}break;
case 1074790550:
this.setShapeId (17, ++i, idSeen);
i = eval.iToken;
break;
case 135267329:
propertyName = "cross";
propertyValue = Boolean.TRUE;
break;
case 1073742040:
propertyName = "cross";
propertyValue = Boolean.FALSE;
break;
case 1073742066:
if (this.isFloatParameter (i + 1)) {
var v = this.floatParameter (++i);
if (eval.theTok == 2) {
propertyName = "offsetPercent";
propertyValue = Integer.$valueOf (Clazz.floatToInt (v));
} else {
propertyName = "offset";
propertyValue = Float.$valueOf (v);
}} else {
propertyName = "offsetPt";
propertyValue = this.centerParameter (++i);
i = eval.iToken;
}break;
case 1073742068:
propertyName = "offsetSide";
propertyValue = Float.$valueOf (this.floatParameter (++i));
break;
case 1073742188:
propertyName = "value";
propertyValue = Float.$valueOf (this.floatParameter (++i));
break;
case 1073742196:
propertyName = "width";
propertyValue = Float.$valueOf (this.floatParameter (++i));
break;
default:
if (eval.theTok == 269484209 || JS.T.tokAttr (eval.theTok, 1073741824)) {
this.setShapeId (17, i, idSeen);
i = eval.iToken;
break;
}this.invArg ();
}
idSeen = (eval.theTok != 12291 && eval.theTok != 4102);
if (propertyName != null) this.setShapeProperty (17, propertyName, propertyValue);
}
if (iHaveCoord || iHaveAtoms) this.setShapeProperty (17, "set", null);
});
Clazz.defineMethod (c$, "draw", 
 function () {
var eval = this.e;
eval.sm.loadShape (22);
switch (this.tokAt (1)) {
case 1073742001:
if (this.listIsosurface (22)) return false;
break;
case 1073742102:
var pt = 2;
var type = (this.tokAt (pt) == 1073742138 ? "" : eval.optParameterAsString (pt));
if (type.equalsIgnoreCase ("chemicalShift")) type = "cs";
 else if (type.equalsIgnoreCase ("polyhedra")) type = ":poly";
var scale = 1;
var index = 0;
if (type.length > 0) {
if (this.isFloatParameter (++pt)) index = this.intParameter (pt++);
}if (this.tokAt (pt) == 1073742138) scale = this.floatParameter (++pt);
if (!this.chk) eval.runScript (this.vwr.ms.getPointGroupAsString (this.vwr.bsA (), true, type, index, scale));
return false;
case 137363467:
case 135270418:
case 1052714:
this.e.getCmdExt ().plot (this.st);
return false;
}
var havePoints = false;
var isInitialized = false;
var isSavedState = false;
var isIntersect = false;
var isFrame = false;
var plane;
var tokIntersect = 0;
var translucentLevel = 3.4028235E38;
var colorArgb =  Clazz.newIntArray (-1, [-2147483648]);
var intScale = 0;
var swidth = "";
var iptDisplayProperty = 0;
var center = null;
var thisId = this.initIsosurface (22);
var idSeen = (thisId != null);
var isWild = (idSeen && this.getShapeProperty (22, "ID") == null);
var connections = null;
var iConnect = 0;
for (var i = eval.iToken; i < this.slen; ++i) {
var propertyName = null;
var propertyValue = null;
switch (this.getToken (i).tok) {
case 1614417948:
case 1679429641:
if (this.chk) break;
var vp = this.vwr.getPlaneIntersection (eval.theTok, null, intScale / 100, 0);
intScale = 0;
propertyName = "polygon";
propertyValue = vp;
havePoints = true;
break;
case 4106:
connections =  Clazz.newIntArray (4, 0);
iConnect = 4;
var farray = eval.floatParameterSet (++i, 4, 4);
i = eval.iToken;
for (var j = 0; j < 4; j++) connections[j] = Clazz.floatToInt (farray[j]);

havePoints = true;
break;
case 1678770178:
case 1141899265:
if (connections == null || iConnect > (eval.theTok == 1229980163 ? 2 : 3)) {
iConnect = 0;
connections =  Clazz.newIntArray (-1, [-1, -1, -1, -1]);
}connections[iConnect++] = this.atomExpressionAt (++i).nextSetBit (0);
i = eval.iToken;
connections[iConnect++] = (eval.theTok == 1678770178 ? this.atomExpressionAt (++i).nextSetBit (0) : -1);
i = eval.iToken;
havePoints = true;
break;
case 554176565:
switch (this.getToken (++i).tok) {
case 1048582:
propertyName = "slab";
propertyValue = eval.objectNameParameter (++i);
i = eval.iToken;
havePoints = true;
break;
default:
this.invArg ();
}
break;
case 135267842:
switch (this.getToken (++i).tok) {
case 1614417948:
case 1679429641:
tokIntersect = eval.theTok;
isIntersect = true;
continue;
case 1048582:
propertyName = "intersect";
propertyValue = eval.objectNameParameter (++i);
i = eval.iToken;
isIntersect = true;
havePoints = true;
break;
default:
this.invArg ();
}
break;
case 135266320:
case 1073742106:
var isPoints = (eval.theTok == 135266320);
propertyName = "polygon";
havePoints = true;
var v =  new JU.Lst ();
var nVertices = 0;
var nTriangles = 0;
var points = null;
var vpolygons = null;
if (eval.isArrayParameter (++i)) {
points = eval.getPointArray (i, -1, false);
nVertices = points.length;
} else {
nVertices = Math.max (0, this.intParameter (i));
points =  new Array (nVertices);
for (var j = 0; j < nVertices; j++) points[j] = this.centerParameter (++eval.iToken);

i = eval.iToken;
}var polygons = null;
switch (this.tokAt (i + 1)) {
case 11:
case 12:
var sv = JS.SV.newT (this.getToken (++i));
sv.toArray ();
vpolygons = sv.getList ();
nTriangles = vpolygons.size ();
break;
case 7:
vpolygons = (this.getToken (++i)).getList ();
nTriangles = vpolygons.size ();
break;
case 2:
nTriangles = this.intParameter (++i);
if (nTriangles < 0) isPoints = true;
break;
default:
if (!isPoints && !this.chk) polygons = (J.api.Interface.getInterface ("JU.MeshCapper", this.vwr, "script")).set (null).triangulatePolygon (points);
}
if (polygons == null && !isPoints) {
polygons = JU.AU.newInt2 (nTriangles);
for (var j = 0; j < nTriangles; j++) {
var f = (vpolygons == null ? eval.floatParameterSet (++eval.iToken, 3, 4) : JS.SV.flistValue (vpolygons.get (j), 0));
if (f.length < 3 || f.length > 4) this.invArg ();
polygons[j] =  Clazz.newIntArray (-1, [Clazz.floatToInt (f[0]), Clazz.floatToInt (f[1]), Clazz.floatToInt (f[2]), (f.length == 3 ? 7 : Clazz.floatToInt (f[3]))]);
}
}if (nVertices > 0) {
v.addLast (points);
v.addLast (polygons);
} else {
v = null;
}propertyValue = v;
i = eval.iToken;
break;
case 1297090050:
var xyz = null;
var iSym = 0;
plane = null;
var target = null;
switch (this.tokAt (++i)) {
case 4:
xyz = this.stringParameter (i);
break;
case 12:
xyz = JS.SV.sValue (this.getToken (i));
break;
case 2:
default:
if (!eval.isCenterParameter (i)) iSym = this.intParameter (i++);
if (eval.isCenterParameter (i)) center = this.centerParameter (i);
if (eval.isCenterParameter (eval.iToken + 1)) target = this.centerParameter (++eval.iToken);
if (this.chk) return false;
i = eval.iToken;
}
var bsAtoms = null;
if (center == null && i + 1 < this.slen) {
center = this.centerParameter (++i);
bsAtoms = (this.tokAt (i) == 10 || this.tokAt (i) == 1048577 ? this.atomExpressionAt (i) : null);
i = eval.iToken + 1;
}eval.checkLast (eval.iToken);
if (!this.chk) {
var s = this.vwr.ms.getSymTemp (false).getSymmetryInfoAtom (this.vwr.ms, bsAtoms, xyz, iSym, center, target, thisId, 135176);
this.showString (s.substring (0, s.indexOf ('\n') + 1));
eval.runScript (s.length > 0 ? s : "draw ID \"sym_" + thisId + "*\" delete");
}return false;
case 4115:
isFrame = true;
continue;
case 1048586:
case 9:
case 8:
if (eval.theTok == 9 || !eval.isPoint3f (i)) {
propertyValue = eval.getPoint4f (i);
if (isFrame) {
eval.checkLast (eval.iToken);
if (!this.chk) eval.runScript (JU.Escape.drawQuat (JU.Quat.newP4 (propertyValue), (thisId == null ? "frame" : thisId), " " + swidth, (center == null ?  new JU.P3 () : center), intScale / 100));
return false;
}propertyName = "planedef";
} else {
propertyValue = center = this.getPoint3f (i, true);
propertyName = "coord";
}i = eval.iToken;
havePoints = true;
break;
case 135267841:
case 135266319:
if (!havePoints && !isIntersect && tokIntersect == 0 && eval.theTok != 135267841) {
propertyName = "plane";
break;
}if (eval.theTok == 135266319) {
plane = eval.planeParameter (i);
} else {
plane = eval.hklParameter (++i);
}i = eval.iToken;
if (tokIntersect != 0) {
if (this.chk) break;
var vpc = this.vwr.getPlaneIntersection (tokIntersect, plane, intScale / 100, 0);
intScale = 0;
propertyName = "polygon";
propertyValue = vpc;
} else {
propertyValue = plane;
propertyName = "planedef";
}havePoints = true;
break;
case 1073742000:
propertyName = "lineData";
propertyValue = eval.floatParameterSet (++i, 0, 2147483647);
i = eval.iToken;
havePoints = true;
break;
case 10:
case 1048577:
propertyName = "atomSet";
propertyValue = this.atomExpressionAt (i);
if (isFrame) center = this.centerParameter (i);
i = eval.iToken;
havePoints = true;
break;
case 7:
propertyName = "modelBasedPoints";
propertyValue = eval.theToken.value;
havePoints = true;
break;
case 1073742195:
case 269484080:
break;
case 269484096:
propertyValue = eval.xypParameter (i);
if (propertyValue != null) {
i = eval.iToken;
propertyName = "coord";
havePoints = true;
break;
}if (isSavedState) this.invArg ();
isSavedState = true;
break;
case 269484097:
if (!isSavedState) this.invArg ();
isSavedState = false;
break;
case 1141899269:
propertyName = "reverse";
break;
case 4:
propertyValue = this.stringParameter (i);
propertyName = "title";
break;
case 135198:
propertyName = "vector";
break;
case 1141899267:
propertyValue = Float.$valueOf (this.floatParameter (++i));
propertyName = "length";
break;
case 3:
propertyValue = Float.$valueOf (this.floatParameter (i));
propertyName = "length";
break;
case 1095761935:
propertyName = "modelIndex";
propertyValue = Integer.$valueOf (this.intParameter (++i));
break;
case 2:
if (isSavedState) {
propertyName = "modelIndex";
propertyValue = Integer.$valueOf (this.intParameter (i));
} else {
intScale = this.intParameter (i);
}break;
case 1073742138:
if (++i >= this.slen) this.error (34);
switch (this.getToken (i).tok) {
case 2:
intScale = this.intParameter (i);
continue;
case 3:
intScale = Math.round (this.floatParameter (i) * 100);
continue;
}
this.error (34);
break;
case 1074790550:
thisId = this.setShapeId (22, ++i, idSeen);
isWild = (this.getShapeProperty (22, "ID") == null);
i = eval.iToken;
break;
case 1073742027:
propertyName = "fixed";
propertyValue = Boolean.FALSE;
break;
case 1060869:
propertyName = "fixed";
propertyValue = Boolean.TRUE;
break;
case 1073742066:
var pt = this.getPoint3f (++i, true);
i = eval.iToken;
propertyName = "offset";
propertyValue = pt;
break;
case 1073741906:
propertyName = "crossed";
break;
case 1073742196:
propertyValue = Float.$valueOf (this.floatParameter (++i));
propertyName = "width";
swidth = propertyName + " " + propertyValue;
break;
case 1073741998:
propertyName = "line";
propertyValue = Boolean.TRUE;
break;
case 1073741908:
propertyName = "curve";
break;
case 1074790416:
propertyName = "arc";
break;
case 1073741846:
propertyName = "arrow";
break;
case 1073741880:
propertyName = "circle";
break;
case 1073741912:
propertyName = "cylinder";
break;
case 1073742194:
propertyName = "vertices";
break;
case 1073742048:
propertyName = "nohead";
break;
case 1073741861:
propertyName = "isbarb";
break;
case 1073742130:
propertyName = "rotate45";
break;
case 1073742092:
propertyName = "perp";
break;
case 1666189314:
case 1073741917:
var isRadius = (eval.theTok == 1666189314);
var f = this.floatParameter (++i);
if (isRadius) f *= 2;
propertyValue = Float.$valueOf (f);
propertyName = (isRadius || this.tokAt (i) == 3 ? "width" : "diameter");
swidth = propertyName + (this.tokAt (i) == 3 ? " " + f : " " + (Clazz.floatToInt (f)));
break;
case 1048582:
if ((this.tokAt (i + 2) == 269484096 || isFrame)) {
var pto = center = this.centerParameter (i);
i = eval.iToken;
propertyName = "coord";
propertyValue = pto;
havePoints = true;
break;
}propertyValue = eval.objectNameParameter (++i);
propertyName = "identifier";
havePoints = true;
break;
case 1766856708:
case 603979967:
case 1073742074:
idSeen = true;
translucentLevel = this.getColorTrans (eval, i, false, colorArgb);
i = eval.iToken;
continue;
default:
if (!eval.setMeshDisplayProperty (22, 0, eval.theTok)) {
if (eval.theTok == 269484209 || JS.T.tokAttr (eval.theTok, 1073741824)) {
thisId = this.setShapeId (22, i, idSeen);
i = eval.iToken;
break;
}this.invArg ();
}if (iptDisplayProperty == 0) iptDisplayProperty = i;
i = eval.iToken;
continue;
}
idSeen = (eval.theTok != 12291);
if (havePoints && !isInitialized && !isFrame) {
this.setShapeProperty (22, "points", Integer.$valueOf (intScale));
isInitialized = true;
intScale = 0;
}if (havePoints && isWild) this.invArg ();
if (propertyName != null) this.setShapeProperty (22, propertyName, propertyValue);
}
this.finalizeObject (22, colorArgb[0], translucentLevel, intScale, havePoints, connections, iptDisplayProperty, null);
return true;
});
Clazz.defineMethod (c$, "mo", 
 function (isInitOnly, iShape) {
var eval = this.e;
var offset = 2147483647;
var isNegOffset = false;
var nboType = null;
var bsModels = this.vwr.getVisibleFramesBitSet ();
var propertyList =  new JU.Lst ();
var i0 = 1;
if (this.tokAt (0) == 1073877011 && this.e.slen == 1) {
if (!this.chk) {
var htParams =  new java.util.Hashtable ();
htParams.put ("service", "nbo");
htParams.put ("action", "showPanel");
this.vwr.sm.processService (htParams);
}return;
}if (this.tokAt (1) == 1095766030 || this.tokAt (1) == 4115) {
i0 = eval.modelNumberParameter (2);
if (i0 < 0) this.invArg ();
bsModels.clearAll ();
bsModels.set (i0);
i0 = 3;
}eval.sm.loadShape (iShape);
for (var iModel = bsModels.nextSetBit (0); iModel >= 0; iModel = bsModels.nextSetBit (iModel + 1)) {
var i = i0;
if (this.tokAt (i) == 1073742001 && this.listIsosurface (iShape)) return;
this.setShapeProperty (iShape, "init", Integer.$valueOf (iModel));
var title = null;
var moNumber = (this.getShapeProperty (iShape, "moNumber")).intValue ();
var linearCombination = this.getShapeProperty (iShape, "moLinearCombination");
if (isInitOnly) return;
if (moNumber == 0) moNumber = 2147483647;
var propertyName = null;
var propertyValue = null;
switch (this.getToken (i).tok) {
case 1141899272:
if (iShape == 1073877010) {
this.mo (isInitOnly, 28);
return;
}nboType = this.paramAsStr (++i).toUpperCase ();
break;
case 1074790451:
case 554176565:
propertyName = eval.theToken.value;
propertyValue = this.getCapSlabObject (i, false);
i = eval.iToken;
break;
case 1073741914:
propertyName = "squareLinear";
propertyValue = Boolean.TRUE;
linearCombination =  Clazz.newFloatArray (-1, [1]);
offset = moNumber = 0;
break;
case 2:
moNumber = this.intParameter (i);
linearCombination = this.moCombo (propertyList);
if (linearCombination == null && moNumber < 0) linearCombination =  Clazz.newFloatArray (-1, [-100, -moNumber]);
break;
case 269484192:
switch (this.tokAt (++i)) {
case 1073741973:
case 1073742008:
break;
default:
this.invArg ();
}
isNegOffset = true;
case 1073741973:
case 1073742008:
if ((offset = this.moOffset (i)) == 2147483647) this.invArg ();
moNumber = 0;
linearCombination = this.moCombo (propertyList);
break;
case 1073742037:
moNumber = 1073742037;
linearCombination = this.moCombo (propertyList);
break;
case 1073742108:
moNumber = 1073742108;
linearCombination = this.moCombo (propertyList);
break;
case 1766856708:
this.setColorOptions (null, i + 1, iShape, 2);
break;
case 135266319:
propertyName = "plane";
propertyValue = (this.tokAt (this.e.iToken = ++i) == 1048587 ? null : eval.planeParameter (i));
break;
case 135266320:
this.addShapeProperty (propertyList, "randomSeed", this.tokAt (i + 2) == 2 ? Integer.$valueOf (this.intParameter (i + 2)) : null);
propertyName = "monteCarloCount";
propertyValue = Integer.$valueOf (this.intParameter (i + 1));
break;
case 1073742138:
propertyName = "scale";
propertyValue = Float.$valueOf (this.floatParameter (i + 1));
break;
case 1073741910:
if (this.tokAt (i + 1) == 269484193) {
propertyName = "cutoffPositive";
propertyValue = Float.$valueOf (this.floatParameter (i + 2));
} else {
propertyName = "cutoff";
propertyValue = Float.$valueOf (this.floatParameter (i + 1));
}break;
case 536870916:
propertyName = "debug";
break;
case 1073742054:
propertyName = "plane";
break;
case 1073742104:
case 1073742122:
propertyName = "resolution";
propertyValue = Float.$valueOf (this.floatParameter (i + 1));
break;
case 1073742156:
propertyName = "squareData";
propertyValue = Boolean.TRUE;
break;
case 1073742168:
if (i + 1 < this.slen && this.tokAt (i + 1) == 4) {
propertyName = "titleFormat";
propertyValue = this.paramAsStr (i + 1);
}break;
case 1073741824:
this.invArg ();
break;
default:
if (eval.isArrayParameter (i)) {
linearCombination = eval.floatParameterSet (i, 1, 2147483647);
if (this.tokAt (eval.iToken + 1) == 1073742156) {
this.addShapeProperty (propertyList, "squareLinear", Boolean.TRUE);
eval.iToken++;
}break;
}var ipt = eval.iToken;
if (!eval.setMeshDisplayProperty (iShape, 0, eval.theTok)) this.invArg ();
this.setShapeProperty (iShape, "setProperties", propertyList);
eval.setMeshDisplayProperty (iShape, ipt, this.tokAt (ipt));
return;
}
if (propertyName != null) this.addShapeProperty (propertyList, propertyName, propertyValue);
var haveMO = (moNumber != 2147483647 || linearCombination != null);
if (this.chk) return;
if (nboType != null || haveMO) {
if (haveMO && this.tokAt (eval.iToken + 1) == 4) title = this.paramAsStr (++eval.iToken);
eval.setCursorWait (true);
this.setMoData (propertyList, moNumber, linearCombination, offset, isNegOffset, iModel, title, nboType);
if (haveMO) this.addShapeProperty (propertyList, "finalize", null);
}if (propertyList.size () > 0) this.setShapeProperty (iShape, "setProperties", propertyList);
propertyList.clear ();
}
}, "~B,~N");
Clazz.defineMethod (c$, "setNBOType", 
 function (moData, type) {
var ext = ";AO;  ;PNAO;;NAO; ;PNHO;;NHO; ;PNBO;;NBO; ;PNLMO;NLMO;;MO;  ;NO;".indexOf (";" + type + ";");
if (ext < 0) this.invArg ();
ext = Clazz.doubleToInt (ext / 6) + 31;
var nboLabels = moData.get ("nboLabels");
if (nboLabels == null) this.error (27);
if (this.chk) return;
try {
var orbitals = moData.get (type + "_coefs");
if (orbitals == null) {
var fileName = moData.get ("nboRoot") + "." + ext;
var data = this.vwr.getFileAsString3 (fileName, true, null);
if (data == null) this.error (27);
orbitals = moData.get ("mos");
var dfCoefMaps = orbitals.get (0).get ("dfCoefMaps");
var n = orbitals.size ();
orbitals =  new JU.Lst ();
for (var i = n; --i >= 0; ) {
var mo =  new java.util.Hashtable ();
orbitals.addLast (mo);
mo.put ("dfCoefMaps", dfCoefMaps);
}
(J.api.Interface.getInterface ("J.quantum.QS", this.vwr, "script")).setNboLabels (nboLabels, n, orbitals, 0, type);
data = data.substring (data.lastIndexOf ("--") + 2);
var len = data.length;
var next =  Clazz.newIntArray (1, 0);
for (var i = 0; i < n; i++) {
var mo = orbitals.get (i);
var coefs =  Clazz.newFloatArray (n, 0);
mo.put ("coefficients", coefs);
for (var j = 0; j < n; j++) coefs[j] = JU.PT.parseFloatChecked (data, len, next, false);

}
if (type.equals ("NBO")) {
var occupancies =  Clazz.newFloatArray (n, 0);
for (var j = 0; j < n; j++) occupancies[j] = JU.PT.parseFloatChecked (data, len, next, false);

for (var i = 0; i < n; i++) {
var mo = orbitals.get (i);
mo.put ("occupancy", Float.$valueOf (occupancies[i]));
}
}moData.put (type + "_coefs", orbitals);
}moData.put ("nboType", type);
moData.put ("mos", orbitals);
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
this.error (27);
} else {
throw e;
}
}
}, "java.util.Map,~S");
Clazz.defineMethod (c$, "moCombo", 
 function (propertyList) {
if (this.tokAt (this.e.iToken + 1) != 1073742156) return null;
this.addShapeProperty (propertyList, "squareLinear", Boolean.TRUE);
this.e.iToken++;
return  Clazz.newFloatArray (0, 0);
}, "JU.Lst");
Clazz.defineMethod (c$, "moOffset", 
 function (index) {
var isHomo = (this.getToken (index).tok == 1073741973);
var offset = (isHomo ? 0 : 1);
var tok = this.tokAt (++index);
if (tok == 2 && this.intParameter (index) < 0) offset += this.intParameter (index);
 else if (tok == 269484193) offset += this.intParameter (++index);
 else if (tok == 269484192) offset -= this.intParameter (++index);
return offset;
}, "~N");
Clazz.defineMethod (c$, "setMoData", 
 function (propertyList, moNumber, lc, offset, isNegOffset, modelIndex, title, nboType) {
var eval = this.e;
if (modelIndex < 0) {
modelIndex = this.vwr.am.cmi;
if (modelIndex < 0) eval.errorStr (30, "MO isosurfaces");
}var moData = this.vwr.ms.getInfo (modelIndex, "moData");
if (moData == null) this.error (27);
this.vwr.checkMenuUpdate ();
if (nboType != null) {
this.setNBOType (moData, nboType);
if (lc == null && moNumber == 2147483647) return;
}var mos = null;
var mo;
var f;
var nOrb = 0;
if (lc == null || lc.length < 2) {
if (lc != null && lc.length == 1) offset = 0;
var lastMoNumber = (moData.containsKey ("lastMoNumber") ? (moData.get ("lastMoNumber")).intValue () : 0);
var lastMoCount = (moData.containsKey ("lastMoCount") ? (moData.get ("lastMoCount")).intValue () : 1);
if (moNumber == 1073742108) moNumber = lastMoNumber - 1;
 else if (moNumber == 1073742037) moNumber = lastMoNumber + lastMoCount;
mos = (moData.get ("mos"));
nOrb = (mos == null ? 0 : mos.size ());
if (nOrb == 0) this.error (25);
if (nOrb == 1 && moNumber > 1) this.error (29);
if (offset != 2147483647) {
if (moData.containsKey ("HOMO")) {
moNumber = (moData.get ("HOMO")).intValue () + offset;
} else {
moNumber = -1;
for (var i = 0; i < nOrb; i++) {
mo = mos.get (i);
if ((f = mo.get ("occupancy")) != null) {
if (f.floatValue () < 0.5) {
moNumber = i;
break;
}continue;
} else if ((f = mo.get ("energy")) != null) {
if (f.floatValue () > 0) {
moNumber = i;
break;
}continue;
}break;
}
if (moNumber < 0) this.error (28);
moNumber += offset;
}JU.Logger.info ("MO " + moNumber);
}if (moNumber < 1 || moNumber > nOrb) eval.errorStr (26, "" + nOrb);
}moNumber = Math.abs (moNumber);
moData.put ("lastMoNumber", Integer.$valueOf (moNumber));
moData.put ("lastMoCount", Integer.$valueOf (1));
if (isNegOffset && lc == null) lc =  Clazz.newFloatArray (-1, [-100, moNumber]);
if (lc != null && lc.length < 2) {
mo = mos.get (moNumber - 1);
if ((f = mo.get ("energy")) == null) {
lc =  Clazz.newFloatArray (-1, [100, moNumber]);
} else {
var energy = f.floatValue ();
var bs = JU.BS.newN (nOrb);
var n = 0;
var isAllElectrons = (lc.length == 1 && lc[0] == 1);
for (var i = 0; i < nOrb; i++) {
if ((f = mos.get (i).get ("energy")) == null) continue;
var e = f.floatValue ();
if (isAllElectrons ? e <= energy : e == energy) {
bs.set (i + 1);
n += 2;
}}
lc =  Clazz.newFloatArray (n, 0);
for (var i = 0, pt = 0; i < n; i += 2) {
lc[i] = 1;
lc[i + 1] = (pt = bs.nextSetBit (pt + 1));
}
moData.put ("lastMoNumber", Integer.$valueOf (bs.nextSetBit (0)));
moData.put ("lastMoCount", Integer.$valueOf (Clazz.doubleToInt (n / 2)));
}this.addShapeProperty (propertyList, "squareLinear", Boolean.TRUE);
}this.addShapeProperty (propertyList, "moData", moData);
if (title != null) this.addShapeProperty (propertyList, "title", title);
this.addShapeProperty (propertyList, "molecularOrbital", lc != null ? lc : Integer.$valueOf (Math.abs (moNumber)));
this.addShapeProperty (propertyList, "clear", null);
}, "JU.Lst,~N,~A,~N,~B,~N,~S,~S");
Clazz.defineMethod (c$, "isosurface", 
 function (iShape) {
var eval = this.e;
eval.sm.loadShape (iShape);
if (this.tokAt (1) == 1073742001 && this.listIsosurface (iShape)) return;
var iptDisplayProperty = 0;
var isIsosurface = (iShape == 24);
var isPmesh = (iShape == 29);
var isPlot3d = (iShape == 30);
var isLcaoCartoon = (iShape == 26);
var surfaceObjectSeen = false;
var planeSeen = false;
var isMapped = false;
var isBicolor = false;
var isPhased = false;
var doCalcArea = false;
var doCalcVolume = false;
var isCavity = false;
var haveRadius = false;
var toCache = false;
var isFxy = false;
var haveSlab = false;
var haveIntersection = false;
var isFrontOnly = false;
var data = null;
var cmd = null;
var thisSetNumber = -2147483648;
var nFiles = 0;
var nX;
var nY;
var nZ;
var ptX;
var ptY;
var sigma = NaN;
var cutoff = NaN;
var ptWithin = 0;
var smoothing = null;
var smoothingPower = 2147483647;
var bs = null;
var bsSelect = null;
var bsIgnore = null;
var sbCommand =  new JU.SB ();
var pt;
var plane = null;
var lattice = null;
var fixLattice = false;
var pts;
var color = 0;
var str = null;
var modelIndex = (this.chk ? 0 : -2147483648);
eval.setCursorWait (true);
var idSeen = (this.initIsosurface (iShape) != null);
var isWild = (idSeen && this.getShapeProperty (iShape, "ID") == null);
var isColorSchemeTranslucent = false;
var isInline = false;
var onlyOneModel = null;
var translucency = null;
var colorScheme = null;
var mepOrMlp = null;
var symops = null;
var discreteColixes = null;
var propertyList =  new JU.Lst ();
var defaultMesh = false;
if (isPmesh || isPlot3d) this.addShapeProperty (propertyList, "fileType", "Pmesh");
for (var i = eval.iToken; i < this.slen; ++i) {
var propertyName = null;
var propertyValue = null;
this.getToken (i);
if (eval.theTok == 1073741824) str = this.paramAsStr (i);
switch (eval.theTok) {
case 603979870:
smoothing = (this.getToken (++i).tok == 1048589 ? Boolean.TRUE : eval.theTok == 1048588 ? Boolean.FALSE : null);
if (smoothing == null) this.invArg ();
continue;
case 553648149:
smoothingPower = this.intParameter (++i);
continue;
case 4128:
propertyName = "moveIsosurface";
if (this.tokAt (++i) != 12) this.invArg ();
propertyValue = this.getToken (i++).value;
break;
case 1297090050:
var ff = this.floatArraySet (i + 2, this.intParameter (i + 1), 16);
symops =  new Array (ff.length);
for (var j = symops.length; --j >= 0; ) symops[j] = JU.M4.newA16 (ff[j]);

i = eval.iToken;
break;
case 1089470478:
if (modelIndex < 0) modelIndex = Math.min (this.vwr.am.cmi, 0);
var needIgnore = (bsIgnore == null);
if (bsSelect == null) bsSelect = JU.BSUtil.copy (this.vwr.bsA ());
bsSelect.and (this.vwr.ms.getAtoms (1297090050, Integer.$valueOf (1)));
if (!needIgnore) bsSelect.andNot (bsIgnore);
this.addShapeProperty (propertyList, "select", bsSelect);
if (needIgnore) {
bsIgnore = JU.BSUtil.copy (bsSelect);
JU.BSUtil.invertInPlace (bsIgnore, this.vwr.ms.ac);
isFrontOnly = true;
this.addShapeProperty (propertyList, "ignore", bsIgnore);
sbCommand.append (" ignore ").append (JU.Escape.eBS (bsIgnore));
}sbCommand.append (" symmetry");
if (color == 0) this.addShapeProperty (propertyList, "colorRGB", Integer.$valueOf (1297090050));
symops = this.vwr.ms.getSymMatrices (modelIndex);
break;
case 1073742066:
propertyName = "offset";
propertyValue = this.centerParameter (++i);
i = eval.iToken;
break;
case 528432:
propertyName = "rotate";
propertyValue = (this.tokAt (eval.iToken = ++i) == 1048587 ? null : eval.getPoint4f (i));
i = eval.iToken;
break;
case 1610612740:
propertyName = "scale3d";
propertyValue = Float.$valueOf (this.floatParameter (++i));
break;
case 1073742090:
sbCommand.append (" periodic");
propertyName = "periodic";
break;
case 1073742078:
case 266298:
case 135266320:
propertyName = eval.theToken.value.toString ();
sbCommand.append (" ").appendO (eval.theToken.value);
propertyValue = this.centerParameter (++i);
sbCommand.append (" ").append (JU.Escape.eP (propertyValue));
i = eval.iToken;
break;
case 1679429641:
if (eval.fullCommand.indexOf ("# BBOX=") >= 0) {
var bbox = JU.PT.split (JU.PT.getQuotedAttribute (eval.fullCommand, "# BBOX"), ",");
pts =  Clazz.newArray (-1, [JU.Escape.uP (bbox[0]), JU.Escape.uP (bbox[1])]);
} else if (eval.isCenterParameter (i + 1)) {
pts =  Clazz.newArray (-1, [this.getPoint3f (i + 1, true), this.getPoint3f (eval.iToken + 1, true)]);
i = eval.iToken;
} else {
pts = this.vwr.ms.getBBoxVertices ();
}sbCommand.append (" boundBox " + JU.Escape.eP (pts[0]) + " " + JU.Escape.eP (pts[pts.length - 1]));
propertyName = "boundingBox";
propertyValue = pts;
break;
case 135188:
isPmesh = true;
sbCommand.append (" pmesh");
propertyName = "fileType";
propertyValue = "Pmesh";
break;
case 135267842:
bsSelect = this.atomExpressionAt (++i);
if (this.chk) {
bs =  new JU.BS ();
} else if (this.tokAt (eval.iToken + 1) == 1048577 || this.tokAt (eval.iToken + 1) == 10) {
bs = this.atomExpressionAt (++eval.iToken);
bs.and (this.vwr.ms.getAtomsWithinRadius (5.0, bsSelect, false, null));
} else {
bs = this.vwr.ms.getAtomsWithinRadius (5.0, bsSelect, true, null);
bs.andNot (this.vwr.ms.getAtoms (1095761936, bsSelect));
}bs.andNot (bsSelect);
sbCommand.append (" intersection ").append (JU.Escape.eBS (bsSelect)).append (" ").append (JU.Escape.eBS (bs));
i = eval.iToken;
if (this.tokAt (i + 1) == 135368713) {
i++;
var f = this.getToken (++i).value;
sbCommand.append (" function ").append (JU.PT.esc (f));
if (!this.chk) this.addShapeProperty (propertyList, "func", (f.equals ("a+b") || f.equals ("a-b") ? f : this.createFunction ("__iso__", "a,b", f)));
} else {
haveIntersection = true;
}propertyName = "intersection";
propertyValue =  Clazz.newArray (-1, [bsSelect, bs]);
break;
case 1610625028:
case 135266325:
var isDisplay = (eval.theTok == 1610625028);
if (isDisplay) {
sbCommand.append (" display");
iptDisplayProperty = i;
var tok = this.tokAt (i + 1);
if (tok == 0) continue;
i++;
this.addShapeProperty (propertyList, "token", Integer.$valueOf (1048589));
if (tok == 10 || tok == 1048579) {
propertyName = "bsDisplay";
if (tok == 1048579) {
sbCommand.append (" all");
} else {
propertyValue = this.st[i].value;
sbCommand.append (" ").append (JU.Escape.eBS (propertyValue));
}eval.checkLast (i);
break;
} else if (tok != 135266325) {
eval.iToken = i;
this.invArg ();
}} else {
ptWithin = i;
}var distance;
var ptc = null;
bs = null;
var havePt = false;
if (this.tokAt (i + 1) == 1048577) {
distance = this.floatParameter (i + 3);
if (eval.isPoint3f (i + 4)) {
ptc = this.centerParameter (i + 4);
havePt = true;
eval.iToken = eval.iToken + 2;
} else if (eval.isPoint3f (i + 5)) {
ptc = this.centerParameter (i + 5);
havePt = true;
eval.iToken = eval.iToken + 2;
} else {
bs = eval.atomExpression (this.st, i + 5, this.slen, true, false, false, true);
if (bs == null) this.invArg ();
}} else {
distance = this.floatParameter (++i);
ptc = this.centerParameter (++i);
}if (isDisplay) eval.checkLast (eval.iToken);
i = eval.iToken;
if (eval.fullCommand.indexOf ("# WITHIN=") >= 0) bs = JU.BS.unescape (JU.PT.getQuotedAttribute (eval.fullCommand, "# WITHIN"));
 else if (!havePt) bs = (Clazz.instanceOf (eval.expressionResult, JU.BS) ? eval.expressionResult : null);
if (!this.chk) {
if (bs != null && modelIndex >= 0) {
bs.and (this.vwr.getModelUndeletedAtomsBitSet (modelIndex));
}if (ptc == null) ptc = (bs == null ?  new JU.P3 () : this.vwr.ms.getAtomSetCenter (bs));
this.getWithinDistanceVector (propertyList, distance, ptc, bs, isDisplay);
sbCommand.append (" within ").appendF (distance).append (" ").append (bs == null ? JU.Escape.eP (ptc) : JU.Escape.eBS (bs));
}continue;
case 1073742083:
propertyName = "parameters";
var fparams = eval.floatParameterSet (++i, 1, 10);
i = eval.iToken;
propertyValue = fparams;
sbCommand.append (" parameters ").append (JU.Escape.eAF (fparams));
break;
case 1716520985:
case 1073742190:
onlyOneModel = eval.theToken.value;
var isVariable = (eval.theTok == 1073742190);
var tokProperty = this.tokAt (i + 1);
if (mepOrMlp == null) {
if (!surfaceObjectSeen && !isMapped && !planeSeen) {
this.addShapeProperty (propertyList, "sasurface", Float.$valueOf (0));
sbCommand.append (" vdw");
surfaceObjectSeen = true;
}propertyName = "property";
if (smoothing == null) {
var allowSmoothing = JS.T.tokAttr (tokProperty, 1112539136);
smoothing = (allowSmoothing && this.vwr.getIsosurfacePropertySmoothing (false) == 1 ? Boolean.TRUE : Boolean.FALSE);
}this.addShapeProperty (propertyList, "propertySmoothing", smoothing);
sbCommand.append (" isosurfacePropertySmoothing " + smoothing);
if (smoothing === Boolean.TRUE) {
if (smoothingPower == 2147483647) smoothingPower = this.vwr.getIsosurfacePropertySmoothing (true);
this.addShapeProperty (propertyList, "propertySmoothingPower", Integer.$valueOf (smoothingPower));
sbCommand.append (" isosurfacePropertySmoothingPower " + smoothingPower);
}if (this.vwr.g.rangeSelected) this.addShapeProperty (propertyList, "rangeSelected", Boolean.TRUE);
} else {
propertyName = mepOrMlp;
}str = this.paramAsStr (i);
sbCommand.append (" ").append (str);
if (str.toLowerCase ().indexOf ("property_") == 0) {
data =  Clazz.newFloatArray (this.vwr.ms.ac, 0);
if (this.chk) continue;
data = this.vwr.getDataFloat (str);
if (data == null) this.invArg ();
this.addShapeProperty (propertyList, propertyName, data);
continue;
}var ac = this.vwr.ms.ac;
data =  Clazz.newFloatArray (ac, 0);
if (isVariable) {
var vname = this.paramAsStr (++i);
if (vname.length == 0) {
data = eval.floatParameterSet (i, ac, ac);
} else {
data =  Clazz.newFloatArray (ac, 0);
if (!this.chk) JU.Parser.parseStringInfestedFloatArray ("" + eval.getParameter (vname, 4, true), null, data);
}if (!this.chk) sbCommand.append (" \"\" ").append (JU.Escape.eAF (data));
} else {
this.getToken (++i);
if (!this.chk) {
sbCommand.append (" " + eval.theToken.value);
var atoms = this.vwr.ms.at;
this.vwr.autoCalculate (tokProperty);
if (tokProperty != 1766856708) {
pt =  new JU.P3 ();
for (var iAtom = ac; --iAtom >= 0; ) data[iAtom] = atoms[iAtom].atomPropertyFloat (this.vwr, tokProperty, pt);

}}if (tokProperty == 1766856708) colorScheme = "inherit";
if (this.tokAt (i + 1) == 135266325) {
var d = this.floatParameter (i = i + 2);
sbCommand.append (" within " + d);
this.addShapeProperty (propertyList, "propertyDistanceMax", Float.$valueOf (d));
}}propertyValue = data;
break;
case 1095761935:
case 1095766030:
if (surfaceObjectSeen) this.invArg ();
modelIndex = (eval.theTok == 1095761935 ? this.intParameter (++i) : eval.modelNumberParameter (++i));
sbCommand.append (" modelIndex " + modelIndex);
if (modelIndex < 0) {
propertyName = "fixed";
propertyValue = Boolean.TRUE;
break;
}propertyName = "modelIndex";
propertyValue = Integer.$valueOf (modelIndex);
break;
case 135280133:
propertyName = "select";
var bs1 = this.atomExpressionAt (++i);
propertyValue = bs1;
i = eval.iToken;
var isOnly = (this.tokAt (i + 1) == 1073742072);
if (isOnly) {
i++;
bsIgnore = JU.BSUtil.copy (bs1);
JU.BSUtil.invertInPlace (bsIgnore, this.vwr.ms.ac);
this.addShapeProperty (propertyList, "ignore", bsIgnore);
sbCommand.append (" ignore ").append (JU.Escape.eBS (bsIgnore));
isFrontOnly = true;
}if (surfaceObjectSeen || isMapped) {
sbCommand.append (" select " + JU.Escape.eBS (bs1));
} else {
bsSelect = propertyValue;
if (modelIndex < 0 && bsSelect.nextSetBit (0) >= 0) modelIndex = this.vwr.ms.at[bsSelect.nextSetBit (0)].mi;
}break;
case 1085443:
thisSetNumber = this.intParameter (++i);
break;
case 12289:
propertyName = "center";
propertyValue = this.centerParameter (++i);
sbCommand.append (" center " + JU.Escape.eP (propertyValue));
i = eval.iToken;
break;
case 1073742147:
case 1766856708:
idSeen = true;
var isSign = (eval.theTok == 1073742147);
if (isSign) {
sbCommand.append (" sign");
this.addShapeProperty (propertyList, "sign", Boolean.TRUE);
} else {
if (this.tokAt (i + 1) == 1073741914) {
i++;
propertyName = "colorDensity";
sbCommand.append (" color density");
if (this.isFloatParameter (i + 1)) {
var ptSize = this.floatParameter (++i);
sbCommand.append (" " + ptSize);
propertyValue = Float.$valueOf (ptSize);
}break;
}if (this.getToken (i + 1).tok == 4) {
colorScheme = this.paramAsStr (++i);
if (colorScheme.indexOf (" ") > 0) {
discreteColixes = JU.C.getColixArray (colorScheme);
if (discreteColixes == null) this.error (4);
}} else if (eval.theTok == 1073742018) {
i++;
sbCommand.append (" color mesh");
color = eval.getArgbParam (++i);
this.addShapeProperty (propertyList, "meshcolor", Integer.$valueOf (color));
sbCommand.append (" ").append (JU.Escape.escapeColor (color));
i = eval.iToken;
continue;
}if ((eval.theTok = this.tokAt (i + 1)) == 603979967 || eval.theTok == 1073742074) {
sbCommand.append (" color");
translucency = this.setColorOptions (sbCommand, i + 1, 24, -2);
i = eval.iToken;
continue;
}switch (this.tokAt (i + 1)) {
case 1073741826:
case 1073742114:
this.getToken (++i);
sbCommand.append (" color range");
this.addShapeProperty (propertyList, "rangeAll", null);
if (this.tokAt (i + 1) == 1048579) {
i++;
sbCommand.append (" all");
continue;
}var min = this.floatParameter (++i);
var max = this.floatParameter (++i);
this.addShapeProperty (propertyList, "red", Float.$valueOf (min));
this.addShapeProperty (propertyList, "blue", Float.$valueOf (max));
sbCommand.append (" ").appendF (min).append (" ").appendF (max);
continue;
}
if (eval.isColorParam (i + 1)) {
color = eval.getArgbParam (i + 1);
if (this.tokAt (i + 2) == 1074790746) {
colorScheme = eval.getColorRange (i + 1);
i = eval.iToken;
break;
}}sbCommand.append (" color");
}if (eval.isColorParam (i + 1)) {
color = eval.getArgbParam (++i);
sbCommand.append (" ").append (JU.Escape.escapeColor (color));
i = eval.iToken;
this.addShapeProperty (propertyList, "colorRGB", Integer.$valueOf (color));
idSeen = true;
if (eval.isColorParam (i + 1)) {
color = eval.getArgbParam (++i);
i = eval.iToken;
this.addShapeProperty (propertyList, "colorRGB", Integer.$valueOf (color));
sbCommand.append (" ").append (JU.Escape.escapeColor (color));
isBicolor = true;
} else if (isSign) {
this.invPO ();
}} else if (!isSign && discreteColixes == null) {
this.invPO ();
}continue;
case 135270423:
if (!isIsosurface) this.invArg ();
toCache = !this.chk;
continue;
case 1229984263:
if (this.tokAt (i + 1) != 4) this.invPO ();
continue;
case 1112541194:
case 1649412120:
sbCommand.append (" ").appendO (eval.theToken.value);
var rd = eval.encodeRadiusParameter (i, false, true);
if (rd == null) return;
sbCommand.append (" ").appendO (rd);
if (Float.isNaN (rd.value)) rd.value = 100;
propertyValue = rd;
propertyName = "radius";
haveRadius = true;
if (isMapped) surfaceObjectSeen = false;
i = eval.iToken;
break;
case 135266319:
planeSeen = true;
propertyName = "plane";
propertyValue = eval.planeParameter (i);
i = eval.iToken;
sbCommand.append (" plane ").append (JU.Escape.eP4 (propertyValue));
break;
case 1073742138:
propertyName = "scale";
propertyValue = Float.$valueOf (this.floatParameter (++i));
sbCommand.append (" scale ").appendO (propertyValue);
break;
case 1048579:
if (idSeen) this.invArg ();
propertyName = "thisID";
break;
case 1113198596:
surfaceObjectSeen = true;
++i;
propertyValue = eval.getPoint4f (i);
propertyName = "ellipsoid";
i = eval.iToken;
sbCommand.append (" ellipsoid ").append (JU.Escape.eP4 (propertyValue));
break;
case 135267841:
planeSeen = true;
propertyName = "plane";
propertyValue = eval.hklParameter (++i);
i = eval.iToken;
sbCommand.append (" plane ").append (JU.Escape.eP4 (propertyValue));
break;
case 135182:
surfaceObjectSeen = true;
var lcaoType = this.paramAsStr (++i);
this.addShapeProperty (propertyList, "lcaoType", lcaoType);
sbCommand.append (" lcaocartoon ").append (JU.PT.esc (lcaoType));
switch (this.getToken (++i).tok) {
case 10:
case 1048577:
propertyName = "lcaoCartoon";
bs = this.atomExpressionAt (i);
i = eval.iToken;
if (this.chk) continue;
var atomIndex = bs.nextSetBit (0);
if (atomIndex < 0) this.error (14);
sbCommand.append (" ({").appendI (atomIndex).append ("})");
modelIndex = this.vwr.ms.at[atomIndex].mi;
this.addShapeProperty (propertyList, "modelIndex", Integer.$valueOf (modelIndex));
var axes =  Clazz.newArray (-1, [ new JU.V3 (),  new JU.V3 (), JU.V3.newV (this.vwr.ms.at[atomIndex]),  new JU.V3 ()]);
if (!lcaoType.equalsIgnoreCase ("s") && this.vwr.getHybridizationAndAxes (atomIndex, axes[0], axes[1], lcaoType) == null) return;
propertyValue = axes;
break;
default:
this.error (14);
}
break;
case 1073877010:
var moNumber = 2147483647;
var offset = 2147483647;
var isNegOffset = (this.tokAt (i + 1) == 269484192);
if (isNegOffset) i++;
var linearCombination = null;
switch (this.tokAt (++i)) {
case 0:
eval.bad ();
break;
case 1073741914:
sbCommand.append ("mo [1] squared ");
this.addShapeProperty (propertyList, "squareLinear", Boolean.TRUE);
linearCombination =  Clazz.newFloatArray (-1, [1]);
offset = moNumber = 0;
i++;
break;
case 1073741973:
case 1073742008:
offset = this.moOffset (i);
moNumber = 0;
i = eval.iToken;
sbCommand.append (" mo " + (isNegOffset ? "-" : "") + "HOMO ");
if (offset > 0) sbCommand.append ("+");
if (offset != 0) sbCommand.appendI (offset);
break;
case 2:
moNumber = this.intParameter (i);
sbCommand.append (" mo ").appendI (moNumber);
break;
default:
if (eval.isArrayParameter (i)) {
linearCombination = eval.floatParameterSet (i, 1, 2147483647);
i = eval.iToken;
}}
var squared = (this.tokAt (i + 1) == 1073742156);
if (squared) {
this.addShapeProperty (propertyList, "squareLinear", Boolean.TRUE);
sbCommand.append (" squared");
if (linearCombination == null) linearCombination =  Clazz.newFloatArray (0, 0);
} else if (this.tokAt (i + 1) == 135266320) {
++i;
var monteCarloCount = this.intParameter (++i);
var seed = (this.tokAt (i + 1) == 2 ? this.intParameter (++i) : (-System.currentTimeMillis ()) % 10000);
this.addShapeProperty (propertyList, "monteCarloCount", Integer.$valueOf (monteCarloCount));
this.addShapeProperty (propertyList, "randomSeed", Integer.$valueOf (seed));
sbCommand.append (" points ").appendI (monteCarloCount).appendC (' ').appendI (seed);
}this.setMoData (propertyList, moNumber, linearCombination, offset, isNegOffset, modelIndex, null, null);
surfaceObjectSeen = true;
continue;
case 1073742036:
propertyName = "nci";
sbCommand.append (" " + propertyName);
var tok = this.tokAt (i + 1);
var isPromolecular = (tok != 1229984263 && tok != 4 && tok != 1073742033);
propertyValue = Boolean.$valueOf (isPromolecular);
if (isPromolecular) surfaceObjectSeen = true;
break;
case 1073742016:
case 1073742022:
var isMep = (eval.theTok == 1073742016);
propertyName = (isMep ? "mep" : "mlp");
sbCommand.append (" " + propertyName);
var fname = null;
var calcType = -1;
surfaceObjectSeen = true;
if (this.tokAt (i + 1) == 2) {
calcType = this.intParameter (++i);
sbCommand.append (" " + calcType);
this.addShapeProperty (propertyList, "mepCalcType", Integer.$valueOf (calcType));
}if (this.tokAt (i + 1) == 4) {
fname = this.stringParameter (++i);
sbCommand.append (" /*file*/" + JU.PT.esc (fname));
} else if (this.tokAt (i + 1) == 1716520985) {
mepOrMlp = propertyName;
continue;
}if (!this.chk) try {
data = (fname == null && isMep ? this.vwr.getPartialCharges () : this.getAtomicPotentials (bsSelect, bsIgnore, fname));
} catch (ex) {
if (Clazz.exceptionOf (ex, Exception)) {
} else {
throw ex;
}
}
if (!this.chk && data == null) this.error (32);
propertyValue = data;
break;
case 1313866249:
doCalcVolume = !this.chk;
sbCommand.append (" volume");
break;
case 1074790550:
this.setShapeId (iShape, ++i, idSeen);
isWild = (this.getShapeProperty (iShape, "ID") == null);
i = eval.iToken;
break;
case 1073741888:
if (this.tokAt (i + 1) == 603979967) {
isColorSchemeTranslucent = true;
i++;
}colorScheme = this.paramAsStr (++i).toLowerCase ();
if (colorScheme.equals ("sets")) {
sbCommand.append (" colorScheme \"sets\"");
} else if (eval.isColorParam (i)) {
colorScheme = eval.getColorRange (i);
i = eval.iToken;
}break;
case 1073741828:
propertyName = "addHydrogens";
propertyValue = Boolean.TRUE;
sbCommand.append (" mp.addHydrogens");
break;
case 1073741836:
propertyName = "angstroms";
sbCommand.append (" angstroms");
break;
case 1073741837:
propertyName = "anisotropy";
propertyValue = this.getPoint3f (++i, false);
sbCommand.append (" anisotropy").append (JU.Escape.eP (propertyValue));
i = eval.iToken;
break;
case 1073741842:
doCalcArea = !this.chk;
sbCommand.append (" area");
break;
case 1073741850:
case 1073742076:
surfaceObjectSeen = true;
if (isBicolor && !isPhased) {
sbCommand.append (" phase \"_orb\"");
this.addShapeProperty (propertyList, "phase", "_orb");
}var nlmZprs =  Clazz.newFloatArray (7, 0);
nlmZprs[0] = this.intParameter (++i);
nlmZprs[1] = this.intParameter (++i);
nlmZprs[2] = this.intParameter (++i);
nlmZprs[3] = (this.isFloatParameter (i + 1) ? this.floatParameter (++i) : 6);
sbCommand.append (" atomicOrbital ").appendI (Clazz.floatToInt (nlmZprs[0])).append (" ").appendI (Clazz.floatToInt (nlmZprs[1])).append (" ").appendI (Clazz.floatToInt (nlmZprs[2])).append (" ").appendF (nlmZprs[3]);
if (this.tokAt (i + 1) == 135266320) {
i += 2;
nlmZprs[4] = this.intParameter (i);
nlmZprs[5] = (this.tokAt (i + 1) == 3 ? this.floatParameter (++i) : 0);
nlmZprs[6] = (this.tokAt (i + 1) == 2 ? this.intParameter (++i) : (-System.currentTimeMillis ()) % 10000);
sbCommand.append (" points ").appendI (Clazz.floatToInt (nlmZprs[4])).appendC (' ').appendF (nlmZprs[5]).appendC (' ').appendI (Clazz.floatToInt (nlmZprs[6]));
}propertyName = "hydrogenOrbital";
propertyValue = nlmZprs;
break;
case 1073741866:
sbCommand.append (" binary");
continue;
case 1073741868:
sbCommand.append (" blockData");
propertyName = "blockData";
propertyValue = Boolean.TRUE;
break;
case 1074790451:
case 554176565:
haveSlab = true;
propertyName = eval.theToken.value;
propertyValue = this.getCapSlabObject (i, false);
i = eval.iToken;
break;
case 1073741876:
if (!isIsosurface) this.invArg ();
isCavity = true;
var cavityRadius = (this.isFloatParameter (i + 1) ? this.floatParameter (++i) : 1.2);
var envelopeRadius = (this.isFloatParameter (i + 1) ? this.floatParameter (++i) : 10);
if (this.chk) continue;
if (envelopeRadius > 10) {
eval.integerOutOfRange (0, 10);
return;
}sbCommand.append (" cavity ").appendF (cavityRadius).append (" ").appendF (envelopeRadius);
this.addShapeProperty (propertyList, "envelopeRadius", Float.$valueOf (envelopeRadius));
this.addShapeProperty (propertyList, "cavityRadius", Float.$valueOf (cavityRadius));
propertyName = "cavity";
break;
case 1073741896:
case 1073741900:
propertyName = "contour";
sbCommand.append (" contour");
switch (this.tokAt (i + 1)) {
case 1073741920:
propertyValue = eval.floatParameterSet (i + 2, 1, 2147483647);
sbCommand.append (" discrete ").append (JU.Escape.eAF (propertyValue));
i = eval.iToken;
break;
case 1073741981:
pt = this.getPoint3f (i + 2, false);
if (pt.z <= 0 || pt.y < pt.x) this.invArg ();
if (pt.z == Clazz.floatToInt (pt.z) && pt.z > (pt.y - pt.x)) pt.z = (pt.y - pt.x) / pt.z;
propertyValue = pt;
i = eval.iToken;
sbCommand.append (" increment ").append (JU.Escape.eP (pt));
break;
default:
propertyValue = Integer.$valueOf (this.tokAt (i + 1) == 2 ? this.intParameter (++i) : 0);
sbCommand.append (" ").appendO (propertyValue);
if (this.tokAt (i + 1) == 2) {
this.addShapeProperty (propertyList, propertyName, propertyValue);
propertyValue = Integer.$valueOf (-Math.abs (this.intParameter (++i)));
sbCommand.append (" ").appendO (propertyValue);
}}
break;
case 1073741910:
sbCommand.append (" cutoff ");
if (this.tokAt (++i) == 269484193) {
propertyName = "cutoffPositive";
propertyValue = Float.$valueOf (cutoff = this.floatParameter (++i));
sbCommand.append ("+").appendO (propertyValue);
} else if (this.isFloatParameter (i)) {
propertyName = "cutoff";
propertyValue = Float.$valueOf (cutoff = this.floatParameter (i));
sbCommand.appendO (propertyValue);
} else {
propertyName = "cutoffRange";
propertyValue = eval.floatParameterSet (i, 2, 2);
this.addShapeProperty (propertyList, "cutoff", Float.$valueOf (0));
sbCommand.append (JU.Escape.eAF (propertyValue));
i = eval.iToken;
}break;
case 1073741928:
propertyName = "downsample";
propertyValue = Integer.$valueOf (this.intParameter (++i));
sbCommand.append (" downsample ").appendO (propertyValue);
break;
case 1073741931:
propertyName = "eccentricity";
propertyValue = eval.getPoint4f (++i);
sbCommand.append (" eccentricity ").append (JU.Escape.eP4 (propertyValue));
i = eval.iToken;
break;
case 1074790508:
sbCommand.append (" ed");
this.setMoData (propertyList, -1, null, 0, false, modelIndex, null, null);
surfaceObjectSeen = true;
continue;
case 536870916:
case 1073742041:
sbCommand.append (" ").appendO (eval.theToken.value);
propertyName = "debug";
propertyValue = (eval.theTok == 536870916 ? Boolean.TRUE : Boolean.FALSE);
break;
case 1060869:
sbCommand.append (" fixed");
propertyName = "fixed";
propertyValue = Boolean.TRUE;
break;
case 1073741962:
sbCommand.append (" fullPlane");
propertyName = "fullPlane";
propertyValue = Boolean.TRUE;
break;
case 1073741966:
case 1073741968:
var isFxyz = (eval.theTok == 1073741968);
propertyName = "" + eval.theToken.value;
var vxy =  new JU.Lst ();
propertyValue = vxy;
isFxy = surfaceObjectSeen = true;
sbCommand.append (" ").append (propertyName);
var name = this.paramAsStr (++i);
if (name.equals ("=")) {
sbCommand.append (" =");
name = this.paramAsStr (++i);
sbCommand.append (" ").append (JU.PT.esc (name));
vxy.addLast (name);
if (!this.chk) this.addShapeProperty (propertyList, "func", this.createFunction ("__iso__", "x,y,z", name));
break;
}var dName = JU.PT.getQuotedAttribute (eval.fullCommand, "# DATA" + (isFxy ? "2" : ""));
if (dName == null) dName = "inline";
 else name = dName;
var isXYZ = (name.indexOf ("data2d_") == 0);
var isXYZV = (name.indexOf ("data3d_") == 0);
isInline = name.equals ("inline");
sbCommand.append (" inline");
vxy.addLast (name);
var pt3 = this.getPoint3f (++i, false);
sbCommand.append (" ").append (JU.Escape.eP (pt3));
vxy.addLast (pt3);
var pt4;
ptX = ++eval.iToken;
vxy.addLast (pt4 = eval.getPoint4f (ptX));
sbCommand.append (" ").append (JU.Escape.eP4 (pt4));
nX = Clazz.floatToInt (pt4.x);
ptY = ++eval.iToken;
vxy.addLast (pt4 = eval.getPoint4f (ptY));
sbCommand.append (" ").append (JU.Escape.eP4 (pt4));
nY = Clazz.floatToInt (pt4.x);
vxy.addLast (pt4 = eval.getPoint4f (++eval.iToken));
sbCommand.append (" ").append (JU.Escape.eP4 (pt4));
nZ = Clazz.floatToInt (pt4.x);
if (nX == 0 || nY == 0 || nZ == 0) this.invArg ();
if (!this.chk) {
var fdata = null;
var xyzdata = null;
if (isFxyz) {
if (isInline) {
nX = Math.abs (nX);
nY = Math.abs (nY);
nZ = Math.abs (nZ);
xyzdata = this.floatArraySetXYZ (++eval.iToken, nX, nY, nZ);
} else if (isXYZV) {
xyzdata = this.vwr.getDataFloat3D (name);
} else {
xyzdata = this.vwr.functionXYZ (name, nX, nY, nZ);
}nX = Math.abs (nX);
nY = Math.abs (nY);
nZ = Math.abs (nZ);
if (xyzdata == null) {
eval.iToken = ptX;
eval.errorStr (53, "xyzdata is null.");
}if (xyzdata.length != nX || xyzdata[0].length != nY || xyzdata[0][0].length != nZ) {
eval.iToken = ptX;
eval.errorStr (53, "xyzdata[" + xyzdata.length + "][" + xyzdata[0].length + "][" + xyzdata[0][0].length + "] is not of size [" + nX + "][" + nY + "][" + nZ + "]");
}vxy.addLast (xyzdata);
sbCommand.append (" ").append (JU.Escape.e (xyzdata));
} else {
if (isInline) {
nX = Math.abs (nX);
nY = Math.abs (nY);
fdata = this.floatArraySet (++eval.iToken, nX, nY);
} else if (isXYZ) {
fdata = this.vwr.getDataFloat2D (name);
nX = (fdata == null ? 0 : fdata.length);
nY = 3;
} else {
fdata = this.vwr.functionXY (name, nX, nY);
nX = Math.abs (nX);
nY = Math.abs (nY);
}if (fdata == null) {
eval.iToken = ptX;
eval.errorStr (53, "fdata is null.");
}if (fdata.length != nX && !isXYZ) {
eval.iToken = ptX;
eval.errorStr (53, "fdata length is not correct: " + fdata.length + " " + nX + ".");
}for (var j = 0; j < nX; j++) {
if (fdata[j] == null) {
eval.iToken = ptY;
eval.errorStr (53, "fdata[" + j + "] is null.");
}if (fdata[j].length != nY) {
eval.iToken = ptY;
eval.errorStr (53, "fdata[" + j + "] is not the right length: " + fdata[j].length + " " + nY + ".");
}}
vxy.addLast (fdata);
sbCommand.append (" ").append (JU.Escape.e (fdata));
}}i = eval.iToken;
break;
case 1073741970:
propertyName = "gridPoints";
sbCommand.append (" gridPoints");
break;
case 1073741976:
propertyName = "ignore";
propertyValue = bsIgnore = this.atomExpressionAt (++i);
sbCommand.append (" ignore ").append (JU.Escape.eBS (bsIgnore));
i = eval.iToken;
break;
case 1073741984:
propertyName = "insideOut";
sbCommand.append (" insideout");
break;
case 1073741988:
case 1073741986:
case 1073742100:
sbCommand.append (" ").appendO (eval.theToken.value);
propertyName = "pocket";
propertyValue = (eval.theTok == 1073742100 ? Boolean.TRUE : Boolean.FALSE);
break;
case 1073742002:
propertyName = "lobe";
propertyValue = eval.getPoint4f (++i);
i = eval.iToken;
sbCommand.append (" lobe ").append (JU.Escape.eP4 (propertyValue));
surfaceObjectSeen = true;
break;
case 1073742004:
case 1073742006:
propertyName = "lp";
propertyValue = eval.getPoint4f (++i);
i = eval.iToken;
sbCommand.append (" lp ").append (JU.Escape.eP4 (propertyValue));
surfaceObjectSeen = true;
break;
case 1052701:
if (isMapped || this.slen == i + 1) this.invArg ();
isMapped = true;
if ((isCavity || haveRadius || haveIntersection) && !surfaceObjectSeen) {
surfaceObjectSeen = true;
this.addShapeProperty (propertyList, "bsSolvent", (haveRadius || haveIntersection ?  new JU.BS () : eval.lookupIdentifierValue ("solvent")));
this.addShapeProperty (propertyList, "sasurface", Float.$valueOf (0));
}if (sbCommand.length () == 0) {
plane = this.getShapeProperty (24, "plane");
if (plane == null) {
if (this.getShapeProperty (24, "contours") != null) {
this.addShapeProperty (propertyList, "nocontour", null);
}} else {
this.addShapeProperty (propertyList, "plane", plane);
sbCommand.append ("plane ").append (JU.Escape.eP4 (plane));
planeSeen = true;
plane = null;
}} else if (!surfaceObjectSeen && !planeSeen) {
this.invArg ();
}sbCommand.append ("; isosurface map");
this.addShapeProperty (propertyList, "map", (surfaceObjectSeen ? Boolean.TRUE : Boolean.FALSE));
break;
case 1073742014:
propertyName = "maxset";
propertyValue = Integer.$valueOf (this.intParameter (++i));
sbCommand.append (" maxSet ").appendO (propertyValue);
break;
case 1073742020:
propertyName = "minset";
propertyValue = Integer.$valueOf (this.intParameter (++i));
sbCommand.append (" minSet ").appendO (propertyValue);
break;
case 1073742112:
surfaceObjectSeen = true;
propertyName = "rad";
propertyValue = eval.getPoint4f (++i);
i = eval.iToken;
sbCommand.append (" radical ").append (JU.Escape.eP4 (propertyValue));
break;
case 1073742027:
propertyName = "fixed";
propertyValue = Boolean.FALSE;
sbCommand.append (" modelBased");
break;
case 1073742028:
case 1073742135:
case 1613758488:
onlyOneModel = eval.theToken.value;
var radius;
if (eval.theTok == 1073742028) {
propertyName = "molecular";
sbCommand.append (" molecular");
radius = (this.isFloatParameter (i + 1) ? this.floatParameter (++i) : 1.4);
} else {
this.addShapeProperty (propertyList, "bsSolvent", eval.lookupIdentifierValue ("solvent"));
propertyName = (eval.theTok == 1073742135 ? "sasurface" : "solvent");
sbCommand.append (" ").appendO (eval.theToken.value);
radius = (this.isFloatParameter (i + 1) ? this.floatParameter (++i) : this.vwr.getFloat (570425394));
}sbCommand.append (" ").appendF (radius);
propertyValue = Float.$valueOf (radius);
if (this.tokAt (i + 1) == 1073741961) {
this.addShapeProperty (propertyList, "doFullMolecular", null);
sbCommand.append (" full");
i++;
}surfaceObjectSeen = true;
break;
case 1073742033:
this.addShapeProperty (propertyList, "fileType", "Mrc");
sbCommand.append (" mrc");
continue;
case 1073742064:
case 1073742062:
this.addShapeProperty (propertyList, "fileType", "Obj");
sbCommand.append (" obj");
continue;
case 1073742034:
this.addShapeProperty (propertyList, "fileType", "Msms");
sbCommand.append (" msms");
continue;
case 1073742094:
if (surfaceObjectSeen) this.invArg ();
propertyName = "phase";
isPhased = true;
propertyValue = (this.tokAt (i + 1) == 4 ? this.stringParameter (++i) : "_orb");
sbCommand.append (" phase ").append (JU.PT.esc (propertyValue));
break;
case 1073742104:
case 1073742122:
propertyName = "resolution";
propertyValue = Float.$valueOf (this.floatParameter (++i));
sbCommand.append (" resolution ").appendO (propertyValue);
break;
case 1073742124:
propertyName = "reverseColor";
propertyValue = Boolean.TRUE;
sbCommand.append (" reversecolor");
break;
case 1073742127:
case 1073742146:
propertyName = "sigma";
propertyValue = Float.$valueOf (sigma = this.floatParameter (++i));
sbCommand.append (" sigma ").appendO (propertyValue);
break;
case 1113198597:
propertyName = "geodesic";
propertyValue = Float.$valueOf (this.floatParameter (++i));
sbCommand.append (" geosurface ").appendO (propertyValue);
surfaceObjectSeen = true;
break;
case 1073742154:
propertyName = "sphere";
propertyValue = Float.$valueOf (this.floatParameter (++i));
sbCommand.append (" sphere ").appendO (propertyValue);
surfaceObjectSeen = true;
break;
case 1073742156:
propertyName = "squareData";
propertyValue = Boolean.TRUE;
sbCommand.append (" squared");
break;
case 1073741983:
propertyName = (!surfaceObjectSeen && !planeSeen && !isMapped ? "readFile" : "mapColor");
str = this.stringParameter (++i);
if (str == null) this.invArg ();
if (isPmesh) str = JU.PT.replaceWithCharacter (str, "{,}|", ' ');
if (eval.debugHigh) JU.Logger.debug ("pmesh inline data:\n" + str);
propertyValue = (this.chk ? null : str);
this.addShapeProperty (propertyList, "fileName", "");
sbCommand.append (" INLINE ").append (JU.PT.esc (str));
surfaceObjectSeen = true;
break;
case 4:
var firstPass = (!surfaceObjectSeen && !planeSeen);
propertyName = (firstPass && !isMapped ? "readFile" : "mapColor");
var filename = this.paramAsStr (i);
if (filename.startsWith ("=") && filename.length > 1) {
var info = this.vwr.setLoadFormat (filename, '_', false);
filename = info[0];
var strCutoff = (!firstPass || !Float.isNaN (cutoff) ? null : info[1]);
var diff = info[2];
if (strCutoff != null && !this.chk) {
cutoff = NaN;
var key = (diff == null ? "MAP_SIGMA_DENS" : "DIFF_SIGMA_DENS");
try {
var sfdat = this.vwr.getFileAsString3 (strCutoff, false, null);
JU.Logger.info (sfdat);
sfdat = JU.PT.split (sfdat, key)[1];
cutoff = JU.PT.parseFloat (sfdat);
} catch (e) {
if (Clazz.exceptionOf (e, Exception)) {
JU.Logger.error (key + " -- could  not read " + strCutoff);
} else {
throw e;
}
}
if (cutoff > 0) {
if (diff != null) {
if (Float.isNaN (sigma)) sigma = 3;
this.addShapeProperty (propertyList, "sign", Boolean.TRUE);
}this.showString ("using cutoff = " + cutoff + (Float.isNaN (sigma) ? "" : " sigma=" + sigma));
if (!Float.isNaN (sigma)) {
cutoff *= sigma;
sigma = NaN;
this.addShapeProperty (propertyList, "sigma", Float.$valueOf (sigma));
}this.addShapeProperty (propertyList, "cutoff", Float.$valueOf (cutoff));
sbCommand.append (" cutoff ").appendF (cutoff);
}}if (ptWithin == 0) {
onlyOneModel = "=xxxx";
if (modelIndex < 0) modelIndex = this.vwr.am.cmi;
bs = this.vwr.getModelUndeletedAtomsBitSet (modelIndex);
if (bs.nextSetBit (0) >= 0) {
this.getWithinDistanceVector (propertyList, 2.0, null, bs, false);
sbCommand.append (" within 2.0 ").append (JU.Escape.eBS (bs));
}}if (firstPass) defaultMesh = true;
}if (firstPass && this.vwr.getP ("_fileType").equals ("Pdb") && Float.isNaN (sigma) && Float.isNaN (cutoff)) {
this.addShapeProperty (propertyList, "sigma", Float.$valueOf (-1));
sbCommand.append (" sigma -1.0");
}if (filename.length == 0) {
if (modelIndex < 0) modelIndex = this.vwr.am.cmi;
filename = eval.getFullPathName ();
propertyValue = this.vwr.ms.getInfo (modelIndex, "jmolSurfaceInfo");
}var fileIndex = -1;
if (propertyValue == null && this.tokAt (i + 1) == 2) this.addShapeProperty (propertyList, "fileIndex", Integer.$valueOf (fileIndex = this.intParameter (++i)));
var stype = (this.tokAt (i + 1) == 4 ? this.stringParameter (++i) : null);
surfaceObjectSeen = true;
if (this.chk) {
break;
}var fullPathNameOrError;
var localName = null;
if (propertyValue == null) {
if (eval.fullCommand.indexOf ("# FILE" + nFiles + "=") >= 0) {
filename = JU.PT.getQuotedAttribute (eval.fullCommand, "# FILE" + nFiles);
if (this.tokAt (i + 1) == 1073741848) i += 2;
} else if (this.tokAt (i + 1) == 1073741848) {
localName = this.vwr.fm.getFilePath (this.stringParameter (eval.iToken = (i = i + 2)), false, false);
fullPathNameOrError = this.vwr.getFullPathNameOrError (localName);
localName = fullPathNameOrError[0];
if (this.vwr.fm.getPathForAllFiles () !== "") {
filename = localName;
localName = null;
} else {
this.addShapeProperty (propertyList, "localName", localName);
}}}if (!filename.startsWith ("cache://") && stype == null) {
fullPathNameOrError = this.vwr.getFullPathNameOrError (filename);
filename = fullPathNameOrError[0];
if (fullPathNameOrError[1] != null) eval.errorStr (17, filename + ":" + fullPathNameOrError[1]);
}this.showString ("reading isosurface data from " + filename);
if (stype != null) {
propertyValue = this.vwr.fm.cacheGet (filename, false);
this.addShapeProperty (propertyList, "calculationType", stype);
}if (propertyValue == null) {
this.addShapeProperty (propertyList, "fileName", filename);
if (localName != null) filename = localName;
if (fileIndex >= 0) sbCommand.append (" ").appendI (fileIndex);
}sbCommand.append (" /*file*/").append (JU.PT.esc (filename));
if (stype != null) sbCommand.append (" ").append (JU.PT.esc (stype));
break;
case 4106:
propertyName = "connections";
switch (this.tokAt (++i)) {
case 10:
case 1048577:
propertyValue =  Clazz.newIntArray (-1, [this.atomExpressionAt (i).nextSetBit (0)]);
break;
default:
propertyValue =  Clazz.newIntArray (-1, [Clazz.floatToInt (eval.floatParameterSet (i, 1, 1)[0])]);
break;
}
i = eval.iToken;
break;
case 1095761923:
propertyName = "atomIndex";
propertyValue = Integer.$valueOf (this.intParameter (++i));
break;
case 1073741999:
propertyName = "link";
sbCommand.append (" link");
break;
case 1614417948:
if (iShape != 24) this.invArg ();
if (this.tokAt (i + 1) == 269484193) i++;
propertyName = "extendGrid";
propertyValue = Float.$valueOf (this.floatParameter (++i));
sbCommand.append (" unitcell " + propertyValue);
break;
case 1073741994:
if (iShape != 24) this.invArg ();
pt = this.getPoint3f (++i, false);
i = eval.iToken;
if (pt.x <= 0 || pt.y <= 0 || pt.z <= 0) break;
pt.x = Clazz.floatToInt (pt.x);
pt.y = Clazz.floatToInt (pt.y);
pt.z = Clazz.floatToInt (pt.z);
sbCommand.append (" lattice ").append (JU.Escape.eP (pt));
if (isMapped) {
propertyName = "mapLattice";
propertyValue = pt;
} else {
lattice = pt;
if (this.tokAt (i + 1) == 1060869) {
sbCommand.append (" fixed");
fixLattice = true;
i++;
}}break;
default:
if (eval.theTok == 1073741824) {
propertyName = "thisID";
propertyValue = str;
}if (!eval.setMeshDisplayProperty (iShape, 0, eval.theTok)) {
if (JS.T.tokAttr (eval.theTok, 1073741824) && !idSeen) {
this.setShapeId (iShape, i, idSeen);
i = eval.iToken;
break;
}this.invArg ();
}if (iptDisplayProperty == 0) iptDisplayProperty = i;
i = this.slen - 1;
break;
}
idSeen = (eval.theTok != 12291);
if (isWild && surfaceObjectSeen) this.invArg ();
if (propertyName != null) this.addShapeProperty (propertyList, propertyName, propertyValue);
}
if (!this.chk) {
if ((isCavity || haveRadius) && !surfaceObjectSeen) {
surfaceObjectSeen = true;
this.addShapeProperty (propertyList, "bsSolvent", (haveRadius ?  new JU.BS () : eval.lookupIdentifierValue ("solvent")));
this.addShapeProperty (propertyList, "sasurface", Float.$valueOf (0));
}if (planeSeen && !surfaceObjectSeen && !isMapped) {
this.addShapeProperty (propertyList, "nomap", Float.$valueOf (0));
surfaceObjectSeen = true;
}if (thisSetNumber >= -1) this.addShapeProperty (propertyList, "getSurfaceSets", Integer.$valueOf (thisSetNumber - 1));
if (discreteColixes != null) {
this.addShapeProperty (propertyList, "colorDiscrete", discreteColixes);
} else if ("sets".equals (colorScheme)) {
this.addShapeProperty (propertyList, "setColorScheme", null);
} else if (colorScheme != null) {
var ce = this.vwr.cm.getColorEncoder (colorScheme);
if (ce != null) {
ce.isTranslucent = isColorSchemeTranslucent;
ce.hi = 3.4028235E38;
this.addShapeProperty (propertyList, "remapColor", ce);
}}if (surfaceObjectSeen && !isLcaoCartoon && sbCommand.indexOf (";") != 0) {
propertyList.add (0,  Clazz.newArray (-1, ["newObject", null]));
var needSelect = (bsSelect == null);
if (needSelect) bsSelect = JU.BSUtil.copy (this.vwr.bsA ());
if (modelIndex < 0) modelIndex = this.vwr.am.cmi;
bsSelect.and (this.vwr.getModelUndeletedAtomsBitSet (modelIndex));
if (onlyOneModel != null) {
var bsModels = this.vwr.ms.getModelBS (bsSelect, false);
if (bsModels.cardinality () > 1) eval.errorStr (30, "ISOSURFACE " + onlyOneModel);
if (needSelect) {
propertyList.add (0,  Clazz.newArray (-1, ["select", bsSelect]));
if (sbCommand.indexOf ("; isosurface map") == 0) {
sbCommand =  new JU.SB ().append ("; isosurface map select ").append (JU.Escape.eBS (bsSelect)).append (sbCommand.substring (16));
}}}}if (haveIntersection && !haveSlab) {
if (!surfaceObjectSeen) this.addShapeProperty (propertyList, "sasurface", Float.$valueOf (0));
if (!isMapped) {
this.addShapeProperty (propertyList, "map", Boolean.TRUE);
this.addShapeProperty (propertyList, "select", bs);
this.addShapeProperty (propertyList, "sasurface", Float.$valueOf (0));
}this.addShapeProperty (propertyList, "slab", this.getCapSlabObject (-100, false));
}var timeMsg = (surfaceObjectSeen && this.vwr.getBoolean (603979934));
if (timeMsg) JU.Logger.startTimer ("isosurface");
this.setShapeProperty (iShape, "setProperties", propertyList);
if (timeMsg) this.showString (JU.Logger.getTimerMsg ("isosurface", 0));
if (defaultMesh) {
this.setShapeProperty (iShape, "token", Integer.$valueOf (1073742018));
this.setShapeProperty (iShape, "token", Integer.$valueOf (1073742046));
isFrontOnly = true;
sbCommand.append (" mesh nofill frontOnly");
}}if (lattice != null) {
this.setShapeProperty (iShape, "lattice", lattice);
if (fixLattice) this.setShapeProperty (iShape, "fixLattice", Boolean.TRUE);
}if (symops != null) this.setShapeProperty (iShape, "symops", symops);
if (isFrontOnly) this.setShapeProperty (iShape, "token", Integer.$valueOf (1073741960));
if (iptDisplayProperty > 0) {
if (!eval.setMeshDisplayProperty (iShape, iptDisplayProperty, 0)) this.invArg ();
}if (this.chk) return;
var area = null;
var volume = null;
if (doCalcArea) {
area = this.getShapeProperty (iShape, "area");
if (Clazz.instanceOf (area, Float)) this.vwr.setFloatProperty ("isosurfaceArea", (area).floatValue ());
 else this.vwr.g.setUserVariable ("isosurfaceArea", JS.SV.getVariableAD (area));
}if (doCalcVolume) {
volume = (doCalcVolume ? this.getShapeProperty (iShape, "volume") : null);
if (Clazz.instanceOf (volume, Float)) this.vwr.setFloatProperty ("isosurfaceVolume", (volume).floatValue ());
 else this.vwr.g.setUserVariable ("isosurfaceVolume", JS.SV.getVariableAD (volume));
}if (!isLcaoCartoon) {
var s = null;
if (isMapped && !surfaceObjectSeen) {
this.setShapeProperty (iShape, "finalize", sbCommand.toString ());
} else if (surfaceObjectSeen) {
cmd = sbCommand.toString ();
this.setShapeProperty (iShape, "finalize", (cmd.indexOf ("; isosurface map") == 0 ? "" : " select " + JU.Escape.eBS (bsSelect) + " ") + cmd);
s = this.getShapeProperty (iShape, "ID");
if (s != null && !eval.tQuiet) {
cutoff = (this.getShapeProperty (iShape, "cutoff")).floatValue ();
if (Float.isNaN (cutoff) && !Float.isNaN (sigma)) JU.Logger.error ("sigma not supported");
s += " created " + this.getShapeProperty (iShape, "message");
}}var sarea;
var svol;
if (doCalcArea || doCalcVolume) {
sarea = (doCalcArea ? "isosurfaceArea = " + (Clazz.instanceOf (area, Float) ? "" + area : JU.Escape.eAD (area)) : null);
svol = (doCalcVolume ? "isosurfaceVolume = " + (Clazz.instanceOf (volume, Float) ? "" + volume : JU.Escape.eAD (volume)) : null);
if (s == null) {
if (doCalcArea) this.showString (sarea);
if (doCalcVolume) this.showString (svol);
} else {
if (doCalcArea) s += "\n" + sarea;
if (doCalcVolume) s += "\n" + svol;
}}if (s != null) this.showString (s);
}if (translucency != null) this.setShapeProperty (iShape, "translucency", translucency);
this.setShapeProperty (iShape, "clear", null);
if (toCache) this.setShapeProperty (iShape, "cache", null);
if (iShape != 26) this.listIsosurface (iShape);
}, "~N");
Clazz.defineMethod (c$, "lcaoCartoon", 
 function () {
var eval = this.e;
eval.sm.loadShape (26);
if (eval.tokAt (1) == 1073742001 && this.listIsosurface (26)) return;
this.setShapeProperty (26, "init", eval.fullCommand);
if (this.slen == 1) {
this.setShapeProperty (26, "lcaoID", null);
return;
}var idSeen = false;
var translucency = null;
for (var i = 1; i < this.slen; i++) {
var propertyName = null;
var propertyValue = null;
switch (this.getToken (i).tok) {
case 1074790451:
case 554176565:
propertyName = eval.theToken.value;
if (this.tokAt (i + 1) == 1048588) eval.iToken = i + 1;
propertyValue = this.getCapSlabObject (i, true);
i = eval.iToken;
break;
case 12289:
this.isosurface (26);
return;
case 528432:
var degx = 0;
var degy = 0;
var degz = 0;
switch (this.getToken (++i).tok) {
case 1112541205:
degx = this.floatParameter (++i) * 0.017453292;
break;
case 1112541206:
degy = this.floatParameter (++i) * 0.017453292;
break;
case 1112541207:
degz = this.floatParameter (++i) * 0.017453292;
break;
default:
this.invArg ();
}
propertyName = "rotationAxis";
propertyValue = JU.V3.new3 (degx, degy, degz);
break;
case 1048589:
case 1610625028:
case 3145768:
propertyName = "on";
break;
case 1048588:
case 12294:
case 3145770:
propertyName = "off";
break;
case 12291:
propertyName = "delete";
break;
case 10:
case 1048577:
propertyName = "select";
propertyValue = this.atomExpressionAt (i);
i = eval.iToken;
break;
case 1766856708:
translucency = this.setColorOptions (null, i + 1, 26, -2);
if (translucency != null) this.setShapeProperty (26, "settranslucency", translucency);
i = eval.iToken;
idSeen = true;
continue;
case 603979967:
case 1073742074:
eval.setMeshDisplayProperty (26, i, eval.theTok);
i = eval.iToken;
idSeen = true;
continue;
case 1113200651:
case 4:
propertyValue = this.paramAsStr (i).toLowerCase ();
if (propertyValue.equals ("spacefill")) propertyValue = "cpk";
propertyName = "create";
if (eval.optParameterAsString (i + 1).equalsIgnoreCase ("molecular")) {
i++;
propertyName = "molecular";
}break;
case 135280133:
if (this.tokAt (i + 1) == 10 || this.tokAt (i + 1) == 1048577) {
propertyName = "select";
propertyValue = this.atomExpressionAt (i + 1);
i = eval.iToken;
} else {
propertyName = "selectType";
propertyValue = this.paramAsStr (++i);
if (propertyValue.equals ("spacefill")) propertyValue = "cpk";
}break;
case 1073742138:
propertyName = "scale";
propertyValue = Float.$valueOf (this.floatParameter (++i));
break;
case 1073742004:
case 1073742006:
propertyName = "lonePair";
break;
case 1073742112:
case 1073742111:
propertyName = "radical";
break;
case 1073742028:
propertyName = "molecular";
break;
case 1073741904:
propertyValue = this.paramAsStr (++i);
propertyName = "create";
if (eval.optParameterAsString (i + 1).equalsIgnoreCase ("molecular")) {
i++;
propertyName = "molecular";
}break;
case 1074790550:
propertyValue = eval.setShapeNameParameter (++i);
i = eval.iToken;
if (idSeen) this.invArg ();
propertyName = "lcaoID";
break;
default:
if (eval.theTok == 269484209 || JS.T.tokAttr (eval.theTok, 1073741824)) {
if (eval.theTok != 269484209) propertyValue = this.paramAsStr (i);
if (idSeen) this.invArg ();
propertyName = "lcaoID";
break;
}break;
}
if (eval.theTok != 12291) idSeen = true;
if (propertyName == null) this.invArg ();
this.setShapeProperty (26, propertyName, propertyValue);
}
this.setShapeProperty (26, "clear", null);
});
Clazz.defineMethod (c$, "contact", 
 function () {
var eval = this.e;
eval.sm.loadShape (25);
if (this.tokAt (1) == 1073742001 && this.listIsosurface (25)) return false;
var iptDisplayProperty = 0;
eval.iToken = 1;
var thisId = this.initIsosurface (25);
var idSeen = (thisId != null);
var isWild = (idSeen && this.getShapeProperty (25, "ID") == null);
var bsA = null;
var bsB = null;
var bs = null;
var rd = null;
var params = null;
var colorDensity = false;
var sbCommand =  new JU.SB ();
var minSet = 2147483647;
var displayType = 135266319;
var contactType = 0;
var distance = NaN;
var saProbeRadius = NaN;
var localOnly = true;
var intramolecular = null;
var userSlabObject = null;
var colorpt = 0;
var colorByType = false;
var tok;
var modelIndex = -2147483648;
var okNoAtoms = (eval.iToken > 1);
for (var i = eval.iToken; i < this.slen; ++i) {
switch (tok = this.getToken (i).tok) {
default:
okNoAtoms = true;
if (!eval.setMeshDisplayProperty (25, 0, eval.theTok)) {
if (eval.theTok != 269484209 && !JS.T.tokAttr (eval.theTok, 1073741824)) this.invArg ();
thisId = this.setShapeId (25, i, idSeen);
i = eval.iToken;
break;
}if (iptDisplayProperty == 0) iptDisplayProperty = i;
i = eval.iToken;
continue;
case 1074790550:
okNoAtoms = true;
this.setShapeId (25, ++i, idSeen);
isWild = (this.getShapeProperty (25, "ID") == null);
i = eval.iToken;
break;
case 1766856708:
switch (this.tokAt (i + 1)) {
case 1073741914:
tok = 0;
colorDensity = true;
sbCommand.append (" color density");
i++;
break;
case 1141899272:
tok = 0;
colorByType = true;
sbCommand.append (" color type");
i++;
break;
}
if (tok == 0) break;
case 603979967:
case 1073742074:
okNoAtoms = true;
if (colorpt == 0) colorpt = i;
eval.setMeshDisplayProperty (25, i, eval.theTok);
i = eval.iToken;
break;
case 554176565:
okNoAtoms = true;
userSlabObject = this.getCapSlabObject (i, false);
this.setShapeProperty (25, "slab", userSlabObject);
i = eval.iToken;
break;
case 1073741914:
colorDensity = true;
sbCommand.append (" density");
if (this.isFloatParameter (i + 1)) {
if (params == null) params =  Clazz.newFloatArray (1, 0);
params[0] = -Math.abs (this.floatParameter (++i));
sbCommand.append (" " + -params[0]);
}break;
case 1073742122:
var resolution = this.floatParameter (++i);
if (resolution > 0) {
sbCommand.append (" resolution ").appendF (resolution);
this.setShapeProperty (25, "resolution", Float.$valueOf (resolution));
}break;
case 1095766030:
case 1095761935:
modelIndex = (eval.theTok == 1095761935 ? this.intParameter (++i) : eval.modelNumberParameter (++i));
sbCommand.append (" modelIndex " + modelIndex);
break;
case 135266325:
case 1276118018:
distance = this.floatParameter (++i);
sbCommand.append (" within ").appendF (distance);
break;
case 269484193:
case 2:
case 3:
rd = eval.encodeRadiusParameter (i, false, false);
if (rd == null) return false;
sbCommand.append (" ").appendO (rd);
i = eval.iToken;
break;
case 1073741990:
case 1073741989:
intramolecular = (tok == 1073741989 ? Boolean.TRUE : Boolean.FALSE);
sbCommand.append (" ").appendO (eval.theToken.value);
break;
case 1073742020:
minSet = this.intParameter (++i);
break;
case 1612189718:
case 1073741881:
case 1649412120:
contactType = tok;
sbCommand.append (" ").appendO (eval.theToken.value);
break;
case 1073742135:
if (this.isFloatParameter (i + 1)) saProbeRadius = this.floatParameter (++i);
case 1074790451:
case 1073742036:
case 3145756:
localOnly = false;
case 1276117512:
case 1073741961:
case 135266319:
case 4106:
displayType = tok;
sbCommand.append (" ").appendO (eval.theToken.value);
if (tok == 1073742135) sbCommand.append (" ").appendF (saProbeRadius);
break;
case 1073742083:
params = eval.floatParameterSet (++i, 1, 10);
i = eval.iToken;
break;
case 10:
case 1048577:
if (isWild || bsB != null) this.invArg ();
bs = JU.BSUtil.copy (this.atomExpressionAt (i));
i = eval.iToken;
if (bsA == null) bsA = bs;
 else bsB = bs;
sbCommand.append (" ").append (JU.Escape.eBS (bs));
break;
}
idSeen = (eval.theTok != 12291);
}
if (!okNoAtoms && bsA == null) this.error (13);
if (this.chk) return false;
if (bsA != null) {
if (contactType == 1649412120 && rd == null) rd =  new J.atomdata.RadiusData (null, 0, J.atomdata.RadiusData.EnumType.OFFSET, J.c.VDW.AUTO);
var rd1 = (rd == null ?  new J.atomdata.RadiusData (null, 0.26, J.atomdata.RadiusData.EnumType.OFFSET, J.c.VDW.AUTO) : rd);
if (displayType == 1073742036 && bsB == null && intramolecular != null && intramolecular.booleanValue ()) bsB = bsA;
 else bsB = eval.getMathExt ().setContactBitSets (bsA, bsB, localOnly, distance, rd1, true);
switch (displayType) {
case 1074790451:
case 1073742135:
var bsSolvent = eval.lookupIdentifierValue ("solvent");
bsA.andNot (bsSolvent);
bsB.andNot (bsSolvent);
bsB.andNot (bsA);
break;
case 3145756:
bsB.andNot (bsA);
break;
case 1073742036:
if (minSet == 2147483647) minSet = 100;
this.setShapeProperty (25, "minset", Integer.$valueOf (minSet));
sbCommand.append (" minSet ").appendI (minSet);
if (params == null) params =  Clazz.newFloatArray (-1, [0.5, 2]);
}
if (intramolecular != null) {
params = (params == null ?  Clazz.newFloatArray (2, 0) : JU.AU.ensureLengthA (params, 2));
params[1] = (intramolecular.booleanValue () ? 1 : 2);
}if (params != null) sbCommand.append (" parameters ").append (JU.Escape.eAF (params));
this.setShapeProperty (25, "set",  Clazz.newArray (-1, [Integer.$valueOf (contactType), Integer.$valueOf (displayType), Boolean.$valueOf (colorDensity), Boolean.$valueOf (colorByType), bsA, bsB, rd, Float.$valueOf (saProbeRadius), params, Integer.$valueOf (modelIndex), sbCommand.toString ()]));
if (colorpt > 0) eval.setMeshDisplayProperty (25, colorpt, 0);
}if (iptDisplayProperty > 0) {
if (!eval.setMeshDisplayProperty (25, iptDisplayProperty, 0)) this.invArg ();
}if (userSlabObject != null && bsA != null) this.setShapeProperty (25, "slab", userSlabObject);
if (bsA != null && (displayType == 1073742036 || localOnly)) {
var volume = this.getShapeProperty (25, "volume");
var v;
var isFull = (displayType == 1073741961);
if (JU.AU.isAD (volume)) {
var vs = volume;
v = 0;
for (var i = 0; i < vs.length; i++) v += (isFull ? vs[i] : Math.abs (vs[i]));

} else {
v = (volume).floatValue ();
}v = (Math.round (v * 1000) / 1000.);
if (colorDensity || displayType != 1276117512) {
var nsets = (this.getShapeProperty (25, "nSets")).intValue ();
var s = "Contacts: " + (nsets < 0 ? Clazz.doubleToInt (-nsets / 2) : nsets);
if (v != 0) s += ", with " + (isFull ? "approx " : "net ") + "volume " + v + " A^3";
this.showString (s);
}}return true;
});
Clazz.defineMethod (c$, "cgo", 
 function () {
var eval = this.e;
eval.sm.loadShape (23);
if (this.tokAt (1) == 1073742001 && this.listIsosurface (23)) return false;
var iptDisplayProperty = 0;
var thisId = this.initIsosurface (23);
var idSeen = (thisId != null);
var isWild = (idSeen && this.getShapeProperty (23, "ID") == null);
var isInitialized = false;
var data = null;
var translucentLevel = 3.4028235E38;
var colorArgb =  Clazz.newIntArray (-1, [-2147483648]);
var intScale = 0;
for (var i = eval.iToken; i < this.slen; ++i) {
var propertyName = null;
var propertyValue = null;
var tok = this.getToken (i).tok;
switch (tok) {
case 269484096:
case 1073742195:
case 7:
if (data != null || isWild) this.invArg ();
data =  new JU.Lst ();
var ai =  Clazz.newIntArray (-1, [i, this.slen]);
if (!eval.getShapePropertyData (23, "data",  Clazz.newArray (-1, [this.st, ai, data, this.vwr]))) this.invArg ();
i = ai[0];
continue;
case 1073742138:
if (++i >= this.slen) this.error (34);
switch (this.getToken (i).tok) {
case 2:
intScale = this.intParameter (i);
continue;
case 3:
intScale = Math.round (this.floatParameter (i) * 100);
continue;
}
this.error (34);
break;
case 1766856708:
case 603979967:
case 1073742074:
translucentLevel = this.getColorTrans (eval, i, false, colorArgb);
i = eval.iToken;
idSeen = true;
continue;
case 1074790550:
thisId = this.setShapeId (23, ++i, idSeen);
isWild = (this.getShapeProperty (23, "ID") == null);
i = eval.iToken;
break;
default:
if (!eval.setMeshDisplayProperty (23, 0, eval.theTok)) {
if (eval.theTok == 269484209 || JS.T.tokAttr (eval.theTok, 1073741824)) {
thisId = this.setShapeId (23, i, idSeen);
i = eval.iToken;
break;
}this.invArg ();
}if (iptDisplayProperty == 0) iptDisplayProperty = i;
i = eval.iToken;
continue;
}
idSeen = (eval.theTok != 12291);
if (data != null && !isInitialized) {
propertyName = "points";
propertyValue = Integer.$valueOf (intScale);
isInitialized = true;
intScale = 0;
}if (propertyName != null) this.setShapeProperty (23, propertyName, propertyValue);
}
this.finalizeObject (23, colorArgb[0], translucentLevel, intScale, data != null, data, iptDisplayProperty, null);
return true;
});
Clazz.defineMethod (c$, "getAtomicPotentials", 
 function (bsSelected, bsIgnore, fileName) {
var potentials =  Clazz.newFloatArray (this.vwr.ms.ac, 0);
var m = J.api.Interface.getOption ("quantum.MlpCalculation", this.vwr, "script");
m.set (this.vwr);
var data = (fileName == null ? null : this.vwr.getFileAsString3 (fileName, false, null));
m.assignPotentials (this.vwr.ms.at, potentials, this.vwr.getSmartsMatch ("a", bsSelected), this.vwr.getSmartsMatch ("/noAromatic/[$(C=O),$(O=C),$(NC=O)]", bsSelected), bsIgnore, data);
return potentials;
}, "JU.BS,JU.BS,~S");
Clazz.defineMethod (c$, "getCapSlabObject", 
 function (i, isLcaoCartoon) {
if (i < 0) {
return JU.TempArray.getSlabWithinRange (i, 0);
}var eval = this.e;
var data = null;
var tok0 = this.tokAt (i);
var isSlab = (tok0 == 554176565);
var tok = this.tokAt (i + 1);
var plane = null;
var pts = null;
var d;
var d2;
var bs = null;
var slabColix = null;
var slabMeshType = null;
if (tok == 603979967) {
var slabTranslucency = (this.isFloatParameter (++i + 1) ? this.floatParameter (++i) : 0.5);
if (eval.isColorParam (i + 1)) {
slabColix = Short.$valueOf (JU.C.getColixTranslucent3 (JU.C.getColix (eval.getArgbParam (i + 1)), slabTranslucency != 0, slabTranslucency));
i = eval.iToken;
} else {
slabColix = Short.$valueOf (JU.C.getColixTranslucent3 (1, slabTranslucency != 0, slabTranslucency));
}switch (tok = this.tokAt (i + 1)) {
case 1073742018:
case 1073741938:
slabMeshType = Integer.$valueOf (tok);
tok = this.tokAt (++i + 1);
break;
default:
slabMeshType = Integer.$valueOf (1073741938);
break;
}
}switch (tok) {
case 1048588:
eval.iToken = i + 1;
return Integer.$valueOf (-2147483648);
case 1048587:
eval.iToken = i + 1;
break;
case 1048582:
i++;
data =  Clazz.newArray (-1, [Float.$valueOf (1), this.paramAsStr (++i)]);
tok = 1073742018;
break;
case 135266325:
i++;
if (this.tokAt (++i) == 1073742114) {
d = this.floatParameter (++i);
d2 = this.floatParameter (++i);
data =  Clazz.newArray (-1, [Float.$valueOf (d), Float.$valueOf (d2)]);
tok = 1073742114;
} else if (this.isFloatParameter (i)) {
d = this.floatParameter (i);
if (eval.isCenterParameter (++i)) {
var pt = this.centerParameter (i);
if (this.chk || !(Clazz.instanceOf (eval.expressionResult, JU.BS))) {
pts =  Clazz.newArray (-1, [pt]);
} else {
var atoms = this.vwr.ms.at;
bs = eval.expressionResult;
pts =  new Array (bs.cardinality ());
for (var k = 0, j = bs.nextSetBit (0); j >= 0; j = bs.nextSetBit (j + 1), k++) pts[k] = atoms[j];

}} else {
pts = eval.getPointArray (i, -1, false);
}if (pts.length == 0) {
eval.iToken = i;
this.invArg ();
}data =  Clazz.newArray (-1, [Float.$valueOf (d), pts, bs]);
} else {
data = eval.getPointArray (i, 4, false);
tok = 1679429641;
}break;
case 1679429641:
eval.iToken = i + 1;
data = JU.BoxInfo.getUnitCellPoints (this.vwr.ms.getBBoxVertices (), null);
break;
case 1073741872:
case 1614417948:
eval.iToken = i + 1;
var unitCell = this.vwr.getCurrentUnitCell ();
if (unitCell == null) {
if (tok == 1614417948) this.invArg ();
} else {
pts = JU.BoxInfo.getUnitCellPoints (unitCell.getUnitCellVerticesNoOffset (), unitCell.getCartesianOffset ());
var iType = Clazz.floatToInt (unitCell.getUnitCellInfoType (6));
var v1 = null;
var v2 = null;
switch (iType) {
case 3:
break;
case 1:
v2 = JU.V3.newVsub (pts[2], pts[0]);
v2.scale (1000);
case 2:
v1 = JU.V3.newVsub (pts[1], pts[0]);
v1.scale (1000);
pts[0].sub (v1);
pts[1].scale (2000);
if (iType == 1) {
pts[0].sub (v2);
pts[2].scale (2000);
}break;
}
data = pts;
}break;
case 10:
case 1048577:
data = this.atomExpressionAt (i + 1);
tok = 3;
if (!eval.isCenterParameter (++eval.iToken)) {
isSlab = true;
break;
}data = null;
default:
if (!isLcaoCartoon && isSlab && this.isFloatParameter (i + 1)) {
d = this.floatParameter (++i);
if (!this.isFloatParameter (i + 1)) return Integer.$valueOf (Clazz.floatToInt (d));
d2 = this.floatParameter (++i);
data =  Clazz.newArray (-1, [Float.$valueOf (d), Float.$valueOf (d2)]);
tok = 1073742114;
break;
}plane = eval.planeParameter (++i);
var off = (this.isFloatParameter (eval.iToken + 1) ? this.floatParameter (++eval.iToken) : NaN);
if (!Float.isNaN (off)) plane.w -= off;
data = plane;
tok = 135266319;
}
var colorData = (slabMeshType == null ? null :  Clazz.newArray (-1, [slabMeshType, slabColix]));
return JU.TempArray.getSlabObjectType (tok, data, !isSlab, colorData);
}, "~N,~B");
Clazz.defineMethod (c$, "setColorOptions", 
 function (sb, index, iShape, nAllowed) {
var eval = this.e;
this.getToken (index);
var translucency = "opaque";
if (eval.theTok == 603979967) {
translucency = "translucent";
if (nAllowed < 0) {
var value = (this.isFloatParameter (index + 1) ? this.floatParameter (++index) : 3.4028235E38);
eval.setShapeTranslucency (iShape, null, "translucent", value, null);
if (sb != null) {
sb.append (" translucent");
if (value != 3.4028235E38) sb.append (" ").appendF (value);
}} else {
eval.setMeshDisplayProperty (iShape, index, eval.theTok);
}} else if (eval.theTok == 1073742074) {
if (nAllowed >= 0) eval.setMeshDisplayProperty (iShape, index, eval.theTok);
} else {
eval.iToken--;
}nAllowed = Math.abs (nAllowed);
for (var i = 0; i < nAllowed; i++) {
if (eval.isColorParam (eval.iToken + 1)) {
var color = eval.getArgbParam (++eval.iToken);
this.setShapeProperty (iShape, "colorRGB", Integer.$valueOf (color));
if (sb != null) sb.append (" ").append (JU.Escape.escapeColor (color));
} else if (eval.iToken < index) {
this.invArg ();
} else {
break;
}}
return translucency;
}, "JU.SB,~N,~N,~N");
Clazz.defineMethod (c$, "createFunction", 
 function (fname, xyz, ret) {
var e = ( new JS.ScriptEval ()).setViewer (this.vwr);
try {
e.compileScript (null, "function " + fname + "(" + xyz + ") { return " + ret + "}", false);
var params =  new JU.Lst ();
for (var i = 0; i < xyz.length; i += 2) params.addLast (JS.SV.newV (3, Float.$valueOf (0)).setName (xyz.substring (i, i + 1)));

return  Clazz.newArray (-1, [e.aatoken[0][1].value, params]);
} catch (ex) {
if (Clazz.exceptionOf (ex, Exception)) {
return null;
} else {
throw ex;
}
}
}, "~S,~S,~S");
Clazz.defineMethod (c$, "getWithinDistanceVector", 
 function (propertyList, distance, ptc, bs, isShow) {
var v =  new JU.Lst ();
var pts =  new Array (2);
if (bs == null) {
var pt1 = JU.P3.new3 (distance, distance, distance);
var pt0 = JU.P3.newP (ptc);
pt0.sub (pt1);
pt1.add (ptc);
pts[0] = pt0;
pts[1] = pt1;
v.addLast (ptc);
} else {
var bbox = this.vwr.ms.getBoxInfo (bs, -Math.abs (distance));
pts[0] = bbox.getBoundBoxVertices ()[0];
pts[1] = bbox.getBoundBoxVertices ()[7];
if (bs.cardinality () == 1) v.addLast (this.vwr.ms.at[bs.nextSetBit (0)]);
}if (v.size () == 1 && !isShow) {
this.addShapeProperty (propertyList, "withinDistance", Float.$valueOf (distance));
this.addShapeProperty (propertyList, "withinPoint", v.get (0));
}this.addShapeProperty (propertyList, (isShow ? "displayWithin" : "withinPoints"),  Clazz.newArray (-1, [Float.$valueOf (distance), pts, bs, v]));
}, "JU.Lst,~N,JU.P3,JU.BS,~B");
Clazz.defineMethod (c$, "addShapeProperty", 
 function (propertyList, key, value) {
if (this.chk) return;
propertyList.addLast ( Clazz.newArray (-1, [key, value]));
}, "JU.Lst,~S,~O");
Clazz.defineMethod (c$, "floatArraySetXYZ", 
 function (i, nX, nY, nZ) {
var eval = this.e;
var tok = this.tokAt (i++);
if (tok == 1073742195) tok = this.tokAt (i++);
if (tok != 269484096 || nX <= 0) this.invArg ();
var fparams = JU.AU.newFloat3 (nX, -1);
var n = 0;
while (tok != 269484097) {
tok = this.getToken (i).tok;
switch (tok) {
case 1073742195:
case 269484097:
continue;
case 269484080:
i++;
break;
case 269484096:
fparams[n++] = this.floatArraySet (i, nY, nZ);
i = ++eval.iToken;
tok = 0;
if (n == nX && this.tokAt (i) != 269484097) this.invArg ();
break;
default:
this.invArg ();
}
}
return fparams;
}, "~N,~N,~N,~N");
Clazz.defineMethod (c$, "floatArraySet", 
 function (i, nX, nY) {
var tok = this.tokAt (i++);
if (tok == 1073742195) tok = this.tokAt (i++);
if (tok != 269484096) this.invArg ();
var fparams = JU.AU.newFloat2 (nX);
var n = 0;
while (tok != 269484097) {
tok = this.getToken (i).tok;
switch (tok) {
case 1073742195:
case 269484097:
continue;
case 269484080:
i++;
break;
case 269484096:
i++;
var f =  Clazz.newFloatArray (nY, 0);
fparams[n++] = f;
for (var j = 0; j < nY; j++) {
f[j] = this.floatParameter (i++);
if (this.tokAt (i) == 269484080) i++;
}
if (this.tokAt (i++) != 269484097) this.invArg ();
tok = 0;
if (n == nX && this.tokAt (i) != 269484097) this.invArg ();
break;
default:
this.invArg ();
}
}
return fparams;
}, "~N,~N,~N");
Clazz.defineMethod (c$, "initIsosurface", 
 function (iShape) {
var eval = this.e;
this.setShapeProperty (iShape, "init", eval.fullCommand);
eval.iToken = 0;
var tok1 = this.tokAt (1);
var tok2 = this.tokAt (2);
if (tok1 == 12291 || tok2 == 12291 && this.tokAt (++eval.iToken) == 1048579) {
this.setShapeProperty (iShape, "delete", null);
eval.iToken += 2;
if (this.slen > eval.iToken) {
this.setShapeProperty (iShape, "init", eval.fullCommand);
this.setShapeProperty (iShape, "thisID", "+PREVIOUS_MESH+");
}return null;
}eval.iToken = 1;
if (!eval.setMeshDisplayProperty (iShape, 0, tok1)) {
this.setShapeProperty (iShape, "thisID", "+PREVIOUS_MESH+");
if (iShape != 22) this.setShapeProperty (iShape, "title",  Clazz.newArray (-1, [eval.thisCommand]));
if (tok1 != 1074790550 && (tok2 == 269484209 || tok1 == 269484209 && eval.setMeshDisplayProperty (iShape, 0, tok2))) {
var id = this.setShapeId (iShape, 1, false);
eval.iToken++;
return id;
}}return null;
}, "~N");
Clazz.defineMethod (c$, "listIsosurface", 
 function (iShape) {
var s = (this.slen > 3 ? "0" : this.tokAt (2) == 0 ? "" : " " + this.getToken (2).value);
if (!this.chk) this.showString (this.getShapeProperty (iShape, "list" + s));
return true;
}, "~N");
});
