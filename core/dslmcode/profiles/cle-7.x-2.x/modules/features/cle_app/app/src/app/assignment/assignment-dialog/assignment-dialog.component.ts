import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Router } from '@angular/router';
import { Assignment } from '../../assignment'
import { AssignmentService } from '../../assignment.service';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-assignment-dialog',
  templateUrl: './assignment-dialog.component.html',
  styleUrls: ['./assignment-dialog.component.css'],
  providers: [AssignmentService]
})
export class AssignmentDialogComponent implements OnInit {
  assignment:Assignment = new Assignment();

  constructor(
    private route:ActivatedRoute,
    private router:Router,
    private assignmentService:AssignmentService
  ) { }

  ngOnInit() {
    this.route.params
      .subscribe(params => {
        if (typeof params['assignmentId'] !== 'undefined') {
          this.assignmentService.getAssignment(params['assignmentId'])
            .subscribe(data => {
              this.assignment = data;
            });
        }
      })
  }

  onAssignmentSave($event) {
    this.router.navigate([{outlets: {dialog: null}}]);
  }
}
