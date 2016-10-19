import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';

@Injectable()
export class AssignmentService {
  constructor(private http: Http) { 
  }

  getAssignments() {
    return this.http.get('app/mocks/assignments.json')
      .map(data => data.json().list);
  }

}