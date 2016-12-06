import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { AppSettings } from './app-settings';
import { ElmslnService } from './elmsln.service';
import { Cookie } from 'ng2-cookies/ng2-cookies';

@Injectable()
export class UserService {
  private loggedIn = false;

  constructor(
    private elmslnService: ElmslnService,
  ) { }

  login(username:string, password:string) {
    Cookie.set('basicAuthCredentials',  btoa(username + ":" + password));
    this.elmslnService.login();
  }

  logout() {
    this.elmslnService.logout();
  }
}