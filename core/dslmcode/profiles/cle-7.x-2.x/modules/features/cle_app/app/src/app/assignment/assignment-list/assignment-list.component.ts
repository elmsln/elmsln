import { Component, OnInit } from '@angular/core';
import { AssignmentService } from '../../assignment.service';

@Component({
  selector: 'cle-assignment-list',
  templateUrl: './assignment-list.component.html',
  styleUrls: ['./assignment-list.component.css'],
  providers: [AssignmentService]
})
export class AssignmentListComponent implements OnInit {
  assignments: Array<any>;

  constructor(private assignmentService: AssignmentService) { }

  ngOnInit() {
    this.assignmentService.getAssignments()
        .subscribe(data => this.assignments = data);
  }
}
