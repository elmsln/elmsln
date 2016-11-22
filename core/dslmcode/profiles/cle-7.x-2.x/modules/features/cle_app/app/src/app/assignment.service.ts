import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { ElmslnService } from './elmsln.service';
import { AppSettings } from './app-settings';

@Injectable()
export class AssignmentService {
  constructor(
    private elmsln: ElmslnService
  ) { }

  getAssignments() {
    return this.elmsln.get(AppSettings.BASE_PATH + 'node.json?type=cle_assignment')
      .map(data => data.json().list)
  }

  getAssignment(assignmentId) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'node/'+ assignmentId +'.json?deep-load-refs=user,node')
      .map(data => data.json())
  }
}