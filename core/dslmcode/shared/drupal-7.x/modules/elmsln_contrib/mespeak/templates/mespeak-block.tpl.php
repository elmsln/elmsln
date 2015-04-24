<form id="speakData" onsubmit="meSpeak.speak(speakText.value, { amplitude: amplitude.value, wordgap: wordgap.value, pitch: pitch.value, speed: speed.value, variant: variant.options[variant.selectedIndex].value }); return false">
  <p><strong>Text:</strong>
<textarea id="speakText" name="speakText"></textarea>
  <input type="submit" value="Go!" />
  <input type="button" value="Stop" onclick="meSpeak.stop(); return true;" /></p>
  <p><strong>Options:</strong>
  Amplitude: <input type="text" name="amplitude" size=5 value="100" />
  Pitch: <input type="text" name="pitch" size=5 value="50" />
  Speed: <input type="text" name="speed" size=5 value="175" />
  Word gap: <input type="text" name="wordgap" size=5 value="0" />
  Variant: <select name="variant" id="variantSelect">
    <option value="">None</option>
    <option value="f1">f1 (female 1)</option>
    <option value="f2">f2 (female 2)</option>
    <option value="f3">f3 (female 3)</option>
    <option value="f4">f4 (female 4)</option>
    <option value="f5">f5 (female 5)</option>
    <option value="m1">m1 (male 1)</option>
    <option value="m2">m2 (male 2)</option>
    <option value="m3">m3 (male 3)</option>
    <option value="m4">m4 (male 4)</option>
    <option value="m5">m5 (male 5)</option>
    <option value="m6">m6 (male 6)</option>
    <option value="m7">m7 (male 7)</option>
    <option value="croak">croak</option>
    <option value="klatt">klatt</option>
    <option value="klatt2">klatt2</option>
    <option value="klatt3">klatt3</option>
    <option value="whisper"  selected="selected">whisper</option>
    <option value="whisperf">whisperf (female)</option>
  </select></p>
</form>
<form onsubmit="return false">
  <p><strong>Voice:</strong> <select id="voiceSelect"  onchange="mespeak.loadVoice(this.options[this.selectedIndex].value);">
    <option value="ca">ca - Catalan</option>
  <option value="cs">cs - Czech</option>
  <option value="de">de - German</option>
  <option value="el">el - Greek</option>
  <option value="en/en">en - English</option>
  <option value="en/en-n"  selected="selected">en-n - English, regional</option>
  <option value="en/en-rp">en-rp - English, regional</option>
  <option value="en/en-sc">en-sc - English, Scottish</option>
  <option value="en/en-us">en-us - English, US</option>
  <option value="en/en-wm">en-wm - English, regional</option>
  <option value="eo">eo - Esperanto</option>
  <option value="es">es - Spanish</option>
  <option value="es-la">es-la - Spanish, Latin America</option>
  <option value="fi">fi - Finnish</option>
  <option value="fr">fr - French</option>
  <option value="hu">hu - Hungarian</option>
  <option value="it">it - Italian</option>
  <option value="kn">kn - Kannada</option>
  <option value="la">la - Latin</option>
  <option value="lv">lv - Latvian</option>
  <option value="nl">nl - Dutch</option>
  <option value="pl">pl - Polish</option>
  <option value="pt">pt - Portuguese, Brazil</option>
  <option value="pt-pt">pt-pt - Portuguese, European</option>
  <option value="ro">ro - Romanian</option>
  <option value="sk">sk - Slovak</option>
  <option value="sv">sv - Swedish</option>
  <option value="tr">tr - Turkish</option>
  <option value="zh">zh - Mandarin Chinese (Pinyin)</option>
  <option value="zh-yue">zh-yue - Cantonese Chinese</option>
</select></p>
</form>
