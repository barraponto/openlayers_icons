<?php
// $Id: openlayers_icons.styles.inc,v 1.3 2010/03/12 18:56:25 tmcw Exp $

/**
 * @file
 * Definition for Maki icons as OpenLayers 2.x styles
 */

function _openlayers_icons_openlayers_styles() {
  global $base_url;
  //kpr($base_url);
  //Clear the styles array, so we can always start a fresh implementation.
  $styles = array();
  //Icon templates are just an array of icons and their names.
  $icon_templates = variable_get('openlayers_icons_icon_templates', NULL);
  if (!empty($icon_templates)) {
    //Loop through icon templates.
    foreach ($icon_templates as $icon_title => $icon_template) {
      //Create our style class here.
      //Make sure the image path is absolute for jscript.
      $icon_template['url'] = $base_url .'/' .$icon_template['url'];
      //Create style.
      $style              = new stdClass();
      $style->api_version = 1;
      $style->name        = $icon_template['name'];
      $style->title       = $icon_template['title'];
      $style->description = t('!image', array('!image' => theme('image', $icon_template['url'], $icon_template['title'], $icon_template['title'], array('class' => 'openlayers_icon'), FALSE)));
      $style->data        = array(
        'fillOpacity'     => 1,
        'externalGraphic' => $icon_template['url'],
        'graphicWidth'    => $icon_template['info']['width'],
        'graphicheight'   => $icon_template['info']['height'],
      );
      $styles[ereg_replace('[^A-Za-z0-9]', '_', $style->name)] = $style;
    }
  }
  //kpr($styles);
  return $styles;
}