import { Injectable } from '@angular/core';
import { Http, Headers, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { Critique } from './critique';
import { AppSettings } from './app-settings';

@Injectable()
export class CritiqueService {
  constructor(private http: Http) {
  }

  getCritiques() {
    return this.http.get('app/mocks/critiques.json')
      .map(data => data.json().list);
  }

  createCritique(critique: Critique) {
    console.log('createCritique');
    let body = {};
    let authorId = '';
    let basepath = AppSettings.BASE_PATH;

    let headers = new Headers();
    headers.append('Content-Type', 'application/json');
    headers.append('X-CSRF-Token', localStorage.getItem('x-csrf'));

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
      author: {
        id: 1
      }
    }

    this.http.post(basepath + 'node.json', body, { headers })
      .subscribe(res => {
        console.log(res);
      })
  }
}