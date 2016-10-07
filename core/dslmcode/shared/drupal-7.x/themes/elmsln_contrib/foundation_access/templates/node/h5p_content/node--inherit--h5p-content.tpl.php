<?php if (isset($content['field_figurelabel_ref'])): ?>
  <?php print render($content['field_figurelabel_ref'][0]); ?>
<?php endif; ?>
  <iframe id="node_<?php print $nid;?>" class="entity_iframe entity_iframe_node entity_iframe_tool_elmsmedia elmsmedia_h5p_content" src="<?php print $iframe_path; ?>" width="100%" frameborder="0" allowfullscreen="true" webkitallowfullscreen="true" mozallowfullscreen="true"></iframe>