declare const Drupal:any;

export class AppSettings {
  public static get BASE_PATH(): string { 
    if (typeof Drupal !== 'undefined') {
      return Drupal.settings;
    }
    else {
      return 'http://studio.elmsln.local/studio2/';
    }
  }
}
