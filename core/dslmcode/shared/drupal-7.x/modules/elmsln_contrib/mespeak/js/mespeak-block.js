(function ($) {
  $(document).ready(function(){
    $('#speakText').html($(Drupal.settings.mespeak.selector).html().replace(/<\/?[^>]+>/gi, '').trim());
    meSpeak.loadConfig(Drupal.settings.mespeak.path + "mespeak_config.json");
    meSpeak.loadVoice(Drupal.settings.mespeak.path + "voices/en/en.json");

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
  });
})(jQuery);