Clazz.declarePackage ("J.render");
Clazz.load (["J.render.CageRenderer", "JU.P3"], "J.render.AxesRenderer", null, function () {
c$ = Clazz.decorateAsClass (function () {
this.originScreen = null;
this.colixes = null;
Clazz.instantialize (this, arguments);
}, J.render, "AxesRenderer", J.render.CageRenderer);
Clazz.prepareFields (c$, function () {
this.originScreen =  new JU.P3 ();
this.colixes =  Clazz.newShortArray (3, 0);
});
Clazz.overrideMethod (c$, "initRenderer", 
function () {
this.endcap = 2;
this.draw000 = false;
});
Clazz.overrideMethod (c$, "render", 
function () {
var axes = this.shape;
var mad = this.vwr.getObjectMad (1);
if (mad == 0 || !this.g3d.checkTranslucent (false)) return false;
var isXY = (axes.axisXY.z != 0);
if (!isXY && this.tm.isNavigating () && this.vwr.getBoolean (603979889)) return false;
this.imageFontScaling = this.vwr.imageFontScaling;
if (this.vwr.areAxesTainted ()) {
var f = axes.font3d;
axes.initShape ();
if (f != null) axes.font3d = f;
}this.font3d = this.vwr.gdata.getFont3DScaled (axes.font3d, this.imageFontScaling);
var modelIndex = this.vwr.am.cmi;
var isUnitCell = (this.vwr.g.axesMode == 603979808);
if (this.vwr.ms.isJmolDataFrameForModel (modelIndex) && !this.vwr.ms.getJmolFrameType (modelIndex).equals ("plot data")) return false;
if (isUnitCell && modelIndex < 0 && this.vwr.getCurrentUnitCell () == null) return false;
var nPoints = 6;
var labelPtr = 0;
if (isUnitCell && this.ms.unitCells != null) {
nPoints = 3;
labelPtr = 6;
} else if (isXY) {
nPoints = 3;
labelPtr = 9;
} else if (this.vwr.g.axesMode == 603979810) {
nPoints = 6;
labelPtr = (this.vwr.getBoolean (603979806) ? 15 : 9);
}if (axes.labels != null) {
if (nPoints != 3) nPoints = (axes.labels.length < 6 ? 3 : 6);
labelPtr = -1;
}var isDataFrame = this.vwr.isJmolDataFrame ();
var slab = this.vwr.gdata.slab;
var diameter = mad;
var drawTicks = false;
if (isXY) {
if (this.exportType == 1) return false;
if (mad >= 20) {
diameter = (mad > 500 ? 5 : Clazz.doubleToInt (mad / 100));
if (diameter == 0) diameter = 2;
} else {
if (this.g3d.isAntialiased ()) diameter += diameter;
}this.g3d.setSlab (0);
var z = axes.axisXY.z;
this.pt0i.setT (z == 3.4028235E38 || z == -3.4028235E38 ? this.tm.transformPt2D (axes.axisXY) : this.tm.transformPt (axes.axisXY));
this.originScreen.set (this.pt0i.x, this.pt0i.y, this.pt0i.z);
var zoomDimension = this.vwr.getScreenDim ();
var scaleFactor = zoomDimension / 10 * axes.scale;
if (this.g3d.isAntialiased ()) scaleFactor *= 2;
for (var i = 0; i < 3; i++) {
this.tm.rotatePoint (axes.getAxisPoint (i, false), this.p3Screens[i]);
this.p3Screens[i].z *= -1;
this.p3Screens[i].scaleAdd2 (scaleFactor, this.p3Screens[i], this.originScreen);
}
} else {
drawTicks = (axes.tickInfos != null);
if (drawTicks) {
this.checkTickTemps ();
this.tickA.setT (axes.getOriginPoint (isDataFrame));
}this.tm.transformPtNoClip (axes.getOriginPoint (isDataFrame), this.originScreen);
diameter = this.getDiameter (Clazz.floatToInt (this.originScreen.z), mad);
for (var i = nPoints; --i >= 0; ) this.tm.transformPtNoClip (axes.getAxisPoint (i, isDataFrame), this.p3Screens[i]);

}var xCenter = this.originScreen.x;
var yCenter = this.originScreen.y;
this.colixes[0] = this.vwr.getObjectColix (1);
this.colixes[1] = this.vwr.getObjectColix (2);
this.colixes[2] = this.vwr.getObjectColix (3);
for (var i = nPoints; --i >= 0; ) {
if (isXY && axes.axisType != null && !axes.axisType.contains (J.render.AxesRenderer.axesTypes[i])) continue;
this.colix = this.colixes[i % 3];
this.g3d.setC (this.colix);
var label = (axes.labels == null ? J.render.AxesRenderer.axisLabels[i + labelPtr] : i < axes.labels.length ? axes.labels[i] : null);
if (label != null && label.length > 0) this.renderLabel (label, this.p3Screens[i].x, this.p3Screens[i].y, this.p3Screens[i].z, xCenter, yCenter);
if (drawTicks) {
this.tickInfo = axes.tickInfos[(i % 3) + 1];
if (this.tickInfo == null) this.tickInfo = axes.tickInfos[0];
this.tickB.setT (axes.getAxisPoint (i, isDataFrame));
if (this.tickInfo != null) {
this.tickInfo.first = 0;
this.tickInfo.signFactor = (i % 6 >= 3 ? -1 : 1);
}}this.renderLine (this.originScreen, this.p3Screens[i], diameter, drawTicks && this.tickInfo != null);
}
if (nPoints == 3 && !isXY) {
var label0 = (axes.labels == null || axes.labels.length == 3 || axes.labels[3] == null ? "0" : axes.labels[3]);
if (label0 != null && label0.length != 0) {
this.colix = this.vwr.cm.colixBackgroundContrast;
this.g3d.setC (this.colix);
this.renderLabel (label0, this.originScreen.x, this.originScreen.y, this.originScreen.z, xCenter, yCenter);
}}if (isXY) this.g3d.setSlab (slab);
return false;
});
Clazz.defineMethod (c$, "renderLabel", 
 function (str, x, y, z, xCenter, yCenter) {
var strAscent = this.font3d.getAscent ();
var strWidth = this.font3d.stringWidth (str);
var dx = x - xCenter;
var dy = y - yCenter;
if ((dx != 0 || dy != 0)) {
var dist = Math.sqrt (dx * dx + dy * dy);
dx = (strWidth * 0.75 * dx / dist);
dy = (strAscent * 0.75 * dy / dist);
x += dx;
y += dy;
}var xStrBaseline = Math.floor (x - strWidth / 2);
var yStrBaseline = Math.floor (y + strAscent / 2);
this.g3d.drawString (str, this.font3d, Clazz.doubleToInt (xStrBaseline), Clazz.doubleToInt (yStrBaseline), Clazz.floatToInt (z), Clazz.floatToInt (z), 0);
}, "~S,~N,~N,~N,~N,~N");
Clazz.defineStatics (c$,
"axisLabels",  Clazz.newArray (-1, ["+X", "+Y", "+Z", null, null, null, "a", "b", "c", "X", "Y", "Z", null, null, null, "X", null, "Z", null, "(Y)", null]),
"axesTypes",  Clazz.newArray (-1, ["a", "b", "c"]));
});
