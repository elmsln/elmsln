import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { Critique } from './critique';
import { AppSettings } from './app.settings';
import { ElmslnService } from './elmsln.service';

@Injectable()
export class CritiqueService {
  constructor(
    private http: Http,
    private elmslnService: ElmslnService
  ) { }

  getSubmissionCritiques(submissionId) {
    return this.elmslnService.get(AppSettings.BASE_PATH + 'node.json?status=1,type=cle_critique&deep-load-refs=node,user&field_cle_crit_sub_ref=' + submissionId)
      .map(data => data.json().list);
  }

  createCritique(critique: Critique) {
    console.log('createCritique');
    let body = {};
    let authorId = '';

    body = {
      type: 'cle_critique',
      title: 'Critique',
      field_cle_crit_feedback: {
        value: critique.body,
        format: 'student_format'
      },
      field_cle_crit_sub_ref: {
        id: critique.submissionId
      },
      author: 4
    }

    return this.elmslnService.post(AppSettings.BASE_PATH + 'node.json', body);
  }

  /**
   * Instead of doing a hard delete, we are just going to set to
   * unpublish
   */
  deleteCritique(critique: any) {
    console.log('unpublish critique');
    let critiqueId = critique.nid;
    let body = {
      "status": "0"
    }

    return this.elmslnService.put(AppSettings.BASE_PATH + 'node/'+ critiqueId +'.json', body);
  }
}