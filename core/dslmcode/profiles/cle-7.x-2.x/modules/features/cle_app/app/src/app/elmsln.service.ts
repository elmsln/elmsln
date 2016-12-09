import { Injectable } from '@angular/core';
import { Http, Headers, Response, RequestOptions } from '@angular/http';
import { AppSettings } from './app-settings';
import { Cookie } from 'ng2-cookies/ng2-cookies';
declare const Drupal:any;

@Injectable()
export class ElmslnService {

  constructor(
    private http: Http
  ) { }

  createAuthorizationHeader(headers:Headers) {
    let basicAuthCredentials =  Cookie.get('basicAuthCredentials');
    if (basicAuthCredentials) {
      headers.append('Authorization', 'Basic ' + basicAuthCredentials);
    }
  }

  createCSRFTokenHeader(headers:Headers) {
    let csrftoken = Cookie.get('x-csrf-token');
    console.log('Current CSRF Token ', csrftoken);
    if (!csrftoken) {
      this.http
        .get(AppSettings.BASE_PATH + 'restws/session/token', {headers})
        .subscribe(data => {
          // Get the CSRF Token and set it to local storage
          console.log('Got the CSRF Token ', data);
          let token = data['_body'];
          Cookie.set('x-csrf-token', token);
          headers.append('x-csrf-token', token);
          return headers;
        });
    }
    else {
      headers.append('x-csrf-token', csrftoken);
      return headers;
    }
  }

  login() {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);

    return true;
  }

  logout() {
    Cookie.delete('x-csrf-token');
    Cookie.delete('basicAuthCredentials');

    return true;
  }

  get(url) {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);

    return this.http.get(url, {
      headers: headers
    });
  }

  post(url, data) {
    let headers = new Headers();
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
}
