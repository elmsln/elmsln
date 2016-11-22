import { Component, OnInit } from '@angular/core';
import { AssignmentService } from '../../assignment.service';
import { Router } from '@angular/router';

@Component({
  selector: 'cle-assignment-list',
  templateUrl: './assignment-list.component.html',
  styleUrls: ['./assignment-list.component.css'],
  providers: [AssignmentService]
})
export class AssignmentListComponent implements OnInit {
  assignments: Array<any>;

  constructor(
    private assignmentService: AssignmentService,
    private router: Router
  ) { }

  ngOnInit() {
    this.assignmentService.getAssignments()
      .subscribe(data => { 
        this.assignments = data
      });
  }

  viewAssignment(assignmentId) {
    this.router.navigate(['/assignments/' + assignmentId]);
  }
}