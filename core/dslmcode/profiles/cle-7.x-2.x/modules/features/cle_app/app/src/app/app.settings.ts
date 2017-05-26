declare const Drupal:any;

export class AppSettings {
  public static get BASE_PATH(): string { 
    if (typeof Drupal !== 'undefined') {
      return Drupal.settings.basePath;
    }
    else {
      return 'http://studio.elmsln.local/heymp/';
    }
  }

  public static get USERNAME(): string {
    return 'mgp140';
  }

  public static get PASSWORD(): string {
    return 'root';
  }
}
