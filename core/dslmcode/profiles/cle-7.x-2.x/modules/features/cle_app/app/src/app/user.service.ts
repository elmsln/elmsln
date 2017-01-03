import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { AppSettings } from './app-settings';
import { ElmslnService } from './elmsln.service';
import { Cookie } from 'ng2-cookies/ng2-cookies';
import { ActionTypes, loadPermissions } from './app.actions';
import { Store } from '@ngrx/store'; 

@Injectable()
export class UserService {
  private loggedIn = false;

  constructor(
    private elmslnService: ElmslnService,
    private store: Store<{}>
  ) { }

  login(username:string, password:string) {
    Cookie.set('basicAuthCredentials',  btoa(username + ":" + password));
    this.elmslnService.login();
    this.store.dispatch(loadPermissions());
  }

  logout() {
    this.elmslnService.logout();
  }

}