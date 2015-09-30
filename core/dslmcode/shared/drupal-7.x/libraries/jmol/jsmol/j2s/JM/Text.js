Clazz.declarePackage ("JM");
Clazz.load (["JM.Object2d"], "JM.Text", ["javajs.awt.Font", "JU.PT", "J.shape.Shape", "JU.Txt", "JV.JC"], function () {
c$ = Clazz.decorateAsClass (function () {
this.textUnformatted = null;
this.doFormatText = false;
this.lines = null;
this.font = null;
this.fid = 0;
this.ascent = 0;
this.descent = 0;
this.lineHeight = 0;
this.offsetX = 0;
this.offsetY = 0;
this.textWidth = 0;
this.textHeight = 0;
this.text = null;
this.widths = null;
this.vwr = null;
this.image = null;
this.imageScale = 1;
this.boxYoff2 = 0;
this.xAdj = 0;
this.yAdj = 0;
this.y0 = 0;
this.pointerPt = null;
Clazz.instantialize (this, arguments);
}, JM, "Text", JM.Object2d);
Clazz.defineMethod (c$, "getText", 
function () {
return this.text;
});
Clazz.defineMethod (c$, "setOffset", 
function (offset) {
this.offsetX = JV.JC.getXOffset (offset);
this.offsetY = JV.JC.getYOffset (offset);
this.pymolOffset = null;
this.valign = 3;
}, "~N");
Clazz.makeConstructor (c$, 
 function (vwr) {
this.vwr = vwr;
this.boxXY =  Clazz.newFloatArray (5, 0);
}, "JV.Viewer");
c$.newLabel = Clazz.defineMethod (c$, "newLabel", 
function (vwr, font, text, colix, bgcolix, align, scalePixelsPerMicron, value) {
var t =  new JM.Text (vwr);
t.set (font, colix, align, true, scalePixelsPerMicron, value);
t.setText (text);
t.bgcolix = bgcolix;
return t;
}, "JV.Viewer,javajs.awt.Font,~S,~N,~N,~N,~N,~A");
c$.newEcho = Clazz.defineMethod (c$, "newEcho", 
function (vwr, font, target, colix, valign, align, scalePixelsPerMicron) {
JM.Text.isEcho = true;
var t =  new JM.Text (vwr);
t.set (font, colix, align, false, scalePixelsPerMicron, null);
t.target = target;
if (target.equals ("error")) valign = 0;
t.valign = valign;
t.z = 2;
t.zSlab = -2147483648;
return t;
}, "JV.Viewer,javajs.awt.Font,~S,~N,~N,~N,~N");
Clazz.defineMethod (c$, "set", 
 function (font, colix, align, isLabelOrHover, scalePixelsPerMicron, value) {
this.scalePixelsPerMicron = scalePixelsPerMicron;
this.isLabelOrHover = isLabelOrHover;
this.colix = colix;
this.align = align;
this.pymolOffset = value;
this.setFont (font, isLabelOrHover);
}, "javajs.awt.Font,~N,~N,~B,~N,~A");
Clazz.defineMethod (c$, "getFontMetrics", 
 function () {
this.descent = this.font.getDescent ();
this.ascent = this.font.getAscent ();
this.lineHeight = this.ascent + this.descent;
});
Clazz.defineMethod (c$, "setFontFromFid", 
function (fid) {
if (this.fid == fid) return;
this.fontScale = 0;
this.setFont (javajs.awt.Font.getFont3D (fid), true);
}, "~N");
Clazz.defineMethod (c$, "setText", 
function (text) {
if (this.image != null) this.getFontMetrics ();
this.image = null;
if (text != null && text.length == 0) text = null;
if (this.text != null && this.text.equals (text)) return;
this.text = text;
this.textUnformatted = text;
this.doFormatText = (JM.Text.isEcho && text != null && (text.indexOf ("%{") >= 0 || text.indexOf ("@{") >= 0));
if (!this.doFormatText) this.recalc ();
}, "~S");
Clazz.defineMethod (c$, "setImage", 
function (image) {
this.image = image;
this.recalc ();
}, "~O");
Clazz.defineMethod (c$, "setScale", 
function (scale) {
this.imageScale = scale;
this.recalc ();
}, "~N");
Clazz.defineMethod (c$, "setFont", 
function (f3d, doAll) {
this.font = f3d;
if (this.font == null) return;
this.getFontMetrics ();
if (!doAll) return;
this.fid = this.font.fid;
this.recalc ();
}, "javajs.awt.Font,~B");
Clazz.defineMethod (c$, "setFontScale", 
function (scale) {
if (this.fontScale == scale) return;
this.fontScale = scale;
if (this.fontScale != 0) this.setFont (this.vwr.gdata.getFont3DScaled (this.font, scale), true);
}, "~N");
Clazz.overrideMethod (c$, "recalc", 
function () {
if (this.image != null) {
this.textWidth = this.textHeight = 0;
this.boxWidth = this.vwr.apiPlatform.getImageWidth (this.image) * this.fontScale * this.imageScale;
this.boxHeight = this.vwr.apiPlatform.getImageHeight (this.image) * this.fontScale * this.imageScale;
this.ascent = 0;
return;
}if (this.text == null) {
this.text = null;
this.lines = null;
this.widths = null;
return;
}if (this.font == null) return;
this.lines = JU.PT.split (this.text, (this.text.indexOf ("\n") >= 0 ? "\n" : "|"));
this.textWidth = 0;
this.widths =  Clazz.newIntArray (this.lines.length, 0);
for (var i = this.lines.length; --i >= 0; ) this.textWidth = Math.max (this.textWidth, this.widths[i] = this.stringWidth (this.lines[i]));

this.textHeight = this.lines.length * this.lineHeight;
this.boxWidth = this.textWidth + (this.fontScale >= 2 ? 16 : 8);
this.boxHeight = this.textHeight + (this.fontScale >= 2 ? 16 : 8);
});
Clazz.defineMethod (c$, "formatText", 
function () {
this.text = (JM.Text.isEcho ? JU.Txt.formatText (this.vwr, this.textUnformatted) : this.textUnformatted);
this.recalc ();
});
Clazz.defineMethod (c$, "setPosition", 
function (scalePixelsPerMicron, imageFontScaling, isAbsolute, boxXY) {
if (boxXY == null) boxXY = this.boxXY;
 else this.boxXY = boxXY;
this.setWindow (this.vwr.gdata.width, this.vwr.gdata.height, scalePixelsPerMicron);
if (scalePixelsPerMicron != 0 && this.scalePixelsPerMicron != 0) this.setFontScale (scalePixelsPerMicron / this.scalePixelsPerMicron);
 else if (this.fontScale != imageFontScaling) this.setFontScale (imageFontScaling);
if (this.doFormatText) this.formatText ();
var dx = this.offsetX * imageFontScaling;
var dy = this.offsetY * imageFontScaling;
this.xAdj = (this.fontScale >= 2 ? 8 : 4);
this.yAdj = this.ascent - this.lineHeight + this.xAdj;
if (this.isLabelOrHover) {
boxXY[0] = this.movableX;
boxXY[1] = this.movableY;
if (this.pymolOffset != null) {
var pixelsPerAngstrom = this.vwr.tm.scaleToScreen (this.z, 1000);
var pz = this.pymolOffset[3];
var dz = (pz < 0 ? -1 : 1) * Math.max (0, Math.abs (pz) - 1) * pixelsPerAngstrom;
this.z -= Clazz.floatToInt (dz);
pixelsPerAngstrom = this.vwr.tm.scaleToScreen (this.z, 1000);
dx = this.getPymolXYOffset (this.pymolOffset[1], this.textWidth, pixelsPerAngstrom);
dy = -this.getPymolXYOffset (-this.pymolOffset[2], this.ascent - this.descent, pixelsPerAngstrom);
this.xAdj = (this.fontScale >= 2 ? 8 : 4);
this.yAdj = 0;
dy += this.descent;
boxXY[0] = this.movableX - this.xAdj;
boxXY[1] = this.movableY - this.yAdj;
this.y0 = this.movableY - dy - this.descent;
isAbsolute = true;
this.boxYoff2 = -2;
} else {
this.boxYoff2 = 0;
}JM.Text.setBoxXY (this.boxWidth, this.boxHeight, dx, dy, boxXY, isAbsolute);
} else {
this.setPos (this.fontScale);
}this.boxX = boxXY[0];
this.boxY = boxXY[1];
if (this.adjustForWindow) this.setBoxOffsetsInWindow (0, this.isLabelOrHover ? 16 * this.fontScale + this.lineHeight : 0, this.boxY - this.textHeight);
this.y0 = this.boxY + this.yAdj;
}, "~N,~N,~B,~A");
Clazz.defineMethod (c$, "getPymolXYOffset", 
 function (off, width, ppa) {
var f = (off < -1 ? -1 : off > 1 ? 0 : (off - 1) / 2);
off = (off < -1 || off > 1 ? off + (off < 0 ? 1 : -1) : 0);
return f * width + off * ppa;
}, "~N,~N,~N");
Clazz.defineMethod (c$, "setPos", 
 function (scale) {
var xLeft;
var xCenter;
var xRight;
var is3dEcho = (this.xyz != null);
if (this.valign == 3 || this.valign == 4) {
var x = (this.movableXPercent != 2147483647 ? Clazz.doubleToInt (this.movableXPercent * this.windowWidth / 100) : is3dEcho ? this.movableX : this.movableX * scale);
var offsetX = this.offsetX * scale;
xLeft = xRight = xCenter = x + offsetX;
} else {
xLeft = 5 * scale;
xCenter = Clazz.doubleToInt (this.windowWidth / 2);
xRight = this.windowWidth - xLeft;
}this.boxXY[0] = xLeft;
switch (this.align) {
case 8:
this.boxXY[0] = xCenter - this.boxWidth / 2;
break;
case 12:
this.boxXY[0] = xRight - this.boxWidth;
}
this.boxXY[1] = 0;
switch (this.valign) {
case 0:
break;
case 2:
this.boxXY[1] = Clazz.doubleToInt (this.windowHeight / 2);
break;
case 1:
this.boxXY[1] = this.windowHeight;
break;
default:
var y = (this.movableYPercent != 2147483647 ? Clazz.doubleToInt (this.movableYPercent * this.windowHeight / 100) : is3dEcho ? this.movableY : this.movableY * scale);
this.boxXY[1] = (is3dEcho ? y : (this.windowHeight - y)) + this.offsetY * scale;
}
if (this.align == 8) this.boxXY[1] -= (this.image != null ? this.boxHeight : this.xyz != null ? this.boxHeight : this.ascent - this.boxHeight) / 2;
 else if (this.image != null) this.boxXY[1] -= 0;
 else if (this.xyz != null) this.boxXY[1] -= Clazz.doubleToInt (this.ascent / 2);
}, "~N");
c$.setBoxXY = Clazz.defineMethod (c$, "setBoxXY", 
function (boxWidth, boxHeight, xOffset, yOffset, boxXY, isAbsolute) {
var xBoxOffset;
var yBoxOffset;
if (xOffset > 0 || isAbsolute) {
xBoxOffset = xOffset;
} else {
xBoxOffset = -boxWidth;
if (xOffset == 0) xBoxOffset /= 2;
 else xBoxOffset += xOffset;
}if (isAbsolute || yOffset > 0) {
yBoxOffset = -boxHeight - yOffset;
} else if (yOffset == 0) {
yBoxOffset = -boxHeight / 2;
} else {
yBoxOffset = -yOffset;
}boxXY[0] += xBoxOffset;
boxXY[1] += yBoxOffset;
boxXY[2] = boxWidth;
boxXY[3] = boxHeight;
}, "~N,~N,~N,~N,~A,~B");
Clazz.defineMethod (c$, "stringWidth", 
 function (str) {
var w = 0;
var f = 1;
var subscale = 1;
if (str == null) return 0;
if (str.indexOf ("<su") < 0 && str.indexOf ("<color") < 0) return this.font.stringWidth (str);
var len = str.length;
var s;
for (var i = 0; i < len; i++) {
if (str.charAt (i) == '<') {
if (i + 8 <= len && (str.substring (i, i + 7).equals ("<color ") || str.substring (i, i + 8).equals ("</color>"))) {
var i1 = str.indexOf (">", i);
if (i1 >= 0) {
i = i1;
continue;
}}if (i + 5 <= len && ((s = str.substring (i, i + 5)).equals ("<sub>") || s.equals ("<sup>"))) {
i += 4;
f = subscale;
continue;
}if (i + 6 <= len && ((s = str.substring (i, i + 6)).equals ("</sub>") || s.equals ("</sup>"))) {
i += 5;
f = 1;
continue;
}}w += this.font.stringWidth (str.substring (i, i + 1)) * f;
}
return w;
}, "~S");
Clazz.defineMethod (c$, "setXYA", 
function (xy, i) {
if (i == 0) {
xy[2] = this.boxX;
switch (this.align) {
case 8:
xy[2] += this.boxWidth / 2;
break;
case 12:
xy[2] += this.boxWidth - this.xAdj;
break;
default:
xy[2] += this.xAdj;
}
xy[0] = xy[2];
xy[1] = this.y0;
}switch (this.align) {
case 8:
xy[0] = xy[2] - Clazz.doubleToInt (this.widths[i] / 2);
break;
case 12:
xy[0] = xy[2] - this.widths[i];
}
xy[1] += this.lineHeight;
}, "~A,~N");
Clazz.defineMethod (c$, "appendFontCmd", 
function (s) {
s.append ("  " + J.shape.Shape.getFontCommand ("echo", this.font));
if (this.scalePixelsPerMicron > 0) s.append (" " + (10000 / this.scalePixelsPerMicron));
}, "JU.SB");
Clazz.defineStatics (c$,
"isEcho", false);
});
