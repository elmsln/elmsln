<script type="text/javascript">
(function ($) {
  $(document).ready(function(){
    $('#speakText').html($(Drupal.settings.mespeak.selector).html().replace(/<\/?[^>]+>/gi, '').trim());
    meSpeak.loadConfig(Drupal.settings.mespeak.path + "mespeak_config.json");
    meSpeak.loadVoice(Drupal.settings.mespeak.path + "voices/en/en.json");

    function loadVoice(id) {
      var fname="voices/"+id+".json";
      meSpeak.loadVoice(fname, voiceLoaded);
    }

    function voiceLoaded(success, message) {
      if (success) {
        alert("Voice loaded: "+message+".");
      }
      else {
        alert("Failed to load a voice: "+message);
      }
    }

    /*
      auto-speak glue:
      additional functions for generating a link and parsing any url-params provided for auto-speak
    */

    var formFields = ['text','amplitude','wordgap','pitch','speed'];

    function autoSpeak() {
      // checks url for speech params, sets and plays them, if found.
      // also adds eventListeners to update a link with those params using current values
      var i,l,n,params,pairs,pair,
          speakNow=null,
          useDefaultVoice=true,
          q=document.location.search,
          f=document.getElementById('speakData'),
          s1=document.getElementById('variantSelect'),
          s2=document.getElementById('voiceSelect');
      if (!f || !s2) return; // form and/or select not found
      if (q.length>1) {
        // parse url-params
        params={};
        pairs=q.substring(1).split('&');
        for (i=0, l=pairs.length; i<l; i++) {
          pair=pairs[i].split('=');
          if (pair.length==2) params[pair[0]]=decodeURIComponent(pair[1]);
        }
        // insert params into the form or complete them from defaults in form
        for (i=0, l=formFields.length; i<l; i++) {
          n=formFields[i];
          if (params[n]) {
            f.elements[n].value=params[n];
          }
          else {
            params[n]=f.elements[n].value;
          }
        }
        if (params.variant) {
          for (i=0, l=s1.options.length; i<l; i++) {
            if (s1.options[i].value==params.variant) {
              s1.selectedIndex=i;
              break;
            }
          }
        }
        else {
          params.variant='';
        }
        // compile a function to speak with given params for later use
        // play only, if param "auto" is set to "true" or "1"
        if (params.auto=='true' || params.auto=='1') {
          speakNow = function() {
            meSpeak.speak(params.text, {
              amplitude: params.amplitude,
              wordgap: params.wordgap,
              pitch: params.pitch,
              speed: params.speed,
              variant: params.variant
            });
          };
        }
        // check for any voice specified by the params (other than the default)
        if (params.voice && params.voice!=s2.options[s2.selectedIndex].value) {
          // search selected voice in selector
          for (i=0, l=s2.options.length; i<l; i++) {
            if (s2.options[i].value==params.voice) {
              // voice found: adjust the form, load voice-data and provide a callback to speak
              s2.selectedIndex=i;
              meSpeak.loadVoice('voices/'+params.voice+'.json', function(success, message) {
                if (success) {
                  if (speakNow) speakNow();
                }
                else {
                  if (window.console) console.log('Failed to load requested voice: '+message);
                }
              });
              useDefaultVoice=false;
              break;
            }
          }
        }
        // standard voice: speak (deferred until config is loaded)
        if (speakNow && useDefaultVoice) speakNow();
      }
      // initial url-processing done, add eventListeners for updating the link
      for (i=0, l=formFields.length; i<l; i++) {
        f.elements[formFields[i]].addEventListener('change', updateSpeakLink, false);
      }
      s1.addEventListener('change', updateSpeakLink, false);
      s2.addEventListener('change', updateSpeakLink, false);
      // finally, inject a link with current values into the page
      updateSpeakLink();
    }

    function updateSpeakLink() {
      // injects a link for auto-execution using current values into the page
      var i,l,n,f,s,v,url,el,params=new Array();
      // collect values from form
      f=document.getElementById('speakData');
      for (i=0, l=formFields.length; i<l; i++) {
        n=formFields[i];
        params.push(n+'='+encodeURIComponent(f.elements[n].value));
      }
      // get variant
      s=document.getElementById('variantSelect');
      if (s.selectedIndex>=0) params.push('variant='+s.options[s.selectedIndex].value);
      // get current voice, default to 'en/en' as a last resort
      s=document.getElementById('voiceSelect');
      if (s.selectedIndex>=0) v=s.options[s.selectedIndex].value;
      if (!v) v=meSpeak.getDefaultVoice() || 'en/en';
      params.push('voice='+encodeURIComponent(v));
      params.push('auto=true');
      // assemble the url and add it as GET-link to the page
      url='?'+params.join('&');
      url=url.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;').replace(/\"/g, '&quot;');
      el=document.getElementById('linkdisplay');
      if (el) el.innerHTML='Instant Link: <a href="'+url+'">Speak this</a>.';
    }

    // trigger auto-speak at DOMContentLoaded
    if (document.addEventListener) document.addEventListener( "DOMContentLoaded", autoSpeak, false );

    /*
      end of auto-speak glue
    */
  });
})(jQuery);
  </script>

<style type="text/css">
  body {max-width: 1000px; }
  h3 { margin-top: 2em; }
  form p
  {
    margin-top: 0.5em;
    margin-bottom: 0.5em;
  }
  p.codesample
  {
    margin: 1em 0;
    padding: 1em 0 1em 2em;
    white-space: pre;
    font-family: monospace;
    line-height: 120%;
    background-color: #f2f2f2;
  }
  p.codesample strong { color: #111; }
  hr.separator
  {
    margin-top: 2em;
    margin-bottom: 2em;
  }
  blockquote.note
  {
    margin-left: 2em;
    font-size: 90%;
  }
  a.noteLink { text-decoration: none; }
  ul.bottomMargin li { margin-bottom: 0.2em; }
  dl.history dt
  {
    font-weight: normal;
    font-variant: normal;
    float: left;
    vertical-align: top;
    clear: both;
  }
  dl.history dd
  {
    vertical-align: top;
    margin-left: 3.5em;
    margin-bottom: 0.3em;
  }
  table.opttable { margin-left: 2em; }
  table.opttable td { white-space: nowrap; }
  table.opttable td:first-child { padding-right: 1.5em; }
  p.history_codesample
  {
    padding: 1em;
    white-space: pre;
    font-family: monospace;
    font-size: 90%;
    line-height: 120%;
    background-color: #eee;
  }
  p.history_codesample span.comment { color: #555; }
</style>
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
      <option value="" selected>None</option>
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
      <option value="whisper">whisper</option>
      <option value="whisperf">whisperf (female)</option>
    </select></p>
  </form>
  <form onsubmit="return false">
    <p><strong>Voice:</strong> <select id="voiceSelect"  onchange="loadVoice(this.options[this.selectedIndex].value);">
      <option value="ca">ca - Catalan</option>
    <option value="cs">cs - Czech</option>
    <option value="de">de - German</option>
    <option value="el">el - Greek</option>
    <option value="en/en" selected="selected">en - English</option>
    <option value="en/en-n">en-n - English, regional</option>
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
