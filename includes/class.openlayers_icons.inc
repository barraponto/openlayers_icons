<?php
/**
 * @file class.openlayers_icons.inc
 * Class for dynamically generated custom icons as OpenLayers 2.x styles
 * This allows us to use virtually any properly sized icon for open layer maps.
 */

class openlayersIcons {

  //When we are done with our object, or do not reference it anymore PHP will automatically try and kill it off from memory if we have this set.
  function __destruct() {
    //Unset from memory.
    unset($this);
  }

  /**
   * @name _scanImages()
   * Scans images in the modules images directory for a list of icons to create template files.
   */
  public static function _scanImages() {
    //Icon templates, thanks MAKI for the roadmap!
    $icon_templates = array();
    //Check the base directory for permissions.
    $directory = OPENLAYERS_ICONS_IMAGES_DIRECTORY;
    file_check_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
    //Find all the icons in our images directory, only PNG are allowed!
    $icons = file_scan_directory($directory, '.png');
    //Sort file names alpha
    ksort($icons);
    //Convert the icons into a template that open layers understands.
    foreach ($icons as $key => $icon) {
      //Convert hte file name and then make our array pieces. Sanitize titles from image names.
      $title = t('@name',array('@name' => ucwords(ereg_replace('[^A-Za-z0-9]', ' ', $icon->name))));
      //Get the info for this image.
      $info  = image_get_info($icon->filename);
      if (!empty($info['width']) && !empty($info['height'])) {
        //If we have image info, we know we have a good image to use, so then let it pass!
        $icon_templates[] = array(
          'title'    => $title,
          'name'     => $icon->name,
          'basename' => $icon->basename,
          'url'      => $icon->filename,
          'info'     => $info,
        );
      }
    }
    //Return templates.
    return $icon_templates;
  }

}