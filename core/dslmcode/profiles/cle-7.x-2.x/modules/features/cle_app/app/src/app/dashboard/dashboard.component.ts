import { Component, OnInit } from '@angular/core';
import { AssignmentService } from '../assignment.service';

@Component({
  selector: 'cle-dashboard',
  templateUrl: './dashboard.component.html',
  styleUrls: ['./dashboard.component.css'],
  providers: [AssignmentService]
})
export class DashboardComponent implements OnInit {

  constructor(
    private assignmentService: AssignmentService
  ) { }

  ngOnInit() {
  }
}
