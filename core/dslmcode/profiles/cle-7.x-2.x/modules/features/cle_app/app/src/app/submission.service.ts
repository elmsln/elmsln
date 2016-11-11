import { Injectable } from '@angular/core';
import { ElmslnService } from './elmsln.service';
import { Observable } from 'rxjs/Observable';
import './rxjs-operators';;
import { Submission } from './submission';
import { AppSettings } from './app-settings';

@Injectable()
export class SubmissionService {
  // For testing
  // array = [{name:'mike', id:1}, {name:'bryan', id:2}];
  constructor(
    private elmslnService: ElmslnService
  ) { }

  getSubmissions() {
    // return Observable.from(this.array);
    return this.elmslnService.get(AppSettings.BASE_PATH + 'node.json?type=cle_submission')
      .map((res) => res.json().list);
  }

  getSubmission(submissionID: number) {
    return this.elmslnService.get(AppSettings.BASE_PATH + 'node/'+ submissionID +'.json?deep-load-refs=node,user')
      .map((res) => res.json());
  }
}
