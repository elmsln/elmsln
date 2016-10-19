import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';

@Injectable()
export class UserService {
  constructor(private http: Http) {
  }

  getUsers(): Observable<any> {
    return this.http.get('app/mocks/users.json')
      .map(data => data.json().list);
  }
}
