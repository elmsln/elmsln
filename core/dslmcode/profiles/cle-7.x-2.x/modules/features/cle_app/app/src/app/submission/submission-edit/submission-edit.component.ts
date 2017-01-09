import { Component, OnInit, ViewChild } from '@angular/core';
import { ActivatedRoute, Params, Router } from '@angular/router';
import { Store } from '@ngrx/store';
import { Observable } from 'rxjs';
import { Submission } from '../submission';
import { updateSubmission } from '../submission.actions';
import { SubmissionFormComponent } from '../submission-form/submission-form.component';

@Component({
  selector: 'app-submission-edit',
  templateUrl: './submission-edit.component.html',
  styleUrls: ['./submission-edit.component.css']
})
export class SubmissionEditComponent implements OnInit {
  @ViewChild(SubmissionFormComponent) submissionFormComponent:SubmissionFormComponent;
  submission$: Observable<Submission>;
  submissionId:number;
  submissionFormDirty:boolean;

  constructor(
    private route: ActivatedRoute,
    private router: Router,
    private store: Store<{}>
  ) {
  }

  ngOnInit() {
    this.route.params.forEach((params:Params) => {
      if (typeof params['submissionId'] !== 'undefined') {
        let id = params['submissionId'];
        this.submissionId = Number(id);
        console.log(this.submissionId);
      }
    });

    if (this.submissionId) {
      this.submission$ = this.store.select('submissions')
        .map((state:any) => state.submissions.find((sub:Submission) => sub.id === this.submissionId))
    }
  }

  onSubmissionSave($event) {
    this.store.dispatch(updateSubmission($event));
    this.submissionFormComponent.form.reset();
  }

  onSubmissionCancel() {
    if (this.submissionFormDirty) {
      if (confirm('You have unsaved changes. Are you sure you want to navigate away from this page?')) {
        this.router.navigate(['/submissions/' + this.submissionId ]);
        this.submissionFormComponent.form.reset();
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
