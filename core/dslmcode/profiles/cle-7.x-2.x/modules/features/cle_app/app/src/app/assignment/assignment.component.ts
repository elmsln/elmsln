import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Location } from '@angular/common';
import { Assignment } from '../assignment';
import { AssignmentService } from '../assignment.service';
import { Observable } from 'rxjs';

@Component({
  selector: 'cle-assignment',
  templateUrl: './assignment.component.html',
  styleUrls: ['./assignment.component.css'],
  providers: [AssignmentService]
})
export class AssignmentComponent implements OnInit {
  assignmentId: number;
  assignment: Assignment;
  date: number;

  constructor(
    private router: Router,
    private route: ActivatedRoute,
    private location: Location,
    private assignmentService: AssignmentService
  ) { }

  ngOnInit() {
    this.route.params.forEach((params: Params) => {
      let id = +params['id'];
      this.assignmentId = id;
    });

    if (this.assignmentId) {
      this.assignmentService.getAssignment(this.assignmentId)
        // turn it into a flatMap so we can analize each object
        // .flatMap((array, index) => array)
        // find out if the objects id matches the assignment_id
        // of the current page
        // .filter(data => data.nid !== 'undefined')
        // .filter(data => data.nid === String(this.assignmentId))
        // assign the result to the local assignment
      // @todo this should be handled better
        .subscribe(data => {
          this.assignment = data.data;
        });
    }
  }

  backButton() {
    this.location.back();
  }

  gotToProjects() {
    this.router.navigate(['/projects']);
  }
}