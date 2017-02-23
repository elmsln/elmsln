import { Component, OnInit, ElementRef, OnDestroy, OnChanges, AfterViewChecked } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Location } from '@angular/common';
import { Assignment } from './assignment';
import { AssignmentService } from './assignment.service';
import { Observable } from 'rxjs';
import { Store } from '@ngrx/store';
import { loadAssignments, startCritque } from './assignment.actions';
import { ElmslnService } from '../elmsln.service';
import * as fromRoot from '../app.reducer';
declare const jQuery:any;

@Component({
  selector: 'cle-assignment',
  templateUrl: './assignment.component.html',
  styleUrls: ['./assignment.component.css'],
  providers: [AssignmentService]
})
export class AssignmentComponent implements OnInit, AfterViewChecked {
  assignmentId:number;
  date:number;
  userCanSubmit$:Observable<boolean>;
  userCanEdit$:Observable<boolean>;
  assignments$:Observable<Assignment[]>;
  submissions$:Observable<any[]>;

  constructor(
    private router: Router,
    private route: ActivatedRoute,
    private location: Location,
    private assignmentService: AssignmentService,
    private el:ElementRef,
    private store: Store<fromRoot.State>,
    private elmslnService:ElmslnService
  ) { 
  }

  ngOnInit() {
    this.route.params.forEach((params: Params) => {
      if (params['id']) {
        let id = +params['id'];
        this.assignmentId = Number(id);
      }
    });

    // check the permissions store to see if the user has edit
    this.userCanEdit$ = this.store.select(fromRoot.getUserPermissions)
      .map((state:any) => state.includes('edit any cle_assignment content'));
    
    // get my submissions
    this.submissions$ = this.store.select(fromRoot.getAllSubmissions)
      .map((state:any) => state.filter(s => s.assignment === this.assignmentId));

    if (this.assignmentId) {
      this.assignments$ = this.store.select(fromRoot.getAssignments)
        .map((state:any) => state.find(assignment => {
          return assignment.id === this.assignmentId;
        }))
        .map((state:any) => {
          return [state];
        })
    }
  }

  ngAfterViewChecked() {
  }

  onEditAssignment(assignment:Assignment) {
    const url = 'assignment-edit/' + assignment.id;
    this.router.navigate([{outlets: {dialog: url}}])
  }

  onCreateSubmission(assignment:Assignment) {
    const url = 'submissions/create/' + assignment.id;
    this.router.navigate([url]);
  }

  onStartCritique(assignment:Assignment) {
    this.store.dispatch(startCritque(assignment));
  }
}