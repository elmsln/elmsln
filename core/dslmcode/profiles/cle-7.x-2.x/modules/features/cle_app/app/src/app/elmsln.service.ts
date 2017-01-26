import { Injectable } from '@angular/core';
import { Http, Headers, Response, RequestOptions } from '@angular/http';
import { AppSettings } from './app-settings';
import { Cookie } from 'ng2-cookies/ng2-cookies';
import {Observable} from "rxjs";
import { Store } from '@ngrx/store';
declare const Drupal:any;

@Injectable()
export class ElmslnService {

  constructor(
    private http: Http,
    private store: Store<{}>
  ) { }

  createAuthorizationHeader(headers:Headers) {
    let basicAuthCredentials =  Cookie.get('basicAuthCredentials');
    if (basicAuthCredentials) {
      headers.append('Authorization', 'Basic ' + basicAuthCredentials);
    }
  }

  createCSRFTokenHeader(headers:Headers) {
    this.store.select('user')
      .map((state:any) => state.token)
      .subscribe(
        (token) => {
          headers.append('x-csrf-token', token);
          return headers;
        }
      )
  }


  login() {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);

    return true;
  }

  logout() {
    Cookie.delete('basicAuthCredentials');
    // localStorage.clear();

    return true;
  }

  get(url) {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    // this.createCSRFTokenHeader(headers);

    return this.http.get(url, {
      headers: headers
    });
  }

  post(url, data) {
    let headers = new Headers();
    headers.append('Accept', 'application/json');
    headers.append('Content-Type', 'application/json');
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);

    console.log('Post headers ', headers);
    
    return this.http.post(url, data, {
      headers: headers
    });
  }

  put(url, data) {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);

    return this.http.put(url, data, {
      headers: headers
    })
  }

  delete(url) {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);

    return this.http.delete(url, {
      headers: headers
    })
  }

  getUserProfile() {
    return this.get(AppSettings.BASE_PATH + 'api/v1/elmsln/user')
      .map(data => data.json())
  }

  /**
   * Create a file entity from base64 image
   */
  createImage(image) {
    const body = {
      name: 'default-image-name',
      type: 'image',
      /**
       * @todo need to add logic to to specify whether the user uploaded images
       *       file path's are public or private.
       */
      file_wrapper: 'public',
      data: image
    }
    return this.post(AppSettings.BASE_PATH + 'api/v1/elmsln/files/create', body)
      .map(data => data.json().file)
  }

  // helper to execute callbacks that are located in an objects like nodes and user
  evalCallbacks(object:any):void {
    try {
      if (object.environment.callbacks) {
        let callbacks:string[] = object.environment.callbacks;
        callbacks
          .map(callback => {
            eval(callback);
          })
      }
    }catch(e){}
  }

  exportLifecycleHook(componentName:string):void {
    if (typeof Drupal !== 'undefined') {
      Drupal.settings.cleApp = Drupal.settings.cleApp || {};
      Drupal.settings.cleApp.callbacks = Drupal.settings.cleApp.callbacks || {};
      if (typeof Drupal.settings.cleApp.callbacks[componentName] === 'function') {
        let callback:any = Drupal.settings.cleApp.callbacks[componentName];
        callback();
      }
    }
  }
}
