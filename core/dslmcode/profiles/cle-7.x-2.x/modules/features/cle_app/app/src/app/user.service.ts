import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { AppSettings } from './app-settings';

@Injectable()
export class UserService {
  private loggedIn = false;

  constructor(private http: Http) {
    this.loggedIn = !!localStorage.getItem('x-csrf');
  }

  login() {
    let headers = new Headers();
    headers.append('Content-type', 'application/json');

    return this.http
      .post(AppSettings.BASE_PATH + 'restws/session/token', {headers})
      .subscribe(data => {
        // Get the CSRF Token and set it to local storage
        localStorage.setItem('x-csrf', data._body);
        // log the user in
        this.loggedIn = true;
      });
  }

  getUsers(): Observable<any> {
    return this.http.get('app/mocks/users.json')
      .map(data => data.json().list);
  }
}
