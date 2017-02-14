import { Component, OnInit, Input, OnChanges } from '@angular/core';
import { Submission } from '../submission';
import { SubmissionService } from '../submission.service';

@Component({
  selector: 'app-submission-critique',
  templateUrl: './submission-critique.component.html',
  styleUrls: ['./submission-critique.component.scss']
})
export class SubmissionCritiqueComponent implements OnInit, OnChanges {
  @Input() submission: Submission;
  @Input() editMode: boolean;
  critique: Submission;
  assignment;

  constructor(
    private submissionService: SubmissionService
  ) {
  }

  ngOnInit() {
  }

  ngOnChanges() {
    // get the submission critique
    this.submissionService.getSubmission(this.submission.relatedSubmission)
      .subscribe((submission:Submission) => this.critique = submission);
    
    this.submissionService.getSubmissionAssignment(this.submission)
      .subscribe(assignment => this.assignment = assignment)
  }
}
