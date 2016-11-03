import { Injectable } from '@angular/core';
import { Http, Response, Headers } from '@angular/http';
import { Observable } from 'rxjs/Observable';
import './rxjs-operators';;
import { Submission } from './submission';

@Injectable()
export class SubmissionService {
  // For testing
  // array = [{name:'mike', id:1}, {name:'bryan', id:2}];
  constructor(
    private http: Http
  ) { }

  getSubmissions() {
    // return Observable.from(this.array);
    return this.http.get('http://studio.elmsln.local/math033/node.json?type=cle_submission')
      .map((res: Response) => res.json().list);
  }

  getSubmission(submissionID: number) {
    return this.http.get('http://studio.elmsln.local/math033/node/'+ submissionID +'.json?deep-load-refs=node,user')
      .map((res: Response) => res.json());
  }
}
