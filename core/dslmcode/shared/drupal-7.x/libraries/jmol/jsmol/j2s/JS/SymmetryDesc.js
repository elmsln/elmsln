Clazz.declarePackage ("JS");
Clazz.load (null, "JS.SymmetryDesc", ["java.lang.Float", "java.util.Hashtable", "JU.Lst", "$.M4", "$.Measure", "$.P3", "$.P4", "$.PT", "$.Quat", "$.SB", "$.V3", "JM.Atom", "JS.SpaceGroup", "$.SymmetryOperation", "JU.Escape"], function () {
c$ = Clazz.declareType (JS, "SymmetryDesc");
Clazz.makeConstructor (c$, 
function () {
});
Clazz.defineMethod (c$, "getDescription", 
function (op, uc, pta00, ptTarget, id, modelSet) {
if (!op.isFinalized) op.doFinalize ();
var vtemp =  new JU.V3 ();
var ptemp =  new JU.P3 ();
var ptemp2 =  new JU.P3 ();
var pta01 =  new JU.P3 ();
var pta02 =  new JU.P3 ();
var ftrans =  new JU.V3 ();
var vtrans =  new JU.V3 ();
var vcentering = null;
if (op.centering != null) {
vcentering = JU.V3.newV (op.centering);
uc.toCartesian (vcentering, false);
}var haveCentering = false;
if (pta00 == null || Float.isNaN (pta00.x)) pta00 =  new JU.P3 ();
if (ptTarget != null) {
JS.SymmetryDesc.setFractional (uc, pta00, pta01, ptemp);
op.rotTrans (pta01);
uc.toCartesian (pta01, false);
uc.toUnitCell (pta01, ptemp);
pta02.setT (ptTarget);
uc.toUnitCell (pta02, ptemp);
if (pta01.distance (pta02) > 0.1) return null;
JS.SymmetryDesc.setFractional (uc, pta00, pta01, null);
op.rotTrans (pta01);
JS.SymmetryDesc.setFractional (uc, ptTarget, pta02, null);
vtrans.sub2 (pta02, pta01);
}pta01.set (1, 0, 0);
pta02.set (0, 1, 0);
var pta03 = JU.P3.new3 (0, 0, 1);
pta01.add (pta00);
pta02.add (pta00);
pta03.add (pta00);
if (haveCentering) vtrans.sub (op.centering);
var pt0 = JS.SymmetryDesc.rotTransCart (op, uc, pta00, vtrans);
var pt1 = JS.SymmetryDesc.rotTransCart (op, uc, pta01, vtrans);
var pt2 = JS.SymmetryDesc.rotTransCart (op, uc, pta02, vtrans);
var pt3 = JS.SymmetryDesc.rotTransCart (op, uc, pta03, vtrans);
var vt1 = JU.V3.newVsub (pt1, pt0);
var vt2 = JU.V3.newVsub (pt2, pt0);
var vt3 = JU.V3.newVsub (pt3, pt0);
JS.SymmetryDesc.approx (vtrans);
vtemp.cross (vt1, vt2);
var haveInversion = (vtemp.dot (vt3) < 0);
if (haveInversion) {
pt1.sub2 (pt0, vt1);
pt2.sub2 (pt0, vt2);
pt3.sub2 (pt0, vt3);
}var info = JU.Measure.computeHelicalAxis (pta00, pt0, JU.Quat.getQuaternionFrame (pt0, pt1, pt2).div (JU.Quat.getQuaternionFrame (pta00, pta01, pta02)));
var pa1 = info[0];
var ax1 = info[1];
var ang1 = Clazz.floatToInt (Math.abs (JU.PT.approx ((info[3]).x, 1)));
var pitch1 = JS.SymmetryOperation.approxF ((info[3]).y);
if (haveInversion) {
pt1.add2 (pt0, vt1);
pt2.add2 (pt0, vt2);
pt3.add2 (pt0, vt3);
}var trans = JU.V3.newVsub (pt0, pta00);
if (trans.length () < 0.1) trans = null;
var ptinv = null;
var ipt = null;
var ptref = null;
var isTranslation = (ang1 == 0);
var isRotation = !isTranslation;
var isInversionOnly = false;
var isMirrorPlane = false;
if (isRotation || haveInversion) trans = null;
if (haveInversion && isTranslation) {
ipt = JU.P3.newP (pta00);
ipt.add (pt0);
ipt.scale (0.5);
ptinv = pt0;
isInversionOnly = true;
} else if (haveInversion) {
var d = (pitch1 == 0 ?  new JU.V3 () : ax1);
var f = 0;
switch (ang1) {
case 60:
f = 0.6666667;
break;
case 120:
f = 2;
break;
case 90:
f = 1;
break;
case 180:
ptref = JU.P3.newP (pta00);
ptref.add (d);
pa1.scaleAdd2 (0.5, d, pta00);
if (ptref.distance (pt0) > 0.1) {
trans = JU.V3.newVsub (pt0, ptref);
JS.SymmetryDesc.setFractional (uc, trans, ptemp, null);
ftrans.setT (ptemp);
} else {
trans = null;
}isRotation = false;
haveInversion = false;
isMirrorPlane = true;
}
if (f != 0) {
vtemp.sub2 (pta00, pa1);
vtemp.add (pt0);
vtemp.sub (pa1);
vtemp.sub (d);
vtemp.scale (f);
pa1.add (vtemp);
ipt =  new JU.P3 ();
ipt.scaleAdd2 (0.5, d, pa1);
ptinv =  new JU.P3 ();
ptinv.scaleAdd2 (-2, ipt, pta00);
ptinv.scale (-1);
}} else if (trans != null) {
ptemp.setT (trans);
uc.toFractional (ptemp, false);
if (JS.SymmetryOperation.approxF (ptemp.x) == 1) {
ptemp.x = 0;
}if (JS.SymmetryOperation.approxF (ptemp.y) == 1) {
ptemp.y = 0;
}if (JS.SymmetryOperation.approxF (ptemp.z) == 1) {
ptemp.z = 0;
}ftrans.setT (ptemp);
uc.toCartesian (ptemp, false);
trans.setT (ptemp);
}var ang = ang1;
JS.SymmetryDesc.approx0 (ax1);
if (isRotation) {
var ptr =  new JU.P3 ();
vtemp.setT (ax1);
var ang2 = ang1;
if (haveInversion) {
ptr.add2 (pa1, vtemp);
ang2 = Math.round (JU.Measure.computeTorsion (ptinv, pa1, ptr, pt0, true));
} else if (pitch1 == 0) {
ptr.setT (pa1);
ptemp.scaleAdd2 (1, ptr, vtemp);
ang2 = Math.round (JU.Measure.computeTorsion (pta00, pa1, ptemp, pt0, true));
} else {
ptemp.add2 (pa1, vtemp);
ptr.scaleAdd2 (0.5, vtemp, pa1);
ang2 = Math.round (JU.Measure.computeTorsion (pta00, pa1, ptemp, pt0, true));
}if (ang2 != 0) ang1 = ang2;
}if (isRotation && !haveInversion && pitch1 == 0) {
if (ax1.z < 0 || ax1.z == 0 && (ax1.y < 0 || ax1.y == 0 && ax1.x < 0)) {
ax1.scale (-1);
ang1 = -ang1;
}}var info1 = "identity";
if (isInversionOnly) {
ptemp.setT (ipt);
uc.toFractional (ptemp, false);
info1 = "Ci: " + JS.SymmetryDesc.strCoord (ptemp, op.isBio);
} else if (isRotation) {
if (haveInversion) {
info1 = "" + (Clazz.doubleToInt (360 / ang)) + "-bar axis";
} else if (pitch1 != 0) {
info1 = "" + (Clazz.doubleToInt (360 / ang)) + "-fold screw axis";
ptemp.setT (ax1);
uc.toFractional (ptemp, false);
info1 += "|translation: " + JS.SymmetryDesc.strCoord (ptemp, op.isBio);
} else {
info1 = "C" + (Clazz.doubleToInt (360 / ang)) + " axis";
}} else if (trans != null) {
var s = " " + JS.SymmetryDesc.strCoord (ftrans, op.isBio);
if (isTranslation) {
info1 = "translation:" + s;
} else if (isMirrorPlane) {
var fx = JS.SymmetryOperation.approxF (ftrans.x);
var fy = JS.SymmetryOperation.approxF (ftrans.y);
var fz = JS.SymmetryOperation.approxF (ftrans.z);
s = " " + JS.SymmetryDesc.strCoord (ftrans, op.isBio);
if (fx != 0 && fy != 0 && fz != 0) {
if (Math.abs (fx) == Math.abs (fy) && Math.abs (fy) == Math.abs (fz)) info1 = "d-";
 else info1 = "g-";
} else if (fx != 0 && fy != 0 || fy != 0 && fz != 0 || fz != 0 && fx != 0) info1 = "n-";
 else if (fx != 0) info1 = "a-";
 else if (fy != 0) info1 = "b-";
 else info1 = "c-";
info1 += "glide plane|translation:" + s;
}} else if (isMirrorPlane) {
info1 = "mirror plane";
}if (haveInversion && !isInversionOnly) {
ptemp.setT (ipt);
uc.toFractional (ptemp, false);
info1 += "|inversion center at " + JS.SymmetryDesc.strCoord (ptemp, op.isBio);
}if (haveCentering) info1 += "|centering " + JS.SymmetryDesc.strCoord (op.centering, op.isBio);
if (op.timeReversal != 0 && op.getSpinOp () == -1) info1 += "|spin flipped";
var cmds = null;
var xyzNew = (op.isBio ? op.xyzOriginal : JS.SymmetryOperation.getXYZFromMatrix (op, false, false, false));
if (id != null) {
var drawid;
var opType = null;
drawid = "\ndraw ID " + id + "_";
var draw1 =  new JU.SB ();
draw1.append (("// " + op.xyzOriginal + "|" + xyzNew + "|" + info1).$replace ('\n', ' ')).appendC ('\n').append (drawid).append ("* delete");
JS.SymmetryDesc.drawLine (draw1, drawid + "frame1X", 0.15, pta00, pta01, "red");
JS.SymmetryDesc.drawLine (draw1, drawid + "frame1Y", 0.15, pta00, pta02, "green");
JS.SymmetryDesc.drawLine (draw1, drawid + "frame1Z", 0.15, pta00, pta03, "blue");
var color;
if (isRotation) {
var ptr =  new JU.P3 ();
color = "red";
ang = ang1;
var scale = 1;
vtemp.setT (ax1);
if (haveInversion) {
opType = drawid + "rotinv";
ptr.add2 (pa1, vtemp);
if (pitch1 == 0) {
ptr.setT (ipt);
vtemp.scale (3);
ptemp.scaleAdd2 (-1, vtemp, pa1);
draw1.append (drawid).append ("rotVector2 diameter 0.1 ").append (JU.Escape.eP (pa1)).append (JU.Escape.eP (ptemp)).append (" color red");
}scale = pt0.distance (ptr);
draw1.append (drawid).append ("rotLine1 ").append (JU.Escape.eP (ptr)).append (JU.Escape.eP (ptinv)).append (" color red");
draw1.append (drawid).append ("rotLine2 ").append (JU.Escape.eP (ptr)).append (JU.Escape.eP (pt0)).append (" color red");
} else if (pitch1 == 0) {
opType = drawid + "rot";
var isSpecial = (pta00.distance (pt0) < 0.2);
if (!isSpecial) {
draw1.append (drawid).append ("rotLine1 ").append (JU.Escape.eP (pta00)).append (JU.Escape.eP (pa1)).append (" color red");
draw1.append (drawid).append ("rotLine2 ").append (JU.Escape.eP (pt0)).append (JU.Escape.eP (pa1)).append (" color red");
}vtemp.scale (3);
ptemp.scaleAdd2 (-1, vtemp, pa1);
draw1.append (drawid).append ("rotVector2 diameter 0.1 ").append (JU.Escape.eP (pa1)).append (JU.Escape.eP (ptemp)).append (" color red");
ptr.setT (pa1);
if (pitch1 == 0 && pta00.distance (pt0) < 0.2) ptr.scaleAdd2 (0.5, ptr, vtemp);
} else {
opType = drawid + "screw";
color = "orange";
draw1.append (drawid).append ("rotLine1 ").append (JU.Escape.eP (pta00)).append (JU.Escape.eP (pa1)).append (" color red");
ptemp.add2 (pa1, vtemp);
draw1.append (drawid).append ("rotLine2 ").append (JU.Escape.eP (pt0)).append (JU.Escape.eP (ptemp)).append (" color red");
ptr.scaleAdd2 (0.5, vtemp, pa1);
}ptemp.add2 (ptr, vtemp);
if (haveInversion && pitch1 != 0) {
draw1.append (drawid).append ("rotRotLine1").append (JU.Escape.eP (ptr)).append (JU.Escape.eP (ptinv)).append (" color red");
draw1.append (drawid).append ("rotRotLine2").append (JU.Escape.eP (ptr)).append (JU.Escape.eP (pt0)).append (" color red");
}draw1.append (drawid).append ("rotRotArrow arrow width 0.10 scale " + JU.PT.escF (scale) + " arc ").append (JU.Escape.eP (ptr)).append (JU.Escape.eP (ptemp));
ptemp.setT (haveInversion ? ptinv : pta00);
if (ptemp.distance (pt0) < 0.1) ptemp.set (Math.random (), Math.random (), Math.random ());
draw1.append (JU.Escape.eP (ptemp));
ptemp.set (0, ang, 0);
draw1.append (JU.Escape.eP (ptemp)).append (" color red");
draw1.append (drawid).append ("rotVector1 vector diameter 0.1 ").append (JU.Escape.eP (pa1)).append (JU.Escape.eP (vtemp)).append ("color ").append (color);
}if (isMirrorPlane) {
if (pta00.distance (ptref) > 0.2) draw1.append (drawid).append ("planeVector arrow ").append (JU.Escape.eP (pta00)).append (JU.Escape.eP (ptref)).append (" color indigo");
opType = drawid + "plane";
if (trans != null) {
JS.SymmetryDesc.drawFrameLine ("X", ptref, vt1, 0.15, ptemp, draw1, opType, "red");
JS.SymmetryDesc.drawFrameLine ("Y", ptref, vt2, 0.15, ptemp, draw1, opType, "green");
JS.SymmetryDesc.drawFrameLine ("Z", ptref, vt3, 0.15, ptemp, draw1, opType, "blue");
opType = drawid + "glide";
}color = (trans == null ? "green" : "blue");
vtemp.setT (ax1);
vtemp.normalize ();
var w = -vtemp.x * pa1.x - vtemp.y * pa1.y - vtemp.z * pa1.z;
var plane = JU.P4.new4 (vtemp.x, vtemp.y, vtemp.z, w);
var v =  new JU.Lst ();
var margin = 1.05;
v.addLast (uc.getCanonicalCopy (margin, false));
modelSet.intersectPlane (plane, v, 3);
for (var i = v.size (); --i >= 0; ) {
var pts = v.get (i);
draw1.append (drawid).append ("planep").appendI (i).append (" ").append (JU.Escape.eP (pts[0])).append (JU.Escape.eP (pts[1]));
if (pts.length == 3) draw1.append (JU.Escape.eP (pts[2]));
draw1.append (" color translucent ").append (color);
}
if (v.size () == 0) {
ptemp.add2 (pa1, ax1);
draw1.append (drawid).append ("planeCircle scale 2.0 circle ").append (JU.Escape.eP (pa1)).append (JU.Escape.eP (ptemp)).append (" color translucent ").append (color).append (" mesh fill");
}}if (haveInversion) {
opType = drawid + "inv";
draw1.append (drawid).append ("invPoint diameter 0.4 ").append (JU.Escape.eP (ipt));
draw1.append (drawid).append ("invArrow arrow ").append (JU.Escape.eP (pta00)).append (JU.Escape.eP (ptinv)).append (" color indigo");
if (!isInversionOnly && !haveCentering) {
JS.SymmetryDesc.drawFrameLine ("X", ptinv, vt1, 0.15, ptemp, draw1, opType, "red");
JS.SymmetryDesc.drawFrameLine ("Y", ptinv, vt2, 0.15, ptemp, draw1, opType, "green");
JS.SymmetryDesc.drawFrameLine ("Z", ptinv, vt3, 0.15, ptemp, draw1, opType, "blue");
}}if (trans != null) {
if (ptref == null) ptref = JU.P3.newP (pta00);
draw1.append (drawid).append ("transVector vector ").append (JU.Escape.eP (ptref)).append (JU.Escape.eP (trans));
}if (haveCentering) {
if (opType != null) {
JS.SymmetryDesc.drawFrameLine ("X", pt0, vt1, 0.15, ptemp, draw1, opType, "red");
JS.SymmetryDesc.drawFrameLine ("Y", pt0, vt2, 0.15, ptemp, draw1, opType, "green");
JS.SymmetryDesc.drawFrameLine ("Z", pt0, vt3, 0.15, ptemp, draw1, opType, "blue");
}if (ptTarget == null) {
ptTarget = ptemp;
ptemp.add2 (pt0, vcentering);
}draw1.append (drawid).append ("centeringVector arrow ").append (JU.Escape.eP (pt0)).append (JU.Escape.eP (ptTarget)).append (" color cyan");
}ptemp2.setT (pt0);
if (haveCentering) ptemp2.add (vcentering);
ptemp.sub2 (pt1, pt0);
ptemp.scaleAdd2 (0.9, ptemp, ptemp2);
JS.SymmetryDesc.drawLine (draw1, drawid + "frame2X", 0.2, ptemp2, ptemp, "red");
ptemp.sub2 (pt2, pt0);
ptemp.scaleAdd2 (0.9, ptemp, ptemp2);
JS.SymmetryDesc.drawLine (draw1, drawid + "frame2Y", 0.2, ptemp2, ptemp, "green");
ptemp.sub2 (pt3, pt0);
ptemp.scaleAdd2 (0.9, ptemp, ptemp2);
JS.SymmetryDesc.drawLine (draw1, drawid + "frame2Z", 0.2, ptemp2, ptemp, "purple");
draw1.append ("\nvar pt00 = " + JU.Escape.eP (pta00));
draw1.append ("\nsym_point = pt00");
draw1.append ("\nvar p0 = " + JU.Escape.eP (ptemp2));
draw1.append ("\nvar set2 = within(0.2,p0);if(!set2){set2 = within(0.2,p0.uxyz.xyz)}");
draw1.append ("\nsym_target = set2;if (set2) {");
draw1.append (drawid).append ("offsetFrameX diameter 0.20 @{set2.xyz} @{set2.xyz + ").append (JU.Escape.eP (vt1)).append ("*0.9} color red");
draw1.append (drawid).append ("offsetFrameY diameter 0.20 @{set2.xyz} @{set2.xyz + ").append (JU.Escape.eP (vt2)).append ("*0.9} color green");
draw1.append (drawid).append ("offsetFrameZ diameter 0.20 @{set2.xyz} @{set2.xyz + ").append (JU.Escape.eP (vt3)).append ("*0.9} color purple");
draw1.append ("\n}\n");
cmds = draw1.toString ();
draw1 = null;
drawid = null;
}if (trans == null) ftrans = null;
if (isRotation) {
if (haveInversion) {
} else if (pitch1 == 0) {
} else {
trans = JU.V3.newV (ax1);
ptemp.setT (trans);
uc.toFractional (ptemp, false);
ftrans = JU.V3.newV (ptemp);
}}if (isMirrorPlane) {
ang1 = 0;
}if (haveInversion) {
if (isInversionOnly) {
pa1 = null;
ax1 = null;
trans = null;
ftrans = null;
}} else if (isTranslation) {
pa1 = null;
ax1 = null;
}if (ax1 != null) ax1.normalize ();
var m2 = null;
m2 = JU.M4.newM4 (op);
if (haveCentering) vtrans.add (op.centering);
if (vtrans.length () != 0) {
m2.m03 += vtrans.x;
m2.m13 += vtrans.y;
m2.m23 += vtrans.z;
}xyzNew = (op.isBio ? m2.toString () : op.modDim > 0 ? op.xyzOriginal : JS.SymmetryOperation.getXYZFromMatrix (m2, false, false, false));
return  Clazz.newArray (-1, [xyzNew, op.xyzOriginal, info1, cmds, JS.SymmetryDesc.approx0 (ftrans), JS.SymmetryDesc.approx0 (trans), JS.SymmetryDesc.approx0 (ipt), JS.SymmetryDesc.approx0 (pa1), JS.SymmetryDesc.approx0 (ax1), Integer.$valueOf (ang1), m2, vtrans, op.centering]);
}, "JS.SymmetryOperation,J.api.SymmetryInterface,JU.P3,JU.P3,~S,JM.ModelSet");
c$.setFractional = Clazz.defineMethod (c$, "setFractional", 
 function (uc, pt00, pt01, offset) {
pt01.setT (pt00);
if (offset != null) uc.toUnitCell (pt01, offset);
uc.toFractional (pt01, false);
}, "J.api.SymmetryInterface,JU.T3,JU.P3,JU.P3");
c$.drawFrameLine = Clazz.defineMethod (c$, "drawFrameLine", 
 function (xyz, pt, v, width, ptemp, draw1, key, color) {
ptemp.setT (pt);
ptemp.add (v);
JS.SymmetryDesc.drawLine (draw1, key + "Frame" + xyz, width, pt, ptemp, "translucent " + color);
}, "~S,JU.P3,JU.V3,~N,JU.P3,JU.SB,~S,~S");
c$.rotTransCart = Clazz.defineMethod (c$, "rotTransCart", 
 function (op, uc, pt00, vtrans) {
var p0 = JU.P3.newP (pt00);
uc.toFractional (p0, false);
op.rotTrans (p0);
p0.add (vtrans);
uc.toCartesian (p0, false);
return p0;
}, "JS.SymmetryOperation,J.api.SymmetryInterface,JU.P3,JU.V3");
c$.strCoord = Clazz.defineMethod (c$, "strCoord", 
 function (p, isBio) {
JS.SymmetryDesc.approx0 (p);
return (isBio ? p.x + " " + p.y + " " + p.z : JS.SymmetryOperation.fcoord (p));
}, "JU.T3,~B");
c$.drawLine = Clazz.defineMethod (c$, "drawLine", 
 function (s, id, diameter, pt0, pt1, color) {
s.append (id).append (" diameter ").appendF (diameter).append (JU.Escape.eP (pt0)).append (JU.Escape.eP (pt1)).append (" color ").append (color);
}, "JU.SB,~S,~N,JU.P3,JU.P3,~S");
c$.approx0 = Clazz.defineMethod (c$, "approx0", 
 function (pt) {
if (pt != null) {
if (Math.abs (pt.x) < 0.0001) pt.x = 0;
if (Math.abs (pt.y) < 0.0001) pt.y = 0;
if (Math.abs (pt.z) < 0.0001) pt.z = 0;
}return pt;
}, "JU.T3");
c$.approx = Clazz.defineMethod (c$, "approx", 
 function (pt) {
if (pt != null) {
pt.x = JS.SymmetryOperation.approxF (pt.x);
pt.y = JS.SymmetryOperation.approxF (pt.y);
pt.z = JS.SymmetryOperation.approxF (pt.z);
}return pt;
}, "JU.T3");
Clazz.defineMethod (c$, "getSymmetryInfo", 
function (sym, iModel, iAtom, uc, xyz, op, pt, pt2, id, type, modelSet) {
if (pt2 != null) return this.getSymmetryInfoString (sym, iModel, op, pt, pt2, (id == null ? "sym" : id), type == 1826248716 ? "label" : null, modelSet);
var isBio = uc.isBio ();
var iop = op;
var centering = null;
if (xyz == null) {
var ops = uc.getSymmetryOperations ();
if (ops == null || op == 0 || Math.abs (op) > ops.length) return (type == 135176 ? "draw ID sym_* delete" : "");
xyz = ops[iop = Math.abs (op) - 1].xyz;
centering = ops[iop].centering;
} else {
iop = op = 0;
}var symTemp = modelSet.getSymTemp (true);
symTemp.setSpaceGroup (false);
var i = (isBio ? symTemp.addBioMoleculeOperation (uc.spaceGroup.finalOperations[iop], op < 0) : symTemp.addSpaceGroupOperation ((op < 0 ? "!" : "=") + xyz, Math.abs (op)));
if (i < 0) return "";
var opTemp = symTemp.getSpaceGroupOperation (i);
if (!isBio) opTemp.centering = centering;
var info;
if (pt != null || iAtom >= 0) pt = JU.P3.newP (pt == null ? modelSet.at[iAtom] : pt);
if (type == 135266320) {
if (isBio) return "";
symTemp.setUnitCell (uc.getUnitCellParams (), false);
uc.toFractional (pt, false);
if (Float.isNaN (pt.x)) return "";
var sympt =  new JU.P3 ();
symTemp.newSpaceGroupPoint (i, pt, sympt, 0, 0, 0);
symTemp.toCartesian (sympt, false);
return sympt;
}info = this.getDescription (opTemp, uc, pt, pt2, (id == null ? "sym" : id), modelSet);
var ang = (info[9]).intValue ();
switch (type) {
case 135266306:
return info;
case 1073742001:
var sinfo =  Clazz.newArray (-1, [info[0], info[1], info[2], JU.Escape.eP (info[4]), JU.Escape.eP (info[5]), JU.Escape.eP (info[6]), JU.Escape.eP (info[7]), JU.Escape.eP (info[8]), "" + info[9], "" + JU.Escape.e (info[10])]);
return sinfo;
case 1073741982:
return info[0];
default:
case 1826248716:
return info[2];
case 135176:
return info[3];
case 1073742178:
return info[5];
case 12289:
return info[6];
case 135266320:
return info[7];
case 1073741854:
case 135266319:
return ((ang == 0) == (type == 135266319) ? info[8] : null);
case 135266305:
return info[9];
case 12:
return info[10];
}
}, "JS.Symmetry,~N,~N,JS.Symmetry,~S,~N,JU.P3,JU.P3,~S,~N,JM.ModelSet");
Clazz.defineMethod (c$, "getSymmetryInfoString", 
function (sym, modelIndex, symOp, pt1, pt2, drawID, type, modelSet) {
var sginfo = this.getSpaceGroupInfo (sym, modelIndex, null, symOp, pt1, pt2, drawID, modelSet);
if (sginfo == null) return "";
var labelOnly = "label".equals (type);
var prettyMat = "fmatrix".equals (type);
var infolist = sginfo.get ("operations");
if (infolist == null) return "";
var sb =  new JU.SB ();
symOp--;
for (var i = 0; i < infolist.length; i++) {
if (infolist[i] == null || symOp >= 0 && symOp != i) continue;
if (drawID != null) return infolist[i][3];
if (sb.length () > 0) sb.appendC ('\n');
if (prettyMat) {
JS.SymmetryOperation.getPrettyMatrix (sb, infolist[i][10]);
sb.appendC ('\t');
} else if (!labelOnly) {
if (symOp < 0) sb.appendI (i + 1).appendC ('\t');
sb.append (infolist[i][0]).appendC ('\t');
}sb.append (infolist[i][2]);
}
if (sb.length () == 0 && drawID != null) sb.append ("draw " + drawID + "* delete");
return sb.toString ();
}, "JS.Symmetry,~N,~N,JU.P3,JU.P3,~S,~S,JM.ModelSet");
Clazz.defineMethod (c$, "getSpaceGroupInfo", 
function (sym, modelIndex, sgName, symOp, pt1, pt2, drawID, modelSet) {
var strOperations = null;
var info = null;
var cellInfo = null;
var infolist = null;
var isStandard = true;
if (sgName == null) {
if (modelIndex <= 0) modelIndex = (Clazz.instanceOf (pt1, JM.Atom) ? (pt1).mi : modelSet.vwr.am.cmi);
var isBio = false;
if (modelIndex < 0) strOperations = "no single current model";
 else if (!(isBio = (cellInfo = modelSet.am[modelIndex].biosymmetry) != null) && (cellInfo = modelSet.getUnitCell (modelIndex)) == null) strOperations = "not applicable";
if (strOperations != null) {
info =  new java.util.Hashtable ();
info.put ("spaceGroupInfo", strOperations);
info.put ("symmetryInfo", "");
} else if (pt1 == null && drawID == null && symOp != 0) {
info = modelSet.getInfo (modelIndex, "spaceGroupInfo");
}if (info != null) return info;
info =  new java.util.Hashtable ();
if (pt1 == null && drawID == null && symOp == 0) modelSet.setInfo (modelIndex, "spaceGroupInfo", info);
sgName = cellInfo.getSpaceGroupName ();
var ops = cellInfo.getSymmetryOperations ();
var sg = (isBio ? (cellInfo).spaceGroup : null);
var jf = "";
if (ops == null) {
strOperations = "\n no symmetry operations";
} else {
isStandard = !isBio;
if (isBio) sym.spaceGroup = (JS.SpaceGroup.getNull (false)).set (false);
 else sym.setSpaceGroup (false);
strOperations = "\n" + ops.length + " symmetry operations:";
infolist =  new Array (ops.length);
var centering = null;
for (var i = 0; i < ops.length; i++) {
var op = (ops[i]);
var xyz = op.xyz;
var iop = (isBio ? sym.addBioMoleculeOperation (sg.finalOperations[i], false) : sym.addSpaceGroupOperation ("=" + xyz, i + 1));
if (iop < 0) continue;
op = sym.getSpaceGroupOperation (i);
if (op.timeReversal != 0 || op.modDim > 0) isStandard = false;
centering = op.setCentering (centering, false);
jf += ";" + xyz;
infolist[i] = (symOp > 0 && symOp - 1 != iop ? null : this.getDescription (op, cellInfo, pt1, pt2, drawID, modelSet));
if (infolist[i] != null) strOperations += "\n" + (i + 1) + "\t" + infolist[i][0] + "\t" + infolist[i][2];
}
}jf = jf.substring (jf.indexOf (";") + 1);
if (sgName.indexOf ("[--]") >= 0) sgName = jf;
} else {
info =  new java.util.Hashtable ();
}info.put ("spaceGroupName", sgName);
if (infolist != null) {
info.put ("operations", infolist);
info.put ("symmetryInfo", strOperations);
}var data;
if (isStandard) {
data = sym.getSpaceGroupInfoStr (sgName, cellInfo);
if (data == null || data.equals ("?")) data = "could not identify space group from name: " + sgName + "\nformat: show spacegroup \"2\" or \"P 2c\" " + "or \"C m m m\" or \"x, y, z;-x ,-y, -z\"";
} else {
data = sgName;
}info.put ("spaceGroupInfo", data);
return info;
}, "JS.Symmetry,~N,~S,~N,JU.P3,JU.P3,~S,JM.ModelSet");
Clazz.defineMethod (c$, "getSymmetryInfoAtom", 
function (bsAtoms, xyz, op, pt, pt2, id, type, modelSet) {
var iModel = -1;
if (bsAtoms == null) {
iModel = modelSet.vwr.am.cmi;
if (iModel < 0) return "";
bsAtoms = modelSet.vwr.getModelUndeletedAtomsBitSet (iModel);
}var iAtom = bsAtoms.nextSetBit (0);
if (iAtom < 0) return "";
iModel = modelSet.at[iAtom].mi;
var uc = modelSet.am[iModel].biosymmetry;
if (uc == null) uc = modelSet.getUnitCell (iModel);
return (uc == null ? "" : this.getSymmetryInfo (uc, iModel, iAtom, uc, xyz, op, pt, pt2, id, type, modelSet));
}, "JU.BS,~S,~N,JU.P3,JU.P3,~S,~N,JM.ModelSet");
});
