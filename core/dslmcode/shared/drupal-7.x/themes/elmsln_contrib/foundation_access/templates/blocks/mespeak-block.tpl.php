<form id="speakData">
<textarea id="speakText" name="speakText" style="display:none;"></textarea>
  <label for="variant">Voice</label>
  <select name="variant" id="variantSelect">
    <option value="whisper" selected="selected">Male</option>
    <option value="f5">Female</option>
    <option value="whisperf">Robot</option>
  </select>
  <input type="button" value="Speak" onclick="meSpeak.speak(speakText.value, { amplitude: amplitude.value, wordgap: wordgap.value, pitch: pitch.value, speed: speed.value, variant: variant.options[variant.selectedIndex].value }); return true;" />
  <input type="button" value="Stop" onclick="meSpeak.stop(); return true;" />

  <input type="hidden" name="amplitude" size=5 value="100" />
  <input type="hidden" name="pitch" size=5 value="50" />
  <input type="hidden" name="speed" size=5 value="175" />
  <input type="hidden" name="wordgap" size=5 value="0" />
</form>
<form onsubmit="return false" style="display:none;">
  <select id="voiceSelect"  onchange="mespeak.loadVoice(this.options[this.selectedIndex].value);">
    <option value="en/en">en - English</option>
  </select>
</form>
