import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';

@Injectable()
export class CritiqueService {
  constructor(private http: Http) {
  }

  getCritiques() {
    return this.http.get('app/mocks/critiques.json')
      .map(data => data.json().list);
  }
}
