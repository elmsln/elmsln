import { Component, OnInit, ElementRef, Input, OnChanges, ChangeDetectionStrategy } from '@angular/core';
import { AssignmentService } from '../../assignment.service';
import { Assignment } from '../../assignment';
import { Router } from '@angular/router';
import { Observable, Subject } from 'rxjs';
import { Project } from '../../project';
import { Store } from '@ngrx/store';
import { createCritiqueAssignment } from '../../app.actions';
declare const $:any;

@Component({
  selector: 'cle-assignment-list',
  templateUrl: './assignment-list.component.html',
  styleUrls: ['./assignment-list.component.css'],
  providers: [AssignmentService],
  changeDetection: ChangeDetectionStrategy.OnPush
})
export class AssignmentListComponent implements OnChanges, OnInit {
  // takes in optional project id parameter which will filter assignments
  // by the project
  @Input() assignments:Assignment[];
  userCanEdit$:Observable<boolean> = this.assignmentService.userCanEdit;

  constructor(
    private assignmentService: AssignmentService,
    private router: Router,
    private store: Store<{}>
  ) { 
  }

  ngOnInit() {

  }

viewAssignment(assignmentId) {
  if (assignmentId) {
    this.router.navigate(['/assignments/' + assignmentId]);
  }
}

createAssignment() {
  this.router.navigate(['/assignments/new']);
}

onEditAssignment(assignment:Assignment) {
  const url = 'assignment-edit/' + assignment.id;
  this.router.navigate([{outlets: {dialog: url}}])
}

onDeleteAssignment(assignment:Assignment) {
  const url = 'assignment-delete/' + assignment.id;
  this.router.navigate([{outlets: {dialog: url}}])
}

addCritique(assignment:Assignment) {
  this.store.dispatch(createCritiqueAssignment(assignment));
}

// when we get new assignments, make sure we sort them
ngOnChanges() {
  this.sortAssignmentsByDate();
}

sortAssignmentsByDate() {
  if (this.assignments) {
    this.assignments.sort((a:Assignment,b:Assignment) => {
        let aDate = null;
        let bDate = null;

        if (!a.startDate) {
          aDate = a.endDate;
        }
        if (!b.startDate) {
          bDate = b.endDate;
        }

        if (aDate && bDate) {
          if (aDate < bDate) {
            return -1;
          }
          else if (aDate > bDate) {
            return 1;
          }
          else {
            return 0;
          }
        }
        else if (aDate && !bDate) {
          return -1;
        }
        else if (!aDate && bDate) {
          return 1;
        }
      });
    }
  }
}