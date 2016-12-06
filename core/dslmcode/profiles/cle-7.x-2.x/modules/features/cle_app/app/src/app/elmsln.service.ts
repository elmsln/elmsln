import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { AppSettings } from './app-settings';
import { Cookie } from 'ng2-cookies/ng2-cookies';

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
    if (!localStorage.getItem('x-csrf')) {
      this.http
        .get(AppSettings.BASE_PATH + 'restws/session/token', {headers})
        .subscribe(data => {
          // Get the CSRF Token and set it to local storage
          let token = data['_body'];
          Cookie.set('x-csrf-token', token);
          return headers;
        });
    }
    else {
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
    localStorage.removeItem('basicAuthCredentials');
    localStorage.removeItem('x-csrf');

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
    this.createAuthorizationHeader(headers);
    // this.createCSRFTokenHeader(headers);
    
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
