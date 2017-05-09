import { Assignment } from '../../assignment/assignment';
import { Component, OnInit, ViewChild, ElementRef } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { Submission } from '../submission';
import { updateSubmission } from '../submission.actions';
import { SubmissionFormComponent } from '../submission-form/submission-form.component';
import { SubmissionService } from '../submission.service';
import * as fromRoot from '../../app.reducer';
import { SubmissionStates } from '../submission.reducer';
declare const Materialize:any;
declare const jQuery:any;

@Component({
  selector: 'app-submission-edit',
  templateUrl: './submission-edit.component.html',
  styleUrls: ['./submission-edit.component.css']
})
export class SubmissionEditComponent implements OnInit {
  @ViewChild(SubmissionFormComponent) submissionFormComponent:SubmissionFormComponent;
  submission$: Observable<Submission>;
  submissionId:number;
  assignmentId:number;
  assignment$:Observable<Assignment>;
  submissionFormDirty:boolean;
  isSaving:boolean = false;
  isCritique:boolean = false;
  critiqueSubmission:Submission;
  submissionType$:Observable<string>;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private store: Store<{}>,
    private submissionService: SubmissionService,
    private el: ElementRef
  ) {
  }

  ngOnInit() {
    this.route.params.forEach((params:Params) => {
      if (typeof params['submissionId'] !== 'undefined') {
        let id = params['submissionId'];
        this.submissionId = Number(id);
      }
    });

    if (this.submissionId) {
      this.submission$ = this.store.select(fromRoot.getAllSubmissions)
        .map((state:any) => state.find((sub:Submission) => {
          this.assignmentId = sub.assignment;
          return sub.id === this.submissionId;
        }))
    }

    this.store.select(fromRoot.getSubmissionCurrentState)
      .subscribe((state:SubmissionStates) => {
        // saving is happening
        if (state === SubmissionStates.saving && !this.isSaving) {
          this.isSaving = true;
          Materialize.toast('Updating submission...', 30000, 'toast-submission-update');
        }
        else if (state === SubmissionStates.default && this.isSaving) {
          jQuery('.toast-submission-update').remove();
          Materialize.toast('Submission updated', 1500);
          this.router.navigate(['/assignments/' + this.assignmentId]);
        }
      })

    // get the current assignemnt
    this.assignment$ = this.submission$
      // make sure this submission has an assignment
      .filter((s:Submission) => {
        if (s) {
          if (s.assignment) {
            return true;
          }
        }
        return false
      })
      .mergeMap((s:Submission) => {
        return this.store.select(fromRoot.getAssignments)
            .map((state:any) => state.find((a:Assignment) => a.id === s.assignment))
      })

    this.assignment$
      .subscribe((assignment:Assignment) => {
        if (assignment) {
          if (assignment.critiqueMethod !== 'none') {
            this.isCritique = true;
          }
        }
      })
    
    this.submissionType$ = this.submissionService.getSubmissionType(this.submission$);
  }

  onSubmissionSave($event) {
    this.store.dispatch(updateSubmission($event));
    // this.submissionFormComponent.form.reset();
  }

  onSubmissionCancel() {
    if (this.submissionFormDirty) {
      if (confirm('You have unsaved changes. Are you sure you want to navigate away from this page?')) {
        this.router.navigate(['/submissions/' + this.submissionId ]);
        // this.submissionFormComponent.form.reset();
      }
    }
    else {
      this.router.navigate(['/submissions/' + this.submissionId ]);
      this.submissionFormComponent.form.reset();
    }
  }

  onFormChanges($event) {
    this.submissionFormDirty = $event;
  }
}
