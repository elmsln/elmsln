import { Component, OnInit, ElementRef, Input } from '@angular/core';
import { AssignmentService } from '../../assignment.service';
import { Assignment } from '../../assignment';
import { Router } from '@angular/router';
import { Observable } from 'rxjs';
import { Project } from '../../project';
declare const $:any;

@Component({
  selector: 'cle-assignment-list',
  templateUrl: './assignment-list.component.html',
  styleUrls: ['./assignment-list.component.css'],
  providers: [AssignmentService]
})
export class AssignmentListComponent implements OnInit {
  // takes in optional project id parameter which will filter assignments
  // by the project
  @Input() project:Project;
  assignments: Assignment[];

  constructor(
    private assignmentService: AssignmentService,
    private router: Router
  ) { }

ngOnInit() {
  this.getAssignments();
}

getAssignments() {
  this.assignmentService.getAssignments(this.project.id)
    .subscribe(data => {
      this.assignments = data;
      this.sortAssignmentsByDate();
    });
}

viewAssignment(assignmentId) {
  this.router.navigate(['/assignments/' + assignmentId]);
}

createAssignment() {
  this.router.navigate(['/assignments/new']);
}

onEditAssignment(assignment:Assignment) {
  const url = 'assignment-edit/' + assignment.id;
  this.router.navigate([{outlets: {dialog: url}}])
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