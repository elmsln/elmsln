import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { AppSettings } from './app-settings';

@Injectable()
export class ElmslnService {

  constructor(private http: Http) { }

  createAuthorizationHeader(headers:Headers) {
    let basicAuthCredentials =  localStorage.getItem('basicAuthCredentials');
    if (basicAuthCredentials) {
      headers.append('Authorization', 'Basic ' + basicAuthCredentials);
    }
  }

  createCSRFTokenHeader(headers:Headers) {
    if (!localStorage.getItem('x-csrf')) {
      return this.http
        .get(AppSettings.BASE_PATH + 'restws/session/token', {headers})
        .subscribe(data => {
          // Get the CSRF Token and set it to local storage
          localStorage.setItem('x-csrf', data.json());
        });
    }
    headers.append('x-csrf-token', localStorage.getItem('x-csrf'));
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
    this.createCSRFTokenHeader(headers);

    return this.http.get(url, {
      headers: headers
    });
  }

  post(url, data) {
    let headers = new Headers();
    this.createAuthorizationHeader(headers);
    this.createCSRFTokenHeader(headers);
    
    return this.http.post(url, data, {
      headers: headers
    });
  }
}
