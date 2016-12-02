import { Injectable } from '@angular/core';
import { Http, Response } from '@angular/http';
import { Observable } from 'rxjs';
import { ElmslnService } from './elmsln.service';
import { AppSettings } from './app-settings';
import { Assignment } from './assignment';

@Injectable()
export class AssignmentService {
  constructor(
    private elmsln: ElmslnService
  ) { }

  getAssignments(projectId?:number) {
    // 
    let query = projectId ? '?project=' + projectId : '';
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments' + query)
      .map(data => data.json())
  }

  getAssignment(assignmentId) {
    return this.elmsln.get(AppSettings.BASE_PATH + 'api/v1/cle/assignments/' + assignmentId)
      .map(data => data.json())
  }

  createAssignment(assignment:Assignment) {
    let newAssignment: any;

    // We have to construct a new assignment object to send to RESTws
    newAssignment = {
      type: 'cle_assignment',
      title: assignment.title,
      body: {
        value: assignment.body,
      }
    }
    
    return this.elmsln.post(AppSettings.BASE_PATH + 'node.json', newAssignment)
      .map(data => data.json())
  }
}